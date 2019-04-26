# Serial Shutdown
A simple C++ App to communicate with Arduino or any other micro controller via serial port and shut a windows PC down. 
Examples included are HTML GUI for ESP32 with SPIFFS and simple serial sketch.

## ESP32 Dependancies:
The following dependancies are needed for the ESP32 sketch, not for the simple one.

[ESPAsyncWebserver](https://github.com/me-no-dev/ESPAsyncWebServer)

[SPIFFS Plugin](https://github.com/me-no-dev/arduino-esp32fs-plugin)

## Installing:
Install Arduino IDE and the dependancies. Open the `.ino` and set the upload settings and hit upload.
After that, for ESP32, click on **ESP32 Sketch data upload** to upload the data to SPIFFS.

![Arduino](https://raw.githubusercontent.com/shreyask21/serial-shutdown/master/screenshot3.png "SPIFFS Upload")

## Testing:
Connect the ESP32 to PC and connect to ESP32 WiFi access point (aka hotspot) and visit [192.168.4.1](http://192.168.4.1).

![Webpage](https://raw.githubusercontent.com/shreyask21/serial-shutdown/master/screenshot2.png "Webpage")

Run the `WindowsClient.exe` and click on shutdown.

## Changing COM Port number:

### First method:

Edit the `\\\\.\\COM1` in the WindowsClient.cpp

```
char *port_name = "\\\\.\\COM1"
```

### Second method:

Open up `device manager`, go to the `Ports (COM & LPT)` then select correct device, click on properties, then `port settings` then advanced and then `port number`.
![Device manager](https://raw.githubusercontent.com/shreyask21/serial-shutdown/master/screenshot1.png "Device Manager")
