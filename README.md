##### openCAN

openCAN is an open source firmware platform for working with vehicle CAN bus networks. It can sit on the bus as a node, reading and injecting messages, or inline as a man-in-the-middle, filtering and rewriting traffic in real time. Built on the 32-bit SAMD21, programmable through the Arduino IDE, with fully open source firmware.

🔧 Hardware Features


✅ 8 Digital Outputs
✅ 6 Analog Inputs
✅ Dual MCP2515 CAN Controllers
✅ 32-bit Microcontroller (ATSAMD21G)


### 🚗 What Can It Do?

openCAN can operate as a man-in-the-middle (MITM) device on the CAN bus, intercepting, filtering, and modifying CAN messages in real time. This allows for creative applications in automotive systems, retrofits, and diagnostics.

Example Use Cases

### 🔄 Cross-Platform Signal Translation (Engine Swaps)

Bridge a donor engine's CAN messages to a chassis that expects a different format:


Read RPM, coolant temp, oil pressure, and other signals from the engine-side CAN bus
Repackage them into the message IDs and formats the chassis cluster expects
Factory gauges, warning lights, and chimes work correctly without cluster modification or a standalone digital dash


### 🌡 PWM Fan Control

Use coolant temperature data from the CAN bus to:


Generate a PWM output signal
Drive an electric fan based on temperature profile


### 🚙 Speed Signal Generation

Generate a VSS (vehicle speed signal) for a swapped engine, transmission, or ECU:


Read output shaft speed sensor, speed sensor pulses, or ABS speed data
Calculate vehicle speed based on tire size and final drive ratio
Output a corrected speed signal (CAN message or pulse output) for the ECU, cluster, and cruise control to use


### 🛠 Gauge Reassignment

Display oil temperature on the coolant temp gauge:


Read oil temp from CAN Bus A
Rewrite it as coolant temp on CAN Bus B
Toggle the mode with an existing switch (e.g., cruise control cancel)


### ⛽ E85/Flex Fuel Content Monitoring

Read an ethanol content sensor and make fueling decisions in real time:


Read frequency output from a flex fuel sensor on a digital input
Calculate ethanol percentage and fuel temperature
Broadcast the values as a custom CAN message for the ECU or a digital dash to consume
Optionally trigger a relay output (e.g. enable a secondary fuel pump or water/meth injection) above a set ethanol percentage


### 🏁 RPM-Triggered Outputs

Use live RPM data from the CAN bus to fire outputs at specific thresholds:


Read engine RPM from the powertrain CAN bus
Trigger a relay output above a set RPM (shift light, exhaust valve, anti-lag solenoid)
Combine with throttle position or clutch switch input for launch control or 2-step style logic


### 🛟 Failsafe Monitoring

Add protection the donor ECU doesn't provide on a swapped platform:


Monitor oil pressure switch and coolant temp sender on analog inputs
If oil pressure drops or coolant temp exceeds a threshold, trigger a relay output (warning light, fuel pump cutoff, fan to max)
Runs independently of the ECU, so it works even if the donor ECU has no concept of the new chassis's sensors


### 🔧 Hardware Details

Microcontroller: ATSAMD21G

### 🚌 CAN Interfaces (Dual MCP2515)

CAN BusCS PinINT PinCAN1D10D2CAN2D11D3

### ⚡ Digital Outputs

All 8 digital output channels are NPN switch-to-ground stages (MMBT2222A). VIN pulls the output node high through a base/collector resistor, and the SAMD21 GPIO drives the transistor base, pulling the output low when active. D0, D1, and D4–D7 are the six low-amp output control channels. D8 and D9 are sized for relay coil drive. (D2 and D3 are reserved as the CAN controller interrupt lines.)

PinDriverResistorFunctionD0Q1 (MMBT2222A)R1 (1k)Low-amp output controlD1Q2 (MMBT2222A)R20 (1k)Low-amp output controlD4Q3 (MMBT2222A)R4 (1k)Low-amp output controlD5Q4 (MMBT2222A)R10 (510)Low-amp output controlD6Q5 (MMBT2222A)R11 (510)Low-amp output controlD7Q6 (MMBT2222A)R17 (1k)Low-amp output controlD8Q7 (MMBT2222A)RL8 (1k)Relay control via ground switchD9Q8 (MMBT2222A)RL9 (1k)Relay control via ground switch

### 📥 Analog Inputs

PinResistorsFunctionA0R2 (1k pull-up to 3.3V)Resistive sensor input (e.g. fuel/temp senders)A1R3 (1k pull-up to 3.3V)Resistive sensor input (e.g. fuel/temp senders)A2R13/R14 (1k pull-up to 3.3V)Switch-to-ground inputA3R15/R16 (1k pull-up to 3.3V)Switch-to-ground inputA4R22 (4.7k) / R23 (2.2k to GND)0-5V analog sensor input, ~1.6V at pin for 5V signalA5R21 (4.7k) / R24 (2.2k to GND)0-5V analog sensor input, ~1.6V at pin for 5V signal

### 🔌 Connecting to openCAN

Arduino IDE Setup


Download and install the Arduino IDE from arduino.cc/en/software
Open the IDE. Go to File → Preferences.
Paste the following URL into the Additional Boards Manager URLs field:
https://raw.githubusercontent.com/two-7/openCAN/main/package_two7_index.json
Go to Tools → Board → Boards Manager.
Search for openCAN SAMD21 Boards and install the package.
Plug the openCAN board into the computer.
Go to Tools → Port and select the COM port openCAN is connected to.
Go to Tools → Board → openCAN SAMD21 Boards → openCAN.
Go to Tools → Serial Monitor.
In the Serial Monitor pane, set the line ending to New Line and the baud rate to 500000.
Live openCAN data streams to the Serial Monitor, refreshing once per second.

### 📷 Board Images

![digital IO](https://github.com/user-attachments/assets/152f15c9-3eba-42aa-979a-cd5451eb33e8)
![3d Board](https://github.com/user-attachments/assets/e2820e35-30a0-4147-82b2-8f1e53d88731)

**NOTE: V1.1 pinout shown below. For V1.2 and V1.3, refer to the terminal labels printed on the board.**

![OpenCAN pinout v1.1](https://github.com/user-attachments/assets/2a63f51d-138e-461c-a77b-e0cef9ffa55e)

<!-- ## Built On OpenCAN

The [RAUSWORKS VIM](https://rausworks.com) (Vehicle Integration Module) runs on the OpenCAN platform. VIM bridges VAG ECUs to Porsche chassis for engine swap builds, reading and translating signals across two independent CAN buses in real time.

VIM is a closed-source application built on this open firmware platform, proof that OpenCAN's dual-CAN architecture handles complex, production automotive integrations. The same board and toolchain that runs VIM is available here for your own projects. --!>
