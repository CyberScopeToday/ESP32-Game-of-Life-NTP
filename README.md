> **Language:**  
> [English (current)](./README.md) | [Русский (Russian)](./README_ru.md)

# ESP32 Conway's Game of Life + NTP Time Display

## 🌍 Project Overview
This project runs Conway's Game of Life on an **SSD1306 OLED display** controlled by an **ESP32**. The ESP32 connects to **WiFi**, fetches the time via **NTP**, and periodically displays it on the screen. The simulation restarts every 30 seconds, and the time appears for 5 seconds every 2 minutes.

<img src="https://github.com/user-attachments/assets/a6fccf93-5a94-4a7b-a547-52c4dbf95fea" width="200">

---

## ✨ Key Features
- **ESP32-based** implementation with an **SSD1306 OLED** display.
- **Conway's Game of Life** simulation with multiple starting patterns.
- **WiFi-enabled**, retrieves real-time **NTP clock** updates.
- **Automatically switches** between simulation and time display.
- **Low-power operation** suitable for battery-powered applications.

## 🔧 Components List
| Component          | Description                      | Quantity |
|-------------------|--------------------------------|----------|
| ESP32 Board      | Main microcontroller           | 1        |
| SSD1306 OLED (I2C) | 128x64 pixels display          | 1        |
| Power Supply     | 5V via USB or LiPo + regulator | 1        |

## 🛠 Wiring Diagram
| ESP32 Pin | OLED Pin |
|-----------|---------|
| GPIO 4 (SDA) | SDA |
| GPIO 5 (SCL) | SCL |
| 3.3V | VCC |
| GND | GND |

**Diagram:**

## 🖥 Arduino IDE Setup
1. **Install ESP32 Board Support**
   - Open **Arduino IDE** → **Preferences**
   - Add ESP32 board URL: `https://dl.espressif.com/dl/package_esp32_index.json`
   - Go to **Board Manager**, search for "ESP32" and install.

2. **Install Required Libraries**
   - **Adafruit GFX**
   - **Adafruit SSD1306**
   - **WiFi**
   - **NTPClient**

## 🔥 Flashing ESP32
1. **Connect ESP32 via USB**
2. **Select Board:** "ESP32 Dev Module"
3. **Set Upload Speed:** `115200`
4. **Press Upload** → If upload fails, hold **BOOT** button during flashing.

## ⏰ Modifying Update Intervals
Change these values in the **main code**:
```cpp
const unsigned long restartInterval = 30000; // Restart simulation every 30s
const unsigned long timeDisplayInterval = 120000; // Show time every 2 min
const unsigned long timeDisplayDuration = 5000; // Show time for 5s
```

## 📡 ThingSpeak Integration (Future Plan)
- Sending **game stats** (population, cycles) to **ThingSpeak**.
- Displaying **weather data** on OLED alongside the game.

## 📝 License
This project is **MIT Licensed** – free to modify and distribute.

🚀 Enjoy your ESP32-powered Conway's Game of Life!

