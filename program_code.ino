#define BLYNK_TEMPLATE_ID "TMPL3Df-tjsGW"
#define BLYNK_TEMPLATE_NAME "Smart Energy Meter"
#define BLYNK_AUTH_TOKEN "_pGB1MQWeaZMhGkLcWDLVePirTpmn-dd"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// LCD Optional (you can disable if not needed)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi credentials
char ssid[] = "B";              // Your WiFi Name
char pass[] = "123456789";      // Your WiFi Password

// CT Sensor Pins
const int ctSupplyPin = 32;
const int ctLoadPin   = 35;

// Output Pins
const int ledPin = 25;
const int buzzerPin = 26;

// Constants
float calFactor = 0.05;      // Adjust for your CT
int numSamples = 100;
float theftThreshold = 0.6;  // Theft detection threshold
float bypassLimit = 1.0;     // Bypass condition
float offLimit = 0.1;

// --- Fluctuation Tracking ---
unsigned long lastCheckTime = 0;
int fluctuationCount = 0;
int fluctuationLimit = 25;   // If >25 fluctuations/min → ATTENTION
unsigned long checkInterval = 60000; // 1 minute

// Variables
float prevSupply = 0, prevLoad = 0;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  lcd.setCursor(0,0);
  lcd.print("Smart Energy Sys");
  delay(1500);
  lcd.clear();
}

void loop() {
  Blynk.run();

  float supplySum = 0, loadSum = 0;
  for (int i = 0; i < numSamples; ++i) {
    supplySum += analogRead(ctSupplyPin);
    loadSum += analogRead(ctLoadPin);
    delay(2);
  }

  float supply = (supplySum / numSamples) * calFactor;
  float load = (loadSum / numSamples) * calFactor;
  if (supply < 0.05) supply = 0;
  if (load < 0.05) load = 0;
  float diff = fabs(load - supply);

  // --- Fluctuation detection ---
  if (fabs(supply - prevSupply) > 0.5 || fabs(load - prevLoad) > 0.5) {
    fluctuationCount++;
  }
  prevSupply = supply;
  prevLoad = load;

  String status = "NORMAL";
  bool alarm = false;

  // --- Determine Status ---
  if (load <= offLimit) {
    status = "OFF";
  }
  else if (supply == 0 && load > bypassLimit) {
    status = "BYPASS";
    alarm = true;
  }
  else if (diff > theftThreshold) {
    status = "THEFT";
    alarm = true;
  }

  // --- Check Fluctuation every 1 minute ---
  if (millis() - lastCheckTime >= checkInterval) {
    if (fluctuationCount > fluctuationLimit) {
      status = "ATTENTION";
      alarm = true;
      fluctuationCount = 0;
    } else {
      fluctuationCount = 0;
    }
    lastCheckTime = millis();
  }

  // --- Outputs ---
  digitalWrite(ledPin, alarm ? HIGH : LOW);
  digitalWrite(buzzerPin, alarm ? HIGH : LOW);

  // --- LCD Display ---
  lcd.setCursor(0,0);
  lcd.print("S:");
  lcd.print(supply,2);
  lcd.print(" L:");
  lcd.print(load,2);
  lcd.print("  ");

  lcd.setCursor(0,1);
  lcd.print("St:");
  lcd.print(status);
  lcd.print("     ");

  // --- Send to Blynk ---
  Blynk.virtualWrite(V0, supply);
  Blynk.virtualWrite(V1, load);
  Blynk.virtualWrite(V2, diff);
  Blynk.virtualWrite(V3, status);

  Serial.print("Supply: "); Serial.print(supply,2);
  Serial.print(" | Load: "); Serial.print(load,2);
  Serial.print(" | Diff: "); Serial.print(diff,2);
  Serial.print(" | Status: "); Serial.println(status);

  delay(1000);
}