#pragma once

// Pin map (MUST match wiring)
#define PIN_HCSR04_TRIG 32
#define PIN_HCSR04_ECHO 33

// WiFi credentials (edit for real hardware)
#define WIFI_SSID "TuSSID"
#define WIFI_PASSWORD "TuPassword"

// HC-SR04 timing
static const unsigned long MEASURE_INTERVAL_MS = 80;      // >= 60ms required
static const unsigned long ECHO_TIMEOUT_US = 30000;       // ~5m max

// Radar visualization config
static const float MAX_DISTANCE_CM = 250.0f;              // shown range on UI
static const int ANGLE_MIN_DEG = 0;
static const int ANGLE_MAX_DEG = 180;
static const int ANGLE_STEP_DEG = 3;
