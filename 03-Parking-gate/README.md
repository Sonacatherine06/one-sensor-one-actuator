# 03 - Parking Gate

An automated parking gate system built for the **Arduino Uno** that combines an
**HC-SR04 ultrasonic distance sensor** with a **servo-actuated gate**. The gate
swings open to **90°** when a car is detected within **50 cm** *and* a push-button
is pressed, then returns to the closed (0°) position when the condition clears.
An LED indicator lights up while the gate is open.

## 📋 Project Overview

| Item | Detail |
| --- | --- |
| **Board** | Arduino Uno (AVR) |
| **Sensor** | HC-SR04 Ultrasonic Distance Sensor (`Trig=7`, `Echo=6`) |
| **Actuators** | SG90 Servo Motor (`D9`), LED Indicator (`D13`) |
| **Input** | Push-button (`D2`, `INPUT_PULLUP`) |
| **Repo** | `one-sensor-one-actuator` |

The Arduino continuously measures the distance to the nearest object in front of
the gate. The gate motor is driven by a standard servo connected to pin 9. Two
conditions must both be true for the gate to open:

1. The push-button is pressed (reads `LOW` via `INPUT_PULLUP`).
2. An object is within **50 cm** of the ultrasonic sensor.

When either condition is no longer met, the gate closes and the LED turns off.
Distance values are streamed to the Serial Monitor for debugging and observation.

---

## 🧩 Components Required

- Arduino Uno
- HC-SR04 Ultrasonic Distance Sensor
- SG90 Micro Servo Motor (or equivalent 5V hobby servo)
- Push-button (momentary, normally open)
- LED (built-in `D13` or external)
- Breadboard
- Jumper wires
- 220Ω resistor (for external LED, if used)

---

## 📐 Circuit Connections

| Component | Arduino Uno Pin | Notes |
| --- | --- | --- |
| HC-SR04 `VCC` | 5V | Power the sensor |
| HC-SR04 `GND` | GND | Common ground |
| HC-SR04 `Trig` | **D7** | Output — triggers the ultrasonic pulse |
| HC-SR04 `Echo` | **D6** | Input — receives the reflected pulse |
| Servo (Signal / Orange) | **D9** | PWM capable pin for `Servo.h` |
| Servo (Red / VCC) | 5V | Servo power |
| Servo (Black / GND) | GND | Servo ground |
| Push-button (one side) | **D2** | `INPUT_PULLUP` — other side to GND |
| LED (built-in) | **D13** | Indicator — lights when gate is open |

> **Note:** The push-button is wired with an internal **pull-up resistor**
> (`pinMode(buttonPin, INPUT_PULLUP)`), so it reads `LOW` when pressed and
> `HIGH` when released. No external resistor is needed for the button. The
> ultrasonic sensor's `Echo` pin can be connected directly to `D6` — the
> HC-SR04 outputs 5V logic which is safe for the Uno's digital inputs.

### ASCII Wiring Diagram

```
                    HC-SR04
                 ┌─────────────┐
   Arduino 5V ───┤ VCC         │
   Arduino GND ──┤ GND         │
         D7  ────┤ Trig        │
         D6  ────┤ Echo        │
                 └─────────────┘

       D2 ────┬──────────┐
              │   [Button]
              └──────────┤
                         └─ D2 (INPUT_PULLUP)

       D9 ──────────────── Servo Signal (Orange)
       5V ──────────────── Servo VCC (Red)
       GND ─────────────── Servo GND (Black)

       D13 ─────────────── LED (+)
        GND ────[220Ω] ──── LED (−)
```

---

## 💻 Code

The sketch lives at [`parking gate/code.ino`](parking%20gate/code.ino).

```cpp
#include <Servo.h>

Servo gate;

int trigPin = 7;
int echoPin = 6;
int buttonPin = 2;

int ledPin = 13;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);
  gate.attach(9);
  gate.write(0);

  Serial.begin(9600);
}

void loop() {

  // Ultrasonic measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Read pushbutton
  int buttonState = digitalRead(buttonPin);

  Serial.print("Distance: ");
  Serial.println(distance);

  // Button pressed AND vehicle is near
  if (buttonState == LOW && distance < 50) {

    gate.write(90);
    digitalWrite(ledPin, HIGH);

  } else {

    gate.write(0);
    digitalWrite(ledPin, LOW);

  }

  delay(100);
}
```

### Code Walkthrough

1. **Pin assignments** — the ultrasonic sensor's `Trig` is on `D7` and `Echo`
   on `D6`. The servo signal is on `D9` (a PWM pin), the push-button on `D2`
   with an internal pull-up, and the LED indicator on `D13`.
2. **`setup()`** — configures `Trig` as `OUTPUT`, `Echo` as `INPUT`, the button
   as `INPUT_PULLUP`, and the LED as `OUTPUT`. The servo is attached to pin 9
   and initialized to **0°** (closed position). Serial communication starts at
   **9600 baud**.
3. **`loop()`** — triggers the ultrasonic sensor, reads the echo pulse, and
   computes the distance in centimeters using the formula
   `distance = duration * 0.034 / 2` (sound speed ≈ 340 m/s).
4. The **distance** is printed to the Serial Monitor every iteration.
5. **Gate logic** — if the button is pressed (`LOW`) *and* the distance is less
   than **50 cm**, the servo turns to **90°** (gate open) and the LED turns on.
   Otherwise the servo returns to **0°** (gate closed) and the LED turns off.
6. A **100 ms delay** paces the loop, giving stable readings without jitter.

---

## ⚙️ How It Works

| Step | Action | Sensor Reading | Gate Position | LED | Serial Output |
| --- | --- | --- | --- | --- | --- |
| 1 | Trigger ultrasonic pulse | — | — | — | — |
| 2 | Measure echo duration | `duration` (µs) | — | — | — |
| 3 | Compute distance | `distance = duration × 0.034 / 2` | — | — | `Distance: <value>` |
| 4 | Read button state | `HIGH` (released) or `LOW` (pressed) | — | — | — |
| 5 | Evaluate condition | `buttonState == LOW && distance < 50` | — | — | — |
| 6a | If **true** | Both conditions met | **90°** (open) | **ON** | `Distance: <value>` |
| 6b | If **false** | One or both unmet | **0°** (closed) | **OFF** | `Distance: <value>` |

The HC-SR04 works by emitting a 40 kHz ultrasonic burst and listening for its
reflection. The time-of-flight is proportional to distance. The servo acts as
the gate actuator — at **0°** the gate bars entry (closed), and at **90°** the
gate lifts (open), allowing a vehicle to pass.

---

## 🎬 Demo

![Parking gate simulation screenshot](parking%20gate/tinker.png)

📹 [Watch the demonstration recording](parking%20gate/Recording%202026-07-29%20235713.mp4) — see the servo gate open when the button is pressed with a car detected within range, and close when the condition clears.

---

## 🔧 Setup Instructions

1. **Wire** the circuit exactly as shown in the connection table and ASCII
   diagram above.
2. Connect the Arduino Uno to your computer via USB.
3. Open the Arduino IDE and select **Tools → Board → Arduino AVR Boards →
   Arduino Uno**.
4. Select the correct **Port** under **Tools → Port**.
5. Install the **Servo** library if not already present (it ships with the
   Arduino IDE by default): **Sketch → Include Library → Manage Libraries...** —
   search for *Servo*.
6. Open [`parking gate/code.ino`](parking%20gate/code.ino) and click
   **Upload**.
7. Open the **Serial Monitor** (Ctrl + Shift + M) at **9600 baud** to view the
   live distance readings.

### Serial Monitor Output

```
Distance: 28
Distance: 12
Distance: 45
Distance: 67
Distance: 0
...
```

When the gate opens you'll see distance values drop below 50 while the button
is held; the servo swings to 90° and the LED on `D13` illuminates.

---

## 📁 Project Structure

```
03-Parking-gate/
├── README.md                          # This file
└── parking gate/
    ├── code.ino                       # Arduino sketch
    ├── tinker.png                     # Wiring / simulation screenshot
    └── Recording 2026-07-29 235713.mp4  # Demonstration video
```

---

## 🛠️ Troubleshooting

| Symptom | Check |
| --- | --- |
| Servo doesn't move | Verify the servo is powered (5V/GND), the signal wire is on `D9`, and `gate.attach(9)` is called in `setup()`. Test with `gate.write(90)` in a simple sketch. |
| Distance always reads 0 or 999 | Check that `Trig` is on `D7` and `Echo` on `D6`. Ensure the HC-SR04 is powered (5V/GND). An `Echo` reading of 0 may indicate the sensor isn't detecting a reflection. |
| Button has no effect | Confirm the button is wired with one side to `D2` and the other to `GND`. The internal pull-up means it should read `HIGH` when open. |
| LED stays off | The built-in `D13` LED should light when the gate opens. If using an external LED, check polarity and the 220Ω resistor. |
| Servo jitters / resets | The servo may be drawing too much current from the Uno's 5V regulator. Power the servo from an external 5V supply and share a common ground. |

---

## ✅ Learning Outcomes

- Using the Arduino **`Servo.h`** library to control a hobby servo by angle
- Reading distance with an **HC-SR04 ultrasonic sensor** (pulse trigger + echo
  timing)
- Using **`INPUT_PULLUP`** for a momentary push-button without an external
  resistor
- Combining **sensor + actuator** logic with **compound conditions** (`&&`)
- Serial monitor debugging with `Serial.print()` / `Serial.println()`

---