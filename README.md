# One Sensor One Actuator

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

A collection of 10 Arduino Uno projects, each demonstrating a **one-sensor-to-one-actuator** relationship. Every project pairs a single sensor input with a single actuator output, covering a range of common electronic components and sensing principles.

---

## Repository Overview

| # | Project | Sensor | Actuator | Key Pins |
|---|---------|--------|----------|----------|
| 01 | [Automatic Fan](01-Automatic-fan/) | Temperature (TMP36, A0) | DC Motor (pin 9) | A0, 9 |
| 02 | [Smart Dustbin](02-Smart-dustbin/) | Ultrasonic (HC-SR04) + LDR (A0) | Servo + Buzzer | 7, 6, A0, 8, 9 |
| 03 | [Parking Gate](03-Parking-gate/) | Ultrasonic (HC-SR04) + Button | Servo + LED | 7, 6, 2, 13, 9 |
| 04 | [Fire Alarm](04-Fire-alarm/) | Temperature (A0) + LDR (A1) | LED (13) + Buzzer (8) | A0, A1, 13, 8 |
| 05 | [Security Alarm](05-Security-alarm/) | PIR + Push Button | LED (13) + Buzzer (8) | 2, 3, 13, 8 |
| 06 | [Gas Leak Alarm](06-Gas-leak-alarm/) | Gas Sensor (A0) | Buzzer (8) | A0, 8 |
| 07 | [Motion Detection Light](07-Motion-detection-light/) | PIR | LED (13) | 2, 13 |
| 08 | [Parking Distance](08-Parking-distance/) | Ultrasonic (HC-SR04) | Buzzer (8) | 9, 10, 8 |
| 09 | [Soil Moisture Indicator](09-Soil-moisture-indicator/) | Soil Moisture (A0) | Servo (9) | A0, 9 |
| 10 | [Water Level Indicator](10-water-level-indicator/) | Ultrasonic (HC-SR04) | LED (13) | 9, 10, 13 |

---

## Technologies Used

- **Language:** C++
- **Framework:** Arduino Uno (AVR)
- **IDE:** Arduino IDE (or PlatformIO)
- **Libraries:** `Servo.h` (for servo motor projects)

---

## Hardware Requirements

| Component | Quantity | Projects |
|-----------|----------|----------|
| Arduino Uno | 1 | All |
| Breadboard | 1+ | All |
| Jumper wires | 20+ | All |
| USB cable | 1 | All |
| TMP36 Temperature Sensor | 1 | 01, 04 |
| Servo Motor (SG90) | 1 | 02, 03, 09 |
| DC Motor | 1 | 01 |
| HC-SR04 Ultrasonic Sensor | 1 | 02, 03, 08, 10 |
| LDR (Light Dependent Resistor) | 1 | 02, 04 |
| Push Button | 1 | 03, 05 |
| PIR Motion Sensor | 1 | 05, 07 |
| Gas Sensor (MQ) | 1 | 06 |
| Piezo Buzzer | 1 | 02, 04, 05, 06, 08 |
| LED | 2+ | 01, 03, 04, 07, 10 |
| 220–330 Ω Resistors | 5+ | Projects with LEDs |
| Potentiometer (10kΩ) | 1 | (for calibration) |

---

## Installation

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Connect your Arduino Uno to your computer via USB.
3. Select **Tools → Board → Arduino AVR Boards → Arduino Uno**.
4. Select the correct **Tools → Port**.
5. Open the project folder of your choice and open the `code.ino` file.

---

## Usage

Each project folder contains:
- `code.ino` — the Arduino source code
- `image.png` — a photo of the circuit or setup
- `Recording.mp4` (where available) — a demonstration video

Upload the `code.ino` file to your Arduino Uno and observe the sensor-actuator interaction.

---

## Learning Outcomes

Through these 10 projects, you will learn:

- Analog sensor reading (`analogRead`)
- Digital sensor reading (`digitalRead`)
- Ultrasonic distance measurement (`pulseIn`)
- Temperature sensing with TMP36
- Servo motor control (`Servo.h`)
- Buzzer tone generation (`tone`, `noTone`)
- LED control and PWM (`analogWrite`)
- PIR motion detection
- Button input with pull-up resistors
- Sensor fusion (multiple sensors → single actuator)

---

## License

This repository is licensed under the MIT License.
