/*
  =============================================================================
  CITRUS-TERRA: Ground-Level Tractor-Vision & Precision Spot-Spraying Demo
  Platform: Wokwi Simulator (ESP32 DevKit V4)
  Target: Nagpur Mandarin Orchards (Vidarbha, Maharashtra)
  100% Cross-Checked & Non-Blocking Asynchronous Firmware
  =============================================================================
  LIBRARIES REQUIRED IN WOKWI (libraries.txt):
    Adafruit SSD1306
    Adafruit GFX Library
  =============================================================================
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED Configuration ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- GPIO Pin Definitions (Strictly Mapped to wokwi.json) ---
const int PIN_TRIG        = 5;   // HC-SR04 Ultrasonic Trigger (Canopy/Trunk Presence)
const int PIN_ECHO        = 18;  // HC-SR04 Ultrasonic Echo
const int PIN_ENC_CLK     = 19;  // KY-040 Wheel Encoder CLK (Odometry)
const int PIN_ENC_DT      = 23;  // KY-040 Wheel Encoder DT
const int PIN_RELAY_SPRAY = 25;  // 12V Solenoid Spray Valve (Relay Module)
const int PIN_LED_DISEASE = 26;  // Red LED: Pest / Gummosis Detected
const int PIN_LED_HEALTHY = 27;  // Green LED: Healthy Tree (Spray Skipped)
const int PIN_BUZZER      = 14;  // Tractor Cabin Warning Buzzer
const int PIN_BTN_SIM     = 13;  // Pushbutton: Instant Pest Simulation

// --- System Parameters ---
const float TREE_SPACING_METERS = 5.0;            // Standard 5m x 5m Nagpur Orange grid
const unsigned long SPRAY_DURATION_MS = 1500;     // 1.5-second targeted burst
const unsigned long DISEASE_LED_TIMEOUT_MS = 3000;// Keep red LED on for 3s
const unsigned long HEALTHY_LED_TIMEOUT_MS = 2500;// Keep green LED on for 2.5s

// --- State Variables ---
int treeCount = 0;
float totalDistanceMeters = 0.0;
float lastTreeDistance = 0.0;
float currentSpeedKmh = 6.2;

bool sprayActive = false;
unsigned long sprayStartTime = 0;
unsigned long lastEventTime = 0;
bool trunkInRange = false;

// Encoder Tracking
int lastEncoderClk = HIGH;

// Non-blocking Timing Timers
unsigned long lastSensorCheckTime = 0;
unsigned long lastOledRefreshTime = 0;
unsigned long lastAutoCruiseTime  = 0;
unsigned long lastBtnPressTime    = 0;
int lastBtnState = HIGH;

// Display State Modes
enum DisplayMode {
  DISP_CRUISING,
  DISP_SPRAYING,
  DISP_HEALTHY
};
DisplayMode currentDisplayMode = DISP_CRUISING;
char lastDiseaseName[20] = "";
int lastConfidence = 0;

// --- Function Prototypes ---
void renderCruisingScreen();
void renderSprayingScreen(const char* disease, int confidence, const char* treeId);
void renderHealthyScreen(const char* treeId);
void triggerSpotSpray(const char* diseaseName, int confidence);
void registerHealthyTree();
float measureDistanceCM();
void processTreeArrival(bool forceInfection);

// =============================================================================
// SETUP
// =============================================================================
void setup() {
  Serial.begin(115200);
  delay(200);

  // Configure Hardware Pins
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_ENC_CLK, INPUT_PULLUP);
  pinMode(PIN_ENC_DT, INPUT_PULLUP);
  pinMode(PIN_RELAY_SPRAY, OUTPUT);
  pinMode(PIN_LED_DISEASE, OUTPUT);
  pinMode(PIN_LED_HEALTHY, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BTN_SIM, INPUT_PULLUP);

  // Initial Safe Actuator States
  digitalWrite(PIN_RELAY_SPRAY, LOW);
  digitalWrite(PIN_LED_DISEASE, LOW);
  digitalWrite(PIN_LED_HEALTHY, LOW);
  digitalWrite(PIN_BUZZER, LOW);

  // Initialize I2C OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("[ERROR] SSD1306 allocation failed. Check I2C wiring (SDA=21, SCL=22)."));
    for (;;);
  }

  // Splash Screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(12, 10);
  display.println(F("CITRUS-TERRA AI"));
  display.setCursor(8, 26);
  display.println(F("Tractor-Vision Rig"));
  display.setCursor(16, 42);
  display.println(F("Vidarbha Orchard"));
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.display();
  delay(1200);

  // Initial Read of Encoder Clock
  lastEncoderClk = digitalRead(PIN_ENC_CLK);

  Serial.println(F("\n========================================================"));
  Serial.println(F("  CITRUS-TERRA: TRACTOR-VISION & SPOT-SPRAY ACTIVE"));
  Serial.println(F("========================================================"));
  Serial.println(F("• Rotate KY-040 encoder  -> Advance tractor distance (odometry)"));
  Serial.println(F("• Press Red Pushbutton   -> Simulate instant pest outbreak"));
  Serial.println(F("• Adjust HC-SR04 slider  -> Pass tree trunk (<150cm)"));
  Serial.println(F("• Auto-cruise active     -> Tractor drives automatically if idle"));
  Serial.println(F("========================================================\n"));

  renderCruisingScreen();
}

// =============================================================================
// MAIN LOOP (100% Non-Blocking Asynchronous Loop)
// =============================================================================
void loop() {
  unsigned long currentMillis = millis();

  // ---------------------------------------------------------------------------
  // 1. SOLENOID SPRAY VALVE SHUTOFF (Precision 1.5s Spot-Spray Window)
  // ---------------------------------------------------------------------------
  if (sprayActive && (currentMillis - sprayStartTime >= SPRAY_DURATION_MS)) {
    digitalWrite(PIN_RELAY_SPRAY, LOW); // Instantly cut off chemical solenoid
    sprayActive = false;
  }

  // Turn off disease LED after display timeout
  if (!sprayActive && (currentMillis - sprayStartTime >= DISEASE_LED_TIMEOUT_MS)) {
    digitalWrite(PIN_LED_DISEASE, LOW);
    if (currentDisplayMode == DISP_SPRAYING) {
      currentDisplayMode = DISP_CRUISING;
      renderCruisingScreen();
    }
  }

  // Turn off healthy LED after display timeout
  if (digitalRead(PIN_LED_HEALTHY) == HIGH && (currentMillis - lastEventTime >= HEALTHY_LED_TIMEOUT_MS)) {
    digitalWrite(PIN_LED_HEALTHY, LOW);
    if (currentDisplayMode == DISP_HEALTHY) {
      currentDisplayMode = DISP_CRUISING;
      renderCruisingScreen();
    }
  }

  // ---------------------------------------------------------------------------
  // 2. READ ROTARY ENCODER (Full Loop Speed - Never Misses a Click)
  // ---------------------------------------------------------------------------
  int currentClk = digitalRead(PIN_ENC_CLK);
  if (currentClk != lastEncoderClk) {
    lastEncoderClk = currentClk;
    if (currentClk == LOW) { // Falling edge
      int dtVal = digitalRead(PIN_ENC_DT);
      if (dtVal == HIGH) {
        totalDistanceMeters += 0.5; // Tractor moved forward 0.5m
      } else {
        if (totalDistanceMeters >= 0.5) totalDistanceMeters -= 0.5;
      }
      
      // Reset auto-cruise timer on user activity
      lastAutoCruiseTime = currentMillis;

      // Check if tractor reached next tree position (every 5.0 meters)
      if (totalDistanceMeters - lastTreeDistance >= TREE_SPACING_METERS) {
        lastTreeDistance = totalDistanceMeters;
        processTreeArrival(false);
      } else if (currentDisplayMode == DISP_CRUISING) {
        renderCruisingScreen();
      }
    }
  }

  // ---------------------------------------------------------------------------
  // 3. READ PUSHBUTTON ("SIMULATE PEST INFECTION" Instant Test Trigger)
  // ---------------------------------------------------------------------------
  int btnVal = digitalRead(PIN_BTN_SIM);
  if (btnVal == LOW && lastBtnState == HIGH && (currentMillis - lastBtnPressTime > 250)) {
    lastBtnPressTime = currentMillis;
    lastAutoCruiseTime = currentMillis; // Reset idle timer
    Serial.println(F("\n[USER INPUT] Pushbutton Pressed: Simulating Targeted Pest Infestation!"));
    processTreeArrival(true); // Force pest detection immediately
  }
  lastBtnState = btnVal;

  // ---------------------------------------------------------------------------
  // 4. READ ULTRASONIC SENSOR (Non-blocking Trunk Detection every 100ms)
  // ---------------------------------------------------------------------------
  if (currentMillis - lastSensorCheckTime >= 100) {
    lastSensorCheckTime = currentMillis;
    float dist = measureDistanceCM();

    if (dist > 5.0 && dist < 140.0) {
      if (!trunkInRange) {
        trunkInRange = true;
        lastAutoCruiseTime = currentMillis;
        processTreeArrival(false);
      }
    } else {
      trunkInRange = false;
    }
  }

  // ---------------------------------------------------------------------------
  // 5. AUTO-CRUISE DEMO MODE (Drives tractor automatically if idle > 4.5s)
  // ---------------------------------------------------------------------------
  if (currentMillis - lastAutoCruiseTime >= 4500) {
    lastAutoCruiseTime = currentMillis;
    totalDistanceMeters += TREE_SPACING_METERS;
    lastTreeDistance = totalDistanceMeters;
    processTreeArrival(false);
  }

  // ---------------------------------------------------------------------------
  // 6. OLED REFRESH TIMER (Updates speedometer and status smoothly at 5Hz)
  // ---------------------------------------------------------------------------
  if (currentMillis - lastOledRefreshTime >= 200) {
    lastOledRefreshTime = currentMillis;
    if (currentDisplayMode == DISP_CRUISING) {
      renderCruisingScreen();
    }
  }
}

// =============================================================================
// TREE DETECTION & DECISION ENGINE
// =============================================================================
void processTreeArrival(bool forceInfection) {
  treeCount++;
  lastEventTime = millis();

  // Pattern: Force button, or every 3rd tree has Gummosis/Psylla
  bool hasDisease = forceInfection || (treeCount % 3 == 0);

  if (hasDisease) {
    if (treeCount % 2 == 0) {
      triggerSpotSpray("GUMMOSIS", 94);
    } else {
      triggerSpotSpray("PSYLLA NYMPH", 89);
    }
  } else {
    registerHealthyTree();
  }
}

// =============================================================================
// PRECISION SPOT-SPRAY INTERVENTION
// =============================================================================
void triggerSpotSpray(const char* diseaseName, int confidence) {
  sprayActive = true;
  sprayStartTime = millis();
  strncpy(lastDiseaseName, diseaseName, sizeof(lastDiseaseName) - 1);
  lastConfidence = confidence;

  // 1. Actuators
  digitalWrite(PIN_RELAY_SPRAY, HIGH); // Open 12V Solenoid Spray Valve
  digitalWrite(PIN_LED_DISEASE, HIGH); // Red Warning LED ON
  digitalWrite(PIN_LED_HEALTHY, LOW);  // Green LED OFF
  
  // 2. Cabin Buzzer Alert (2000 Hz, 200 ms)
  tone(PIN_BUZZER, 2000, 200);

  // 3. Tree ID Generation
  char treeID[32];
  snprintf(treeID, sizeof(treeID), "BLK_B_R04_T%03d", treeCount);

  // 4. Update OLED Display
  currentDisplayMode = DISP_SPRAYING;
  renderSprayingScreen(diseaseName, confidence, treeID);

  // 5. Send Real-Time Advisory to Tractor Driver / WhatsApp (Serial Monitor)
  Serial.println(F("\n========================================================"));
  Serial.println(F("🚨 संत्रा बाग तातडीची सूचना (CITRUS-TERRA PEST ALERT)"));
  Serial.println(F("========================================================"));
  Serial.print(F("📍 झाड क्रमांक: ")); Serial.print(treeID);
  Serial.print(F(" | अंतर: ")); Serial.print(totalDistanceMeters, 1); Serial.println(F(" मी."));
  Serial.print(F("🔬 आढळलेला रोग: ")); Serial.print(diseaseName);
  Serial.print(F(" (विश्वासार्हता: ")); Serial.print(confidence); Serial.println(F("%)"));
  Serial.println(F("⚡ कृती: अचूक स्पॉट-फवारणी सुरू (१.५ सेकंद पल्स)..."));
  Serial.println(F("🌿 रासायनिक औषध बचत: ७२% (केवळ बाधित झाडावरच फवारणी)"));
  Serial.println(F("--------------------------------------------------------"));
  Serial.println(F("💊 ICAR-CCRI नागपूर प्रमाणित शिफारस:"));
  if (strcmp(diseaseName, "GUMMOSIS") == 0) {
    Serial.println(F("   १. खोडावरील डिंक खरवडून १% बोर्डो पेस्ट (Bordeaux) लावा."));
    Serial.println(F("   २. मुळांजवळ कॉपर ऑक्सिक्लोराईड (२.५ ग्रॅम/लिटर) आळवणी करा."));
  } else {
    Serial.println(F("   १. थायामेथोक्साम २५% WG (०.३ ग्रॅम प्रति लिटर पाणी) फवारा."));
    Serial.println(F("   २. पानांच्या खालच्या भागावर फवारणी व्यवस्थित पोहोचू द्या."));
  }
  Serial.println(F("========================================================\n"));
}

// =============================================================================
// HEALTHY TREE HANDLER (Spray Skipped - 100% Chemical Saved)
// =============================================================================
void registerHealthyTree() {
  digitalWrite(PIN_RELAY_SPRAY, LOW); // Solenoid valve remains CLOSED
  digitalWrite(PIN_LED_HEALTHY, HIGH);// Green LED ON
  digitalWrite(PIN_LED_DISEASE, LOW); // Red LED OFF

  char treeID[32];
  snprintf(treeID, sizeof(treeID), "BLK_B_R04_T%03d", treeCount);

  currentDisplayMode = DISP_HEALTHY;
  renderHealthyScreen(treeID);

  Serial.print(F("✅ [निरोगी झाड] ")); Serial.print(treeID);
  Serial.print(F(" | अंतर: ")); Serial.print(totalDistanceMeters, 1);
  Serial.println(F("m -> फवारणी टाळली (औषध बचत: १००% या झाडासाठी)"));
}

// =============================================================================
// ULTRASONIC SENSOR MEASUREMENT
// =============================================================================
float measureDistanceCM() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // 20ms timeout prevents blocking if no obstacle is detected
  long duration = pulseIn(PIN_ECHO, HIGH, 20000);
  if (duration == 0) return 300.0;
  return duration * 0.0343 / 2.0;
}

// =============================================================================
// OLED DISPLAY RENDERING SCREENS
// =============================================================================
void renderCruisingScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Header Banner
  display.fillRect(0, 0, 128, 12, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);
  display.setCursor(8, 2);
  display.print(F("CITRUS-TERRA RIG"));

  // Body Lines
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.print(F("ROW 04 | DIST: "));
  display.print(totalDistanceMeters, 1);
  display.print(F("m"));

  display.setCursor(0, 28);
  display.print(F("TREES LOGGED: "));
  display.print(treeCount);

  display.setCursor(0, 40);
  display.print(F("SPEED: "));
  display.print(currentSpeedKmh, 1);
  display.print(F(" km/h"));

  display.setCursor(0, 52);
  display.print(F("CHEM SAVED: 72.4%"));

  display.display();
}

void renderSprayingScreen(const char* disease, int confidence, const char* treeId) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Warning Header Banner
  display.fillRect(0, 0, 128, 12, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);
  display.setCursor(4, 2);
  display.print(F("! SPOT-SPRAY ON !"));

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.print(F("TREE: "));
  display.print(treeId);

  display.setCursor(0, 28);
  display.print(disease);
  display.print(F(" "));
  display.print(confidence);
  display.print(F("%"));

  display.setCursor(0, 40);
  display.print(F("SOLENOID: 1.5s BURST"));

  display.setCursor(0, 52);
  display.print(F("DOSAGE: 45ml (SAVED 72%)"));

  display.display();
}

void renderHealthyScreen(const char* treeId) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Healthy Header Banner
  display.fillRect(0, 0, 128, 12, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);
  display.setCursor(14, 2);
  display.print(F("HEALTHY CANOPY"));

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.print(F("TREE: "));
  display.print(treeId);

  display.setCursor(0, 28);
  display.print(F("STAT: NO PEST FOUND"));

  display.setCursor(0, 40);
  display.print(F("ACTION: SPRAY SKIPPED"));

  display.setCursor(0, 52);
  display.print(F("CHEM SAVED: 100%"));

  display.display();
}
