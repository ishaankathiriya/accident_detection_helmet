const int vibPin = 8;
const int sw = 10;
const int buzzer = 7;
const int signal = 6; // Connect NANO Pin 6 to ESP D5
int i = 0;
void setup() {
  Serial.begin(9600);
  pinMode(vibPin, INPUT);
  pinMode(signal, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
}
void loop() {
  if (digitalRead(vibPin) == 0) {
    for (i = 1; i <= 10; i++) {
      Serial.println("Accident Detected!");
      digitalWrite(buzzer, HIGH);
      delay(250);
      digitalWrite(buzzer, LOW);
      delay(250);
      if (digitalRead(sw) == LOW) {
        Serial.println("Accident Deactivated!");
        // Deactivate
        digitalWrite(buzzer, LOW);
        break;
      }
    }
    if(i > 10)
    {
      digitalWrite(signal, HIGH);
      Serial.println("Accident Signal Activated!");
      delay(10000);
      digitalWrite(signal, LOW);
      Serial.println("Accident Signal Deactivated!");
      i = 0;
    }
  }
  delay(10);
}

// Pending!!