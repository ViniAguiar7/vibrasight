# VibraSight

## Overview

VibraSight is a low-cost smart cane designed to help visually impaired people detect obstacles and improve mobility safety through haptic feedback and ultrasonic sensing.

The project was inspired by accessibility challenges commonly found in Brazilian urban environments, especially in cities like São Paulo, where public spaces, transportation systems, and sidewalks are often not fully adapted for visually impaired people.

Unlike traditional canes, VibraSight aims to detect not only ground-level obstacles, but also elevated objects such as signs, branches, and poorly positioned urban structures that may represent safety risks.

The system is based on affordable, accessible components, focusing on low-cost implementation without sacrificing usability or user autonomy.

---

## Project Status

Current stage: functional prototype under development and testing.

Current version: **V1.4**

---

## Problem Definition

Visually impaired people face a high risk of collisions during daily mobility, especially with obstacles positioned above the detection range of traditional canes. These collisions may cause injuries, falls, and reduced independence.

Although assistive technologies already exist, many solutions are financially inaccessible in the Brazilian context, often costing more than R$500. In addition, several devices rely mainly on audio alerts, which may become ineffective in noisy environments or uncomfortable for users who prefer tactile feedback.

This project aims to bridge the gap between accessibility, affordability, and safety by providing a practical, low-cost, and intuitive mobility assistance solution.

---

## Current Features

* Ultrasonic obstacle detection
* Detection of ground-level and elevated obstacles
* Haptic feedback using vibration motors
* Independent vibration control for each detection direction
* ESP32-based control system
* Non-blocking motor control using `millis()`
* Non-blocking ultrasonic measurement system
* Sequential ultrasonic sensor activation to reduce interference
* Low-cost hardware architecture

---

## Current Progress

* Functional three-sensor ultrasonic distance detection
* Distance-based haptic feedback logic
* Three independent vibration motor control
* Non-blocking motor timing using `millis()`
* Non-blocking ultrasonic measurement using `micros()`
* Sequential sensor measurement system
* Real-world hardware testing on ESP32

---

## V1.4

### Overview

VibraSight V1.4 improves the ultrasonic sensing system by replacing the blocking `pulseIn()` function with a non-blocking ultrasonic measurement system.

The main goal of this version was to improve the reliability of the three ultrasonic sensors and reduce possible interference between them.

### Hardware

| Component    | TRIG | ECHO | Motor |
| ------------ | ---: | ---: | ----: |
| Left sensor  |   D5 |  D18 |   D22 |
| Right sensor |  D19 |  D21 |   D23 |
| Top sensor   |  D32 |  D33 |   D25 |

### Main Changes

1. Replaced `pulseIn()` with a non-blocking Echo measurement system using `micros()`.

2. Added individual states for the ultrasonic measurement process.

3. Only one ultrasonic sensor is triggered at a time.

4. Added a short safety interval between sensor measurements to reduce possible ultrasonic interference.

5. Added a timeout for ultrasonic Echo measurements.

6. Kept independent `millis()` timers for the left, right, and top vibration motors.

7. Reduced Serial Monitor output frequency to avoid unnecessary processing.

### Ultrasonic Measurement System

The sensors are activated sequentially:

```text
LEFT
  ↓
RIGHT
  ↓
TOP
  ↓
LEFT
  ↓
RIGHT
  ↓
TOP
```

Each sensor goes through four states:

```text
WAITING_FOR_TRIGGER
        ↓
WAITING_FOR_ECHO_START
        ↓
WAITING_FOR_ECHO_END
        ↓
WAITING_FOR_NEXT_SENSOR
```

This allows the ESP32 to continue executing the motor control logic while waiting for ultrasonic measurements.

### Vibration System

The vibration motors use `millis()` instead of `delay()` for their timing.

The vibration behavior depends on the measured distance:

```text
> 70 cm
Motor OFF

30 to 70 cm
Slow vibration

10 to 30 cm
Fast vibration

≤ 10 cm
Continuous vibration
```

Each motor has its own timer and state, allowing the left, right, and top motors to operate independently.

### Problem Addressed

In previous versions, the three ultrasonic sensors could interfere with each other because their measurements were performed sequentially using blocking functions.

This could result in incorrect distance readings, especially when the sensors were physically close to each other.

V1.4 addresses this by controlling the sensors individually and adding a safety interval between measurements.

### Current Limitations

The current version still uses `delayMicroseconds(10)` to generate the short trigger pulse required by the HC-SR04. This delay is only 10 microseconds and does not significantly affect the overall system responsiveness.

The ultrasonic sensors can still potentially experience interference depending on their physical positioning and the environment.

Further improvements may include measurement filtering, sensor validation, improved vibration patterns, and additional power management.

---

## Future Improvements

* Measurement filtering and validation
* Smarter vibration feedback system
* Improved power management
* Motion-based power saving system using IMU sensors
* Modular architecture
* Compact and resistant enclosure
* Improved sensor positioning
* More extensive real-world testing

---

## Prototype

[image]

Current V1.4 prototype using an ESP32, three ultrasonic sensors, and three vibration motors.

---

## Development History

### V1.1

* Two ultrasonic sensors
* Two vibration motors
* Basic distance detection
* Initial haptic feedback system

### V1.2

* Two ultrasonic sensors
* Two vibration motors
* Replaced blocking vibration delays with `millis()`

### V1.3

* Added third ultrasonic sensor
* Added third vibration motor
* Added elevated obstacle detection
* Identified ultrasonic sensor interference

### V1.4

* Three ultrasonic sensors
* Three vibration motors
* Non-blocking ultrasonic measurement
* Sequential sensor activation
* Reduced ultrasonic interference
* Independent `millis()` motor control
* Improved system responsiveness
