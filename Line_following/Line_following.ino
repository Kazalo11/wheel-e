/*this is the code to be implemented in overall_code for line following. 
 *The changing of motor speeds is not included as it would be more readable 
 *in a seperate function that takes PID_Value to control motor. 
  */
//PID setup
float Kp = 25;
float Ki = 0;
float Kd = 15;
float error = 0, derivative = 0, integral = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0;
int flag = 0;

int standard_speed = 100;
float max_value = 500;
float new_speed;

//need input data from line followers


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
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
    int left_light_s = analogRead(A3);
    int right_light_s = analogRead(A4);
    error = (left_light_s - right_light_s) * 0.5; //if right light greater, robot is too far left, number is negitive and vice versa 
    P = Kp * error;

    integral = integral + error;
    I = Ki * integral;

    derivative = error - previous_error;
    D = Kd * derivative;

    Serial.print("left light sensor reading = ");
    Serial.println(left_light_s);   // the raw analog reading
    Serial.print("right light sensor reading = ");
    Serial.println(right_light_s);   // the raw analog reading
    delay(500);
    previous_error = error;
    
    PID_value = P + I + D;
    //add something like if PID_value < certain value return 0 else return new value
    return(map(PID_value,0, max_value,0,1));



    

}

void motor_control() {
     new_speed = line_follower() * standard_speed + standard_speed; 
     myMotor->setSpeed(new_speed);
     myMotor2->setSpeed(new_speed);
     myMotor->run(FORWARD);
     myMotor2->run(FORWARD);
}
