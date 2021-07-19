// Switches light on when user enters the room
// Uses Ultrasonic Sensor
int triggerPin = 2;
int echoPin=3;
int pingTravelTime;
float pingTravelTimeSeconds;
int delayT1=10;
int delayT2=100;
int delayT3=250;
float distance; // in cm
int arrayLength = 5;
float distances[5];
float sum=0;
float velocity = 340; // in m/s
float velocityCmPerSecond = 340*100.; // in cm/s
int ledPin=6;
int triggerDistance = 5;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sendPulse();
  calculateDistance();
  lightSwitch();
  displayDistance();
  delay(delayT3);
}

void sendPulse(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(delayT1);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(delayT1);
  digitalWrite(triggerPin, LOW); // launches sound wave.
  // echoPin goes high until sound wave returns
  pingTravelTime = pulseIn(echoPin, HIGH); // measures how long echoPin is high
}

void calculateDistance(){
  pingTravelTimeSeconds = pingTravelTime/1000000.;
  distance= velocityCmPerSecond*(pingTravelTimeSeconds/2.);
}

void lightSwitch(){
  if(distance<=triggerDistance){
    digitalWrite(ledPin, HIGH);
    delay(10000);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}

void displayDistance(){
  Serial.print("distance ");
  Serial.println(distance);
}
