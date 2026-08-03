# Smart Dustbin (Ultrasonic Bin)

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

An Arduino Uno project that automatically opens a dustbin lid using a **servo motor** when an object (hand) is detected by an **ultrasonic sensor (HC-SR04)**, and activates a **buzzer** in low-light conditions using an **LDR**.

---

## Description

This project combines two sensors with two actuators:

1. **Ultrasonic sensor (HC-SR04)** — measures distance. When an object is detected within **20 cm**, a servo motor opens the dustbin lid to **90°**. When the object moves away, the lid closes back to **0°**.
2. **LDR (Light Dependent Resistor)** — measures ambient light. When light is low (dark, reading `< 300`), a buzzer activates.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Main controller |
| Ultrasonic Sensor (HC-SR04) | 1 | Distance measurement |
| Servo Motor (SG90) | 1 | Lid actuator |
| LDR (Light Dependent Resistor) | 1 | Light sensor |
| Buzzer (Active/Passive) | 1 | Audio alert |
| 10 kΩ Resistor | 1 | LDR pull-down resistor |
| Breadboard | 1 | For prototyping |
| Jumper wires | — | Male-to-male/male-to-female |

---

## Pin Connections

| Arduino Pin | Component | Notes |
|-------------|-----------|-------|
| **7** | HC-SR04 (Trig) | Ultrasonic trigger signal |
| **6** | HC-SR04 (Echo) | Ultrasonic echo signal |
| **A0** | LDR | Analog light sensor input |
| **8** | Buzzer | Active buzzer output |
| **9** | Servo Motor | Servo signal wire (PWM) |
| **5V** | HC-SR04 (VCC), Servo (VCC) | Power |
| **GND** | All components | Common ground |

---

## How It Works

```cpp
#include <Servo.h>

Servo lid;
int trig = 7;       // HC-SR04 Trig
int echo = 6;       // HC-SR04 Echo
int ldr = A0;       // LDR analog input
int buzzer = 8;     // Buzzer output

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  lid.attach(9);    // Servo on pin 9
  lid.write(0);     // Lid initially closed
}

void loop() {
  // --- Ultrasonic distance measurement ---
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  int distance = duration * 0.034 / 2;  // Convert to cm

  // --- Open/close lid based on distance ---
  if (distance < 20) {
    lid.write(90);   // Open lid
  } else {
    lid.write(0);    // Close lid
  }

  // --- Light-dependent buzzer ---
  int light = analogRead(ldr);
  if (light < 300) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
}
```

1. **Ultrasonic measurement** — trigger pin sends a 10μs HIGH pulse, the sensor emits an ultrasonic wave and waits for the echo. `pulseIn()` measures the echo pulse duration.
2. **Distance calculation** — `distance = duration × 0.034 / 2` converts time to centimeters (sound speed = 340 m/s).
3. **Lid control** — if an object is within 20 cm, the servo opens the lid (90°); otherwise, it closes (0°).
4. **Buzzer control** — LDR value is read. When ambient light is low (< 300), the buzzer activates.

---

## Working Principle

| Sensor | Threshold | Actuator | Action |
|--------|-----------|----------|--------|
| Ultrasonic (HC-SR04) | distance < 20 cm | Servo motor | Lid opens (90°) |
| Ultrasonic (HC-SR04) | distance ≥ 20 cm | Servo motor | Lid closes (0°) |
| LDR | light < 300 | Buzzer | ON |
| LDR | light ≥ 300 | Buzzer | OFF |

---

## Expected Output

The system operates silently (no serial output). Behavior:

- **When you place your hand within 20 cm** of the ultrasonic sensor, the servo motor opens the dustbin lid.
- **When you remove your hand**, the lid closes automatically.
- **When it's dark** (LDR reading < 300), the buzzer sounds continuously.
- **When it's bright** (LDR reading ≥ 300), the buzzer is silent.

---

## File Structure

```
02-Smart-dustbin/
├── README.md        ← This file
├── Smart dustbin/
│   ├── code.ino     ← Arduino source code
│   ├── image.png    ← Setup photo
│   └── Recording.mp4 ← Demonstration video
```

---

## Installation & Usage

1. Connect all components as per the **Pin Connections** table.
2. Connect the Arduino Uno to your computer.
3. Install the **Servo** library via **Sketch → Include Library → Manage Libraries** (if not pre-installed).
4. Open `code.ino` in Arduino IDE.
5. Select **Board → Arduino Uno** and the correct **Port**.
6. Click **Upload** to flash the code.
7. Test by placing your hand near the ultrasonic sensor.

---

## Learning Outcomes

- ✅ Ultrasonic distance measurement with HC-SR04
- ✅ Servo motor position control (`Servo.h` library)
- ✅ Analog light sensing with LDR
- ✅ Multi-sensor actuation logic
- ✅ `pulseIn()` function for time measurement

---

## Future Improvements

- Add an LCD display showing distance and light readings
- Calibrate the LDR threshold with a potentiometer
- Replace the buzzer with an LED for night-light mode
- Add a delay before auto-closing the lid

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
