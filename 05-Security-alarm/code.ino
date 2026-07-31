int pir = 2;
int button = 3;
int led = 13;
int buzzer = 8;

void setup() {
  pinMode(pir, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int motion = digitalRead(pir);
  int buttonState = digitalRead(button);

  if (motion == HIGH || buttonState == LOW) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
  } 
  else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }
}