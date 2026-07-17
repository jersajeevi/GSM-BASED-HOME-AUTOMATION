# GSM-BASED-HOME-AUTOMATION
# GSM Home Automation using LPC2129

## Overview

This project implements a GSM-based Home Automation System using the LPC2129 ARM7 microcontroller. The system allows users to remotely control home appliances such as lights and fans by sending SMS commands to a GSM modem. The received commands are processed by the LPC2129, and the corresponding devices are switched ON or OFF.

The system also displays the received commands and device status on a 16x2 LCD.

---

## Features

* Remote appliance control using SMS
* Control of:

  * Light 1
  * Light 2
  * Fan (Motor)
  * All devices together
* Real-time status display on 16x2 LCD
* UART communication with GSM modem
* SMS command validation
* Simple and low-cost home automation solution

---

## Hardware Requirements

* LPC2129 ARM7 Development Board
* GSM Module (SIM800/SIM900)
* 16x2 LCD Display
* Relay Module / Driver Circuit
* DC Fan / Motor
* LEDs for appliance simulation
* Power Supply (5V/3.3V)
* Connecting Wires

---

## Software Requirements

* Keil uVision IDE
* Embedded C
* Flash Magic (for programming LPC2129)

---

## Pin Configuration

| Device         | LPC2129 Pin   |
| -------------- | ------------- |
| GSM TX         | P0.0 (RXD0)   |
| GSM RX         | P0.1 (TXD0)   |
| LCD Data D4-D7 | P0.14 - P0.21 |
| LCD RS         | P0.12         |
| LCD EN         | P0.13         |
| Light 1        | P1.23         |
| Light 2        | P1.24         |
| Fan Motor IN1  | P1.25         |
| Fan Motor IN2  | P1.26         |

---

## SMS Commands

| SMS Command  | Action               |
| ------------ | -------------------- |
| *FAN ON#     | Turn Fan ON          |
| *FAN OFF#    | Turn Fan OFF         |
| *LIGHT1 ON#  | Turn Light 1 ON      |
| *LIGHT1 OFF# | Turn Light 1 OFF     |
| *LIGHT2 ON#  | Turn Light 2 ON      |
| *LIGHT2 OFF# | Turn Light 2 OFF     |
| *ALL ON#     | Turn ON all devices  |
| *ALL OFF#    | Turn OFF all devices |

> Note: Commands must end with '#' character.

---

## Working Principle

1. LPC2129 initializes UART, LCD, and GSM modem.
2. GSM modem is configured using AT commands.
3. User sends an SMS command to the GSM module.
4. GSM forwards the message through UART.
5. LPC2129 reads and validates the command.
6. Corresponding output pins are activated/deactivated.
7. Appliance status is displayed on the LCD.

---

## GSM AT Commands Used

```text
AT
AT+CMGF=1
AT+CNMI=2,2,0,0,0
AT+CMGS="Mobile_Number"
```

* `AT` → Check modem communication
* `AT+CMGF=1` → Text mode SMS
* `AT+CNMI=2,2,0,0,0` → Direct SMS indication
* `AT+CMGS` → Send SMS

---

## Project Structure

```text
GSM-Home-Automation/
│
├── GSMPROJECT.C
├── README.md
└── Documentation/
```

---

## Future Enhancements

* Android application control
* IoT cloud integration
* Appliance status feedback SMS
* Voice command support
* Temperature and security monitoring
* Multiple user authentication

---

## Applications

* Smart Homes
* Office Automation
* Industrial Monitoring
* Remote Device Control
* Energy Management Systems

---

## Author

**Jeevitha K**

B.E. Electronics and Communication Engineering

##
