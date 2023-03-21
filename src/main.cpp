#include <Arduino.h>
#include <Servo.h>
#include <IRremote.hpp>

Servo servo1;
const long up = 0xB946FF00;
const long down = 0xEA15FF00;
const long left = 0xBB44FF00;
const long right = 0xBC43FF00;
int IR_RECEIVE_PIN = 12;
int val1 = 0;

void setup() {
  Serial.begin(9600);
  servo1.attach(9);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("starting IR rceiver...");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR rceiver active");
}
void loop() {
if (IrReceiver.decode()){
  long result = IrReceiver.decodedIRData.decodedRawData;
  switch (result){
    case right:
    Serial.println("right");
    val1 = val1 + 8;
    servo1.write(val1);
    break;
  case left:
    Serial.println("left");
    val1 = val1 - 8;
    servo1.write(val1);
    break;
  case up:
    Serial.println("up");
    break;
  case down:
    Serial.println("down");
    break;
  default:
    break;
  }
  IrReceiver.resume();
}
}