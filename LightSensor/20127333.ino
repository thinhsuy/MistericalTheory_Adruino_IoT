// C++ code
//
int sensor = A0;
int light = 2;
void setup()
{
  pinMode(sensor, INPUT);
  pinMode(light, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(sensor);
  if (value>=500)
  	digitalWrite(light, HIGH);
  else 
    digitalWrite(light, LOW);
}