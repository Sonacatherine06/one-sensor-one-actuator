# Parking Distance Warning System

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

An Arduino Uno project that uses an **ultrasonic sensor (HC-SR04)** to measure the distance to nearby objects. When an object is detected within **10 cm**, a **buzzer** sounds to warn the driver during parking.

---

## Description

This project implements a parking distance warning system. An HC-SR04 ultrasonic sensor measures the distance to the nearest object. When the distance drops below 10 cm (indicating a close obstacle), a buzzer on pin **8** activates with a 1000 Hz tone. At distances of 10 cm or more, the buzzer is silent.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Main controller |
| Ultrasonic Sensor (HC-SR04) | 1 | Distance measurement |
| Buzzer (Active/Passive) | 1 | Audio warning |
| Breadboard | 1 | For prototyping |
| Jumper wires | — | Male-to-male/male-to-female |

---

## Pin Connections

| Arduino Pin | Component | Notes |
|-------------|-----------|-------|
| **9** | HC-SR04 (Trig) | Ultrasonic trigger signal |
| **10** | HC-SR04 (Echo) | Ultrasonic echo signal |
| **8** | Buzzer | Audio warning output |
| **5V** | HC-SR04 (VCC) | Power |
| **GND** | HC-SR04 (GND), Buzzer (−) | Common ground |

---

## How It Works

```cpp
const int trig = 9;    // HC-SR04 Trig on pin 9
const int echo = 10;   // HC-SR04 Echo on pin 10
const int buzzer = 8;  // Buzzer on pin 8

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  int distance = duration * 0.034 / 2;  // Convert to cm

  if (distance < 10)
    tone(buzzer, 1000);       // 1000 Hz tone
  else
    noTone(buzzer);           // No tone

  delay(100);
}
```

1. **Ultrasonic pulse** — a 10 μs HIGH pulse is sent to the Trig pin. The sensor emits an ultrasonic wave (40 kHz) and waits for the reflected echo.
2. **Echo measurement** — `pulseIn(echo, HIGH)` measures the duration of the echo pulse (time of flight).
3. **Distance calculation** — `distance = duration × 0.034 / 2` converts the time to centimeters (speed of sound ≈ 340 m/s).
4. **Buzzer control** — when the distance is less than 10 cm, `tone(8, 1000)` drives the buzzer at 1000 Hz. Otherwise, `noTone(8)` silences it.

---

## Working Principle

| Distance | Condition | Buzzer (Pin 8) |
|----------|-----------|----------------|
| < 10 cm | Object close | ON (1000 Hz tone) |
| ≥ 10 cm | Object far/none | OFF (silent) |

---

## Expected Output

The system does **not** output serial data. The buzzer behavior:

- **Object within 10 cm:** Buzzer emits a continuous 1000 Hz tone.
- **Object at 10+ cm:** Buzzer is silent.

The distance is measured and the buzzer state updated every **100 ms**.

---

## File Structure

```
08-Parking-distance/
├── README.md        ← This file
├── Parking distance/
│   ├── code.ino     ← Arduino source code
│   ├── Recording .mp4 ← Demonstration video
│   └── Screenshot 2026-07-30 021552.png ← Screenshot
```

---

## Installation & Usage

1. Wire the HC-SR04 (Trig → 9, Echo → 10) and buzzer (→ 8) as per the pin table.
2. Connect the Arduino Uno to your computer.
3. Open `code.ino` in Arduino IDE.
4. Select **Board → Arduino Uno** and the correct **Port**.
5. Click **Upload**.
6. Place an object within 10 cm of the sensor to hear the buzzer.

---

## Learning Outcomes

- ✅ Ultrasonic distance sensing (HC-SR04)
- ✅ `pulseIn()` function for time measurement
- ✅ Tone generation with `tone()` and `noTone()`
- ✅ Threshold-based alert system design
- ✅ Time-of-flight distance calculation

---

## Future Improvements

- Add an LED bar or buzzer that increases in frequency as the distance decreases
- Display the distance on an LCD or OLED screen
- Add a vibration motor for haptic feedback
- Use the system for rear-view parking assistance with multiple distance thresholds

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
