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

7.Working Principle:

The Restricted Access Embedded Console for Multi-Channel Telemetry Access is controlled by the LPC2129 microcontroller.

System Initialization:
When the system is powered ON, the LPC2129 initializes the LCD, keypad, EEPROM, SPI, UART, ADC, and GSM module.

PIN Authentication:
The user enters a 10-digit PIN through the keypad. The entered PIN is compared with the PIN stored in EEPROM. The system allows a maximum of three incorrect attempts.

Restricted Access:
If the user enters the wrong PIN three times, access is blocked and "LIMIT REACHED" is displayed. A GSM alert can also be sent.

Telemetry Selection:
After successful authentication, the LCD displays "ENTER 0 OR 1". The user can select:

0 – Voltage Monitoring
1 – Temperature Monitoring

Voltage Monitoring:
When 0 is selected, the MCP3204 ADC measures the input voltage through the SPI protocol and the measured value is displayed on the LCD.

Temperature Monitoring:
When 1 is selected, the LM35 measures temperature. The LPC2129 reads the sensor value through its ADC interface.

Automatic Fan Control:
If the temperature is 30°C or above, the LPC2129 activates the fan through GPIO. If the temperature is below 30°C, the fan remains OFF.

GSM Alert:
During an over-temperature condition, the GSM module sends an alert message through UART.

Continuous Operation:
After the selected monitoring operation is completed, the system returns to the 0/1 selection menu, allowing the user to select another telemetry channel without resetting the system.

8.Advantages:

    Provides secure access using PIN authentication.
    Stores the PIN in EEPROM for reliable access control.
    Supports voltage and temperature monitoring.
    Provides automatic fan control during high temperature.
    Sends GSM alerts for critical conditions.
    Displays real-time information on the LCD.
    Supports multiple communication interfaces: I²C, SPI, UART, GPIO, and ADC.
    Simple and cost-effective embedded solution.

9.Future Scope
    Add IoT connectivity for remote monitoring through a mobile or web application.
    Store sensor readings in cloud/database storage for analysis and history.
    Add more sensors for current, humidity, pressure, and gas monitoring.
    Implement RFID, fingerprint, or OTP authentication for enhanced security.
    Add real-time data logging using external memory or SD card.
    Enable remote fan/device control through GSM or IoT.
    Develop a mobile application for monitoring and alerts.
    Add battery backup for continuous operation during power failure.
     Expand the system to support multiple telemetry channels and devices.
     
10. Main Features:
    PIN-based restricted access
    Three failed-attempt limit
    EEPROM-based PIN storage
    Voltage monitoring
    Temperature monitoring
    Automatic fan control
    GSM alert system
    LCD status display
    Multi-protocol communication using I²C, SPI, UART, GPIO, and ADC


Conclusion:
The Restricted Access Embedded Console for Multi-Channel Telemetry Access successfully combines secure authentication with real-time telemetry monitoring using the LPC2129. The system provides PIN protection, voltage and temperature monitoring, automatic fan control, and GSM alerts. The use of I²C, SPI, UART, GPIO, and ADC makes the system flexible and suitable for future expansion.
            
