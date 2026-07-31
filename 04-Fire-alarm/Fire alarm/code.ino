int tempSensor = A0;
int ldrSensor = A1;

int led = 13;
int buzzer = 8;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  int tempValue = analogRead(tempSensor);
  int lightValue = analogRead(ldrSensor);

  Serial.print("Temperature value: ");
  Serial.println(tempValue);

  Serial.print("Light value: ");
  Serial.println(lightValue);

  // TMP36 controls LED
  if (tempValue > 300) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  // LDR controls buzzer
  if (lightValue < 500) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}