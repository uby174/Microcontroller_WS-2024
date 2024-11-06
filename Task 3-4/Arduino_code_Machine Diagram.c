// Define pin numbers for traffic lights
const int trafficGreenPin = 2;
const int trafficYellowPin = 3;
const int trafficRedPin = 4;

// Define pin numbers for pedestrian lights
const int pedestrianRedPin = 5;
const int pedestrianGreenPin = 6;

// Define pin number for pedestrian button
const int pedestrianButtonPin = 7;

// State definitions for traffic light system
enum TrafficState {
  TRAFFIC_GREEN,
  PEDESTRIAN_WAITING,
  TRAFFIC_YELLOW,
  TRAFFIC_RED
};

// State definitions for pedestrian light system
enum PedestrianState {
  PEDESTRIAN_RED,
  PEDESTRIAN_GREEN
};

// Initialize states
TrafficState trafficState = TRAFFIC_GREEN;
PedestrianState pedestrianState = PEDESTRIAN_RED;

// Timing variables (in milliseconds)
unsigned long stateStartTime = 0;

// Timeouts defined
const unsigned long TG_TIMEOUT = 10000;   // Traffic green timeout: 10 seconds
const unsigned long TYR_TIMEOUT = 2000;   // Green phase hold before pedestrian waiting: 2 seconds
const unsigned long TY_TIMEOUT = 5000;    // Traffic yellow timeout: 5 seconds
const unsigned long TR_TIMEOUT = 10000;   // Traffic red timeout: 10 seconds
const unsigned long PG_TIMEOUT = 10000;   // Pedestrian green timeout: 10 seconds

void setup() {
  // Initialize traffic light pins as outputs
  pinMode(trafficGreenPin, OUTPUT);
  pinMode(trafficYellowPin, OUTPUT);
  pinMode(trafficRedPin, OUTPUT);

  // Initialize pedestrian light pins as outputs
  pinMode(pedestrianRedPin, OUTPUT);
  pinMode(pedestrianGreenPin, OUTPUT);

  // Initialize pedestrian button pin as input with internal pull-up resistor
  pinMode(pedestrianButtonPin, INPUT_PULLUP);

  // Start with traffic green and pedestrian red lights on
  digitalWrite(trafficGreenPin, HIGH);
  digitalWrite(pedestrianRedPin, HIGH);

  stateStartTime = millis();  // Record the start time of the initial state
}

void loop() {
  unsigned long currentTime = millis();

  // Read the pedestrian button (active LOW)
  bool pedestrianButtonPressed = !digitalRead(pedestrianButtonPin);

  switch (trafficState) {
    case TRAFFIC_GREEN:
      if (currentTime - stateStartTime >= TG_TIMEOUT || pedestrianButtonPressed) {
        trafficState = PEDESTRIAN_WAITING;
        stateStartTime = currentTime;
      }
      break;

    case PEDESTRIAN_WAITING:
      if (currentTime - stateStartTime >= TYR_TIMEOUT) {
        trafficState = TRAFFIC_YELLOW;
        stateStartTime = currentTime;

        // Turn off traffic green, turn on traffic yellow
        digitalWrite(trafficGreenPin, LOW);
        digitalWrite(trafficYellowPin, HIGH);
      }
      break;

    case TRAFFIC_YELLOW:
      if (currentTime - stateStartTime >= TY_TIMEOUT) {
        trafficState = TRAFFIC_RED;
        stateStartTime = currentTime;

        // Turn off traffic yellow, turn on traffic red
        digitalWrite(trafficYellowPin, LOW);
        digitalWrite(trafficRedPin, HIGH);

        // Change pedestrian state to green
        pedestrianState = PEDESTRIAN_GREEN;
        digitalWrite(pedestrianRedPin, LOW);
        digitalWrite(pedestrianGreenPin, HIGH);
      }
      break;

    case TRAFFIC_RED:
      if (currentTime - stateStartTime >= TR_TIMEOUT) {
        trafficState = TRAFFIC_GREEN;
        stateStartTime = currentTime;

        // Turn off traffic red, turn on traffic green
        digitalWrite(trafficRedPin, LOW);
        digitalWrite(trafficGreenPin, HIGH);

        // Change pedestrian state to red
        pedestrianState = PEDESTRIAN_RED;
        digitalWrite(pedestrianGreenPin, LOW);
        digitalWrite(pedestrianRedPin, HIGH);
      }
      break;
  }

  // Manage pedestrian light timing
  if (pedestrianState == PEDESTRIAN_GREEN) {
    if (currentTime - stateStartTime >= PG_TIMEOUT) {
      pedestrianState = PEDESTRIAN_RED;
      digitalWrite(pedestrianGreenPin, LOW);
      digitalWrite(pedestrianRedPin, HIGH);
    }
  }
}
