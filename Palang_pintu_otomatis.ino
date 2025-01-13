#include <Servo.h> // Servo library
Servo myServo; // Servo instance
int angle = 0;

long duration;
int distance;

int echoPin = 11;
int trigPin = 12;
int ledPalangmerah = 9;
int ledPalanghijau = 8;
int buzzer = 10;

int sensorHujan = A0;
int ledHujan = 6;
int buzzer1 = 5;
int valueHujan;

void setup() {
  pinMode(ledPalangmerah, OUTPUT);
  pinMode(ledPalanghijau, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  myServo.attach(7); // Attach servo to pin 7
  myServo.write(0);  // Set servo to initial position

  pinMode(A0, INPUT);
  pinMode(ledHujan, OUTPUT);
  pinMode(buzzer1, OUTPUT);
}

void loop() {
  // Ultrasonic sensor reading
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance < 7) {
    angle = 90; 
    digitalWrite(ledPalangmerah, LOW);
    digitalWrite(ledPalanghijau, HIGH);
    tone(buzzer, 1000); 
  } else {
    angle = 0; 
    digitalWrite(ledPalangmerah, HIGH);
    digitalWrite(ledPalanghijau, LOW);
    noTone(buzzer); 
  }

  myServo.write(angle);
  delay(500); 

  valueHujan = analogRead(sensorHujan);
  if (valueHujan < 100){
    digitalWrite(ledHujan, HIGH);
    tone(buzzer1,1000);  
  } else {
    digitalWrite (ledHujan, LOW);
    noTone(buzzer1);
  } 
}
