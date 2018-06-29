# nodemcu-esp8266-433Mhz-Ritter
A software to control 433 Mhz remote plugs from ritter with an nodemcu controller

## Hardware specification
You need an NodeMCU ESP-8266 controller which includes minimum an 433 Mhz transmitter and optional an DHT11 and\\or PIR sensor.

## Setup

### Dependent Libraries
The following libraries need to be present in your Arduino library folder:
- https://github.com/adafruit/Adafruit_Sensor
- https://github.com/1technophile/NewRemoteSwitch

### Configuration
Please adapt the configuration files in main/config to your needs

### Transfer

Open the main/main.ino file and transfer it over the Arduino IDE to an Nodemcu ESP-8266 controller.

## Use
To use the controller call the controller with the IP on Port 80.
Afterwards you can use the buttons to switch 433Mhz Remote Plugs on and off.

## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">Creative Commons Attribution-NonCommercial 4.0 International License</a>.
