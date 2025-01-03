# ESP32LedWiFiFirmware
Simple ESP32 firmware to control LED via WiFi/WebServer.

Make sure that [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets) library is setup in Arduino IDE Library manager.

Base connection scheme:
![scheme](https://github.com/amusement-x-labs/ESP32LedWiFiFirmware/blob/main/Scheme.png)

Pins connection:
| ESP32 PIN | SCHEME |
| ------ | ------ |
| D4 | Resistor |
| GND | LED cathode (small one) |