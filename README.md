# Restricted-Access Embedded Console for Multi Channel Telemetry Access
LPC2129-based secure telemetry system with keypad PIN authentication and EEPROM storage. It monitors voltage using MCP3204-SPI and temperature using LM35-ADC. LCD displays status, while GSM-UART sends alerts and GPIO controls the fan during high temperature. Three wrong PIN attempts restrict access.

1. Abstract
The Restricted Access Embedded Console for Multi-Channel Telemetry Access is an embedded monitoring system based on the LPC2129 microcontroller. The system provides secure PIN-based access using a keypad and stores the PIN in EEPROM. After authentication, the user can select voltage or temperature monitoring. Voltage is measured using the MCP3204 ADC, while temperature is measured using an LM35 sensor. When the temperature reaches or exceeds 30°C, a fan is automatically switched ON and an alert is sent through a GSM module. The system uses I²C, SPI, UART, GPIO, and ADC interfaces and displays the system status on an LCD.

2. Objectives
    Secure the system using PIN authentication.
    Store the PIN in EEPROM.
    Monitor voltage and temperature.
    Automatically control the fan based on temperature.
    Send GSM alerts during high temperature or failed access attempts.
    Display monitoring information on an LCD.

3. Hardware Components:
    LPC2129 Microcontroller – Main controller.
    16×2 LCD – Displays system information.
    4×4 Keypad – PIN entry and menu selection.
    I²C EEPROM – Stores the authorized PIN.
    LM35 Temperature Sensor – Measures temperature.
    MCP3204 ADC – Measures analog voltage.
    GSM Module – Sends alert messages.
    DC Fan – Provides cooling.
    Fan Driver Circuit – Controls the fan.
    Power Supply – Supplies power to the circuit.

4. Software Components:
    Embedded C – Application programming.
    Keil µVision – Development and compilation.
    LCD Driver – LCD control.
    Keypad Driver – Keypad scanning.
    I²C Driver – EEPROM communication.
    SPI Driver – MCP3204 communication.
    UART Driver – GSM communication.
    GSM Driver – GSM configuration and SMS transmission.
    ADC Interface – LM35 temperature measurement.
    GPIO Control – Fan, LCD, and keypad control.

5. Communication Protocols / Interfaces
Protocol / Interface	Application
I²C	LPC2129 ↔ EEPROM
SPI	LPC2129 ↔ MCP3204
UART	LPC2129 ↔ GSM
GPIO	Keypad, LCD, Fan control
ADC	LPC2129 ↔ LM35
6. Block Diagram

                    ┌──────────────┐
                    │    KEYPAD    │
                    │ PIN / 0 / 1  │
                    └──────┬───────┘
                           │ GPIO
                           ▼
                    ┌──────────────┐
                    │    LPC2129   │
                    │     MCU      │
                    └──┬──┬──┬──┬──┘
                       │  │  │  │
              ┌────────┘  │  │  └─────────┐
              ▼           ▼  ▼            ▼
           ┌─────┐     ┌──────┐┌──────┐ ┌─────┐
           │ LCD │     │EEPROM││MCP3204│ │ GSM │
           └─────┘     └──────┘└──┬───┘ └─────┘
            GPIO         I²C   SPI │      UART
                                   ▼
                              Voltage Input


                         ┌──────────┐
                         │   LM35   │
                         │  Sensor  │
                         └────┬─────┘
                              │ ADC
                              ▼
                           LPC2129
                              │ GPIO
                              ▼
                       ┌─────────────┐
                       │ Fan Driver  │
                       └──────┬──────┘
                              ▼
                             FAN

7. Working Principle

START
  ↓
Initialize LPC2129 and peripherals
  ↓
Enter PIN
  ↓
Compare PIN with EEPROM
  ↓
 ┌───────────────┐
 │               │
WRONG           CORRECT
 │               │
 ↓               ↓
Count++       ENTER 0 OR 1
 │               │
 ├─ 3 attempts   ├── 0 → Voltage Monitoring
 │               │
 ↓               └── 1 → Temperature Monitoring
LIMIT REACHED              │
                           ↓
                     Temperature ≥ 30°C
                           │
                    ┌──────┴──────┐
                    ↓             ↓
                  FAN ON        GSM ALERT
                           │
                           ↓
                    Return to 0/1 Menu

8. Main Features

    PIN-based restricted access
    Three failed-attempt limit
    EEPROM-based PIN storage
    Voltage monitoring
    Temperature monitoring
    Automatic fan control
    GSM alert system
    LCD status display
    Multi-protocol communication using I²C, SPI, UART, GPIO, and ADC
