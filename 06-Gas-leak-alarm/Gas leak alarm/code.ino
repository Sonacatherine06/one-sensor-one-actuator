int gasSensor = A0;
int buzzer = 8;

void setup()
{
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int gasValue = analogRead(gasSensor);

  Serial.println(gasValue);

  if(gasValue > 400)
  {
    digitalWrite(buzzer, HIGH);
  }
  else
  {
    digitalWrite(buzzer, LOW);
  }

  delay(200);
}