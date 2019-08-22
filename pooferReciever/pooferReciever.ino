#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
const byte numPoofers = 3;
byte pooferPins[numPoofers] = {5, 6, 7};
long pooferOffTimes[numPoofers] = {0, 0, 0};
long nextPulseTime = 0;
const byte phonePin = 1;
void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  for (int i=0; i< numPoofers; i++){
    pinMode(pooferPins[i], OUTPUT);
    digitalWrite(pooferPins[i], LOW);
  }
  pinMode (phonePin, INPUT_PULLUP);
}
void loop() {
  while (HC12.available()) {
    int inputTriggered = HC12.read();
    //Serial.println(inputTriggered);
    if (inputTriggered % 2){
      triggerPoofer(0, 1000);
    }
    else{
      triggerPoofer(1, 1000);      
    }
  }
  if (!digitalRead(phonePin)){
    triggerPoofer(2, 30);
  }

  checkPoofers();
}

void checkPoofers(){
  for (int i=0; i< numPoofers; i++){
    if (pooferOffTimes[i] > 0 && millis() > pooferOffTimes[i]){
      digitalWrite(pooferPins[i], LOW);
      pooferOffTimes[i] = 0;
    }
  }
}
void triggerPoofer(byte poofer, int onTime){
  pooferOffTimes[poofer] = millis() + onTime;
  digitalWrite(pooferPins[poofer], HIGH);
}
