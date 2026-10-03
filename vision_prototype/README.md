# ESP32-CAM Vision Prototype

This subsystem explored embedded object detection using an ESP32-CAM
and a model trained through Edge Impulse.

## What was completed

- Collected/labeled pen and pencil image data
- Trained a two-class object-detection model in Edge Impulse
- Exported the model for embedded inference
- Tested ESP32-CAM image capture and pen/pencil inference

## Intended integration

Presence detected
→ Motor runs/stops
→ ESP32-CAM captures image
→ ML inference
→ Pen/pencil detection

The motor-control and vision subsystems were tested independently.
Final communication between the two subsystems was not completed.

## Third-party software

`edge_impulse_camera_inference.ino` is based on the Edge Impulse
Arduino camera inference example and retains its original license notice.

The generated Edge Impulse deployment SDK/model files are not
redistributed in this repository.
