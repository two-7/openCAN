# OpenCAN

**OpenCAN** is a 32-bit embedded system firmware project designed for CAN bus control, monitoring, and manipulation. It supports a range of real-time vehicle data applications and is open-sourced to enable easy customization and experimentation.

## 🔧 Hardware Features

- ✅ 8 Digital Outputs
- ✅ 6 Analog Inputs
- ✅ Dual MCP2515 CAN Controllers
- ✅ 32-bit Microcontroller (ATSAMD21)

## 🚗 What Can It Do?

OpenCAN can operate as a **man-in-the-middle (MITM)** device on the CAN bus, intercepting, filtering, and modifying CAN messages in real time. This allows for creative applications in automotive systems, retrofits, and diagnostics.

### Example Use Cases

#### 🌡 PWM Fan Control

Use **coolant temperature** data from the CAN bus to:

- Generate a PWM output signal
- Drive an electric fan based on temperature profile

#### 🛠 Gauge Reassignment

Display **oil temperature** on the **coolant temp gauge**:

- Read oil temp from CAN Bus A
- Rewrite it as coolant temp on CAN Bus B
- Toggle the mode with an existing switch (e.g., cruise control cancel)

#### ⛽ E85/Flex Fuel Content Monitoring

Read an ethanol content sensor and make fueling decisions in real time:

- Read frequency output from a flex fuel sensor on a digital input
- Calculate ethanol percentage and fuel temperature
- Broadcast the values as a custom CAN message for the ECU or a digital dash to consume
- Optionally trigger a relay output (e.g. enable a secondary fuel pump or water/meth injection) above a set ethanol percentage

#### 🏁 RPM-Triggered Outputs

Use live RPM data from the CAN bus to fire outputs at specific thresholds:

- Read engine RPM from the powertrain CAN bus
- Trigger a relay output above a set RPM (shift light, exhaust valve, anti-lag solenoid)
- Combine with throttle position or clutch switch input for launch control or 2-step style logic

#### 🔄 Cross-Platform Signal Translation (Engine Swaps)

Bridge a donor engine's CAN messages to a chassis that expects a different format:

- Read RPM, coolant temp, oil pressure, and other signals from the engine-side CAN bus
- Repackage them into the message IDs and formats the chassis cluster expects
- Factory gauges, warning lights, and chimes work correctly without cluster modification or a standalone digital dash

#### 🛟 Failsafe Monitoring

Add protection the donor ECU doesn't provide on a swapped platform:

- Monitor oil pressure switch and coolant temp sender on analog inputs
- If oil pressure drops or coolant temp exceeds a threshold, trigger a relay output (warning light, fuel pump cutoff, fan to max)
- Runs independently of the ECU, so it works even if the donor ECU has no concept of the new chassis's sensors

#### 🚙 Speed Signal Generation

Generate a VSS (vehicle speed signal) for a swapped transmission or ECU:

- Read output shaft speed sensor on a digital input
- Calculate vehicle speed based on tire size and final drive ratio
- Output a corrected speed signal (CAN message or pulse output) for the ECU, cluster, and cruise control to use

## 🔧 Hardware Details

**Microcontroller**: ATSAMD21G

### 🚌 CAN Interfaces (Dual MCP2515)

| CAN Bus | CS Pin | INT Pin |
| ------- | ------ | ------- |
| CAN1    | D10    | D2      |
| CAN2    | D11    | D3      |

### ⚡ Digital Outputs

All 8 digital output channels are NPN switch-to-ground stages (MMBT2222A). VIN pulls the output node high through a base/collector resistor, and the SAMD21 GPIO drives the transistor base, pulling the output low when active. D0–D7 are low-amperage output control channels, D8–D9 are sized for relay coil drive.

| Pin | Driver | Resistor | Function |
| --- | ------ | -------- | -------- |
| D0  | Q1 (MMBT2222A) | R1 (1k)  | Low-amp output control |
| D1  | Q2 (MMBT2222A) | R20 (1k) | Low-amp output control |
| D4  | Q3 (MMBT2222A) | R4 (1k)  | Low-amp output control |
| D5  | Q4 (MMBT2222A) | R10 (510) | Low-amp output control |
| D6  | Q5 (MMBT2222A) | R11 (510) | Low-amp output control |
| D7  | Q6 (MMBT2222A) | R17 (1k) | Low-amp output control |
| D8  | Q7 (MMBT2222A) | RL8 (1k) | Relay control via ground switch |
| D9  | Q8 (MMBT2222A) | RL9 (1k) | Relay control via ground switch |

### 📥 Analog Inputs

| Pin | Resistors | Function |
| --- | --------- | -------- |
| A0  | R2 (1k pull-up to 3.3V) | Resistive sensor input (e.g. fuel/temp senders) |
| A1  | R3 (1k pull-up to 3.3V) | Resistive sensor input (e.g. fuel/temp senders) |
| A2  | R13/R14 (1k pull-up to 3.3V) | Switch-to-ground input |
| A3  | R15/R16 (1k pull-up to 3.3V) | Switch-to-ground input |
| A4  | R22 (4.7k) / R23 (2.2k to GND) | 0-5V analog sensor input, ~1.6V at pin for 5V signal |
| A5  | R21 (4.7k) / R24 (2.2k to GND) | 0-5V analog sensor input, ~1.6V at pin for 5V signal |

### 📷 Board Images

![digital IO](https://github.com/user-attachments/assets/152f15c9-3eba-42aa-979a-cd5451eb33e8)
![3d Board](https://github.com/user-attachments/assets/e2820e35-30a0-4147-82b2-8f1e53d88731)

**NOTE: V1.1 pinout shown below. For V1.2 and V1.3, refer to the terminal labels printed on the board.**

![OpenCAN pinout v1.1](https://github.com/user-attachments/assets/2a63f51d-138e-461c-a77b-e0cef9ffa55e)

## Built On OpenCAN

The [RAUSWORKS VIM](https://rausworks.com) (Vehicle Integration Module) runs on the OpenCAN platform. VIM bridges VAG ECUs to Porsche chassis for engine swap builds, reading and translating signals across two independent CAN buses in real time.

VIM is a closed-source application built on this open firmware platform, proof that OpenCAN's dual-CAN architecture handles complex, production automotive integrations. The same board and toolchain that runs VIM is available here for your own projects.
