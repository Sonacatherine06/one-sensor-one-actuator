#include <Servo.h>

Servo lid;

int trig = 7;
int echo = 6;
int ldr = A0;
int buzzer = 8;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);

  lid.attach(9);
  lid.write(0);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  int distance = duration * 0.034 / 2;

  int light = analogRead(ldr);

  if (distance < 20) {
    lid.write(90);
  } 
  else {
    lid.write(0);
  }

  if (light < 300) {
    digitalWrite(buzzer, HIGH);
  } 
  else {
    digitalWrite(buzzer, LOW);
  }
}