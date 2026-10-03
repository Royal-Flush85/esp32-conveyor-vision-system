# ESP32 Automation & Vision Prototype

An embedded-systems project exploring **PIR-triggered DC motor control** and **embedded computer vision** using ESP32 hardware.

The project was developed as two primary subsystems:

1. An **ESP32-S3 motor-control prototype** using an HC-SR501 PIR motion sensor, PWM motor control, and finite-state-machine logic.
2. An **ESP32-CAM vision prototype** using an Edge Impulse object-detection model trained to distinguish pens from pencils.

Both subsystems were tested independently. The intended mechanical conveyor assembly and final communication between the motor-control and vision subsystems were not completed during the project timeline.

---

## System Overview

### Motor-Control Subsystem

```text
Human / IR Motion
        ↓
HC-SR501 PIR Sensor
        ↓
     ESP32-S3
        ↓
Finite-State Machine
IDLE → RUNNING → STOPPING
        ↓
    Motor Driver
        ↓
      DC Motor
```

The HC-SR501 provides a digital motion signal to the ESP32-S3. When motion is detected, the controller activates the DC motor for a fixed interval before stopping and returning to a ready state.

The firmware uses `millis()`-based timing rather than blocking delays for state transitions.

### Vision Subsystem

```text
ESP32-CAM
    ↓
Image Capture
    ↓
Edge Impulse Model
    ↓
Pen / Pencil Detection
```

The vision subsystem was developed separately using an ESP32-CAM and an object-detection model trained through Edge Impulse.

The model was tested for recognizing two classes:

- Pen
- Pencil

---

## Intended Final System

The intended end-to-end architecture was:

```text
Motion Detected
      ↓
Motor-Control Subsystem
      ↓
Mechanical Conveyor
      ↓
ESP32-CAM Image Capture
      ↓
ML Inference
      ↓
Pen / Pencil Detection
      ↓
Control Decision
```

The motor-control and computer-vision subsystems were independently prototyped, but the full mechanical conveyor and communication between the subsystems were not completed.

---

## Motor-Control Implementation

The motor controller uses:

- ESP32-S3
- HC-SR501 PIR motion sensor
- DC motor
- Motor driver
- PWM motor enable
- Finite-state-machine control

The firmware implements three states:

### `IDLE`

The system waits for the PIR sensor to detect motion.

### `RUNNING`

When motion is detected, the motor starts and runs for a fixed duration.

### `STOPPING`

The motor stops temporarily before the system returns to `IDLE` and waits for another motion trigger.

This structure replaced an earlier implementation that relied on blocking `delay()` calls.

---

## Vision Prototype

The computer-vision prototype used:

- ESP32-CAM
- Edge Impulse
- Embedded image acquisition
- Object detection
- Pen/pencil classification

Images were used to train an Edge Impulse object-detection model for distinguishing pens from pencils.

The trained model was exported for embedded inference and tested using ESP32-CAM image input.

The included camera inference sketch is based on the Edge Impulse Arduino camera inference example and retains its original license notice.

Generated Edge Impulse deployment SDK and model files are intentionally **not redistributed in this repository**.

---

## Repository Structure

```text
esp32-automation-vision-prototype/
│
├── motor_control/
│   └── pir_motor_control.ino
│
├── vision_prototype/
│   ├── edge_impulse_camera_inference.ino
│   └── README.md
│
├── README.md
├── THIRD_PARTY.md
└── .gitignore
```

---

## Project Status

| Component | Status |
| --- | --- |
| HC-SR501 motion detection | Complete |
| ESP32-S3 motor control | Complete |
| PWM motor enable | Complete |
| Non-blocking FSM control | Complete |
| ESP32-CAM image acquisition | Tested |
| Edge Impulse pen/pencil detection | Tested independently |
| Mechanical conveyor assembly | Incomplete |
| Motor-control / vision communication | Incomplete |
| End-to-end automated system | Incomplete |

---

## What I Learned

This project provided experience with:

- ESP32 firmware development
- PIR sensor integration
- DC motor-driver control
- PWM
- Finite-state-machine design
- Non-blocking embedded timing
- ESP32-CAM image acquisition
- Edge Impulse model deployment
- Embedded computer vision
- Hardware/software subsystem integration

The project also highlighted the importance of defining interfaces between mechanical, electrical, and software subsystems early in development.

Although the individual motor-control and vision prototypes were functional, integration became difficult because the subsystem interfaces and mechanical dependencies were not established early enough.

---

## Third-Party Software

The vision prototype uses software and examples provided by Edge Impulse.

The Edge Impulse camera inference sketch included in this repository retains its original copyright and license notice.

Generated Edge Impulse deployment libraries and model files are not redistributed here.

See [`THIRD_PARTY.md`](THIRD_PARTY.md) for additional information.

---

## Technologies

- C / C++
- ESP32-S3
- ESP32-CAM
- Arduino IDE
- HC-SR501 PIR Sensor
- PWM
- Finite-State Machines
- Edge Impulse
- Embedded Computer Vision
