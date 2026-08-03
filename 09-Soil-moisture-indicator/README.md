# Soil Moisture Indicator

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

An Arduino Uno project that detects soil moisture levels using a **soil moisture sensor** and actuates a **servo motor** to indicate whether the soil is dry or wet.

---

## Description

This project reads the analog value from a soil moisture sensor connected to pin **A0**. When the soil is dry (reading < 500), the servo motor on pin **9** moves to **90°** (indicating dry soil). When the soil is sufficiently moist (reading ≥ 500), the servo returns to **0°**. The moisture reading is also printed to the Serial Monitor for monitoring.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Main controller |
| Soil Moisture Sensor | 1 | Analog probe + module |
| Servo Motor (SG90) | 1 | Position indicator |
| Breadboard | 1 | For prototyping |
| Jumper wires | — | Male-to-male/male-to-female |

---

## Pin Connections

| Arduino Pin | Component | Notes |
|-------------|-----------|-------|
| **A0** | Soil Moisture Sensor (A0) | Analog moisture reading |
| **9** | Servo Motor | PWM signal for position control |
| **5V** | Soil Moisture Sensor (VCC) | Power |
| **GND** | All components | Common ground |

---

## How It Works

```cpp
#include <Servo.h>

Servo waterServo;
int soilSensor = A0;   // Soil moisture sensor on A0
int servoPin = 9;      // Servo on pin 9

void setup() {
  waterServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int moistureValue = analogRead(soilSensor);

  Serial.println(moistureValue);

  if (moistureValue < 500) {
    // Dry soil - move servo to indicate dry
    waterServo.write(90);
  } else {
    // Wet soil - return servo to rest
    waterServo.write(0);
  }

  delay(1000);
}
```

1. **Moisture reading** — `analogRead(A0)` returns a value from 0 (completely wet) to 1023 (completely dry), depending on the sensor module's behavior.
2. **Threshold check** — if the value is below 500, the soil is considered dry.
3. **Servo positioning** — the servo moves to 90° when dry, and 0° when wet, providing a visual indication.
4. **Serial output** — the raw moisture value is printed every 1 second.

---

## Working Principle

| Soil Condition | A0 Reading | Condition | Servo Position | Serial Output |
|----------------|------------|-----------|----------------|---------------|
| Dry | < 500 | `moistureValue < 500` | 90° | raw value |
| Wet | ≥ 500 | else | 0° | raw value |

> **Note:** Soil moisture sensor readings depend on soil type, probe depth, and corrosion. Calibrate the 500 threshold by testing with your specific soil conditions.

---

## Expected Output (Serial Monitor)

```
423
418
512
505
489
...
```

- **When soil is dry (reading < 500):** Servo moves to 90°, buzzer/LED would indicate dry.
- **When soil is wet (reading ≥ 500):** Servo returns to 0°.

Readings update every 1 second.

---

## File Structure

```
09-Soil-moisture-indicator/
├── README.md        ← This file
├── Soil Moisture indicator/
│   ├── code.ino     ← Arduino source code
│   ├── image.png    ← Setup photo
│   └── Recording .mp4 ← Demonstration video
```

---

## Installation & Usage

1. Insert the soil moisture probe into the soil.
2. Connect the servo to pin 9 and the moisture sensor to A0.
3. Connect the Arduino Uno to your computer.
4. Open `code.ino` in Arduino IDE.
5. Select **Board → Arduino Uno** and the correct **Port**.
6. Click **Upload**.
7. Open **Serial Monitor** (Ctrl+Shift+M) at **9600 baud** to view readings.

---

## Calibration

The threshold value of 500 may need adjustment based on:

- Soil type (clay, sand, loam)
- Probe insertion depth
- Sensor module characteristics

To calibrate:
1. Upload the code.
2. Open Serial Monitor.
3. Insert the probe into dry soil and note the reading.
4. Insert into wet soil and note the reading.
5. Set the threshold midway between the two values.

---

## Learning Outcomes

- ✅ Analog soil moisture sensor interfacing
- ✅ Servo motor position control (`Servo.h` library)
- ✅ Threshold-based actuator switching
- ✅ Serial Monitor data logging
- ✅ Sensor calibration fundamentals

---

## Future Improvements

- Add a water pump that automatically waters the plant when soil is dry
- Display the moisture percentage on an LCD/OLED screen
- Use multiple threshold levels (dry/wet/critical) for graduated alerts
- Add a potentiometer for adjustable threshold

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
