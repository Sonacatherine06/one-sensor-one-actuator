# Security Alarm

![Arduino](https://img.shields.io/badge/Arduino-Uno-009737)
![Wokwi](https://img.shields.io/badge/Wokwi-Simulation-000000)

An **Arduino Uno** project that turns a PIR motion sensor and a manual panic button into a simple **security alarm**. Whenever motion is detected **or** the button is pressed, a warning **LED** and a **buzzer** are activated simultaneously.

---

## Description

This project implements a basic intrusion-detection alarm using a **one-sensor-one-actuator** design. A passive infrared (PIR) sensor watches for motion while a normally-open push button acts as a manual trigger/panic button. When either input is activated, an LED and a buzzer turn on to raise the alarm. The system continuously polls both inputs and drives both actuators in lock-step, so the alarm is triggered by *either* condition (`OR` logic).

---

## How It Works

```cpp
int motion      = digitalRead(pir);        // PIR output HIGH = motion detected
int buttonState = digitalRead(button);     // Button wired to GND -> LOW when pressed (INPUT_PULLUP)

if (motion == HIGH || buttonState == LOW) {
  digitalWrite(led,    HIGH);             // Alarm LED ON
  digitalWrite(buzzer,  HIGH);             // Buzzer ON
} else {
  digitalWrite(led,    LOW);              // LED OFF
  digitalWrite(buzzer,  LOW);             // Buzzer OFF
}
```

The alarm is raised whenever **motion is detected** (`motion == HIGH`) **or** the **button is pressed** (`buttonState == LOW`). Both actuators are driven together so the visual (LED) and audible (buzzer) alerts always appear in sync.

---

## Working Principle

| Step | Input Status | `motion` | `buttonState` | `LED (13)` | `Buzzer (8)` | Alarm? |
|------|--------------|----------|---------------|------------|--------------|--------|
| 1 | No motion, button idle | LOW | HIGH | LOW | LOW | ❌ Off |
| 2 | Motion detected | HIGH | HIGH | HIGH | HIGH | ✅ On |
| 3 | Button pressed (idle sensor) | LOW | LOW | HIGH | HIGH | ✅ On |
| 4 | Both triggered | HIGH | LOW | HIGH | HIGH | ✅ On |

> **Logic:** `Alarm = motion OR (NOT button)` — i.e. active when *either* the PIR reports motion *or* the active-low button is pressed.

---

## Pin Connections

| Arduino Uno Pin | Component | Mode | Notes |
|-----------------|-----------|------|-------|
| **Digital 2** | PIR Sensor (OUT) | INPUT | HIGH when motion detected |
| **Digital 3** | Push Button (one terminal) | INPUT_PULLUP | LOW when pressed; other terminal → GND |
| **Digital 8** | Buzzer (+) | OUTPUT | Active buzzer, other terminal → GND |
| **Digital 13** | LED (built-in LED) | OUTPUT | On-board LED used directly |
| **5V** | PIR VCC / Button — | POWER | PIR sensor supply |
| **GND** | PIR GND / Button / Buzzer (−) | GROUND | Common ground |

### Wiring Summary

```
Arduino Uno          Components
----------           ----------

 5V      ──────────  PIR VCC
 2       ──────────  PIR OUT
 GND     ──────────  PIR GND

 3       ──────────  Button (one side)
 GND     ──────────  Button (other side)   ← INPUT_PULLUP

 8       ──────────  Buzzer (+)
 GND     ──────────  Buzzer (−)

 13      ──────────  Built-in LED (on-board)
```

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno (ATmega328P) | 1 | Microcontroller board |
| PIR Motion Sensor (HC-SR501 type) | 1 | Passive infrared, digital output |
| Push Button (Tactile, 4-pin) | 1 | Manual panic trigger |
| Buzzer (Active) | 1 | Common 5V active buzzer module |
| LED | 1 | Or use the on-board LED (pin 13) built into the Uno |
| Breadboard | 1 | For prototyping |
| Jumper wires | 8+ | Male-to-male and/or male-to-female |
| USB cable | 1 | For flashing and power |

---

## File Structure

```
05-Security-alarm/
├── README.md        ← This file
├── code.ino         ← Arduino source code (C++)
└── image.png        ← Circuit diagram / simulation screenshot
```

---

## Installation & Running

### Prerequisites

- Arduino IDE 1.x or the Arduino CLI
- Arduino Uno (or a compatible AVR board)
- A micro-USB cable

### Steps

1. Open **Arduino IDE**.
2. Open `code.ino` (`File → Open`).
3. Select your board and port:
   - `Tools → Board → Arduino AVR Boards → Arduino Uno`
   - `Tools → Port → COMxx` (your Arduino's port)
4. Click **Upload** (⬆️).

### Wokwi Simulation

This project can be simulated in [Wokwi for Arduino](https://wokwi.com/projects/new/arduino-uno):

1. Open https://wokwi.org/projects/new/arduino-uno
2. Paste the contents of `code.ino` into the editor
3. Add parts from the Parts List and wire them as below:

| Part | Pin on Part | Connect to |
|------|-------------|------------|
| PIR Motion Sensor | VCC | `5V` |
| PIR Motion Sensor | GND | `GND` |
| PIR Motion Sensor | OUT | `2` |
| Button | Pin 1 (either side) | `3` |
| Button | Pin 2 (either side) | `GND` |
| Active Buzzer | + | `8` |
| Active Buzzer | − | `GND` |
| LED | + (with 220Ω resistor) | `13` |
| LED | − | `GND` |

4. Click **Start Simulation** — trigger motion or press the button to sound the alarm.

---

## Expected Output

This project has **no serial output**; it is purely hardware-driven. The observed behavior is:

- **PIR detects motion** → the **LED turns ON** and the **buzzer sounds**.
- **Button is pressed** → the **LED turns ON** and the **buzzer sounds**.
- **No motion and button idle** → the **LED turns OFF** and the **buzzer is silent**.

Both the LED and buzzer respond simultaneously — there is no separate visual/audio indication; they always act as a single combined alarm.

---

## Learning Outcomes

- ✅ Digital input from a **PIR motion sensor** (`digitalRead`, `INPUT`)
- ✅ **Active-low** button logic with `INPUT_PULLUP`
- ✅ Driving **multiple outputs** (LED + buzzer) from a single condition
- ✅ Boolean **OR** logic for combining sensor and manual inputs
- ✅ Arduino `setup()` / `loop()` structure and GPIO configuration with `pinMode`/`digitalWrite`
- ✅ Building a practical **security-alarm** circuit on a breadboard

---

## Future Improvements

- Add an **LCD/OLED display** or **serial logging** to report trigger events and a trigger count
- Distinguish the trigger source (motion vs. button) so the LED and buzzer can behave differently
- Add a **timeout/snooze** mechanism to automatically silence the alarm after N seconds
- Integrate a **relay** to switch a higher-power siren or flood light
- Add a **debounce** routine for the button (software or hardware) for clean triggering
- Use **interrupts** (`attachInterrupt`) on the PIR to react instantly to motion edges

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
