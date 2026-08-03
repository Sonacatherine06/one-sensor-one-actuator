# Gas Leak Alarm System

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

An Arduino Uno project that detects gas leaks using an **analog gas sensor (MQ series)** and triggers a **buzzer** when the gas concentration exceeds a threshold value of 400.

---

## Description

This project continuously monitors air quality using an analog gas sensor (such as MQ-2 or MQ-3) connected to pin **A0**. The sensor's analog output is read by the Arduino's ADC. When the reading exceeds **400** (indicating dangerous gas levels), a buzzer connected to pin **8** is activated. All readings are also printed to the Serial Monitor for monitoring.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Main controller |
| Gas Sensor (MQ-2/MQ-3) | 1 | Analog gas sensor module |
| Buzzer (Active/Passive) | 1 | Audio alarm |
| Breadboard | 1 | For prototyping |
| Jumper wires | — | Male-to-male/male-to-female |

---

## Pin Connections

| Arduino Pin | Component | Notes |
|-------------|-----------|-------|
| **A0** | Gas Sensor (A0) | Analog gas concentration reading |
| **8** | Buzzer | Audio alarm output |
| **5V** | Gas Sensor (VCC) | Power for sensor heating element |
| **GND** | Gas Sensor (GND), Buzzer (−) | Common ground |

---

## How It Works

```cpp
int gasSensor = A0;   // Gas sensor analog output on A0
int buzzer = 8;       // Buzzer on digital pin 8

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(gasSensor);
  Serial.println(gasValue);

  if (gasValue > 400) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
  delay(200);
}
```

1. **Gas sensing** — the MQ sensor continuously draws current through its heating element and outputs an analog voltage proportional to gas concentration.
2. **ADC conversion** — `analogRead(A0)` converts the sensor voltage to a digital value (0–1023).
3. **Threshold check** — if the reading exceeds 400, the buzzer is activated.
4. **Serial monitoring** — the raw sensor value is printed every 200 ms.

---

## Working Principle

| Gas Level (A0 reading) | Condition | Buzzer (Pin 8) |
|------------------------|-----------|----------------|
| 0–400 | Normal / No gas | OFF |
| > 400 | Gas detected | ON |

The threshold of 400 can be adjusted based on the specific gas sensor and environmental conditions. The value should be calibrated during initial setup by noting the baseline reading in clean air.

---

## Expected Output (Serial Monitor)

```
382
395
412
428
450
...
```

When the gas sensor value exceeds 400:

```
450   ← Buzzer ON
512   ← Buzzer ON
480   ← Buzzer ON
395   ← Buzzer OFF (below threshold)
```

The readings update every 200 ms. The buzzer activates immediately when the threshold is exceeded.

---

## File Structure

```
06-Gas-leak-alarm/
├── README.md        ← This file
├── Gas leak alarm/
│   ├── code.ino     ← Arduino source code
│   ├── image.png    ← Setup photo
│   └── Recording .mp4 ← Demonstration video
```

---

## Installation & Usage

1. Connect the gas sensor to A0 and the buzzer to pin 8.
2. Connect the Arduino Uno to your computer.
3. Open `code.ino` in Arduino IDE.
4. Select **Board → Arduino Uno** and the correct **Port**.
5. Click **Upload**.
6. Open **Serial Monitor** (Ctrl+Shift+M) at **9600 baud** to monitor gas readings.
7. Apply gas (e.g., from an alcohol wipe or butane lighter) near the sensor to trigger the alarm.

---

## Calibration

The threshold value of 400 may need adjustment based on:
- Sensor type (MQ-2 for flammable gases, MQ-3 for alcohol, etc.)
- Ambient temperature and humidity
- Heating time (MQ sensors require 20–60 seconds of preheat)

To calibrate:
1. Upload the code.
2. Open Serial Monitor.
3. Note the baseline reading in clean air.
4. Set the threshold ~50–100 units above the baseline.

---

## Learning Outcomes

- ✅ Analog gas sensor interfacing (MQ series)
- ✅ Threshold-based alarm triggering
- ✅ Serial Monitor data logging for sensor readings
- ✅ Buzzer control with conditional logic

---

## Future Improvements

- Add an LCD or OLED display for real-time gas concentration
- Implement a moving-average filter to reduce noise
- Add a relay to control a ventilation fan automatically
- Use a digital gas sensor (MQ-2 with digital output) for simpler threshold detection

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
