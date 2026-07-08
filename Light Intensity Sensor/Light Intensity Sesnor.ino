int ldrPin = A0;
int ledPin = 8;
int buzzerPin = 9;
int ldrValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  ldrValue = analogRead(ldrPin);

  Serial.print("LDR Value: ");
  Serial.print(ldrValue);

  if (ldrValue < 500) {   // BRIGHT (low value)
    Serial.println(" (DARK)");
    digitalWrite(ledPin, LOW);   // OFF
    digitalWrite(buzzerPin, LOW);
  }
  else {                  // DARK (high value)
    Serial.println(" (BRIGHT)");
    digitalWrite(ledPin, HIGH);  // ON
    digitalWrite(buzzerPin, HIGH);
  }

  delay(200);
}
