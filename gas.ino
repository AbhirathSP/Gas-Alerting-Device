
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial gsm(9,10);
SoftwareSerial ss(6,5);
String phone_no1 = "8971504592";
//String phone_no2 = """;

void sendsms (String phone_no1,float level);
void sendsms1 (String phone_no2,float level);

void send_event(const char *event);

float level;
float rev=0;
int redLed = 12;
int greenLed = 11;
int buzzer = 7;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 300;


void isr() //interrupt service routine
{
rev++;
}

void setup()
{
  Serial.begin(9600);
  gsm.begin(9600);
  ss.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
 

  attachInterrupt(0,isr,RISING);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  level =analogSensor;
  lcd.setCursor(0,0);
  lcd.print("GAS ALERT");
  lcd.setCursor(0,1);
  lcd.print("Level=");
  lcd.print(level);
  lcd.print("");
  
  Serial.println("level-");
  Serial.println(level);
  delay(1000);
  if (analogSensor > sensorThres)
  {
    
    
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
    sendsms(phone_no1, level);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(100);




attachInterrupt(0,isr,RISING);
}





void sendsms(String phoneno,float level)
{
  
  bool newddata = false;
  unsigned long chars;
  unsigned short sentences,failed;
  float flat,flon;
  unsigned long age;
 
  gsm.print("AT+CMGF=1\r");
  delay(400);
  gsm.print("AT+CMGS=\"");
  gsm.print(phoneno);
  gsm.println("\"");
  delay(300);
  Serial.print("GAS IS LEAKING ");
  
  gsm.print("GAS IS LEAKING ");
  
 
  gsm.print(".....");
  
  
  gsm.print("LEVEL = ");
  gsm.print(level);
  gsm.print("");
  gsm.print("\n");
  
  


  
  //gsm.print("\n");

  
  Serial.println("\n ");
  
  
  
}
