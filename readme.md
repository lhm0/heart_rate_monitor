# DIY Arduino Heart Rate Monitor

**A compact, 3D-printed heart rate monitor powered by an ESP8266 microcontroller and a MAX30102 pulse sensor. Open source and easy to build – ideal for makers, students, and tinkerers.**

![device](/documentation/title_page.jpeg)

## ✨ Project Highlights

- Uses only low-cost, widely available components
- All-in-one device: display, microcontroller, and sensor integrated into a compact enclosure
- Custom-designed 3D-printed case (STL files included)
- Open-source C++ code with clean OOP structure
- Works with both **PlatformIO** and the **Arduino IDE**

---

## 🧠 How It Works

The device uses a MAX30102 sensor to detect heartbeats via infrared light absorption. The signal is analyzed in real-time to determine the heart rate, which is displayed on a small OLED screen in both **beats per minute** and **Hertz**.

---

## 🔧 Components

- **Wemos D1 mini** (ESP8266)
- **SSD1306 OLED display** (0.96", I2C, 128x64)
- **MAX30102 pulse sensor**
- **Custom 3D-printed case** (STL files provided)
- Basic wiring and soldering tools

---

## 📦 Getting Started

### Option 1: Arduino IDE

1. Install the following libraries via the Library Manager:
   - `SparkFun MAX3010x Pulse and Proximity Sensor`
   - `ESP8266 and ESP32 OLED driver for SSD1306 displays by ThingPulse`

2. Select the board: **LOLIN(WEMOS) D1 R2 & mini**

3. Open `heart_beat.ino` from the `software_Arduino_IDE` folder, compile, and upload to your D1 mini.

---

### Option 2: PlatformIO (Recommended for advanced users)

1. Install **Visual Studio Code**
2. Add the **PlatformIO extension** from the Extensions Marketplace
3. Open the folder:  /heart_rate_monitor/software_platformIO/
4. All configuration is already set up in `platformio.ini`
5. Click **Build** and **Upload** in the PlatformIO toolbar, or use: platformio run –target upload

---

## 🖨️ 3D Printing

STL files for the enclosure are located in the `3d_print` folder. All parts are optimized for FDM printers and require no supports. Assembly instructions are available in the upcoming Instructables article and YouTube video.

---

## 🎥 Demo Video

👉 *Coming soon: A full demo and build guide on YouTube!*

---

## 🧩 License

This project is licensed under the **MIT License** – feel free to use, modify, and share!

---

## 🤝 Contributions

Feedback, improvements, and pull requests are welcome. Fork it, build it, remix it!

---

## 📫 Contact

Questions or suggestions? Reach out via GitHub Issues.
