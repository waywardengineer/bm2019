#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
const byte numInputPins = 12;
const byte inputPins[numInputPins] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 14, 15};
bool pinStates[numInputPins] = {false, false, false, false, false, false, false, false, false, false, false, false};
char pinCodes[numInputPins] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  for (int i=0; i<numInputPins; i++){
    pinMode(inputPins[i], INPUT_PULLUP);
  }
}
void loop() {
  for (int i=0; i<numInputPins; i++){
    if (!digitalRead(inputPins[i])){
      if (!pinStates[0]){
        HC12.write(i);
        pinStates[0] = true;
      }
    }
    else {
       pinStates[0] = false;
    }
  }
}
