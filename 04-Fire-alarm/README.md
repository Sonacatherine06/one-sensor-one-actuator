# Fire Alarm System

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

An Arduino Uno project that monitors both **temperature** and **ambient light** using two analog sensors. An **LED** activates when temperature is high, and a **buzzer** activates when it's dark. Serial Monitor output provides real-time readings.

---

## Description

This project uses a **TMP36 temperature sensor** (A0) and an **LDR** (A1) to monitor environmental conditions:

- **Temperature monitoring:** When the raw analog reading from A0 exceeds 300, the LED (pin 13) turns on, indicating high temperature.
- **Light monitoring:** When the LDR reading from A1 is below 500, the buzzer (pin 8) activates, indicating low-light conditions.
- Both sensor readings are printed to the Serial Monitor at 9600 baud for debugging.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Main controller |
| TMP36 Temperature Sensor | 1 | Analog temperature sensor |
| LDR (Light Dependent Resistor) | 1 | Light sensor |
| LED | 1 | Temperature indicator |
| Buzzer (Active/Passive) | 1 | Light indicator |
| 220 Ω Resistor | 1 | Current limiting for LED |
| Breadboard | 1 | For prototyping |
| Jumper wires | — | Male-to-male/male-to-female |

---

## Pin Connections

| Arduino Pin | Component | Notes |
|-------------|-----------|-------|
| **A0** | TMP36 (Vout) | Temperature sensor input |
| **A1** | LDR | Light sensor input |
| **13** | LED | Temperature indicator |
| **8** | Buzzer | Light indicator |
| **5V** | TMP36 (VCC), LDR | Power |
| **GND** | All components | Common ground |

---

## How It Works

```cpp
int tempSensor = A0;    // TMP36 on analog pin A0
int ldrSensor = A1;     // LDR on analog pin A1
int led = 13;           // LED on digital pin 13
int buzzer = 8;         // Buzzer on digital pin 8

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int tempValue = analogRead(tempSensor);
  int lightValue = analogRead(ldrSensor);

  Serial.print("Temperature value: ");
  Serial.println(tempValue);
  Serial.print("Light value: ");
  Serial.println(lightValue);

  // LED on when temperature reading is high
  if (tempValue > 300) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  // Buzzer on when it's dark
  if (lightValue < 500) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}
```

1. **Dual sensor reading** — both the TMP36 (A0) and LDR (A1) are read using `analogRead()`, returning values from 0 to 1023.
2. **Temperature threshold** — when the raw ADC value from A0 exceeds 300, the LED on pin 13 is activated.
3. **Light threshold** — when the LDR reading from A1 is below 500, the buzzer on pin 8 is activated.
4. **Serial output** — both readings are logged every 500 ms for monitoring.

---

## Working Principle

| Sensor | Pin | Threshold | Actuator | Action |
|--------|-----|-----------|----------|--------|
| Temperature (TMP36) | A0 | raw > 300 | LED (13) | ON |
| Temperature (TMP36) | A0 | raw ≤ 300 | LED (13) | OFF |
| Light (LDR) | A1 | raw < 500 | Buzzer (8) | ON |
| Light (LDR) | A1 | raw ≥ 500 | Buzzer (8) | OFF |

---

## Expected Output (Serial Monitor)

```
Temperature value: 312
Light value: 450
Temperature value: 315
Light value: 448
...
```

- **LED (pin 13):** ON when temperature sensor value > 300 (adjust based on your environment)
- **Buzzer (pin 8):** ON when light sensor value < 500 (dark environment)

The readings update every 500 ms.

---

## File Structure

```
04-Fire-alarm/
├── README.md        ← This file
├── Fire alarm/
│   ├── code.ino     ← Arduino source code
│   ├── image.png    ← Setup photo
│   └── Recording.mp4 ← Demonstration video
```

---

## Installation & Usage

1. Connect the TMP36, LDR, LED, and buzzer as per the **Pin Connections** table.
2. Connect the Arduino Uno to your computer.
3. Open `code.ino` in Arduino IDE.
4. Select **Board → Arduino Uno** and the correct **Port**.
5. Click **Upload**.
6. Open **Serial Monitor** (Ctrl+Shift+M) at **9600 baud** to view sensor readings.

---

## Learning Outcomes

- ✅ Dual analog sensor reading
- ✅ Threshold-based actuator control
- ✅ Serial Monitor data logging
- ✅ Simultaneous independent sensor-actuator pairs
- ✅ TMP36 temperature sensor characteristics

---

## Future Improvements

- Convert raw ADC values to actual temperature (°C) and light percentage
- Add an LCD display for real-time readings
- Use a buzzer for temperature alerts instead of an LED
- Store threshold values in EEPROM

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
