#include <LiquidCrystal.h>

int ThermistorPin = 0;
int Vo;
int wanted = 0;
int counter=0;
float R1 = 9800;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
lcd.begin(16, 2);
pinMode(6, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(5, OUTPUT);
pinMode(2, OUTPUT);
lcd.setCursor(0, 0);
lcd.print("HEATBED VLO");
lcd.setCursor(0, 1);
lcd.print("Booting up.");
delay(1000);
lcd.print(".");
delay(1000);
lcd.print(".");
delay(1000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Authors: ");
lcd.setCursor(0, 1);
lcd.print("M. Baczmanski");
delay(2000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Authors: ");
lcd.setCursor(0, 1);
lcd.print("J. Dziedzicd");
delay(2000);
lcd.clear();
}

void loop() {
  counter++;
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  if(counter==15)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(T);   
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Wanted: ");
  lcd.print(wanted);   
  lcd.print(" C"); 
  if (digitalRead(6)==LOW)
  {
    wanted++;
    if (wanted>70)
    wanted=70;
  }
  if (digitalRead(3)==LOW)
  {
    wanted--;
    if(wanted<0)
    wanted=0;
  } 
  counter=0;          
  }
  delay(10);

  if(wanted<T)
{
  digitalWrite(5, LOW);
  digitalWrite(2, LOW);
}
else
{
  digitalWrite(5, HIGH);
  digitalWrite(2, HIGH);
}
}
