int triggerPin = 2;
int echoPin=3;
int pingTravelTime;
int delayT1=10;
int delayT2=100;
int delayT3=250;
float distance; // in cm
int arrayLength = 5;
float distances[5];
float sum=0;
float velocity = 340; // in m/s
int closeDistance=200;

int bluePin=20;
int buzzPin=4;
// Load library for lcd
#include <LiquidCrystal.h>
int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
// instantiate lcd object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int displayTime;

#include <IRremote.h> //Make sure to install the library
int IRpin=5;
IRrecv IR(IRpin);
decode_results cmd;
String myCom;

int lapCount = 0;
boolean startedRunning = false;
boolean oldPosition = false;
int startTime = millis()-5000;
int endTime;
float elapsedTime;
float fastestLap;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  
  lcd.begin(16,2); // size
  IR.enableIRIn();
  
  displayTime = millis();
  displayStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  sendPulse();
  calculateDistance();
  //displayDistance();
  countLaps();
}


void displayStart(){
  lcd.setCursor(0,0);
  lcd.print("Begin running!");
}

void countLaps(){
  endTime = millis();
  elapsedTime = endTime - startTime;
  if((distance>=10)&&(!startedRunning)){
    startedRunning = true;
    beep();

    //endTime = millis();
    //elapsedTime = endTime-startTime;
    startTime = endTime;

    if (elapsedTime/1000>=5){
      // restart timer if long break
      Serial.println("firstlap");    
      lapCount = 0;
      startBeep();
      lcd.clear();
    }

    Serial.println("started running");
    Serial.println(lapCount);
    lcd.setCursor(0,0);
    lcd.print(lapCount);
    lcd.print(" laps");

    //delay(200);
  }
  else if ((distance<10)&&(startedRunning)){
    lcd.clear();
    Serial.println(elapsedTime/1000);

    lapCount++;
    if (lapCount ==1){
      fastestLap = elapsedTime;
          beep();
    }
    else if ((lapCount!=1)&&(elapsedTime<fastestLap)){
      fastestBeep();
      fastestLap = elapsedTime;
      Serial.println("fastestLap");
      lcd.setCursor(8,0);
      lcd.print("fastest Lap");
    }
    else{
    beep();
    }
    

    //endTime = millis();
    //elapsedTime = endTime - startTime;
    displayLaps();

    startedRunning = false;
  }
  
}

void startBeep(){
  Serial.println("firstlap");    

  digitalWrite(buzzPin, HIGH);
  delay(delayT2);
  digitalWrite(buzzPin, LOW);
  delay(delayT2);
}

void fastestBeep(){
  tone(buzzPin, 2000);
  delay(delayT2);
  tone(buzzPin, 2500);
  delay(delayT2);
  tone(buzzPin, 3000);
  delay(delayT2);
  noTone(buzzPin);
}


void beep(){
  digitalWrite(buzzPin, HIGH);
  delay(delayT2);
  digitalWrite(buzzPin, LOW);
}
void displayLaps(){
  lcd.setCursor(0,0);
  lcd.print(lapCount);
  lcd.print(" laps");
  lcd.setCursor(0,1);
  lcd.print(elapsedTime/1000);
  lcd.print(" secs");
}

void sendPulse(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(delayT1);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(delayT1);
  digitalWrite(triggerPin, LOW); // launches sound wave.
  digitalWrite(bluePin, HIGH);
  // echoPin goes high until sound wave returns
  pingTravelTime = pulseIn(echoPin, HIGH); // measures how long echoPin is high
  digitalWrite(bluePin, LOW);
}

void calculateDistance(){
  distance= velocity*100.*(pingTravelTime/2./1000000.);
}

void displayDistance(){

if (millis()-displayTime>1000){
  // only change distance display every .5 seconds
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print( " cm");
  Serial.print("distance ");
  Serial.println(distance);
  displayTime = millis();
  // for some reason, every 30 secs it just starts streaming it
}

}
