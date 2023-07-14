void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //set up the gate
  pinMode(2, OUTPUT);
  pinMode(8, INPUT);
  //set up AnaLog
  pinMode(A0, INPUT);
  int gate = 8;
}


void Button(){
  digitalWrite(2, HIGH);
  //pass the electric to gate
  digitalWrite(2, LOW);
  //time sleep
  delay(1000);
  //get input for gate
  if (digitalRead(8)==HIGH)
    Serial.println("Button pressed");
  else
    Serial.println("Button release");
}


void Potentiometer(){
  //gate should be ~a and value in must be 5v
  int value = analogRead(A0);
  int led = map(value, 0, 1023, 0, 225);
  analogWrite(gate, led); 
}


void Buzzer(){
  for (int i=0; i<180; i++){
    //convert degrees to radians
    float sinVal = sin(i*(3.1412/180));
    //generate a frequency from sinValue
    int toneVal = 2000+(int(sinVal*1000));
    tone(gate, toneVal);
    delay(2);
  }
}


long UltrasonicSensor(){
  int trigger = 2;
  int echo = 3;
  //340m/s => 0,034cm/microsecond 
  //value in must be 5v 
  //anti glitch
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  //start sensor
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
    
  long duration = pulseIn(echo, HIGH);
  long distanceCm = duration*0.034/2;
  return distanceCm;
}


void PhotoSensor(){
  int light = A0;
  pinMode(light, INPUT);
  int value = analogRead(light);
  Serial.println(value);
}


#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void LCD(){
  lcd.begin(16, 2);
  lcd.print("Hello World");
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
}


void PirSensor(){
  int sensor = 2;
  pinMode(sensor, INPUT);
  int value = digitalRead(sensor);
  Serial.println(value);
}


void TempSensor()
{
  int Analog = analogRead(A0);
  float celsius = ((Analog*5.0/1023)/0.01)-50;
  Serial.println(celsius);
}


#include <Servo.h>
Servo myservo;
void Servo(){
  int servo = 6; //~
  //set up
  myservo.attach(servo);
  //loop
  myservo.write(90);
}
void loop() {
  // put your main code here, to run repeatedly:
  
  
}

//to run debugging Ctrl+R
//to upload Ctrl+U
//to run monitor Ctrl+Shift+M
