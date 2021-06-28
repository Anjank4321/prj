#include <LiquidCrystal.h>
#include<SoftwareSerial.h>

LiquidCrystal lcd(3,4,5,6,7,8);
int sensorpin = A0;
int buzzer = 13;
int gled = 11;
int rled = 12;
int data = 0;
SoftwareSerial mySerial(9,10);
void setup() 
{
  pinMode(sensorpin,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(rled,OUTPUT);
  randomSeed(analogRead(0));
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" gas detection");
  lcd.setCursor(0,1);
  lcd.print("using gsm module alarm");
  delay(3000);
  lcd.clear();
  }

void loop() 
{
  digitalWrite(gled,HIGH);
  data= analogRead(sensorpin);
  Serial.print("gaslevel:");
  Serial.println("data");
  lcd.print("gas scan is on");
  lcd.setCursor(0,1);
  lcd.print("gas level");
  lcd.print(data);
  delay(1000);
  
     if(data>500)
  {   
    digitalWrite(buzzer,HIGH);
    digitalWrite(rled,HIGH);
    digitalWrite(gled,LOW);
    SendMessage();
    Serial.print("gas detect alarm");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("gas level exceed");
    lcd.print(0,1);
    lcd.print("sms sent");
    delay(1000);
  }
  else
  {
    Serial.print("gas detect alarm");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("gas level normal");
    lcd.print(0,1);
    digitalWrite(buzzer,HIGH);
    digitalWrite(rled,HIGH);
    digitalWrite(gled,LOW);
    delay(1000);
  }
}
  void SendMessage()
  {
    mySerial.println("AT+CMGF=1");
    delay(1000);
    mySerial.println("AT+CMGF=\"+918897625815\"\r");
    delay(1000);
    mySerial.println("Excess gas detected.be carefull");
    delay(1000);
    mySerial.println((char)26);
    delay(1000);
  }
