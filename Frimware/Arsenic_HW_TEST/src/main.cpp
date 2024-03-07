#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Bme280.h>
#include <WS2812Led.h>
#include <MAX17048.h>

#define I2C_SDA 7
#define I2C_SCL 6
#define ONE_WIRE_BUS 3
#define WS2812LedPin 10

WS2812Led wsLED(WS2812LedPin, 1);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;

Bme280TwoWire bme280;

MAX17048 pwr_mgmt;

void setup() 
{
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.println("Wire up");
  
  bme280.begin(Bme280TwoWireAddress::Primary);
  bme280.setSettings(Bme280Settings::indoor());
  Serial.println("BME280 up");

  pwr_mgmt.attatch(Wire);
  Serial.println("MAX17048 up");

  sensors.begin();
  Serial.println("Sensors DB up");
}

void loop() 
{
  wsLED.Clear();
  wsLED.Brightness(20);
  delay(500);
  wsLED.UpdateAll(wsLED.GREEN);

  Serial.println("LED - Green");
  
  auto temperature = String(bme280.getTemperature()) + " °C";
  Serial.println("BME280 temp " + temperature);

  auto humidity = String(bme280.getHumidity()) + " %";
  Serial.println("BME280 Hum " + humidity);

  auto pressure = String(bme280.getPressure() / 100.0) + " hPa";
  Serial.println("Bme Press " + pressure);

  sensors.requestTemperatures();
  
  float dstemp = sensors.getTempCByIndex(0);
  Serial.println("DS temp " + String(dstemp));

  Serial.println("VCELL ADC : ");
  Serial.println(pwr_mgmt.adc());
  Serial.print("VCELL V   : ");
  Serial.println(pwr_mgmt.voltage());
  Serial.print("VCELL SOC : ");
  Serial.print(pwr_mgmt.percent());
  Serial.println(" \%");
  Serial.print("VCELL SOC : ");
  Serial.print(pwr_mgmt.accuratePercent());
  Serial.println(" \%");
  Serial.println();

  delay(2000);
}

