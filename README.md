# ESP32 Automation & Vision Prototype

An embedded-systems project exploring PIR-triggered DC motor control and embedded computer vision using ESP32 hardware.

The project was developed as two primary subsystems:
- An **ESP32-S3 motor-control prototype** using an HC-SR501 PIR motion sensor, PWM motor control, and finite-state-machine logic.
- An **ESP32-CAM vision prototype** using an Edge Impulse object-detection model trained to distinguish pens from pencils.

Both subsystems were tested independently. The intended mechanical conveyor assembly and final communication between the motor-control and vision subsystems were not completed during the project timeline.

---

## System Overview

### Motor-Control Subsystem
