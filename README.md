# Radar Ultrasónico ESP32 + HC-SR04

Proyecto de detección de proximidad con visualización en tiempo real mediante radar y dashboard web local.

> ⚠️ **Estado del proyecto:** simulado y verificado en [Tinkered](https://app.tinkered.ai/). Aún **no se ha construido en hardware real**. El firmware, el esquema y el cableado están completos y listos para montarse; esta es la fase previa a la construcción física.

## ¿Qué hace?

Este proyecto convierte un ESP32 y un sensor ultrasonico HC-SR04 en un radar de proximidad. El sistema escanea un rango de 0° a 180°, mide la distancia a los objetos en cada paso y muestra los resultados en un dashboard web local en tu PC. No requiere internet ni servidores externos; todo ocurre en la red local del ESP32.

## Hardware

*   **ESP32 DevKit V1** (placa de desarrollo)
*   **Sensor Ultrasonico HC-SR04** (rango 2cm - 450cm)
*   **Resistencia 2kΩ** (pull-up para la señal ECHO)
*   **Resistencia 3.9kΩ** (pull-down para la señal ECHO)
*   **Protoboard** (full size)
*   **Cables Jumper** (rojo, negro, amarillo)

## Conexiones (Wiring)

Sigue estos pasos para conectar los componentes en la protoboard. Los pines del ESP32 están basados en el archivo `config.h`.

### 1. Alimentación (Power)
*   **ESP32 VIN (Pin 20b)** → **Protoboard Rail Positivo (5V)**
*   **ESP32 GND_L (Pin 15b)** → **Protoboard Rail Negativo (GND)**
*   **Sensor HC-SR04 VCC** → **Protoboard Rail Positivo (5V)**
*   **Sensor HC-SR04 GND** → **Protoboard Rail Negativo (GND)**

### 2. Señal de Trigger (Envío de pulso)
*   **Sensor HC-SR04 TRIG** → **ESP32 IO32 (Pin 8a)**

### 3. Señal de ECHO (Recepción de eco)
*   **Sensor HC-SR04 ECHO** → **Resistencia 2kΩ (Pin 1)** → **ESP32 IO33 (Pin 9a)**
*   **Resistencia 3.9kΩ** → **GND (Protoboard Rail Negativo)**

> **Nota:** La resistencia de 2kΩ actúa como pull-up y la de 3.9kΩ como pull-down para asegurar lecturas estables en la línea ECHO.

## Cómo usar

1.  **Instalar la herramienta:**
    Asegúrate de tener **PlatformIO** instalado en tu editor de código (VS Code recomendado).

2.  **Configurar WiFi:**
    Edita el archivo `src/config.h` y cambia las credenciales:
    ```cpp
    #define WIFI_SSID "TuSSID"
    #define WIFI_PASSWORD "TuPassword"
    ```

3.  **Subir el código:**
    Conecta el ESP32 a tu PC mediante USB y compila/instala el proyecto en PlatformIO.

4.  **Abrir el Dashboard:**
    Una vez que el ESP32 esté conectado a WiFi, abre tu navegador web y ve a la dirección IP que aparece en el monitor serie (o usa la IP del ESP32 en tu red local).
    *   URL local: `http://<IP_DEL_ESP32>/`

El dashboard se actualizará automáticamente cada 100ms mostrando la distancia y el ángulo actual del objeto detectado.

## Archivos

*   `src/main.cpp`: Lógica principal del radar y servidor web.
*   `src/config.h`: Configuración de pines y credenciales WiFi.
*   `platformio.ini`: Configuración del entorno de compilación.
*   `wiring/wiring.json`: Esquema de conexiones detallado.
*   `docs/steps.json`: Guía paso a paso de montaje.
*   `specs/bom.json`: Lista de materiales.
*   `schematic/main.sch`: Esquema del circuito.

## Roadmap

- [x] Diseño del circuito y simulación en Tinkercad
- [x] Firmware ESP32 (servidor web + lectura del sensor)
- [x] Dashboard web con visualización tipo radar
- [ ] Montaje físico en protoboard
- [ ] Pruebas con hardware real
- [ ] Carcasa / montaje mecánico (servo para barrido de 0°-180°, opcional)

## Autor

Proyecto de **Carlos** ([@yassi](https://github.com/)) — parte de su aprendizaje autodidacta en desarrollo de hardware con ESP32.
