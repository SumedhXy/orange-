# CITRUS-TERRA AI — Design System & UI Style Guide

---

## 1. Visual Philosophy & Design Direction
The user interface is designed for high-contrast, outdoor readability under harsh agricultural lighting conditions inside tractor cabins, while projecting a **state-of-the-art cyber-physical agri-tech aesthetic**.

- **Core Theme**: High-tech Agricultural Dark Mode.
- **Visual Style**: Subtle Glassmorphism, tailored glowing accent borders, ultra-clean geometry, and smooth micro-animations.
- **Target Context**: Rugged Android tablets and driver smartphones mounted on tractor dashboards.

---

## 2. Color Palette & Tokens

### 2.1 Backgrounds & Surfaces
```css
--bg-dark:        #0a0f1d;  /* Deep navy obsidian background */
--bg-radial:      #111a33;  /* Ambient radial gradient center */
--card-bg:        rgba(18, 26, 47, 0.75);  /* Frosted glass card fill */
--card-border:    rgba(255, 255, 255, 0.08); /* Clean crisp separation */
--card-border-hover: rgba(255, 255, 255, 0.20);
```

### 2.2 Semantic Status Colors
```css
/* Healthy Tree / Optimal State / Savings */
--primary:        #10b981;  /* Emerald Green */
--primary-light:  #34d399;  /* High-contrast mint */
--primary-glow:   rgba(16, 185, 129, 0.25);

/* Pest Alert / Gummosis / Active Spot-Spray */
--danger:         #ef4444;  /* Crimson Alert */
--danger-dark:    #dc2626;  /* Deep warning red */
--danger-glow:    rgba(239, 68, 68, 0.35);

/* Warning / Monitor / Intermediate Flush */
--warning:        #f59e0b;  /* Vibrant Amber */
--warning-glow:   rgba(245, 158, 11, 0.25);

/* Tractor Tracking / Position Telemetry */
--accent-cyan:    #06b6d4;  /* Tech Cyan */
--accent-sky:     #38bdf8;  /* Odometry marker */
--accent-glow:    rgba(6, 182, 212, 0.40);
```

### 2.3 Typography & Text
```css
--text-main:      #f8fafc;  /* Crisp snow white for headings & values */
--text-muted:     #94a3b8;  /* Slate gray for secondary labels */
--text-subtle:    #64748b;  /* Dim text for grid indices */
```

---

## 3. Typography Hierarchy

| Role | Font Family | Weight | Size | Letter Spacing |
| :--- | :--- | :--- | :--- | :--- |
| **Brand Title** | `Plus Jakarta Sans` | 800 (Bold) | 1.25rem (20px) | -0.02em |
| **Panel Headers** | `Plus Jakarta Sans` | 700 (SemiBold)| 1.00rem (16px) | -0.01em |
| **Metric Value** | `JetBrains Mono` | 800 (ExtraBold)| 1.80rem (28px) | -0.03em |
| **Telemetry / IDs**| `JetBrains Mono` | 600 (Medium) | 0.85rem (14px) | 0.02em |
| **Body & Advice** | `Plus Jakarta Sans` | 400 / 500 | 0.85rem (14px) | Normal |
| **Labels & Badges**| `Plus Jakarta Sans` | 700 (Bold) | 0.70rem (11px) | 0.05em (Caps) |

---

## 4. UI Components & Micro-Interactions

### 4.1 Telemetry Metric Cards
- **Backdrop**: `backdrop-filter: blur(12px)`.
- **Border**: 1px solid `rgba(255, 255, 255, 0.08)`.
- **Hover**: Subtle `transform: translateY(-2px)` elevation with border illumination.

### 4.2 2D Orchard Map Tree Nodes
- **Size**: 32px $\times$ 32px rounded squircle (`border-radius: 8px`).
- **Healthy Node**: Transparent green background with vibrant emerald border.
- **Infected Node**: Vibrant red fill with continuous pulsing glow animation (`animation: pulse-danger 1.5s infinite`).
- **Tractor Cursor**: Cyan active ring (`outline: 3px solid #06b6d4`) tracking the real-time tractor position.

### 4.3 Dual AI Camera Feeds
- **Aspect Ratio**: 16:9 simulated sensor stream.
- **Bounding Boxes**: Dashed high-contrast vector overlays with floating confidence tags (`Phytophthora (94%)`, `Psylla Nymph (89%)`).
- **Grid Scanlines**: Subtle animated line sweeps conveying active computer vision inferencing.

### 4.4 WhatsApp Vernacular Advisory Stream
- **Theme**: WhatsApp dark green accent (`#25d366` & `#075e54`).
- **Typography**: Clean, readable Marathi script with bulleted ICAR-CCRI prescriptions and emojis for quick field comprehension.
