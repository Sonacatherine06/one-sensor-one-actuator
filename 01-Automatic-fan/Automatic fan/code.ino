int tempPin = A0;
int motor = 9;

void setup() {
  pinMode(motor, OUTPUT);
}

void loop() {
  int value = analogRead(tempPin);
  float voltage = value * 5.0 / 1023.0;
  float temp = (voltage - 0.5) * 100;

  if (temp > 30)
    digitalWrite(motor, HIGH);
  else
    digitalWrite(motor, LOW);

  delay(500);
}