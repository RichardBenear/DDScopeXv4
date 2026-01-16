# LX200 WiFi Bridge for DDScopeX

This project implements a WiFi bridge that allows **SkySafari Plus/Pro** and **Stellarium Mobile** to control a telescope running [DDScopeX/OnStepX](https://github.com/richardbenear/DDScopeX) via the **LX200 protocol**.

It runs on a **Seeed Studio XIAO ESP32-C3** and acts as an LX200 server over WiFi, forwarding commands to a **Teensy 4.1** via UART (`Serial1`). The Teensy responds with appropriate data, which is relayed back to the client app.

This project requires the compatible version of DDScopeX which has the LX200 Handler code (LX200Handler.cpp) since the handshaking and communication connection is handled there.

---

## 💡 Features

- **WiFi Access Point + Station Mode**  
  Connects to Stellarium and SkySafari as an AP and optionally joins an existing WiFi network for dual communication.

- **LX200 Command Forwarding**  
  Forwards commands to DDScopeX/OnStepX over Serial1, handles custom formatting quirks for compatibility (e.g. `:SC`, `:SG+06.0#`).

- **Custom Application Commands**  
  Replies directly to a few app-specific commands such as:
  - `:GVP#` → `OnStepX.DDScopeX#`
  - `:GVN#` → `2.0#`
  - `:GVD#` → `May 2025#`
  
  Handles other communication "quirks" in both Stellarium Mobile and Sky Safari Plus/Pro.

- **Oled Status Display**  
  Shows both the ESP32 AP IP and the IP of the WiFi Display device connected to the Teensy.

- **Reset Trigger from Teensy**  
  Supports a software-reset via a GPIO input from the Teensy (`D10` / `RESET_PIN`).

---

## 📡 Network Configuration

- **Access Point (AP)**
  - SSID: `LX200-ESP32`
  - Password: `password`
  - Static IP: `192.168.4.1`
  - Port: `4030` (standard LX200 TCP port)

- **Station Mode**
  - Credentials pulled from `secrets.h`
  - IP displayed on the OLED

---

## 🔌 Hardware Connections

| ESP32-C3 Pin | Function           | Description                    |
|--------------|--------------------|--------------------------------|
| `D6`         | `TX`               | To Teensy RX (Serial8)         |
| `D7`         | `RX`               | From Teensy TX (Serial8)       |
| `D10`        | `RESET_PIN`        | From Teensy for soft reset     |
| `D4/D5`      | I2C SDA/SCL        | OLED display (optional)        |

---

## 📁 File Structure

| File                        | Purpose                                  |
|-----------------------------|------------------------------------------|
| `src/LX200WifiBridge.cpp`   | Main command forwarding logic            |
| `include/secrets.h`         | WiFi credentials (ignored in Git)        |
| `include/secretsTemplate.h` | Example secrets file for users           |
| `src/OledDisplay.*`         | OLED display handling (I2C, optional)    |

---
