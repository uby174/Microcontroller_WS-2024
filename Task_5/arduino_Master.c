#include <Wire.h>


#define RED_LED 9
#define YELLOW_LED 10
#define GREEN_LED 11
#define BUTTON_PIN 2


enum State { RED, YELLOW, GREEN };
State currentState = GREEN;


volatile bool buttonPressed = false;
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;


const int GREEN_TIME = 5000;    
const int YELLOW_TIME = 2000; 
const int RED_TIME = 5000;     
const int PEDESTRIAN_TIME = 5000; 

void setup() {
  Wire.begin();

  
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);


  pinMode(BUTTON_PIN, INPUT_PULLUP);

 
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);


  setTrafficLights(HIGH, LOW, LOW);
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;
    handlePedestrianCrossing();
  } else {
    trafficLightSequence();
  }
}

void trafficLightSequence() {
  switch (currentState) {
    case GREEN:
      setTrafficLights(HIGH, LOW, LOW);
      delay(GREEN_TIME);
      currentState = YELLOW;
      break;

    case YELLOW:
      setTrafficLights(LOW, HIGH, LOW); 
      delay(YELLOW_TIME);
      currentState = RED;
      break;

    case RED:
      setTrafficLights(LOW, LOW, HIGH); 
      sendCommandToSlave('R'); 
      delay(RED_TIME);
      currentState = GREEN;
      break;
  }
}

void handlePedestrianCrossing() {

  setTrafficLights(LOW, LOW, HIGH); 
  sendCommandToSlave('R'); // Ensure pedestrian red is ON
  delay(1000); 
  // Activate pedestrian green light
  sendCommandToSlave('G'); 
  delay(PEDESTRIAN_TIME);

  // Turn pedestrian light back to red
  sendCommandToSlave('R'); 
  delay(1000); 

  // Resume normal operation
  currentState = GREEN;
}

void handleButtonPress() {
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    buttonPressed = true;
    lastDebounceTime = currentTime;
  }
}

void setTrafficLights(int greenState, int yellowState, int redState) {
  digitalWrite(GREEN_LED, greenState);
  digitalWrite(YELLOW_LED, yellowState);
  digitalWrite(RED_LED, redState);
}

void sendCommandToSlave(char command) {
  Wire.beginTransmission(8); // Address of the slave
  Wire.write(command);
  Wire.endTransmission();
}
