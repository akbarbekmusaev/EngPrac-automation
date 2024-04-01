
void setup() {
  pinMode(closingButtonPin, INPUT_PULLUP);
  pinMode(openingButtonPin, INPUT_PULLUP);
  pinMode(emergencyButtonPin, INPUT_PULLUP);
  
}

const int closingButtonPin =  5;
const int openingButtonPin =  6; 
const int emergencyButtonPin =  7; 

void loop() {
  int closingButtonState = digitalRead(closingButtonPin);
  int openingButtonState = digitalRead(openingButtonPin);
  int emergencyButtonState = digitalRead(emergencyButtonPin);

}
