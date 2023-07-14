// C++ code
//
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int temp = A0;
float prevTemp = 0;

float getTempSensor()
{
  int Analog = analogRead(temp);
  float celsius = ((Analog*5.0/1023)/0.01)-50;
  return celsius;
}
  
void LCD(){
  lcd.begin(16, 12);
  lcd.print("Current Temp is");
}
  
void setup()
{
  pinMode(temp, INPUT);
  Serial.begin(9600);  
  LCD();
}

void loop()
{
  if (getTempSensor()!=prevTemp){
  	prevTemp = getTempSensor();
    lcd.setCursor(0, 1);
  	lcd.print(getTempSensor());
  }
}