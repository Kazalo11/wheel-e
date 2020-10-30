#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started");

  AFMS.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  go_round();
}

void go_round() {
  while (millis() - StartTime <= 3000) { //ADJUST FOR LEFT TRUN
  myMotorLeft->setSpeed(106*leftSteer); //taken from line follower new for straight forwards, reversed one to spin on a point
  myMotorRight->setSpeed(100*rightSteer);
  myMotorLeft->run(BACKWARD);
  myMotorRight->run(FORWARD);
  }
}
