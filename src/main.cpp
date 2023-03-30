#include <Arduino.h>
#include <Servo.h>

Servo servo_verticle;
Servo servo_horizontal;
int feedbackPin = A0;

int horizontal_pos = 0;
int vertical_pos = 0;
float angle = 0.0;
float tHigh = 0;
float tLow = 0;
float tCycle = 0;
float dc = 0;
float dc_min = 2.9;
float dc_max = 97.1;
float errorAngle = 0;

void move(){
  while(1){
    tHigh = pulseIn(feedbackPin, HIGH);
    tLow = pulseIn(feedbackPin, LOW);
    tCycle = tHigh + tLow;
    if(tCycle > 1000 && tCycle < 1200){
      break;
    }
  } 
  
    dc = (100 * tHigh) /tCycle;
    angle = ((dc - dc_min) * 360) / (dc_max - dc_min + 1);
    // Serial.println(angle);
    if(angle < 0){
      angle = 0;
    } else if(angle > 359){
      angle = 359;
    }
    // detect error Angle
    errorAngle = horizontal_pos - angle;
    if(errorAngle > 180){
      errorAngle = errorAngle - 360;
    } else if(errorAngle < -180){
      errorAngle = -errorAngle; // hmmm
    }
    int val = 90 - errorAngle;
    servo_horizontal.write(val);
}
void setup() {
  Serial.begin(9600);
  servo_verticle.attach(4);
  servo_horizontal.attach(3);
  pinMode(feedbackPin, INPUT);
  Serial.println("start");
}
void loop() {
  if(Serial.available()){
    String data1 = Serial.readStringUntil('\n');
    String data2 = Serial.readString();
    horizontal_pos = data1.toInt();
    vertical_pos = data2.toInt();
    Serial.print("horizontal position = ");
    Serial.println(horizontal_pos);
    Serial.print("verticle position = ");
    Serial.println(vertical_pos);
  }
  servo_verticle.write(vertical_pos);
  move();
}