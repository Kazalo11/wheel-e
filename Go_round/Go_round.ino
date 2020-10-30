#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(2);

float leftscale = 1.5;
float rightscale = 1; //adjust these

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
  
  left_turn();
  
  //RIGHT ARC
  bool off_line = true; //so while loop starts
  unsigned long StartTime = millis();
  while (millis() - StartTime <= 1000 /*or off_line = true*/) { // will start arc NOT looking at sensor (as it moves off line) then after a time will continue arc till reaches line again
    int left_light_s = analogRead(A1);
    int right_light_s = analogRead(A0);
   
    myMotorLeft->setSpeed(106*leftscale); //right turn arc around fruit (hopefully), adjust scales to arc around tighter/looser
    myMotorRight->setSpeed(100*rightscale);
    myMotorLeft->run(FORWARD);
    myMotorRight->run(FORWARD);
  
    if (left_light_s >200 and right_light_s >200) { //adjust for actual values
      off_line = false;
    }
  }
  //leaves while loop when line found again, so needs to turn left again (this might be unneeded if line follower good enough)
  left_turn();

  
}

void left_turn(){
  unsigned long StartTime = millis();
  while (millis() - StartTime <= 3000) { //adjust to end at left turn
  myMotorLeft->setSpeed(106); //taken from line follower new for straight forwards, reversed one to spin on a point
  myMotorRight->setSpeed(100);
  myMotorLeft->run(BACKWARD);
  myMotorRight->run(FORWARD);
  }
}
