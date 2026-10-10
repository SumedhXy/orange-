# CITRUS-TERRA AI — Memory & Project State Tracker

---

## 1. Project Identity & Core Objective
- **Project Name**: CITRUS-TERRA AI
- **Focus**: Ground-Level Multi-Angle Vision & Smart IoT Precision Monitoring & Targeted Intervention for Nagpur Orange Orchards in Vidarbha, Maharashtra.
- **Strict Architecture Mandate**: **100% NON-DRONE**. All monitoring is carried out by tractor-mounted multi-angle cameras and autonomous solar IoT smart traps.
- **Key Target Anomaly Types**:
  1. *Phytophthora* Gummosis (trunk collar bark lesions, 0–30 cm).
  2. Asian Citrus Psylla nymphs (*Diaphorina citri*), Citrus Blackflies, and Leaf Miners (under-leaf canopy).

---

## 2. Active Workspace State & File Inventory

| File Name | Purpose & Status |
| :--- | :--- |
| `PRD.md` | **Active**: Comprehensive project requirements, user personas, KPIs, and specifications. |
| `Architecture.md` | **Active**: Full cyber-physical flow, technical stack, pin mapping, and repo layout. |
| `Rules.md` | **Active**: Strict rules (No drones, zero OpenCode, offline-first, non-blocking code). |
| `Phases.md` | **Active**: 5-phase sequential roadmap from Wokwi prototype to FPO commercial rollout. |
| `Design.md` | **Active**: UI design tokens, color palette, typography hierarchy, and component specs. |
| `Memory.md` | **Active (This File)**: Living context tracker ensuring zero context loss across sessions. |
| `index.html` | **Active**: Complete, interactive single-page Tractor-Cabin Web Dashboard (PWA). |
| `wokwi_sketch.ino`| **Active**: ESP32 C++ firmware with 100% non-blocking asynchronous `loop()`. |
| `wokwi.json` | **Active**: Verified Wokwi circuit diagram with valid ESP32 GND and I2C wiring. |
| `wokwi.txt` | **Active**: 1-minute setup guide and diagram copy-paste instructions for Wokwi. |
| `FINAL_SOLUTION_PROPOSAL.pdf`| **Active**: Official publication-ready proposal PDF document. |
| `solution.txt` | **Active**: Detailed technical engineering specification document. |
| `ps.txt` | **Active**: Formal Problem Statement analysis tailored to Vidarbha citrus agronomy. |
| `he.txt` | **Active**: Original user problem brief and baseline notes. |

---

## 3. Major Technical Decisions & Corrections Recorded

1. **Rejection of Aerial Drones (Why Ground Vision Won)**:
   - Drones are physically blind to under-leaf flush and trunk collars beneath dense 3D citrus canopies.
   - Drone LiPo batteries overheat and swell in Vidarbha’s 42–48°C summer temperatures.
   - Commercial drone CapEx (₹8–12 Lakhs) is economically unviable for Vidarbha orange farmers compared to a ₹35,000 tractor rig.

2. **Resolution of Commercial GPS Drift ($\pm 3–5\text{m}$)**:
   - In 5m $\times$ 5m grid spacing, raw GPS misidentifies adjacent trees.
   - CITRUS-TERRA AI couples a Hall-effect tractor wheel encoder (odometry) with an optical ToF trunk sensor to produce deterministic tree keys (`BLK_B_R04_T012`).

3. **Wokwi Simulation Pinout & Logic Corrections**:
   - Upgraded legacy 7-pin SPI OLED to modern 4-pin I2C `board-ssd1306` (`0x3C`, SDA=21, SCL=22).
   - Removed non-existent pins (`GND.4` through `GND.7`), routing all component grounds cleanly to `esp:GND.1` and `esp:GND.2`.
   - Replaced `delay(50)` in `wokwi_sketch.ino` with a non-blocking `millis()` architecture so high-speed rotary encoder pulses are never dropped.
   - Added debounced edge detection on the pushbutton for instant pest simulation and spot-spraying.

4. **Creation of Interactive Web Cockpit (`index.html`)**:
   - Added an offline-capable, responsive Web Dashboard featuring an interactive 2D orchard map, dual simulated camera feeds, real-time solenoid valve indicators, and live Marathi WhatsApp advisory generation.

---

## 4. Current Milestone Status
- [x] Problem statement formalization (`ps.txt`)
- [x] In-depth technical architecture blueprint (`solution.txt`)
- [x] Formal proposal PDF generation (`FINAL_SOLUTION_PROPOSAL.pdf`)
- [x] Wokwi circuit schema & verified firmware (`wokwi.json`, `wokwi_sketch.ino`)
- [x] Interactive Tractor-Cabin Web Dashboard & Demo Suite (`index.html`)
  * Live GIS 2D orchard map (48 trees)
  * Dual-angle YOLO camera simulation with bounding boxes
  * Real-time 1.5s solenoid valve mist particle animation
  * Web Audio API synthesized cabin beeps & sound effects
  * AI Vision Laboratory with interactive sample switching
  * Head-to-head Ground vs Drone battle matrix
  * Interactive Acreage/Cycles Financial ROI Calculator
  * Printable/Exportable Field Scan Report Modal
  * Bilingual Marathi (Varhadi) / English instant toggle
- [x] 6 Core Project Governance Documents (`PRD.md`, `Architecture.md`, `Rules.md`, `Phases.md`, `Design.md`, `Memory.md`)
- [x] Pushed to GitHub repository: https://github.com/KSHITIJadakane/ORANGE-TECH (Branch: `main`)

