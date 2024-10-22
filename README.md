# Automated Hydroponics System

 ## Automated-Hydroponics-System-Using-ESP32-WROOM-32
The system monitors and controls essential environmental factors such as water levels, nutrient delivery, pH balance, temperature, and light intensity in a hydroponic setup
### Project Overview

This project is aimed at automating a hydroponics system using an ESP32-WROOM-32 microcontroller. The system monitors and controls essential environmental factors such as water levels, nutrient delivery, pH balance, temperature, and light intensity in a hydroponic setup. The ESP32-WROOM-32 is connected to various sensors and actuators that manage these parameters autonomously, with the ability to monitor and control the system remotely via Wi-Fi or Bluetooth.
## Features
- Water Level Control: Monitors water levels and refills automatically.
- Nutrient Dispensing: Automatically adds nutrients based on water volume.
- pH Monitoring and Adjustment: Tracks the pH levels and adjusts using pH up or down solutions.
- Temperature Control: Monitors temperature and triggers heaters or coolers.
- Light Control: Manages grow light cycles and intensity based on plant requirements.
- Real-time Monitoring: Data can be monitored remotely via an app or web interface.
- Wi-Fi and Bluetooth Connectivity: Offers flexibility for remote control and notifications.

## Table of Contents

#### 1.Hardware Requirements
#### 2.Circuit Diagram
#### 3.Software Requirements
#### 4.Installation
#### 5.Usage
#### 6.Diagrams
#### 7.Contributing
#### 8.License

## Hardware Requirements

To automate a hydroponics system using the ESP32-WROOM-32, the following hardware components are required:
####  1.ESP32-WROOM-32 Microcontroller
####  2.Water level sensor (Ultrasonic or float switch)
####  3.pH sensor
####  4.Temperature sensor (e.g., DHT22 or DS18B20)
####  5.Solenoid valve for water flow control
####  6.Nutrient dosing pumps (peristaltic pumps for different nutrients)
####  7.pH adjustment pumps (for pH up and down solutions)
####  8.Relay module for controlling lights and pumps
####  9.Grow lights (LEDs or other types)
####  10.Heater/cooler unit (optional, depending on environmental needs)
####  11.Power supply (5V or 12V depending on your components)

## Circuit Diagram

The connections of the components are crucial to ensure proper functionality of the system.
## Schematic:
![Schematic diagram](https://github.com/antonkingsley/Automated-Hydroponics-System/blob/main/screen_shots/Schematic%20diagram.png?raw=true)

- Water Level Sensor: Connected to GPIO32 (as input pin)
- Nutrient Pumps: Controlled via relay module, connected to GPIO pins like GPIO25, GPIO26.
- pH Sensor: Connected to an analog pin (e.g., ADC GPIO34).
- Temperature Sensor: Connected to GPIO4 for data reading.
- Grow Lights: Controlled via a relay, triggered by GPIO pins.
- Heater/Cooler: Optional but also controlled via a relay, GPIO27 or other suitable pins.

## Software Requirements

To make the hydroponics automation system functional, you will need:

####  1.Arduino IDE or PlatformIO installed for writing and uploading code to the ESP32.
####  2.ESP32 board manager added to the Arduino IDE.
####  3.Required libraries:
- WiFi.h
- PubSubClient.h (for MQTT if needed)
- DHT.h (for temperature and humidity sensors)
- Adafruit_Sensor.h (for general sensor support)
- OneWire.h and DallasTemperature.h (if using DS18B20)
- EEPROM.h (to store configuration locally on the ESP32)
####  4.pH sensor library for reading analog pH values.

## Installation
###  Step 1: Setup ESP32 in Arduino IDE

   
####  1.Open Arduino IDE.
####  2.Go to File > Preferences.
####  3.Add the following URL to the "Additional Board Manager URLs":

## arduino

	https://dl.espressif.com/dl/package_esp32_index.json

####  4.Go to Tools > Board > Board Manager, search for ESP32, and install it.
####  5.Select ESP32 Dev Module under Tools > Board.

###  Step 2: Install Required Libraries

Install the necessary libraries in the Arduino IDE by going to Sketch > Include Library > Manage Libraries and searching for the libraries listed in the Software Requirements section.
###  Step 3: Clone the Repository

To get the code, clone this GitHub repository:

## bash	
 	https://github.com/antonkingsley/Automated-Hydroponics-System.git
	
 cd automated-hydroponics-esp32

###  Step 4: Upload the Code

Open the automated_hydroponics.ino file in the Arduino IDE, configure the Wi-Fi credentials and required settings, and upload the code to the ESP32 board.
## Usage
####  Step 1: Connect to Wi-Fi

Once the ESP32 is powered on, it will attempt to connect to the configured Wi-Fi network. Ensure that the correct credentials are set in the code.
####  Step 2: Monitor Sensor Data

You can monitor water level, pH, temperature, and light conditions either via:

- A serial monitor in the Arduino IDE.
- A web interface (if enabled via an embedded web server).
- MQTT broker if integrated with an IoT platform.

####  Step 3: Control Actuators

The system will automatically:

- Trigger the water solenoid valve if water level falls below a set threshold.
- Add nutrients as per the set cycle.
- Adjust pH when it goes beyond the ideal range.
- Control the temperature by turning on or off the heater/cooler.
- Turn on or off the grow lights based on a preset schedule or sensor input.

####  Step 4: Calibration

Ensure the pH sensor and nutrient pumps are calibrated:

- Adjust the sensor readings by comparing with standard solutions.
- Set the nutrient dosing to match your hydroponic system's requirements.

## Diagrams
### Full System Diagram

![Schematic diagram](https://github.com/antonkingsley/Automated-Hydroponics-System/blob/main/screen_shots/Full%20Schematic%20diagram.png?raw=true)

### Component Connections Diagram

####  pH Sensor:
- Connect to analog GPIO34.
- Requires calibration via buffer solutions.

####  Temperature Sensor (DHT22 or DS18B20):
- Connect data pin to GPIO4.

####  Nutrient Pumps:
- Controlled by GPIO25, GPIO26 via relay.

####  Solenoid Valve:
- Connected to GPIO33 via relay for controlling water flow.

### Contributing

Contributions to this project are welcome! Please follow the standard GitHub workflow:

- Fork the repository.
- Create a new branch for your feature or bug fix.
- Submit a pull request with a clear description of your changes.

### License

This project is licensed under the MIT License.


