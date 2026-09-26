#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "config.h"

WebServer server(80);

volatile float g_distanceCm = -1.0f;
volatile bool g_distanceValid = false;
volatile int g_angleDeg = 0;
volatile unsigned long g_lastMeasureMs = 0;

unsigned long lastMeasureTaskMs = 0;
unsigned long lastWifiRetryMs = 0;

int angleDir = 1;

const char INDEX_HTML[] PROGMEM = R"HTML(
<!doctype html>
<html lang="es">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <title>Radar HC-SR04 ESP32</title>
  <style>
    body { background:#061016; color:#8fffa2; font-family:Arial,Helvetica,sans-serif; margin:0; text-align:center; }
    h1 { margin:14px 0 4px; font-size:1.2rem; }
    #info { margin:6px 0 10px; font-size:1rem; }
    canvas { background:#00150a; border:1px solid #0f4; border-radius:8px; max-width:95vw; height:auto; }
    .muted { color:#6fbf7a; font-size:0.9rem; margin-top:6px; }
  </style>
</head>
<body>
  <h1>Radar Ultrasónico HC-SR04 (ESP32)</h1>
  <div id="info">Distancia: --.- cm | Ángulo: ---°</div>
  <canvas id="radar" width="700" height="420"></canvas>
  <div class="muted">API JSON: <code>/api/data</code></div>

<script>
const canvas = document.getElementById('radar');
const ctx = canvas.getContext('2d');
const info = document.getElementById('info');

let latest = {distance_cm:-1, angle_deg:0, valid:false};

function drawRadar(data){
  const w = canvas.width, h = canvas.height;
  const cx = w/2, cy = h-20;
  const maxR = Math.min(w*0.45, h*0.9);
  const maxCm = 250.0;

  ctx.clearRect(0,0,w,h);

  // Grid arcs
  ctx.strokeStyle = '#0a5';
  ctx.lineWidth = 1;
  for(let i=1;i<=5;i++){
    const r = maxR*(i/5);
    ctx.beginPath();
    ctx.arc(cx,cy,r,Math.PI,2*Math.PI);
    ctx.stroke();
  }

  // Angle lines
  for(let a=0;a<=180;a+=30){
    const rad = (Math.PI * a)/180;
    const x = cx + maxR*Math.cos(Math.PI-rad);
    const y = cy - maxR*Math.sin(Math.PI-rad);
    ctx.beginPath();
    ctx.moveTo(cx,cy);
    ctx.lineTo(x,y);
    ctx.stroke();
  }

  // Sweep line
  const ang = data.angle_deg || 0;
  const srad = (Math.PI*ang)/180;
  const sx = cx + maxR*Math.cos(Math.PI-srad);
  const sy = cy - maxR*Math.sin(Math.PI-srad);

  const grad = ctx.createLinearGradient(cx,cy,sx,sy);
  grad.addColorStop(0,'rgba(0,255,80,0.2)');
  grad.addColorStop(1,'rgba(0,255,80,0.95)');
  ctx.strokeStyle = grad;
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.moveTo(cx,cy);
  ctx.lineTo(sx,sy);
  ctx.stroke();

  // Target blip
  if(data.valid && data.distance_cm >= 0){
    const d = Math.min(data.distance_cm, maxCm);
    const r = (d/maxCm)*maxR;
    const tx = cx + r*Math.cos(Math.PI-srad);
    const ty = cy - r*Math.sin(Math.PI-srad);

    ctx.fillStyle = '#8ff';
    ctx.beginPath();
    ctx.arc(tx,ty,6,0,2*Math.PI);
    ctx.fill();

    ctx.strokeStyle = '#8ff';
    ctx.beginPath();
    ctx.arc(tx,ty,14,0,2*Math.PI);
    ctx.stroke();
  }
}

async function updateData(){
  try{
    const res = await fetch('/api/data', {cache:'no-store'});
    if(!res.ok) return;
    latest = await res.json();
    const distTxt = latest.valid ? latest.distance_cm.toFixed(1) + ' cm' : 'fuera de rango';
    info.textContent = `Distancia: ${distTxt} | Ángulo: ${latest.angle_deg}°`;
  }catch(e){
    // ignore transient errors
  }
}

function renderLoop(){
  drawRadar(latest);
  requestAnimationFrame(renderLoop);
}

setInterval(updateData, 100);
updateData();
renderLoop();
</script>
</body>
</html>
)HTML";

float readHCSR04cm() {
  digitalWrite(PIN_HCSR04_TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(PIN_HCSR04_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_HCSR04_TRIG, LOW);

  unsigned long duration = pulseIn(PIN_HCSR04_ECHO, HIGH, ECHO_TIMEOUT_US);
  if (duration == 0) {
    return -1.0f; // timeout / out of range
  }

  // cm = (time_us * speed_of_sound_cm_per_us) / 2
  return (duration * 0.0343f) / 2.0f;
}

void updateAngle() {
  g_angleDeg += angleDir * ANGLE_STEP_DEG;
  if (g_angleDeg >= ANGLE_MAX_DEG) {
    g_angleDeg = ANGLE_MAX_DEG;
    angleDir = -1;
  } else if (g_angleDeg <= ANGLE_MIN_DEG) {
    g_angleDeg = ANGLE_MIN_DEG;
    angleDir = 1;
  }
}

void measureTask() {
  unsigned long now = millis();
  if (now - lastMeasureTaskMs < MEASURE_INTERVAL_MS) return;
  lastMeasureTaskMs = now;

  float d = readHCSR04cm();
  bool valid = (d >= 0.0f);

  g_distanceCm = d;
  g_distanceValid = valid;
  g_lastMeasureMs = now;

  updateAngle();

  if (valid) {
    Serial.printf("[HC-SR04] Distancia: %.2f cm | Angulo: %d° | t=%lu ms\n", d, g_angleDeg, now);
  } else {
    Serial.printf("[HC-SR04] Fuera de rango | Angulo: %d° | t=%lu ms\n", g_angleDeg, now);
  }
}

void handleRoot() {
  server.send_P(200, "text/html; charset=utf-8", INDEX_HTML);
}

void handleApiData() {
  float d = g_distanceCm;
  bool valid = g_distanceValid;
  int angle = g_angleDeg;
  unsigned long t = g_lastMeasureMs;

  String json = "{";
  json += "\"distance_cm\":";
  json += String(d, 2);
  json += ",\"angle_deg\":";
  json += String(angle);
  json += ",\"valid\":";
  json += (valid ? "true" : "false");
  json += ",\"timestamp_ms\":";
  json += String(t);
  json += "}";

  server.sendHeader("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
  server.send(200, "application/json", json);
}

void handleNotFound() {
  server.send(404, "application/json", "{\"error\":\"not_found\"}");
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.printf("Conectando a WiFi SSID: %s\n", WIFI_SSID);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - start) < 20000) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi conectado. IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("No se pudo conectar a WiFi (reintento en loop).");
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);

  pinMode(PIN_HCSR04_TRIG, OUTPUT);
  pinMode(PIN_HCSR04_ECHO, INPUT);
  digitalWrite(PIN_HCSR04_TRIG, LOW);

  connectWiFi();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/data", HTTP_GET, handleApiData);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("Servidor HTTP iniciado en puerto 80");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    unsigned long now = millis();
    if (now - lastWifiRetryMs > 10000) {
      lastWifiRetryMs = now;
      Serial.println("Reintentando WiFi...");
      WiFi.disconnect();
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
  }

  measureTask();
  server.handleClient();
}
