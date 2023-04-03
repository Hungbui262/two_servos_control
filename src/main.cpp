#include <Arduino.h>
#include <Servo.h>

Servo servo_verticle; 
Servo servo_horizontal; 
int feedbackPin = A0; // Feedback pin for horizontal servo

int horizontal_pos = 0;
int vertical_pos = 0;
/*variables for duty cycle calculation*/
float angle = 0.0;
float tHigh = 0;
float tLow = 0;
float tCycle = 0;
float dc = 0;
float dc_min = 2.9; //from datasheet
float dc_max = 97.1; //from data sheet
float errorAngle = 0;

void horizontal_move(){
  /*GET value from feedback PIN to compute duty cycle*/
  while(1){ 
    tHigh = pulseIn(feedbackPin, HIGH);
    tLow = pulseIn(feedbackPin, LOW);
    tCycle = tHigh + tLow;
    if(tCycle > 1000 && tCycle < 1200){
      break;
    }
  } 
    /*Calculate current angle from feedback pin*/
    dc = (100 * tHigh) /tCycle;
    angle = ((dc - dc_min) * 360) / (dc_max - dc_min + 1);

    /*constraint the angle value from 0 to 360 */
    if(angle < 0){
      angle = 0;
    } else if(angle > 359){
      angle = 359;
    }
    
    errorAngle = horizontal_pos - angle; //compare the differences between current angle and target angle to adjust. 
    if(errorAngle > 180){
      errorAngle = errorAngle - 360;
    } else if(errorAngle < -180){
      errorAngle = -errorAngle; 
    }
    int val = 90 - errorAngle; // 90 is the value where CONTINOUS SERVO stop, error angle will be decreasing until err_angle ~=0
    servo_horizontal.write(val);  
}
void setup() {
  Serial.begin(9600);
  servo_verticle.attach(4); // PIN NUMBER 4 
  servo_horizontal.attach(3); // PIN NUMBER 3
  pinMode(feedbackPin, INPUT);
}
void loop() {
  if(Serial.available()){
    String data1 = Serial.readStringUntil('\n'); // READ  String value for horizontal position (0-359)
    String data2 = Serial.readString(); // HIT ENTER, then READ String value for verticle angle (0 - 180) 
    horizontal_pos = data1.toInt(); // convert String value to INT
    vertical_pos = data2.toInt(); // convert String value to INT
    Serial.print("horizontal position = ");
    Serial.println(horizontal_pos);
    Serial.print("verticle position = ");
    Serial.println(vertical_pos);
    Serial.println("--------------");
  }
  servo_verticle.write(vertical_pos); // MOVE SERVO TO VERTICLE POSITION
  horizontal_move(); // CALL FUNCTION HORIZONTAL MOVE, 
}