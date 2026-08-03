# Water Level Indicator

![Arduino](https://img.shields.io/badge/Arduino-Uno-333333)
![C++](https://img.shields.io/badge/Language-C++-00534E)

An Arduino Uno project that detects water level using an **ultrasonic sensor (HC-SR04)**. When the water level is low (distance ≤ 10 cm from sensor), an **LED** on pin 13 turns on to indicate the water level is low.

---

## Description

This project uses an HC-SR04 ultrasonic sensor to measure the distance from the sensor to the water surface. When the distance is **10 cm or less** (indicating a low water level in a container), an LED on pin **13** activates. When the water level is sufficient (distance > 10 cm), the LED turns off. Distance readings are printed to the Serial Monitor for monitoring.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Main controller |
| Ultrasonic Sensor (HC-SR04) | 1 | Distance measurement |
| LED | 1 | Low water level indicator |
| 220 Ω Resistor | 1 | Current limiting for LED |
| Breadboard | 1 | For prototyping |
| Jumper wires | — | Male-to-male/male-to-female |

---

## Pin Connections

| Arduino Pin | Component | Notes |
|-------------|-----------|-------|
| **9** | HC-SR04 (Trig) | Ultrasonic trigger |
| **10** | HC-SR04 (Echo) | Ultrasonic echo |
| **13** | LED | Low water level indicator |
| **5V** | HC-SR04 (VCC) | Power |
| **GND** | HC-SR04 (GND), LED (−) | Common ground |

---

## How It Works

```cpp
const int trigPin = 9;    // HC-SR04 Trig on pin 9
const int echoPin = 10;   // HC-SR04 Echo on pin 10
const int ledPin = 13;    // LED on pin 13

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert to cm

  Serial.println(distance);

  if (distance <= 10) {
    digitalWrite(ledPin, HIGH);    // LED ON = low water
  } else {
    digitalWrite(ledPin, LOW);     // LED OFF = adequate water
  }

  delay(100);
}
```

1. **Ultrasonic measurement** — a 10 μs trigger pulse activates the HC-SR04, which emits an ultrasonic wave and measures the echo return time.
2. **Distance calculation** — `distance = duration × 0.034 / 2` converts time to centimeters.
3. **Water level check** — when distance ≤ 10 cm (water is low), the LED on pin 13 turns on.
4. **Serial monitoring** — the distance value is printed every 100 ms.

---

## Working Principle

| Distance (cm) | Condition | LED (Pin 13) | Status |
|---------------|-----------|-------------|--------|
| ≤ 10 | `distance <= 10` | ON | Low water level |
| > 10 | `distance > 10` | OFF | Adequate water level |

> **Note:** The sensor should be mounted above the water container. The distance reading increases as the water level decreases.

---

## Expected Output (Serial Monitor)

```
12
10
8
5
15
12
...
```

- **LED on (distance ≤ 10 cm):** Water level is low — refill needed.
- **LED off (distance > 10 cm):** Water level is adequate.

Distance readings update every 100 ms.

---

## File Structure

```
10-water-level-indicator/
├── README.md        ← This file
├── Water level indicator/
│   ├── code.ino     ← Arduino source code
│   ├── image.png    ← Setup photo
│   └── Recording .mp4 ← Demonstration video
```

---

## Installation & Usage

1. Mount the HC-SR04 above the water container (pointed downward).
2. Connect Trig → 9, Echo → 10, LED → 13.
3. Connect the Arduino Uno to your computer.
4. Open `code.ino` in Arduino IDE.
5. Select **Board → Arduino Uno** and the correct **Port**.
6. Click **Upload**.
7. Open **Serial Monitor** (Ctrl+Shift+M) at **9600 baud** to view distance readings.
8. Adjust the 10 cm threshold in the code to match your container size.

---

## Learning Outcomes

- ✅ Ultrasonic distance sensing (HC-SR04)
- ✅ `pulseIn()` for time-of-flight measurement
- ✅ Conditional actuator control (LED)
- ✅ Serial Monitor data logging
- ✅ Practical water level monitoring concept

---

## Future Improvements

- Add a buzzer for audible low-water alerts
- Display distance and water percentage on an LCD/OLED screen
- Add multiple threshold levels (low/medium/full) with different LED colors
- Use a floating switch as an alternative to ultrasonic sensing

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
