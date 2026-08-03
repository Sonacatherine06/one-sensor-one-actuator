# Security Alarm System

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

An Arduino Uno project that triggers a **security alarm** (LED + buzzer) when motion is detected by a **PIR sensor** or when a **push button** is manually pressed.

---

## Description

This project implements a dual-trigger security alarm:

- **PIR Motion Sensor (pin 2):** Detects infrared radiation from moving objects.
- **Push Button (pin 3):** Manual trigger with an internal pull-up resistor.
- **Alarm (LED on pin 13 + buzzer on pin 8):** Activates when EITHER the PIR detects motion OR the button is pressed.

The alarm logic uses an OR condition — any single trigger activates the alarm.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Main controller |
| PIR Motion Sensor | 1 | Detects infrared motion |
| Push Button | 1 | Manual trigger |
| LED | 1 | Visual alarm indicator |
| Buzzer (Active/Passive) | 1 | Audio alarm |
| 220 Ω Resistor | 1 | Current limiting for LED |
| Breadboard | 1 | For prototyping |
| Jumper wires | — | Male-to-male/male-to-female |

---

## Pin Connections

| Arduino Pin | Component | Notes |
|-------------|-----------|-------|
| **2** | PIR Sensor (Out) | Motion detection input |
| **3** | Push Button | Manual trigger (INPUT_PULLUP) |
| **13** | LED | Visual alarm indicator |
| **8** | Buzzer | Audio alarm |
| **5V** | PIR (VCC), Button | Power |
| **GND** | All components | Common ground |

---

## How It Works

```cpp
int pir = 2;           // PIR sensor on digital pin 2
int button = 3;       // Push button on digital pin 3 (INPUT_PULLUP)
int led = 13;         // LED on digital pin 13
int buzzer = 8;       // Buzzer on digital pin 8

void setup() {
  pinMode(pir, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int motion = digitalRead(pir);
  int buttonState = digitalRead(button);

  if (motion == HIGH || buttonState == LOW) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }
}
```

1. **PIR sensor** — detects motion by sensing changes in infrared radiation. When motion is detected, the sensor outputs `HIGH`.
2. **Push button** — wired with an internal pull-up resistor. Reads `LOW` when pressed, `HIGH` when released.
3. **OR logic** — the alarm activates if EITHER the PIR detects motion OR the button is pressed.
4. **Actuator activation** — both the LED (pin 13) and buzzer (pin 8) turn on simultaneously when the alarm is triggered.

---

## Working Principle

| PIR State | Button State | LED (13) | Buzzer (8) |
|-----------|-------------|----------|------------|
| No motion (LOW) | Released (HIGH) | OFF | OFF |
| No motion (LOW) | Pressed (LOW) | ON | ON |
| Motion (HIGH) | Released (HIGH) | ON | ON |
| Motion (HIGH) | Pressed (LOW) | ON | ON |

---

## Expected Output

The system does **not** output serial data. The alarm (LED + buzzer) activates immediately when:

- The PIR sensor detects motion (output goes HIGH), **OR**
- The push button is pressed (output goes LOW)

When neither condition is met, both the LED and buzzer turn off.

---

## File Structure

```
05-Security-alarm/
├── README.md        ← This file
├── code.ino         ← Arduino source code
├── image.png        ← Setup photo
└── Recording.mp4    ← Demonstration video
```

---

## Installation & Usage

1. Wire the PIR sensor, push button, LED, and buzzer as per the pin table.
2. Connect the Arduino Uno to your computer.
3. Open `code.ino` in Arduino IDE.
4. Select **Board → Arduino Uno** and the correct **Port**.
5. Click **Upload**.
6. Test by waving your hand in front of the PIR sensor or pressing the button.

---

## Learning Outcomes

- ✅ PIR motion sensor interfacing
- ✅ Push button input with internal pull-up resistor
- ✅ OR logic for multi-trigger alarm systems
- ✅ Simultaneous control of visual (LED) and audio (buzzer) outputs
- ✅ Input pin configuration (`INPUT` vs `INPUT_PULLUP`)

---

## Future Improvements

- Add a delay/timer for the alarm to stay on for a set duration
- Log alarm events with timestamps to Serial Monitor
- Add a siren sound pattern instead of continuous buzzer
- Implement a keypad-based disarm system

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
