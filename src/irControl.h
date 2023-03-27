Servo servo_verticle;
Servo servo_horizontal;
const long up = 0xB946FF00;
const long down =   0xEA15FF00;
const long CCW =   0xBB44FF00;
const long CW =  0xBC43FF00;
const long stop = 0xBF40FF00;
const long hold =   0x0;

int IR_RECEIVE_PIN = 12;
int verticle_pos = 90;
int horiz_pos;


const int cw = 9; // BUTTON CONTROL PIN 9
const int ccw = 8; // BUTTON CONTROL PIN 8
int cw_state, ccw_state;

String movement;