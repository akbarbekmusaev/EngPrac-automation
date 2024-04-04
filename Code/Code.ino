
const int closingButtonPin =  5;
const int openingButtonPin =  6; 
const int emergencyButtonPin =  7; 
const int motorDirectionPin =  3;
const int motorSwitcherPin =  4;
const int mechanismOpenedSensorPin =  2;
const int mechanismClosedSensorPin =  3;
const int motorSpeedSensorPin =  8;


void setup() {
  pinMode(closingButtonPin, INPUT);
  pinMode(openingButtonPin, INPUT);
  pinMode(emergencyButtonPin, INPUT);
  pinMode(motorDirectionPin, OUTPUT);
  pinMode(motorSwitcherPin, OUTPUT);
  pinMode(mechanismOpenedSensorPin, INPUT);
  pinMode(mechanismClosedSensorPin, INPUT);
}

int closingButtonState = digitalRead(closingButtonPin);
int openingButtonState = digitalRead(openingButtonPin);
int emergencyButtonState = digitalRead(emergencyButtonPin);
int mechanismOpenedSensorState = digitalRead(mechanismOpenedSensorPin);
int mechanismClosedSensorState = digitalRead(mechanismClosedSensorPin);
int motorSpeed = analogRead(motorSpeedSensorPin);
const int motorSpeedThreshold = 500;

void loop() {
  if (mechanismClosedSensorState == HIGH && openingButtonPin == HIGH) {
    while (mechanismOpenedSensorState != HIGH) {
      digitalWrite(motorDirectionPin, HIGH);
      digitalWrite(motorSwitcherPin, HIGH);
      if (motorSpeed < motorSpeedThreshold) {
        while (mechanismClosedSensorPin != HIGH) {
          digitalWrite(motorDirectionPin, LOW);
          digitalWrite(motorSwitcherPin, HIGH);
        }
        break;
      }
    }
  } else if (mechanismOpenedSensorState == HIGH && closingButtonState == HIGH) {
    while (mechanismClosedSensorState != LOW) {
      digitalWrite(motorDirectionPin, LOW);
      digitalWrite(motorSwitcherPin, HIGH);
      if (motorSpeed < motorSpeedThreshold) {
        while (mechanismOpenedSensorPin != HIGH) {
          digitalWrite(motorDirectionPin, HIGH);
          digitalWrite(motorSwitcherPin, HIGH);
        }
        break;
      }
    }
  } else if (emergencyButtonState == HIGH) {
      digitalWrite(motorSwitcherPin, LOW);
  }
}
