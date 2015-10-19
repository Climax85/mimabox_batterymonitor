#include <Wire.h>
#include <PCD8544.h>
#include <Adafruit_INA219.h>

//Konfiguration
#define enableChargePin  12
#define inaVoltageFactor 1.113

//LCD Setup
#define SCLK    12
#define MOSI    11
#define DC      10
#define RST      9
#define SCE      8
#define WIDTH   84
#define HEIGHT  48
PCD8544 lcd(SCLK, MOSI, DC, RST, SCE);

//shunt current sensor
Adafruit_INA219 ina219;

//initialize variables
float shuntvoltage   = 0;
float busvoltage     = 0;
float current_mA     = 0;
float loadvoltage    = 0;
float systemvoltage  = 0;
float sum_mA         = 0;

void setup(void)
{
  Serial.begin(115200);
  
  //Initialize the 5110 LCD - Display
  lcd.begin(WIDTH, HEIGHT);
  lcd.setContrast(55);
  lcd.setCursor(0, 0);
  lcd.print(" Akku Monitor");
  
  //Initialize the INA219 - on I2C Bus (A4 & A5)
  ina219.begin();
}

void loop(void)
{
  shuntvoltage  = ina219.getShuntVoltage_mV();
  busvoltage    = ina219.getBusVoltage_V();
  
  //Math for system load voltage with correction factor
  loadvoltage   = ( busvoltage + (shuntvoltage / 1000) ) * inaVoltageFactor;
  
  //measure current
  current_mA    = ina219.getCurrent_mA();
  //add current to sum
  sum_mA       += current_mA;
  
  //print to LCD
  lcd.setCursor(10, 3);
  lcd.print(loadvoltage, 2); lcd.print(" V");
  lcd.setCursor(10, 4);
  lcd.print(current_mA, 1); lcd.print(" mA");
  lcd.setCursor(10, 5);
  lcd.print(sum_mA / 3600, 2); lcd.print(" mAh");
  
  //print to Serial
  Serial.print("Load Voltage: "); Serial.print(loadvoltage, 4); Serial.print(" V");
  Serial.print(" | Current: "); Serial.print(current_mA); Serial.print(" mA");
  Serial.print(" | "); Serial.print(sum_mA); Serial.print(" mA");
  Serial.print(" | "); Serial.print(sum_mA / 3600); Serial.println(" mAh");

  //measure every second
  delay(1000);
}
