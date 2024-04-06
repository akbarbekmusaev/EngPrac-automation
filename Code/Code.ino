
const int closingButtonPin =  5;
const int openingButtonPin =  6; 
const int emergencyButtonPin =  7; 
const int motorDirectionPin =  3;
const int motorSwitcherPin =  4;
const int mechanismOpenedSensorPin =  2;
const int mechanismClosedSensorPin =  3;
const int motorSpeedSensorPin =  1;
const int tipoverSensorPin =  4; 


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

unsigned long time1 = 0;
unsigned long time2 = 0;
float motorRPM = 0;

void loop() {
  if (digitalRead(motorSpeedSensorPin) == HIGH) {
    time1 = time2;
    time2 = millis();
    if (time1 > 0) {
      motorRPM = (1.0 / ((time2 - time1) / 1000.0)) * 60.0;
    }
  }
  if (emergencyButtonState == LOW) {
    if (openingButtonPin == HIGH) {
    if (mechanismOpenedSensorState != HIGH) {
      digitalWrite(motorDirectionPin, HIGH);
      digitalWrite(motorSwitcherPin, HIGH);
      if (motorSpeed < motorSpeedThresholdOpening) {
        digitalWrite(motorSwitcherPin, LOW);
      }
    }
    } else if ( closingButtonState == HIGH) {
    if (mechanismClosedSensorState != HIGH) {
      digitalWrite(motorDirectionPin, LOW);
      digitalWrite(motorSwitcherPin, HIGH);
      if (motorSpeed < motorSpeedThresholdClosing) {
        digitalWrite(motorSwitcherPin, LOW);
      }
    }
  }} else if (emergencyButtonState == HIGH) {
      digitalWrite(motorSwitcherPin, LOW);
  }
}
