
# Smart HVAC Probe

A ESP32-C3 based probe designed for the the automatic matching of r1234yf, r134, HC-30 and R744 refrigerant pressures from current atmospheric temperature.

## Features
This Probe is deisgned for the the automatic matching of r1234yf, r134, HC-30 and R744 refrigerant pressures from current atmospheric temperature.

It is also equipped with a vent probe for use automotive air conditioning performance testing.

Charged and programmed over USB -C 

The probe is a fully enabled WiFi device hosting its own micro web server to to display sensor and pressure data. Any device with a WiFi connection and a web browser can connect. 

Once booted the probe will broadcast a WiFi Connection with the details below.

SSID: Smart_Hvac_Probe  
Default Password: Smart_Hvac_Probe  
Probes IP: 192.168.4.1  

Once WiFi connection is established between probe and device, a device the web browser should redirect you the the hosted probes home page. If not, type the probes IP address into a connect web browser address bar.
 
Once at the Probes homepage you can change the WiFi details and set the default units to used by the probe.  
When any setting are updated the Probe will reboot and you device will need to reconnect with the new details. 

## Screenshots
PCB_V3_EE  
<img src="https://github.com/spoonieau/Arsenic/blob/main/Images/PCB_V3_EE.jpg" width=40% height=40%>

FireFox Mobile  
<img src="https://github.com/spoonieau/Arsenic/blob/main/Images/Screenshot_20240304_184430_Firefox.jpg" width=40% height=40%>

FireFox PC  
<img src="https://github.com/spoonieau/Arsenic/blob/main/Images/Firefox.png" width=40% height=40%>

## Used Libraries
A huge thankyou to the authors of the libraries used below.  

PaulStoffregen - OneWire  
https://github.com/PaulStoffregen/OneWire

milesburton - Arduino-Temperature-Control-Library  
https://github.com/milesburton/Arduino-Temperature-Control-Library

RadioShuttle - WS2812Led  
https://github.com/RadioShuttle/WS2812Led

hideakitai - MAX17048  
https://github.com/hideakitai/MAX17048

malokhvii-eduard - arduino-bme280  
https://github.com/malokhvii-eduard/arduino-bme280

me-no-dev - ESPAsyncWebServer  
https://github.com/me-no-dev/ESPAsyncWebServer

me-no-dev - AsyncTCP  
https://github.com/me-no-dev/AsyncTCP

arduino-libraries   
https://github.com/arduino-libraries

espressif - arduino-esp32  
https://github.com/espressif/arduino-esp32




## License

Libraries that are used carry their own Licenses.  
Project is released under GPL3



