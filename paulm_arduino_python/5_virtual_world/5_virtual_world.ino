// Calculates distance with Ultrasonic sensor
// Sends to Serial Port for Python to read

int triggerPin = 10;
int echoPin=11;
int pingTravelTime;
int delayT1=10;
int delayT2=250;
float distance; // in cm
float velocity = 340; // in m/s

int count = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(triggerPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
sendPulse();
calculateDistance();
displayVelocity();
delay(delayT2);

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
  distance= velocity*100.*(pingTravelTime/2./1000000.);
}

void displayVelocity(){
Serial.println(distance);
}
