#include <LiquidCrystal.h>

int state = 1;
int temp = A0;
int button = 7;
float prevTemper = 0;
int currentState = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void Display(int col, int row, String text){
  lcd.setCursor(col, row); 
  lcd.print(text);
}

void FirstState(){
  if (currentState==1) return;
  lcd.noDisplay();
  lcd.begin(16,2);
  Display(5, 0, "CLASS");
  Display(4, 1, "20CLC04");
  currentState = 1;
}

void SecondState(){
  delay(75);
  lcd.noDisplay();
  lcd.begin(16,2);
  Display(1, 0, "NguyenDuyThinh");
  Display(4, 1, "20127333");
  currentState=2;
}

void GetRealTimeTemper(int col, int row){
  float temper = ((analogRead(temp)*5.0/1023)/0.01)-50;
  if ((prevTemper != temper) or (currentState!=3)){
    Display(col, row, String(temper));
    prevTemper = temper;
  }
}

void ThirdState(){
  GetRealTimeTemper(8, 0);
  if (currentState==3) return;
  lcd.noDisplay();
  lcd.begin(16,2);
  Display(2, 0, "TEMP:");
  GetRealTimeTemper(8, 0);
  currentState=3;
}

void setup()
{
  pinMode(button, INPUT);
  pinMode(temp, INPUT);
  FirstState();
  Serial.begin(9600);
}


void loop()
{
  if(digitalRead(button)==HIGH){
    state++;
    if (state>3) state=1;
  }
  if (state==1) FirstState();
  else if (state==2) SecondState();
  else if (state==3) ThirdState();
  delay(120);
}