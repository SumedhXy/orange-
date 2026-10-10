# CITRUS-TERRA AI — System Architecture & Technical Stack

---

## 1. High-Level Cyber-Physical Architecture

The system consists of three interconnected layers:

```
┌────────────────────────────────────────────────────────────────────────┐
│                   1. SENSING & INTERVENTION (TRACTOR)                  │
│  - Upper Camera (+30° Under-Leaf)     - Lower Camera (-15° Collar)     │
│  - Wheel Encoder (Odometry)           - Lateral ToF / Ultrasonic       │
│  - 12V Solenoid Spray Valve           - Warning Buzzer & Status LEDs   │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │ Edge Video Streams & Sensor Pulses
┌───────────────────────────────────▼────────────────────────────────────┐
│                   2. EDGE COMPUTE & ACTUATION (CABIN)                  │
│  - NVIDIA Jetson Orin Nano (TensorRT YOLOv11 Edge Inference)           │
│  - ESP32 Real-Time Microcontroller (Odometry & Solenoid PWM Timing)    │
│  - Offline SQLite Spatial DB (Deterministic Tree Health Records)       │
│  - Local Web Server / Wi-Fi Hotspot (192.168.4.1:8080)                 │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │ WebSocket / HTTP Telemetry
┌───────────────────────────────────▼────────────────────────────────────┐
│                   3. USER INTERFACE & TELEMETRY LAYER                  │
│  - Driver Cabin Web Dashboard PWA (index.html via local Wi-Fi)         │
│  - Automated Vernacular Advisory Generator (Marathi WhatsApp / SMS)    │
│  - Wokwi Hardware Simulation Suite (diagram.json + wokwi_sketch.ino)   │
└────────────────────────────────────────────────────────────────────────┘
```

---

## 2. Technical Stack Breakdown

### 2.1 Web Application & Dashboard (Frontend)
- **Technology**: Single-page Progressive Web App (PWA) using Vanilla HTML5, CSS3, and JavaScript (ES6+).
- **Design Philosophy**: Zero framework bloat (no React/Angular overhead on low-power cabin tablets).
- **Styling**: Modern dark theme with CSS custom properties, Glassmorphism (`backdrop-filter: blur`), responsive CSS Grid/Flexbox.
- **Typography**: Google Fonts (*Plus Jakarta Sans* for UI, *JetBrains Mono* for telemetry & Tree IDs).
- **Connectivity**: Local WebSocket / HTTP REST polling to the cabin edge server (`http://192.168.4.1`).

### 2.2 Embedded Firmware & Hardware Controller
- **Microcontroller**: ESP32 DevKit V4 (Dual-Core Xtensa LX6 @ 240MHz).
- **Framework**: Arduino C++ (FreeRTOS core).
- **Actuator Timing**: Sub-millisecond non-blocking `millis()` state machine.
- **Display Output**: 0.96" I2C OLED (SSD1306, 128x64, address `0x3C`).
- **Telemetry Serial**: UART @ 115200 baud stream for driver cabin logs.

### 2.3 Edge AI Computer Vision
- **Host Unit**: NVIDIA Jetson Orin Nano (40 TOPS, 15W mode).
- **Models**:
  1. `YOLOv11n-Gummosis`: Trunk bark collar lesion detector (Inference latency: 14ms).
  2. `YOLOv11s-OBB-Psylla`: Under-leaf Psylla nymph & honeydew detector (Inference latency: 22ms).
- **Inference Runtime**: TensorRT FP16 quantization with DeepStream pipeline.

### 2.4 Spatial GIS & Odometry (No GPS Drift)
- **Primary Positioning**: Hall-effect wheel encoder counting rotation pulses ($D = N \times \pi \times \text{Wheel Diameter}$).
- **Tree Alignment**: Lateral ToF distance sensor detecting trunk presence at $< 140\text{cm}$.
- **Tree Hash**: `BLK_[Block]_R[Row]_T[Tree]` (e.g., `BLK_B_R04_T012`).

---

## 3. Repository File & Folder Structure

```
task imp/
├── PRD.md                     # Project Requirements Document
├── Architecture.md            # System Architecture & Technical Stack (This File)
├── Rules.md                   # Strict Development Rules & AI Boundaries
├── Phases.md                  # Step-by-Step Implementation Roadmap
├── Design.md                  # UI/UX Style Guide, Colors & Typography
├── Memory.md                  # Project Context & Progress State Tracker
│
├── index.html                 # Interactive Tractor-Cabin Web Dashboard (PWA)
├── wokwi.json                 # Wokwi Circuit Diagram Specification
├── wokwi_sketch.ino           # ESP32 C++ Production Firmware (Non-blocking)
├── wokwi.txt                  # Wokwi 1-Minute Setup & Circuit Guide
│
├── FINAL_SOLUTION_PROPOSAL.pdf# Formal PDF Proposal for Evaluation
├── solution.txt               # Full In-Depth Technical Specification
├── ps.txt                     # Problem Statement Blueprint
└── he.txt                     # Original Problem Notes & User Brief
```

---

## 4. Hardware Pinout Mapping (ESP32 DevKit V4)

| Peripheral Component | Component Pin | ESP32 Pin | Logic Level | Function |
| :--- | :--- | :--- | :--- | :--- |
| **I2C OLED Display** | `SDA` | `GPIO 21` | 3.3V I2C | Serial Data |
| **I2C OLED Display** | `SCL` | `GPIO 22` | 3.3V I2C | Serial Clock |
| **HC-SR04 ToF Sensor** | `TRIG` | `GPIO 5` | 3.3V / 5V | Ultrasonic Trigger Pulse |
| **HC-SR04 ToF Sensor** | `ECHO` | `GPIO 18` | 3.3V Input | Ultrasonic Echo Return |
| **KY-040 Wheel Encoder**| `CLK` | `GPIO 19` | 3.3V Pullup| Odometry Clock Tick |
| **KY-040 Wheel Encoder**| `DT` | `GPIO 23` | 3.3V Pullup| Direction Indicator |
| **Relay Module (Solenoid)**| `IN` | `GPIO 25` | 3.3V Output| Solenoid Valve Driver |
| **Disease Status LED** | Anode (`A`)| `GPIO 26` | 3.3V Output| Red Warning LED |
| **Healthy Status LED** | Anode (`A`)| `GPIO 27` | 3.3V Output| Green Status LED |
| **Cabin Warning Buzzer**| Pin `2` (+) | `GPIO 14` | 3.3V Output| Driver Audio Alert |
| **Pest Sim Pushbutton** | Pin `1.l` | `GPIO 13` | 3.3V Pullup| Instant Test Trigger |
| **Common Grounds** | `GND` | `GND.1 / GND.2`| 0V | Unified Ground Plane |
