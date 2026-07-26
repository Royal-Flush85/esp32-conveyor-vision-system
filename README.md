# ESP32 Conveyor Vision & Automated Motion Control System

An embedded industrial automation prototype combining an **ESP32-CAM video streaming node** with an **ESP32 PIR motion-triggered conveyor belt controller**. 

The system utilizes a non-blocking **Finite State Machine (FSM)** for precise motor timing, H-bridge PWM speed control, and customized hardware power management to prevent brownout resets.

---

## System Demonstration

<!-- Upload your hand-sensing video or .gif directly into GitHub's README editor -->
![Motion Detection & Motor Stop Demo](YOUR_VIDEO_OR_GIF_URL_HERE)

*Figure 1: Closed-loop motion test showing immediate motor response upon optical/PIR sensor trigger.*

---

## Engineering Highlights & Firmware Architecture

* **Non-Blocking Finite State Machine (FSM):** Replaced blocking `delay()` execution loops with a state machine (`IDLE` → `RUNNING` → `STOPPING`) driven by `millis()` timestamps. This maintains CPU availability for continuous sensor polling and edge logic.
* **Hardware Brownout Mitigation:** Reconfigured ESP32-CAM register states (`RTC_CNTL_BROWN_OUT_REG`) to suppress current-spike reset loops during Wi-Fi initialization and video streaming.
* **PWM Motor Control:** Integrated ESP32 LEDC PWM timer channels to handle dynamic duty cycle scaling on motor driver enable pins (H-bridge IC).
* **Clean Hardware Decoupling:** Separated stream processing from actuation, allowing the vision camera node and physical belt control to run as independent, fault-tolerant network services.

---

## Hardware Configuration & Pinout

### Conveyor Motor Controller (ESP32)

| Component / Function | ESP32 GPIO | Description |
| :--- | :--- | :--- |
| **Motion Sensor (PIR)** | **GPIO 4** | Digital Input (Active High) |
| **Motor Driver IN1** | **GPIO 17** | H-Bridge Logic Output 1 |
| **Motor Driver IN2** | **GPIO 16** | H-Bridge Logic Output 2 |
| **Motor Enable (PWM)** | **GPIO 5** | LEDC Channel 0 PWM Speed Control |

### Vision Camera Node (ESP32-CAM)

| Peripheral | Board | Notes |
| :--- | :--- | :--- |
| **OV2640 Camera** | ESP32-CAM | MJPEG Stream over Wi-Fi |
| **Power Supply** | 5V / 2A External | Dedicated supply to handle RF power spikes |

---

## Repository Structure

```text
esp32-conveyor-vision-system/
├── conveyor_main/
│   └── conveyor_main.ino    # FSM motor controller & sensor state machine
├── camera_streamer/
│   └── camera_streamer.ino  # ESP32-CAM Wi-Fi video streaming node
├── .gitignore               # Excludes build binaries & local IDE cache
└── README.md                # System documentation