#include <Wire.h>
#include <Adafruit_INA219.h>

//shunt current sensor
Adafruit_INA219 ina219;

void setup(void) 
{  
  Serial.begin(115200);
  Serial.println("Hello!");
  
  // Initialize the INA219.
  ina219.begin();
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  //print measurements of INA219 to console
  Serial.print("Load Voltage: "); Serial.print(loadvoltage); Serial.print(" V");
  Serial.print(" - Current: "); Serial.print(current_mA); Serial.println(" mA");

  //measure every second
  delay(1000);
}
