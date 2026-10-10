# CITRUS-TERRA AI — Project Requirements Document (PRD)

---

## 1. Executive Summary & Vision
**CITRUS-TERRA AI** is a low-cost, cyber-physical ground monitoring and precision spot-intervention system designed specifically for **Nagpur Mandarin (*Citrus reticulata*)** orchards in the Vidarbha region of Maharashtra (covering Katol, Warud, Morshi, Amravati, and Nagpur belts).

The system replaces cost-prohibitive, canopy-blind aerial drones with a **tractor-mounted multi-angle vision and precision spot-spraying rig**, paired with **autonomous solar IoT pest sentinels** and an **offline-first cabin Web Dashboard (PWA)**.

---

## 2. Target Users & Stakeholders
1. **Marginal & Smallholder Citrus Farmers (2–10 Acres)**:
   - Need low-cost, actionable crop protection advice in Marathi without expensive tech.
2. **Medium-to-Large Orchard Owners (10–50+ Acres)**:
   - Need to reduce crippling pesticide bills (₹80,000–₹1,50,000/year) and automate routine scouting.
3. **Farmer Producer Organizations (FPOs) & Custom Hiring Centers (CHCs)**:
   - Provide "Precision Monitoring & Targeted Spraying" as a service at $\le ₹250/\text{acre/cycle}$.
4. **Agronomists & ICAR-CCRI Extension Officers**:
   - Central portal data access for regional epidemiological surveillance of Citrus Psylla and Gummosis outbreaks.

---

## 3. Core Problems & Deficiencies Solved
| Problem in Vidarbha Orchards | Traditional / Aerial Drone Limitation | CITRUS-TERRA Solution |
| :--- | :--- | :--- |
| **Under-Leaf Sucking Pests** (Asian Citrus Psylla, Blackflies, Leaf Miners) | Drones fly top-down; physically blind to leaf undersides. | Upper camera tilted 30° upwards with diffuse LED lighting captures under-leaf flush. |
| **Trunk Collar Rot** (*Phytophthora* Gummosis) | Hidden under thick 3D canopy; drones cannot image trunk bases. | Lower camera tilted 15° downwards scans 0–40 cm bark collar directly. |
| **Commercial GPS Drift ($\pm 3\text{m}$ to $5\text{m}$)** | Confuses adjacent trees in standard 5m $\times$ 5m orchard grids. | Hardware Wheel Encoder (odometry) + Optical ToF trunk sensor = Deterministic tree indexing (`BLK_B_R04_T012`). |
| **Extreme Heat & Capital Cost** | Agricultural drones cost ₹8–12 Lakhs; LiPo batteries swell at >42°C. | Tractor rig costs < ₹35,000 CapEx; rugged industrial sensors operate safely at 48°C. |
| **Chemical Overuse & Blanket Spraying** | Blankets entire orchard; 70%+ of pesticide falls on bare soil or healthy foliage. | Solenoid valve spot-sprays *only* infected trees (1.5s burst, 45ml), saving > 65% chemical volume. |

---

## 4. Key Functional Features & Requirements

### 4.1 Tractor-Vision Multi-Angle Camera Rig
- **FR-1.1**: Upper camera tilted +30° capturing under-canopy young flush for Asian Citrus Psylla nymphs and leaf miners.
- **FR-1.2**: Lower camera tilted -15° capturing trunk bark from 0 to 40 cm for *Phytophthora* oozing gum lesions.
- **FR-1.3**: Global-shutter industrial sensors (60 FPS) operating blur-free at 5–8 km/h tractor speed.

### 4.2 Deterministic Tree GIS Indexing
- **FR-2.1**: Hall-effect rotary wheel encoder measuring linear odometry in centimeters.
- **FR-2.2**: Lateral ToF/Ultrasonic sensor confirming tree trunk passage within 140cm.
- **FR-2.3**: Deterministic tree addressing format: `[Block]_[Row]_[Tree]` (e.g., `BLK_B_R04_T012`). Zero GPS drift confusion.

### 4.3 Real-Time Targeted Spot-Spraying Actuator
- **FR-3.1**: 12V high-speed solenoid valve connected to the tractor's existing PTO pressure line.
- **FR-3.2**: Sub-100ms trigger response upon AI disease classification.
- **FR-3.3**: Timed 1.5-second pulsed spray burst delivering exact 45ml targeted dosage.

### 4.4 Tractor-Cabin Local Web Dashboard (PWA)
- **FR-4.1**: 100% offline local web server hosted over tractor Wi-Fi hotspot (`http://192.168.4.1:8080`).
- **FR-4.2**: Real-time 2D interactive orchard map displaying tree nodes (Green = Healthy, Red = Infected).
- **FR-4.3**: Dual live camera visualizer with YOLO detection bounding boxes.
- **FR-4.4**: Live telemetry: Tractor speed, Active Tree ID, Solenoid valve status, Chemical savings counter.

### 4.5 Vernacular Advisory Engine (Marathi / English)
- **FR-5.1**: Automated WhatsApp/SMS advisory generation at end of each row pass.
- **FR-5.2**: ICAR-CCRI approved chemical and organic prescriptions (Bordeaux paste, Copper Oxychloride, Thiamethoxam).
- **FR-5.3**: Exact geo-tagged tree IDs with Google Maps navigation links for targeted manual follow-up.

---

## 5. Non-Functional Requirements
- **NFR-1 (Latency)**: End-to-end edge AI inference and spray solenoid actuation in $< 35\text{ms}$.
- **NFR-2 (Offline Resilience)**: Zero dependence on active 4G/cellular internet during field operations.
- **NFR-3 (Thermal Reliability)**: All electronics rated for Vidarbha peak summer ambient temperatures ($48^\circ\text{C}$).
- **NFR-4 (Power Efficiency)**: Complete rig powered from tractor 12V DC battery with $< 40\text{W}$ consumption.

---

## 6. Success Metrics & Key Performance Indicators (KPIs)
- **Pesticide Volume Reduction**: $\ge 65\%$ reduction vs conventional blanket spraying.
- **Yield Loss Reduction**: Cut *Phytophthora* tree mortality from $18\%$ to $< 3\%$.
- **Operational Cost**: $\le ₹250/\text{acre/pass}$ for FPO service delivery.
- **Spatial Accuracy**: $100\%$ tree-level identification accuracy across 5m grid rows.
