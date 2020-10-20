

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()


void setup() {
  // put your setup code here, to run once:

  AFMS.begin() //activates the adafruit motor

}

void loop() {
  // put your main code here, to run repeatedly:

  myMotor->setSpeed(120); //sets the speed in 
  myMotor ->run(FORWARD); //activates the motor to move forwards;
  
  

}
