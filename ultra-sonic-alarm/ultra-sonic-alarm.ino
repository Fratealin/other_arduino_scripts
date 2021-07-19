int triggerPin = 2;
int echoPin=3;
int pingTravelTime;
int delayT1=10;
int delayT2=100;
int delayT3=500;
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

#include <IRremote.h> //Make sure to install the library
int IRpin=5;
IRrecv IR(IRpin);
decode_results cmd;
String myCom;

int triggerDistance = 150;
int password[] = {0xFF38C7};
int pwdLength=1;
int userInput[1];
int count = 0;
boolean armed = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  
  lcd.begin(16,2); // size
  IR.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  setAlarm();  
  sendPulse();
  calculateDistance();
  displayDistance();
  triggerAlarm();
  delay(delayT3);
}

void setAlarm(){
  if(!armed){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter code");
    lcd.setCursor(0,1);
    lcd.print("To set alarm");
    
    checkPassword();
    armed = true;
    }
    lcd.clear();
    lcd.print("Alarm armed");
}

void checkPassword(){
  // wait for button press
  while (IR.decode(&cmd)==0){ 
    }
  Serial.println(cmd.value,HEX);
  // Todo allow for password with more than one key
  // for(count=0; count<pwdLength;count++){
  // if (cmd.value==0xFFA25D){
  //  count=0;
  //  IR.resume();
  //  }
  //else{
  //  userInput[count]=cmd.value;
  //  }
  if(cmd.value!=0xFF38C7){
    Serial.println("wrong pwd");
    IR.resume();
    checkPassword();
  }
  Serial.println("correct");
  IR.resume();
}


void sendPulse(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(delayT1);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(delayT1);
  digitalWrite(triggerPin, LOW); // launches ultrasonic wave.
  digitalWrite(bluePin, HIGH);
  // echoPin goes high until sound wave returns
  pingTravelTime = pulseIn(echoPin, HIGH); // measures how long echoPin is high
  digitalWrite(bluePin, LOW);
}

void calculateDistance(){
  distance= velocity*100.*(pingTravelTime/2./1000000.);
  }

void displayDistance(){
  Serial.print("distance ");
  Serial.println(distance);
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print( " cm");
}

void triggerAlarm(){
  if (distance<=triggerDistance){
    digitalWrite(bluePin, HIGH);
    digitalWrite(buzzPin, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Intruder alert!");
    lcd.setCursor(0,1);
    lcd.print("Enter code:");
    checkPassword();
    //delay(1000);
    
    armed=false;
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzPin, LOW);
  }
  else{
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzPin, LOW);
  }
}
