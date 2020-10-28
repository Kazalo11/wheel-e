/*this is the code to be implemented in overall_code for line following. 
 *The changing of motor speeds is not included as it would be more readable 
 *in a seperate function that takes PID_Value to control motor. 
  */
//PID setup
float P;
float Kp = 0.2;
float error;

//motors
int standard_speed = 100;
float max_value = 500;
float new_speed;
float right_speed, left_speed;
//need input data from line followers


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()  LEFT
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //RIGHT
// sets up motor




void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
    delay(500);
    Serial.println("Started !!");
    delay(1000);

    AFMS.begin();
}

void loop() { 
     motor_control();
}


float line_follower() {
    // reads the input on analog pin A0 (value between 0 and 1023)
    int left_light_s = analogRead(A2);
    int right_light_s = analogRead(A1);
    error = ((left_light_s - 300) + (right_light_s - 350)) * 0.5; //if right light greater, robot is too far left, number is negative and vice versa ####THIS NEEDS A CONST  (currently 300) TO OFFSET SENSORS SO ERROR IS ZERO WHEN LEFT SENSOR IS LIGHT AN RIGHT IS DARK. IF THIS DOESNT WORK I WILL WRITE TURN LEFT FUNCTION.
    P = Kp * error;


    Serial.print("left light sensor reading = ");
    Serial.println(left_light_s);   // the raw analog reading
    Serial.print("right light sensor reading = ");
    Serial.println(right_light_s);   // the raw analog reading
    Serial.println(P);
    delay(500);
    
    //add something like if PID_value < certain value return 0 else return new value
    return(map(P,0, 325,0,1));
}

void motor_control() {
     right_speed = (standard_speed+10) - line_follower() * standard_speed; //if pid negative, this should be smaller
     left_speed = standard_speed + line_follower() * standard_speed;
     myMotor->setSpeed(left_speed); //LEFT
     myMotor2->setSpeed(right_speed); //RIGHT
     myMotor->run(FORWARD);
     myMotor2->run(FORWARD); //this may be reversed if wheels spinning in opposite direction
}
