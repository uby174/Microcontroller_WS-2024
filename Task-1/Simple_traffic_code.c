enum TrafficLightState { RED, GREEN, YELLOW };
TrafficLightState currentState = RED;

unsigned long previousMillis = 0;

const unsigned long redDuration = 20000;    // 20 seconds
const unsigned long greenDuration = 15000;  // 15 seconds
const unsigned long yellowDuration = 5000;  // 5 seconds

void setup() {
  pinMode(13, OUTPUT); // Red LED
  pinMode(12, OUTPUT); // Yellow LED
  pinMode(11, OUTPUT); // Green LED
}

void loop() {
  unsigned long currentMillis = millis();

  switch (currentState) {
    case RED:
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);

      if (currentMillis - previousMillis >= redDuration) {
        previousMillis = currentMillis;
        currentState = GREEN;
      }
      break;

    case GREEN:
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);

      if (currentMillis - previousMillis >= greenDuration) {
        previousMillis = currentMillis;
        currentState = YELLOW;
      }
      break;

    case YELLOW:
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);

      if (currentMillis - previousMillis >= yellowDuration) {
        previousMillis = currentMillis;
        currentState = RED;
      }
      break;
  }
}
