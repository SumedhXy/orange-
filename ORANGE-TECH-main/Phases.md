# CITRUS-TERRA AI — Implementation Roadmap & Phases

---

## Overview
To ensure systematic development, execution, and deployment, the project is structured into **5 sequential phases**. Each phase contains clear deliverables, testing criteria, and exit gates.

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   PHASE 1   │ ──► │   PHASE 2   │ ──► │   PHASE 3   │ ──► │   PHASE 4   │ ──► │   PHASE 5   │
│ Cyber-Phys. │     │ Interactive │     │ Edge AI CV  │     │ Field Valid.│     │ FPO Cluster │
│  Simulation │     │ Web PWA App │     │  Pipeline   │     │ & Vernacular│     │ Deployment  │
└─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘
```

---

## Phase 1: Cyber-Physical Circuit Simulation & Firmware [COMPLETED ✅]
- **Goal**: Build and verify a complete, zero-error hardware prototype in the Wokwi simulator.
- **Key Deliverables**:
  - `wokwi.json`: Clean wiring schema for ESP32, 4-pin OLED, HC-SR04, KY-040 encoder, relay, LEDs, buzzer, and test button.
  - `wokwi_sketch.ino`: Production-ready C++ firmware with 100% non-blocking asynchronous `loop()`.
  - `wokwi.txt`: Setup documentation and 1-minute execution steps.
- **Exit Gate**: Simulation starts cleanly on `wokwi.com`, buzzer chirps on pest trigger, 1.5s solenoid valve cut-off works reliably, and serial monitor prints Marathi WhatsApp alerts.

---

## Phase 2: Tractor-Cabin Web Dashboard & Visual Telemetry [COMPLETED ✅]
- **Goal**: Create an offline-first, high-contrast Web Dashboard (PWA) for the tractor driver cabin.
- **Key Deliverables**:
  - `index.html`: Modern, responsive single-page web cockpit.
  - Interactive 2D Orchard Map: 4-Row $\times$ 12-Tree grid tracking the moving tractor in real time.
  - Dual AI Camera Viewports: Simulated live streams for trunk collar gummosis and under-leaf Psylla.
  - Real-Time Solenoid Actuator Monitor: Visual feedback of chemical flow state (Closed vs 1.5s burst).
  - Marathi / English WhatsApp Advisory Simulator: Live generation of ICAR-CCRI recommendations.
- **Exit Gate**: Opens instantly in any browser, zero layout errors, smooth 60fps animations, fully usable offline.

---

## Phase 3: Edge AI Vision Pipeline & Model Optimization [IN PROGRESS 🔄]
- **Goal**: Package and optimize the dual deep learning models for low-power edge compute.
- **Key Deliverables**:
  - `YOLOv11n-Gummosis`: Quantized FP16 TensorRT engine running on NVIDIA Jetson Orin Nano (< 15ms latency).
  - `YOLOv11s-OBB-Psylla`: Oriented bounding box model detecting micro-nymphs on leaf undersides (< 22ms latency).
  - Camera Synchronization Script: Python pipeline capturing synchronized frames from dual USB3 global-shutter cameras.
- **Exit Gate**: Sustained 30+ FPS edge inference on Jetson Orin under simulated 45°C ambient conditions.

---

## Phase 4: Local Telemetry Bridge & WhatsApp Integration [PLANNED ⏳]
- **Goal**: Connect physical ESP32 hardware via local Wi-Fi / WebSockets to the Web Dashboard and WhatsApp Business API.
- **Key Deliverables**:
  - WebSocket Telemetry Server: Streaming live speed, odometry, and spray events to `index.html` at 10Hz.
  - Twilio / Meta Cloud WhatsApp Webhook: Automated instant dispatch of row advisories to farmer's mobile number.
  - SQLite Spatial Logger: Local persistence of tree health scores and chemical spray volumes.
- **Exit Gate**: Real tractor trial successfully logs 100 consecutive trees with zero lost packets.

---

## Phase 5: Field Pilot & FPO Commercial Service Rollout [PLANNED ⏳]
- **Goal**: Real-world validation across 50 acres in Katol and Warud orange orchards.
- **Key Deliverables**:
  - Field Mounting Rig: Vibration-damped steel mast mounted to tractor roll cage (ROPS).
  - ICAR-CCRI Nagpur Joint Trial Report: Third-party verification of pesticide reduction (> 65%).
  - FPO Service Playbook: Standard operating procedures for custom hiring centers at ₹250/acre/cycle.
- **Exit Gate**: Demonstrated ₹1,76,000 annual net savings per 20-acre orchard.
