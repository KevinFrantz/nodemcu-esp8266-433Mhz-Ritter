# nodemcu-esp8266-433Mhz-Ritter

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/95b050fe8c9d42f28640c1f52ae7e595)](https://www.codacy.com/manual/KevinFrantz/nodemcu-esp8266-433Mhz-Ritter?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=KevinFrantz/nodemcu-esp8266-433Mhz-Ritter&amp;utm_campaign=Badge_Grade) [![donate on paypal](https://img.shields.io/badge/donate%20-%E2%9D%A4%24%E2%82%AC%C2%A5-important)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=C9USD9N26SYZU&source=url) [![License: AGPL v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

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

## Development

### Styleguide
You MUST hold to the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

## License
The ["GNU AFFERO GENERAL PUBLIC LICENSE"](./LICENSE.txt) applies to this project.
