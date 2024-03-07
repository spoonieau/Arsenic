#include <Arduino.h>
#include <LittleFS.h>
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Bme280.h>
#include <WS2812Led.h>
#include <MAX17048.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>
#include <config.h>
#include <DNSServer.h>
#include <r134a.h>
#include <r1234yf.h>
#include <r744.h>
#include <hychill30.h>

//============Device Setup============

WS2812Led wsLED(WS2812LedPin, 1);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;

Bme280TwoWire bme280;

MAX17048 pwr_mgmt;

//============Wifi/Web Server Setup============
//Dns settings
DNSServer dnsServer;

//Strings to hold device credentials 
String SSID; 
String PWD;
String UNITS;

//Set the device's IP
IPAddress apIP(192, 168, 4, 1);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

// Json Variable to Hold Sensor Readings
JSONVar readings;
JSONVar wifi;
JSONVar newWifi;

// Timer variables
unsigned long lastTime = 0;  
unsigned long timerDelay = 3000; //3sec

//============Vars============
bool reboot = false;
bool clientConnected = false;

uint32_t Freq = 0;

//============Temp to Kpa classes============
r134a r134a_1;
r1234yf r1234yf_1;
r744 r744_1;
hychill30 hychill30_1;

void restartDevice()
{
  ESP.restart();
}

void saveConfig(String newSsid, String newPwd, String newUnits)
{ 
  File file = LittleFS.open("/config.txt", "w");

  if(!file)
   {
    Serial.println("Config not found!!!!");
    Serial.println("Unable to wtite wifi SSID, PWD and Units Please reflash");
    Serial.println("Device will restart");
    reboot = true;
    
   }
  String data = (String (newSsid.c_str()) + '\n' + String (newPwd.c_str()) + '\n' + String (newUnits.c_str()));
  file.print(data);
  
  file.close();

  Serial.println("New SSID: " + newSsid + ", new Password: " + newPwd + " and new Units: " + newUnits + " written"); 
  Serial.println("Device going down for a reboot");
  reboot = true;
}

void readConfig()
{
  File file = LittleFS.open("/config.txt", "r");
  
  //Check if the file exists
   if(!file)
   {
    Serial.println("Config not found!!!!");
    Serial.println("Unable to set wifi SSID and PWD, Please reflash");
    Serial.println("Device will restart");
    reboot = true;
   }

   int line = 0;

   while (file.available())
   {
    if (line == 0)
    {
      String ssdiString=file.readStringUntil('\n');
      SSID = ssdiString.c_str();
    }

    if (line == 1)
    {
      String pwdString=file.readStringUntil('\n');
      PWD = pwdString.c_str();
    }

    if (line == 2)
    {
      String unitsString=file.readStringUntil('\n');
      UNITS = unitsString.c_str();
    }

    line++;
   }
   file.close();
}

void wifiClientConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  clientConnected = true;
  Serial.println("Wifi Client Connected");
  wsLED.Clear();
  //delay (500);
  wsLED.Brightness(20);
  wsLED.UpdateAll(wsLED.GREEN);
  delay (500);
}

void wifiClientDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  clientConnected = false;
  Serial.println("Wifi Client Disconnected");
  wsLED.Clear();
  //delay (500);
  wsLED.Brightness(20);
  wsLED.UpdateAll(wsLED.YELLOW);
  delay (500);
}

void initWiFi() 
{
  Serial.println("Setting as soft access point mode");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  delay(250);

  if (debug)
  {
  Serial.println("SSID:" + String(SSID));
  Serial.println("Password:" + String(PWD));
  }
  WiFi.softAP(SSID.c_str(), PWD.c_str());
  WiFi.hostname(SSID);
  delay(250);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address:");
  Serial.println(IP);
  
  delay(250);
}

void initFS() 
{
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
    Serial.println("Device requires reflashing");
    reboot = true;
  }
  Serial.println("LittleFS mounted successfully");

}

String getHychill30Press()
{
  int aTemp;
  aTemp = round(bme280.getTemperature());

  String press = String(hychill30_1.pressure(aTemp));
  if(debug)
  {
    Serial.print("Hychill30 Pressure: ");
    Serial.print(press);
    Serial.println("Kpa");
  }

  return press;
}

String getR744Press()
{
  int aTemp;
  aTemp = round(bme280.getTemperature());

  String press = String(r744_1.pressure(aTemp));
  if(debug)
  {
    Serial.print("r744 Pressure: ");
    Serial.print(press);
    Serial.println("Kpa");
  }

  return press;
}

String getR1234yfPress ()
{
  int aTemp;
  aTemp = round(bme280.getTemperature());

  String press = String(r1234yf_1.pressure(aTemp));
  if(debug)
  {
    Serial.print("r1234yf Pressure: ");
    Serial.print(press);
    Serial.println("Kpa");
  }

  return press;
}

String getR134aPress()
{
  int aTemp;
  aTemp = round(bme280.getTemperature());

  String press = String(r134a_1.pressure(aTemp)); 

  if(debug)
  {
    Serial.print("r134a Pressure: ");
    Serial.print(press);
    Serial.println("Kpa");
  }

  return press;
}

String getWifiDetails()
{
  wifi["ssid"] = SSID;
  wifi["pwd"] = PWD;
  wifi["unit"] = UNITS;
  String jsonString = JSON.stringify(wifi);
  
  if (debug)
  {
  Serial.println(String(jsonString));
  }

  return jsonString;
}

String readVentTemp()
{
  sensors.requestTemperatures();
  int vTemp;
  vTemp = round(sensors.getTempCByIndex(0));

  if(debug)
  {
    Serial.print("Vent Probe Temperature Celsius:");
    Serial.print(vTemp);
    Serial.println("ºC");
  }
  return String(vTemp);
}

String readAtmosTemp()
{
  int aTemp;
  aTemp = round(bme280.getTemperature());

  if(debug)
  {
    Serial.print("Atmospheric Probe Temperature Celsius:");
    Serial.print(aTemp);
    Serial.println("ºC");
  }
  return String(aTemp);

}

String readAtmosHumidity()
{
  int aHumidity;
  aHumidity = bme280.getHumidity();

   if(debug)
  {
    Serial.print("Atmospheric Probe Humidity:");
    Serial.print(aHumidity);
    Serial.println(" %");
  }
  return String(aHumidity);
}

String readAtmosPressure()
{
  int aPressure;
  aPressure = bme280.getPressure();

   if(debug)
  {
    Serial.print("Atmospheric Probe Pressure:");
    Serial.print(aPressure);
    Serial.println("Pa");
  }
  return String(aPressure);
}

String readBatterySoc()
{
  int bSoc;
  bSoc = pwr_mgmt.percent();

   if(debug)
  {
    Serial.print("Battery SOC:");
    Serial.print(bSoc);
    Serial.println("%");
  }
  return String(bSoc);
}

String getSensorReadings()
{
  readings["ventTemp"] = readVentTemp();
  readings["atmosTemp"] = readAtmosTemp();
  readings["atmosHum"] = readAtmosHumidity();
  readings["atmosPress"] = readAtmosPressure();
  readings["battSoc"] = readBatterySoc();
  readings["r134aKpa"] = getR134aPress();
  readings["r1234yfKpa"] = getR1234yfPress();
  readings["r744Kpa"] = getR744Press();
  readings["hychill30"] = getHychill30Press();

String jsonString = JSON.stringify(readings);

if(debug)
{
  Serial.println("Websocket data " + String(jsonString));
}

return jsonString;
}

String getWifiDetailsDevice()
{
  wifi["ssid"] = SSID;
  wifi["pwd"] = PWD;
  wifi["unit"] = UNITS;
  String jsonString = JSON.stringify(wifi);
  
  if (debug)
  {
  Serial.println(String(jsonString));
  }

  return jsonString;
}

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html"); 
  }
};

void setup() 
{
  //Set cpu Frequency 
  setCpuFrequencyMhz(cpuFreq);

  Freq = getCpuFrequencyMhz();

  //Change the WS2812Led to RED to indicate device booting.
  wsLED.Clear();
  //delay (500);
  wsLED.Brightness(20);
  wsLED.UpdateAll(wsLED.RED);

  Serial.begin(115200);

  Serial.println("*****************************************");
  Serial.println("*                                       *");
  Serial.println("*     ARSENIC                           *");
  Serial.println("*     Smart HVAC TEMP PROBE             *");
  Serial.println("*     By Rick spooner (spoonie)         *");
  Serial.println("*                                       *");
  Serial.println("*****************************************");
  Serial.println("");
  Serial.println("");
  Serial.println("");

  Serial.println("Version: " + String(fwVersion));

  Serial.println("CPU Set to " + String(Freq) + " Mhz");

  initFS();
  readConfig();
  
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.println("Wire up");

  //sensors.begin();
  //Serial.println("Sensors DB up");

  bme280.begin(Bme280TwoWireAddress::Primary);
  bme280.setSettings(Bme280Settings::indoor());
  Serial.println("BME280 up");

  pwr_mgmt.attatch(Wire);
  Serial.println("MAX17048 up");

  initWiFi();

  WiFi.onEvent(wifiClientDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);
  WiFi.onEvent(wifiClientConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STACONNECTED);

   // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(LittleFS, "/index.html", "text/html");

  });

  server.serveStatic("/", LittleFS, "/");
  
  // Request for the latest sensor readings
  server.on("/readings", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = getSensorReadings();
    request->send(200, "application/json", json);
    json = String();
  });

  // Send wifi details to webpage
  server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = getWifiDetailsDevice();
    request->send(200, "application/json", json);
    json = String();
  });

  // Get user updated wifi details
  server.on("/newWifi", HTTP_POST, [](AsyncWebServerRequest *request){
    String newSsid = request->arg("ssid");
    String newPwd = request->arg("pwd");
    String newUnits = request->arg("unit");

    Serial.println("Recived device new SSID: " + newSsid + " & " + "new device password: " + newPwd + " & " + "new device Units" + newUnits);

    saveConfig(newSsid, newPwd, newUnits);
  });

  // When user connets via webpage
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId())
    {
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
    clientConnected = true;
  });

  server.addHandler(&events);
  
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", WiFi.softAPIP());
   
  // Start web server 
  server.begin();
  Serial.println("Web Server Up");

  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP

  wsLED.Clear();
  //delay (500);
  wsLED.Brightness(20);
  wsLED.UpdateAll(wsLED.YELLOW); 
}

void loop() 
{
  if(clientConnected)
  { 
    dnsServer.processNextRequest();

    if ((millis() - lastTime) > timerDelay) 
    {
      // Send Events to the client with the Sensor Readings Every 3 seconds
      events.send("ping",NULL,millis());
      events.send(getSensorReadings().c_str(),"new_readings" ,millis());

      lastTime = millis();
    }
  }
  else
  {
    delay(500);
  }
  
  if(reboot)
  {
    restartDevice();
  }
}

