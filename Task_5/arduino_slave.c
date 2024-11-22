#include <Wire.h>

#define PEDESTRIAN_RED_LED 10
#define PEDESTRIAN_GREEN_LED 11

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);


  pinMode(PEDESTRIAN_RED_LED, OUTPUT);
  pinMode(PEDESTRIAN_GREEN_LED, OUTPUT);


  digitalWrite(PEDESTRIAN_RED_LED, HIGH);
  digitalWrite(PEDESTRIAN_GREEN_LED, LOW);
}

void loop() {
}

void receiveEvent(int bytesReceived) {
  while (Wire.available()) {
    char command = Wire.read();
    if (command == 'G') {
      // Turn pedestrian green light ON, red light OFF
      digitalWrite(PEDESTRIAN_GREEN_LED, HIGH);
      digitalWrite(PEDESTRIAN_RED_LED, LOW);
    } else if (command == 'R') {
      // Turn pedestrian red light ON, green light OFF
      digitalWrite(PEDESTRIAN_GREEN_LED, LOW);
      digitalWrite(PEDESTRIAN_RED_LED, HIGH);
    }
  }
}
