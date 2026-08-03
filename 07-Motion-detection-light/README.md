# Motion Detection Light

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

An Arduino Uno project that automatically turns on an **LED** when a **PIR motion sensor** detects movement. When no motion is detected, the LED turns off.

---

## Description

This is a simple motion-activated lighting system. A **PIR (Passive Infrared) sensor** connected to pin **2** detects infrared radiation from moving objects. When motion is detected, the sensor outputs `HIGH`, and the LED on pin **13** turns on. When motion stops, the LED turns off.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Main controller |
| PIR Motion Sensor | 1 | Detects infrared motion |
| LED | 1 | Lighting indicator |
| 220 Ω Resistor | 1 | Current limiting for LED |
| Breadboard | 1 | For prototyping |
| Jumper wires | — | Male-to-male/male-to-female |

---

## Pin Connections

| Arduino Pin | Component | Notes |
|-------------|-----------|-------|
| **2** | PIR Sensor (Out) | Digital motion detection input |
| **13** | LED | Motion indicator (built-in LED on most Arduinos) |
| **5V** | PIR Sensor (VCC) | Power |
| **GND** | PIR Sensor (GND), LED | Common ground |

> **Note:** Pin 13 has a built-in LED on the Arduino Uno board, so no external LED is strictly required for testing.

---

## How It Works

```cpp
int pir = 2;    // PIR sensor on digital pin 2
int led = 13;   // LED on digital pin 13

void setup() {
  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  if (digitalRead(pir) == HIGH) {
    digitalWrite(led, HIGH);   // LED ON when motion detected
  } else {
    digitalWrite(led, LOW);    // LED OFF when no motion
  }
}
```

1. **PIR sensor** — detects changes in infrared radiation emitted by moving objects. When motion is detected, the sensor outputs `HIGH`.
2. **LED control** — when the PIR output is `HIGH`, the LED is turned on. When the PIR output is `LOW`, the LED is turned off.

---

## Working Principle

| PIR Sensor (Pin 2) | LED (Pin 13) |
|---------------------|-------------|
| HIGH (motion detected) | ON |
| LOW (no motion) | OFF |

---

## Expected Output

The system does **not** output serial data. The LED on pin 13 (or an external LED) turns on immediately when motion is detected and turns off when motion stops.

- **During motion:** LED is ON.
- **After motion stops:** LED turns OFF (the PIR holds HIGH for a few seconds after motion, then returns LOW).

---

## File Structure

```
07-Motion-detection-light/
├── README.md        ← This file
├── Motion detection light/
│   ├── code.ino     ← Arduino source code
│   ├── image.png    ← Setup photo
│   └── Recording.mp4 ← Demonstration video
```

---

## Installation & Usage

1. Connect the PIR sensor to pin 2 and the LED to pin 13.
2. Connect the Arduino Uno to your computer.
3. Open `code.ino` in Arduino IDE.
4. Select **Board → Arduino Uno** and the correct **Port**.
5. Click **Upload**.
6. Move your hand in front of the PIR sensor to see the LED light up.

---

## Learning Outcomes

- ✅ PIR motion sensor interfacing
- ✅ Digital input reading (`digitalRead`)
- ✅ Digital output control (`digitalWrite`)
- ✅ Real-time sensor-to-actuator mapping
- ✅ Understanding PIR sensor behavior (hold time after detection)

---

## Future Improvements

- Add a delay so the LED stays on for N seconds after motion stops
- Replace the LED with a relay-controlled lamp
- Log motion events with timestamps to Serial Monitor
- Add a light-dependent enable (only activate at night)

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
