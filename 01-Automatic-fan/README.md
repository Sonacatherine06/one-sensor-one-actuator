# Automatic Fan

A temperature-controlled **DC fan** (or motor) project built for the **Arduino Uno**. A **TMP36** analog temperature sensor on `A0` reads the ambient temperature; whenever it rises above **30 °C** the fan on **pin 9** switches on, otherwise it stays off. The sketch contains no serial output — it is a pure sensor-to-actuator loop.

| Item | Detail |
| --- | --- |
| **Board** | Arduino Uno (AVR) |
| **Sensor** | TMP36 analog temperature sensor (`A0`) |
| **Actuator** | DC motor / fan (`D9`) |
| **Repo** | `one-sensor-one-actuator` |

---

## Demo

![Automatic fan wiring and breadboard layout](Automatic%20fan/image.png)

📹 [Watch the demonstration recording](Automatic%20fan/Recording.mp4) — observe the fan switch on when the temperature exceeds 30 °C.

---

## How It Works

The Arduino continuously samples the TMP36 every **500 ms** and converts the raw analog reading into a temperature in degrees Celsius using the sensor's linear transfer function:

> **TMP36 formula:** 500 mV at 0 °C, 10 mV / °C
>
> ```
> voltage  = reading × (5.0 / 1023.0)     // analog reading → volts
> temp(°C) = (voltage − 0.5) × 100          // 0.5 V offset, 10 mV/°C
> ```

| Reading | Action | Motor (D9) |
| --- | --- | --- |
| `temp > 30` | Fan turns **ON** | `HIGH` |
| `temp ≤ 30` | Fan stays **OFF** | `LOW` |

The logic runs in an infinite `loop()` paced by a 500 ms `delay()`. **No serial output** is produced — the sketch is a self-contained sensor→actuator controller ideal for a standalone enclosure.

---

## Components Required

| Qty | Component | Notes |
| --- | --- | --- |
| 1 | Arduino Uno (or compatible AVR board) | Development board |
| 1 | TMP36 / analog temperature sensor (3-pin) | Connected to `A0` |
| 1 | DC motor, fan, or small 5 V brushless fan | Driven on `D9` |
| 1 | NPN transistor (2N2222 / BC547 / BC337) | Switches the motor on/off |
| 1 | 1 kΩ resistor | Base resistor for the transistor |
| 1 | Flyback diode (1N4007 / 1N4004) | Protects against motor back-EMF |
| 1 | Breadboard + jumper wires | For prototyping |

> **Motor driver note:** Arduino pins can source only ~20 mA. A small fan or motor must be switched through an **NPN transistor** (low-side switching). The flyback diode across the motor terminals is essential to suppress the inductive kick when the motor turns off.

---

## Wiring / Circuit Connections

| Component | Arduino Pin |
| --- | --- |
| TMP36 `VCC` (pin 1) | `5V` |
| TMP36 `GND` (pin 3) | `GND` |
| TMP36 `OUT` (pin 2) | `A0` |
| Motor — (red / +) | `5V` (or external 5 V supply) |
| Motor + (black / −) | Transistor **Collector** |
| Transistor **Base** | `D9` (via 1 kΩ resistor) |
| Transistor **Emitter** | `GND` |
| Diode — (striped end) | Motor + side / `5V` |
| Diode + (non-striped) | Motor − side / Transistor Collector |

### ASCII Wiring Diagram

```
                ┌───────────────────── TMP36 ─────────────────────┐
   5V ───────────┤ VCC (1)          OUT (2) ──────── A0           │
                └────────────────── GND (3) ──────── GND          │
                                                                    │
   5V ──── Motor (+)   Motor (−) ──── Transistor Collector         │
                             │           │                          │
                             │    ┌──────┴──────┐                  │
                             │    │   1N4007    │                  │
                             │    │  (flyback)  │                  │
                             │    └──────┬──────┘                  │
                             │           │                          │
                       Transistor Base   │                          │
                        (2N2222)         │                          │
                          │              │                         │
  D9 ───── 1 kΩ ───────────┴───► Base   Emitter ───────── GND    │
                                                                    │
                                                                   │
                                                   (Reference only)│
```

> The actual breadboard layout may differ from this simplified diagram. Refer to [`image.png`](Automatic%20fan/image.png) for the physical wiring used in the demonstration.

---

## Code

The sketch lives in [`Automatic fan/code.ino`](Automatic%20fan/code.ino).

```cpp
int tempPin = A0;
int motor = 9;

void setup() {
  pinMode(motor, OUTPUT);
}

void loop() {
  int value = analogRead(tempPin);
  float voltage = value * 5.0 / 1023.0;
  float temp = (voltage - 0.5) * 100;

  if (temp > 30)
    digitalWrite(motor, HIGH);
  else
    digitalWrite(motor, LOW);

  delay(500);
}
```

### Code Walkthrough

1. **Pin assignments** — `tempPin = A0` reads the TMP36 output; `motor = 9` controls the transistor that switches the fan.
2. **`setup()`** — configures the motor pin as a digital `OUTPUT`. No `Serial.begin()` because there is no serial logging.
3. **`loop()`** — the core sensor→actuator logic:
   - `analogRead(tempPin)` returns a 0–1023 value proportional to the sensor voltage.
   - `voltage = value * 5.0 / 1023.0` converts the reading to volts (assuming a 5 V supply).
   - `temp = (voltage - 0.5) * 100` applies the TMP36 formula: subtract the 500 mV zero-scale offset and scale by 10 mV/°C.
   - `if (temp > 30)` turns the motor **on**; otherwise it turns **off**.
   - `delay(500)` paces the loop at 500 ms.

---

## Getting Started

1. **Wire** the circuit exactly as shown in the connection table above (TMP36 → `A0`, motor through a transistor on `D9`).
2. Open [`Automatic fan/code.ino`](Automatic%20fan/code.ino) in the **Arduino IDE**.
3. Select **Tools → Board → Arduino AVR Boards → Arduino Uno**.
4. Select the correct **Port**.
5. Click **Upload**.
6. Apply power or warm the TMP36 above 30 °C — the fan should start spinning. Cool it below 30 °C and the fan stops.

> **Tip:** Because there is no serial output, use a multimeter or an external thermometer to verify the TMP36 voltage and confirm the fan responds around the 30 °C threshold.

---

## Threshold Tuning

The temperature threshold is a plain float comparison on a single line:

| Parameter | Line | Default | Description |
| --- | --- | --- | --- |
| `temp > 30` | `if (temp > 30)` | 30 | Temperature in °C above which the fan turns on |

- Lower the value (e.g. `> 25`) for a more sensitive, always-on-at-room-temp response.
- Raise the value (e.g. `> 35`) for a higher trigger point in hot environments.
- The 500 ms loop delay is set by `delay(500)` at the end of `loop()`.

---

## Project Structure

```
01-Automatic-fan/
├── README.md                # This file
└── Automatic fan/
    ├── code.ino             # Arduino sketch
    ├── image.png            # Wiring / breadboard photo
    └── Recording.mp4        # Demonstration video
```

---

## Troubleshooting

| Symptom | Check |
| --- | --- |
| Fan never turns on | Is the temperature actually above 30 °C? Measure the TMP36 voltage — 30 °C ≈ 0.8 V. |
| Fan runs constantly | Confirm the TMP36 `OUT` goes to `A0`, not a digital pin. Check the `temp > 30` comparison. |
| Fan is weak / doesn't spin | Verify the transistor orientation (Collector / Base / Emitter). The motor needs enough voltage and current — measure the supply. |
| Transistor gets very hot | The motor may draw too much current; add a heatsink or use a relay / motor driver module instead. |
| Temperature reads wrong | Make sure the TMP36 is powered by a stable 5 V. A noisy or sagging supply throws off the conversion. |

---

## License

This project is part of the **one-sensor-one-actuator** repository, licensed under the MIT License.
