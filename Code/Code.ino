const int closingButtonPin =  5;
const int openingButtonPin =  6; 
const int emergencyButtonPin =  7; 
const int motorDirectionPin =  3;
const int motorSwitcherPin =  4;
const int mechanismOpenedSensorPin =  2;
const int mechanismClosedSensorPin =  3;
const int motorRPMSensorPin =  1;
const int tipoverSensorPin =  4; 

void setup() {
  pinMode(closingButtonPin, INPUT);
  pinMode(openingButtonPin, INPUT);
  pinMode(emergencyButtonPin, INPUT);
  pinMode(motorDirectionPin, OUTPUT);
  pinMode(motorSwitcherPin, OUTPUT);
  pinMode(mechanismOpenedSensorPin, INPUT);
  pinMode(mechanismClosedSensorPin, INPUT);
  pinMode(motorRPMSensorPin, INPUT);
  pinMode(tipoverSensorPin, INPUT);
}

unsigned long time1 = 0;
float motorRPM = 200.0;
bool LastMotorSensorState = LOW;
const int motorRPMThreshold = 200;
int state = 0;

void loop() {
  if (digitalRead(emergencyButtonPin) == HIGH || digitalRead(tipoverSensorPin) == LOW) {
    digitalWrite(motorSwitcherPin, LOW);
    state = 0;
    return;
  }

  if (digitalRead(motorRPMSensorPin) == HIGH && LastMotorSensorState == LOW) {
    if (time1 > 0) {
      motorRPM = (1.0 / ((millis() - time1) / 1000.0)) * 60.0;
    }
    time1 = millis();
  }
  LastMotorSensorState = digitalRead(motorRPMSensorPin);

  if (digitalRead(openingButtonPin) == HIGH && state == 0) {
    state = 1;
  } else if (digitalRead(closingButtonPin) == HIGH && state == 0) {
    state = -1;
  }

  if (state == 1) {
    if (digitalRead(mechanismOpenedSensorPin) != HIGH) {
      digitalWrite(motorDirectionPin, HIGH);
      digitalWrite(motorSwitcherPin, HIGH);
    } else {
      digitalWrite(motorSwitcherPin, LOW);
      state = 0;
    }
  } else if (state == -1) {
    if (digitalRead(mechanismClosedSensorPin) != HIGH) {
      digitalWrite(motorDirectionPin, LOW);
      digitalWrite(motorSwitcherPin, HIGH);
    } else {
      digitalWrite(motorSwitcherPin, LOW);
      state = 0;
    }
  }
}
