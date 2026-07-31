#include <Servo.h>

Servo gate;

int trigPin = 7;
int echoPin = 6;
int buttonPin = 2;

int ledPin = 13;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);

  gate.attach(9);
  gate.write(0);

  Serial.begin(9600);
}

void loop() {

  // Ultrasonic measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Read pushbutton
  int buttonState = digitalRead(buttonPin);

  Serial.print("Distance: ");
  Serial.println(distance);

  // Button pressed AND vehicle is near
  if (buttonState == LOW && distance < 50) {

    gate.write(90);
    digitalWrite(ledPin, HIGH);

  } else {

    gate.write(0);
    digitalWrite(ledPin, LOW);

  }

  delay(100);
}