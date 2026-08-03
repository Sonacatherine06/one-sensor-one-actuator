#include <Servo.h>

Servo waterServo;

int soilSensor = A0;
int servoPin = 9;

void setup()
{
  waterServo.attach(servoPin);
  Serial.begin(9600);
}

void loop()
{
  int moistureValue = analogRead(soilSensor);

  Serial.println(moistureValue);

  if (moistureValue < 500)
  {
    // Dry soil - open water valve
    waterServo.write(90);
  }
  else
  {
    // Wet soil - close water valve
    waterServo.write(0);
  }

  delay(1000);
}