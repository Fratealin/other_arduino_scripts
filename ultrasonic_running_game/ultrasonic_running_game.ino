// Toggles between armed and unarmed at random intervals
// When player moves into zone, alarm sounds
// See how many times you can get into the zone
int triggerPin = 4;
int echoPin=5;
int pingTravelTime;
int delayT1=10;
int delayT2=100;
int delayT3=500;
int randomDT=10000;
float distance; // in cm
int arrayLength = 5;
float distances[5];
float sum=0;
float velocity = 340; // in m/s
int triggerDistance=100;

int bluePin=2;
int buzzPin=3;
boolean armed = false;
boolean triggered = false;
int count;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(triggerPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(bluePin, OUTPUT);
pinMode(buzzPin, OUTPUT);

// if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  getRandomDelayTime();

}

void loop() {
  // put your main code here, to run repeatedly:
  count = randomDT;
  while(count>0){

    sendPulse();
    calculateDistance();
    displayDistance();
    
    triggerAlarm();
    
    delay(delayT3);
    count--;
    Serial.println(armed);
    Serial.println(count);
  }
 toggleAlarm();
 
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
Serial.print("distance ");
Serial.println(distance);

}

void toggleAlarm(){
  if (armed==true){
    armed=false;
  }
  else{
    armed=true;
  }
}

void getRandomDelayTime(){
  randomDT = random(10, 25);
  Serial.println(randomDT);
}

void triggerAlarm(){
  if ((distance<=triggerDistance)&&(armed==true)){
  digitalWrite(bluePin, HIGH);
  digitalWrite(buzzPin, HIGH);
  triggered = true;
  
  }
  else if ((distance>triggerDistance)&&(armed==true)){
    // when player moves out of zone, resets to unarmed
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzPin, LOW);
    if (triggered==true){
      triggered=false;
      count=1;
    }
  }
  else {
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzPin, LOW);
    triggered= false;
  }
}
