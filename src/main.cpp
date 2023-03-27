#include <Arduino.h>
#include <Servo.h>
#include <IRremote.hpp>
#include <irControl.h>



void setup() {
  Serial.begin(9600);
  servo_verticle.attach(4); // SERVO VERTICLE PIN 4
  servo_horizontal.attach(3); // SERVO HORIZONTAL PIN 3
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(cw, INPUT_PULLUP);
  pinMode(ccw, INPUT_PULLUP);
}
void loop() {

/*THIS IS USING BUTTON TO CONTROL PIN */
// cw_state = digitalRead(cw);
// ccw_state = digitalRead(ccw);
// if(cw_state == LOW){
//   Serial.println("cw push");
//   servo_horizontal.write(85);
//   delay(100);
// }
// if(ccw_state == LOW){
//   Serial.println("ccw push");
//   servo_horizontal.write(100);
//   delay(100);
// }else{
//   servo_horizontal.write(90);
// }

if (IrReceiver.decode()){
  long result = IrReceiver.decodedIRData.decodedRawData;
  Serial.println(result, HEX);
  switch (result){
    case CW:
      movement = "cw";
      break;
    case CCW:
      movement = "ccw";
      break;
    case up:
      movement = "up";
      break;
    case down:
    movement = "down";
      break;

    case stop:
      servo_horizontal.write(90);
      break;
  case hold:
    if(movement.equals("up")){
      verticle_pos = verticle_pos - 20;
      if(verticle_pos < 0){
        verticle_pos = 0;
      }
      servo_verticle.write(verticle_pos);
    }
    else if(movement.equals("down")){
      verticle_pos = verticle_pos + 20;
      if(verticle_pos < 0){
        verticle_pos = 0;
      }
      servo_verticle.write(verticle_pos);   
    }
    else if(movement.equals("cw")){
      servo_horizontal.write(85);
      delay(30);
    }
    else if(movement.equals("ccw")){
      servo_horizontal.write(100);
      delay(30);
    }
  break;
  }
  servo_horizontal.write(90);
  IrReceiver.resume();
}
}