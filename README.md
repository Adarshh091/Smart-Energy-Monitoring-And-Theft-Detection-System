# ⚡ Smart Energy Monitoring and Theft Detection System (IoT + ESP32)

## 📘 Overview
This project monitors household or industrial energy usage in real time and detects electricity theft using CT sensors and an ESP32 microcontroller.  
It compares supply and load current to identify abnormal usage like bypass, theft, or reverse flow. Live data is shown on an LCD and synced with the Blynk IoT app.

---

## 🚀 Features
- Real-time current monitoring (Supply & Load)
- Theft and bypass detection
- LCD display for real-time readings
- Buzzer and LED alerts
- Cloud-based IoT monitoring via Blynk
- Automatic system reset

---

## 🧩 Hardware Components
- ESP32  
- CT Sensor (30A) × 2  
- LCD 16x2 (I2C)  
- Buzzer  
- LED  
- Push Button  
- Breadboard  
- Jumper Wires  

---

## ⚙ Working Principle
1. *Normal Condition* → Supply ≈ Load (no theft detected)  
2. *Off Condition* → Load ≈ 0, system idle  
3. *Bypass Condition* → Supply = 0 A but Load > 1 A  
4. *Reverse Condition* → Current flows opposite to supply line  
5. *Theft Condition* → Difference > 0.6 A between Supply and Load  

When theft or bypass occurs → *LED & Buzzer turn ON* and *LCD freezes* with last reading.

---

## 🌐 IoT (Blynk Integration)
Blynk Cloud is used to view real-time readings remotely.  
Users can monitor:
- Supply and Load currents  
- Threshold status  
- Theft and Bypass alerts  

---

## 🧰 Software Requirements
- Arduino IDE  
- ESP32 Board Package  
- Blynk Library  
- LiquidCrystal_I2C Library  
- WiFi Library  

---

## 🔧 Circuit Connections
 
<img width="1481" height="929" alt="Screenshot 2025-10-02 085709" src="https://github.com/user-attachments/assets/ed7cb631-a345-4c05-beb6-ba2defcbcd01" />



## 📊 Results
- Displays live current readings on LCD and Blynk app  
- Detects theft and bypass accurately  
- Provides both local (alarm) and remote (IoT) monitoring  

---

## 👥 Team Members
Adarsh Kumar | Abhinav Singh | Netraja | Sakshi Choubey 
---


This project demonstrates the practical use of IoT in modern electrical monitoring systems.

---

### 🖇 Repository Structure
