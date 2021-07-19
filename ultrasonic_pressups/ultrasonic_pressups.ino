// Count pressups using ultrasonic sensor

int triggerPin = 2;
int echoPin=3;
int pingTravelTime; // in micro seconds
float pingTravelTimeSeconds;
int delayT1=10;
int delayT2=100;
int delayT3=250;
float distance; // in cm
float previousDistance;
int arrayLength = 10;
float distances[10];
float sum=0;
float velocityCmPerSecond = 340*100.; // in cm/s
int pressupTriggerPosition=15;

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


int pressupCount = 0;
boolean bodyDown = false;
boolean oldPosition = false;
int startTime = millis()-5000;
int endTime;
float elapsedTime;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  
  lcd.begin(16,2); // size
  
  displayTime = millis();
  displayStart();

}

void loop() {
  // put your main code here, to run repeatedly: 
  sendPulse();
  calculateDistance();
  displayDistance();
  countPressups();
}

void displayStart(){
  lcd.setCursor(0,0);
  lcd.print("Begin pressups!");
}

void sendPulse(){
  // launch ultrasonic wave.
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(delayT1);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(delayT1);
  digitalWrite(triggerPin, LOW);
  
  // echoPin goes high until sound wave returns
  // measure how long echoPin is high
  pingTravelTime = pulseIn(echoPin, HIGH); 
}

void countPressups(){
  if((distance<=pressupTriggerPosition)&&(!bodyDown)){
    bodyDown = true;
    digitalWrite(buzzPin, HIGH);
    endTime = millis();
    elapsedTime = endTime-startTime;
    
    if (elapsedTime/1000>=5){
      // restart timer if long break    
      pressupCount = 0;
      lcd.clear();
    }
    
    pressupCount++;
    startTime = endTime;
    displayPressups();
  }
  else if ((distance>pressupTriggerPosition)&&(bodyDown)){
    bodyDown = false;
    digitalWrite(buzzPin, LOW);
    Serial.println("up");
  }
}

void displayPressups(){
  Serial.println("down");
    Serial.println(pressupCount);
    lcd.setCursor(0,0);
    lcd.print(pressupCount);
    lcd.print("  pressups");
    //delay(200);
}

void calculateDistance(){
  pingTravelTimeSeconds = pingTravelTime/1000000.;
  distance= velocityCmPerSecond*(pingTravelTimeSeconds/2.);
}

void displayDistance(){
  if (millis()-displayTime>1000){
    // only change display display every 1 second
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.print( " cm");
    Serial.print("distance ");
    Serial.println(distance);
    displayTime = millis();
    // for some reason, every 30 secs it just starts streaming data
  }
}
