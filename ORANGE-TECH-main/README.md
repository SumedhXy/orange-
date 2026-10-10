# CITRUS-TERRA AI 🍊🚜
### Ground-Level Multi-Angle Vision & Precision Spot-Spraying System for Nagpur Mandarin Orchards in Vidarbha
*(100% Non-Drone Cyber-Physical Architecture)*

[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32%20DevKit%20V4-blue.svg)](https://wokwi.com)
[![Edge AI: Jetson Orin](https://img.shields.io/badge/Edge%20AI-NVIDIA%20Jetson%20Orin-76B900.svg)](https://nvidia.com)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Wokwi Simulator](https://img.shields.io/badge/Simulation-Wokwi%20IoT-orange.svg)](https://wokwi.com)
[![Agronomy: ICAR-CCRI](https://img.shields.io/badge/Prescription-ICAR--CCRI%20Nagpur-emerald.svg)](https://ccri.icar.gov.in)

---

## 🌟 Executive Overview
**CITRUS-TERRA AI** is a cyber-physical orchard monitoring and precision intervention system designed specifically for **Nagpur Mandarin (*Citrus reticulata*)** orchards across Vidarbha (Katol, Warud, Morshi, Amravati, and Nagpur).

Unlike aerial drones—which are physically blind to under-leaf sucking pests and trunk collar rot, suffer battery swelling in 45°C heat, and cost ₹8–12 Lakhs—CITRUS-TERRA AI operates directly from the ground by mounting a multi-angle vision and precision spot-spraying rig onto existing orchard tractors and power-tillers during routine passes.

---

## 🚀 Key Highlights & Capabilities
- **Direct Line-of-Sight Under-Leaf Imaging**: Upper camera (+30°) with diffuse LED lighting detects Asian Citrus Psylla (*Diaphorina citri*) nymphs and Leaf Miners.
- **Uncompromised Trunk Collar Inspection**: Lower camera (-15°) inspects 0–40 cm bark base for *Phytophthora* Gummosis oozing lesions.
- **Deterministic Spatial GIS (Zero GPS Drift)**: Combines wheel encoder odometry and optical ToF trunk sensors to uniquely address trees (`BLK_B_R04_T012`) in standard 5m × 5m grids without commercial GPS drift.
- **Real-Time Targeted Spot-Spraying**: High-speed 12V solenoid valve delivers a 1.5-second targeted burst (45 ml) directly to infected trees, **cutting chemical usage by > 65%** and saving **₹1,76,000 per 20 acres annually**.
- **Driver Cabin Web Cockpit (PWA)**: Offline-first interactive dashboard (`index.html`) running over the tractor's local Wi-Fi hotspot (`http://192.168.4.1`).
- **Automated Vernacular WhatsApp Advisories**: Dispatches ICAR-CCRI approved Marathi prescriptions with Google Maps navigation links.

---

## 📂 Project Structure & Governance
```
├── index.html                 # Interactive Tractor-Cabin Web Dashboard & Demo Suite
├── wokwi_sketch.ino           # ESP32 C++ Production Firmware (Non-blocking)
├── wokwi.json                 # Wokwi Circuit Diagram Specification
├── wokwi.txt                  # 1-Minute Wokwi Setup & Circuit Guide
│
├── FINAL_SOLUTION_PROPOSAL.pdf# Formal PDF Proposal for Evaluation & Defense
├── solution.txt               # Full In-Depth Technical Specification
├── ps.txt                     # Problem Statement Blueprint
├── he.txt                     # Baseline Notes & Original User Brief
│
├── PRD.md                     # Project Requirements Document
├── Architecture.md            # System Architecture & Technical Stack
├── Rules.md                   # Strict Development Rules & AI Boundaries
├── Phases.md                  # Step-by-Step Implementation Roadmap
├── Design.md                  # UI/UX Style Guide, Colors & Typography
└── Memory.md                  # Living Context & Progress State Tracker
```

---

## 💻 Quick Start & Demonstration

### 1. Interactive Web Application
Simply open `index.html` in any modern web browser (Chrome, Edge, Firefox, Safari) to launch the full interactive demonstration cockpit:
- Real-time 2D Orchard GIS matrix (48 trees).
- Dual AI camera feeds with live YOLO bounding box scanner.
- 12V Solenoid valve mist particle animation.
- Web Audio API synthesized cabin alerts.
- Interactive Ground vs Drone battle matrix & Financial ROI calculator.

### 2. Wokwi IoT Circuit Simulation
1. Visit [Wokwi ESP32 Simulator](https://wokwi.com/projects/new/esp32).
2. Paste the contents of `wokwi.json` into the `diagram.json` tab.
3. Paste `wokwi_sketch.ino` into `sketch.ino`.
4. In `libraries.txt`, add:
   ```
   Adafruit SSD1306
   Adafruit GFX Library
   ```
5. Click **Start Simulation (Play)**!

---

## 👨‍💻 Author & Engineering Credits
- **Project Lead**: Kshitij Adakane
- **Institution**: St. Vincent Pallotti College of Engineering & Technology, Nagpur
- **Regional Target**: Katol, Warud, Morshi, Amravati, Nagpur Citrus Belt (Vidarbha, Maharashtra)
