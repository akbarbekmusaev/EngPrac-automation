
const int closingButtonPin =  5;
const int openingButtonPin =  6; 
const int emergencyButtonPin =  7; 
const int motorDirectionPin =  3;
const int motorSwitcherPin =  4;
const int mechanismOpenedSensorPin =  2;
const int mechanismClosedSensorPin =  3;
const int motorSpeedSensorPin =  8;
const int tipoverSensorPin =  9; 


void setup() {
  pinMode(closingButtonPin, INPUT);
  pinMode(openingButtonPin, INPUT);
  pinMode(emergencyButtonPin, INPUT);
  pinMode(motorDirectionPin, OUTPUT);
  pinMode(motorSwitcherPin, OUTPUT);
  pinMode(mechanismOpenedSensorPin, INPUT);
  pinMode(mechanismClosedSensorPin, INPUT);
  pinMode(motorSpeedSensorPin, INPUT);
  pinMode(tipoverSensorPin, INPUT);
}

int closingButtonState = digitalRead(closingButtonPin);
int openingButtonState = digitalRead(openingButtonPin);
int emergencyButtonState = digitalRead(emergencyButtonPin);
int mechanismOpenedSensorState = digitalRead(mechanismOpenedSensorPin);
int mechanismClosedSensorState = digitalRead(mechanismClosedSensorPin);
int motorSpeed = analogRead(motorSpeedSensorPin);
const int motorSpeedThresholdOpening = 500;
const int motorSpeedThresholdClosing = 500;

void loop() {
  if (emergencyButtonState == LOW) {
    if (openingButtonPin == HIGH) {
    while (mechanismOpenedSensorState != HIGH) {
      digitalWrite(motorDirectionPin, HIGH);
      digitalWrite(motorSwitcherPin, HIGH);
      if (motorSpeed < motorSpeedThresholdOpening) {
        digitalWrite(motorSwitcherPin, LOW);
        break;
      }
    }
    } else if ( closingButtonState == HIGH) {
    while (mechanismClosedSensorState != HIGH) {
      digitalWrite(motorDirectionPin, LOW);
      digitalWrite(motorSwitcherPin, HIGH);
      if (motorSpeed < motorSpeedThresholdClosing) {
        digitalWrite(motorSwitcherPin, LOW);
        break;
      }
    }
  }} else if (emergencyButtonState == HIGH) {
      digitalWrite(motorSwitcherPin, LOW);
  }
}
}