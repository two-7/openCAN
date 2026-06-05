# OpenCAN

**Open CAN** is a 32-bit embedded system firmware project designed for CAN bus control, monitoring, and manipulation. It supports a range of real-time vehicle data applications and is open-sourced to enable easy customization and experimentation.

## 🔧 Hardware Features

- ✅ 8 Digital Outputs  
- ✅ 6 Analog Inputs  
- ✅ Dual MCP2515 CAN Controllers  
- ✅ 32-bit Microcontroller (ATSAMD21)

## 🚗 What Can It Do?

Open CAN can operate as a **man-in-the-middle (MITM)** device on the CAN bus, intercepting, filtering, and modifying CAN messages in real time. This allows for creative applications in automotive systems, retrofits, and diagnostics.

### Example Use Cases

#### 🛠 Gauge Reassignment
Display **oil temperature** on the **coolant temp gauge**:
- Read oil temp from CAN Bus A
- Rewrite it as coolant temp on CAN Bus B
- Toggle the mode with an existing switch (e.g., cruise control cancel)

#### 🌡 PWM Fan Control
Use **coolant temperature** data from the CAN bus to:
- Generate a PWM output signal
- Drive an electric fan based on temperature profile

## 🔧 Hardware Details

**Microcontroller**: ATSAMD21G  
**Bootloader**: Arduino Zero / SparkFun Mini SAMD bootloader  

### 🚌 CAN Interfaces (Dual MCP2515)
| CAN Bus | CS Pin | INT Pin |
|---------|--------|---------|
| CAN1    | D10    | D2      |
| CAN2    | D11    | D3      |

### ⚡ Digital Outputs
| Pin        | Function                        |
|------------|---------------------------------|
| D0–D1, D4–D7 | Switch 12V (High-side drive)     |
| D8–D9      | Relay control via ground switch |

### 📥 Analog Inputs
| Pin   | Configuration Description                                                             |
|--------|----------------------------------------------------------------------------------------|
| A0–A1 | Reads resistors using a 1kΩ voltage divider                                            |
| A2–A3 | Reads switch-to-ground inputs                                                         |
| A4–A5 | Reads 12V sensor signals via voltage divider:  
`[12V input] → 4.7kΩ → [SAMD pin] → 2.2kΩ → GND` |

![digital IO](https://github.com/user-attachments/assets/9faa2da8-8e4c-43a7-91cf-a10a13ae3909)

**NOTE*** V1.1 PINOUT ONLY - V1.2 and V1.3 refer to the terminal labels printed on the board.**
![OpenCAN pinout v1 1](https://github.com/user-attachments/assets/2a63f51d-138e-461c-a77b-e0cef9ffa55e)
