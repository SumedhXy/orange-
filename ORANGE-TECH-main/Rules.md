# CITRUS-TERRA AI — Rules & AI Boundary Constraints

---

## 1. Absolute Architecture Constraints (Non-Negotiable)

1. **STRICT NO-DRONE RULE**:
   - Drones are **permanently prohibited** from this solution.
   - Any suggestion to introduce UAVs/drones violates core Vidarbha citrus agronomy (canopy line-of-sight blindness to leaf undersides and trunk collars, thermal battery failure at 45°C, and ₹8–12L prohibitive cost).
   - All visual inspection and targeted intervention **must be ground-based** (Tractor-Vision or Solar IoT sentinels).

2. **DETERMINISTIC SPATIAL INDEXING (NO RAW GPS DRIFT)**:
   - Never rely on raw commercial GPS alone for tree identification ($\pm 3–5\text{m}$ error is unacceptable).
   - Always combine wheel odometry (encoder pulses) with optical/ToF trunk detection to maintain deterministic tree coordinates: `BLK_[Block]_R[Row]_T[Tree]`.

3. **ZERO OPENCODE DEPENDENCIES**:
   - OpenCode/terminal agent was permanently removed due to extreme latency and instability.
   - Do NOT regenerate `forcmd.txt`, `foranti.txt`, `sync_state.json`, or inter-agent protocols.

---

## 2. Web Application & Dashboard Rules (`index.html`)

1. **Zero Framework Bloat (Vanilla First)**:
   - Build all web pages using standard, clean **HTML5, modern CSS3, and Vanilla JavaScript**.
   - Do NOT inject bulky dependencies (React, Angular, Next.js, or complex bundlers) unless explicitly commanded.
   - Do NOT use TailwindCSS CDN links without prior confirmation. Use curated CSS custom variables.

2. **Aesthetic & Visual Excellence**:
   - Provide an immediate "WOW" factor with modern, polished dark mode UI (`#0a0f1d`), glassmorphism, subtle glowing borders, and smooth micro-animations.
   - Use Google Fonts (*Plus Jakarta Sans* and *JetBrains Mono*). Never use plain browser default serif fonts.
   - Use semantic, descriptive color coding:
     - `Healthy`: Vibrant Emerald Green (`#10b981`)
     - `Pest / Infection`: Alert Crimson (`#ef4444`)
     - `Tractor Position / Telemetry`: Cyan (`#06b6d4`)
     - `Warning / Action`: Amber (`#f59e0b`)

3. **Offline-First Resilience**:
   - All interactive features on `index.html` must function completely offline when opened locally in any modern browser without an internet connection.

---

## 3. Embedded Firmware & Wokwi Simulation Rules

1. **Strictly Non-Blocking Loops (`wokwi_sketch.ino`)**:
   - **NEVER** use blocking `delay()` calls in the Arduino `loop()` function.
   - All timers (solenoid spray cutoffs, sensor ping intervals, OLED display refresh rates, button debouncing) must use asynchronous `millis()` arithmetic.
   - The rotary encoder must be polled continuously at CPU speed to guarantee zero missed ticks.

2. **Pin Mapping Integrity (`wokwi.json`)**:
   - All pins specified in the C++ firmware must strictly mirror `wokwi.json` connections.
   - Only use valid Wokwi ESP32 pin names:
     - Ground pins: `esp:GND.1` and `esp:GND.2` only (do NOT invent `GND.4` or `GND.5`).
     - OLED I2C: `esp:21` (SDA) and `esp:22` (SCL) at I2C address `0x3C`.
     - Pushbutton: pins `1.l` and `2.l`.
     - Buzzer: pin `2` (positive) and pin `1` (negative).

---

## 4. Agricultural & Agronomy Integrity

1. **ICAR-CCRI Validation**:
   - All chemical recommendations must follow official **ICAR-Central Citrus Research Institute (CCRI) Nagpur** guidelines:
     - *Phytophthora Gummosis*: 1% Bordeaux paste bark painting + Copper Oxychloride (2.5g/L) root basin drenching.
     - *Asian Citrus Psylla*: Thiamethoxam 25% WG (0.3g/L) targeted to young flush.
   - Never recommend generic, unapproved chemicals.

2. **Vernacular Priority (Marathi / Varhadi)**:
   - All farmer alerts and advisories must be available in authentic Marathi and localized Varhadi dialect terms to ensure practical adoption by Vidarbha farmers.
