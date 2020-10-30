float leftSteer = 1.0;
float rightSteer = 1.0;
float threshold_right = 70;
float threshold_left = 80; //vary these 2 parameters depending on lighting



#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(2);
// sets up motor


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started");

  AFMS.begin();
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  line_follower();

}

void line_follower() {
  myMotorLeft->setSpeed(106*leftSteer);
  myMotorRight->setSpeed(100*rightSteer);
  myMotorLeft->run(FORWARD);
  myMotorRight->run(FORWARD);
  
  int left_light_s = analogRead(A1);
  int right_light_s = analogRead(A0);
  
  /*Serial.print("Left Light reading: ");
  Serial.println(left_light_s);
  Serial.print("Right Light reading: ");
  Serial.println(right_light_s); */
  
  if (left_light_s < threshold_left) { //if left is below threshold then must have gone off the line, vary right
    Serial.println("Steer Right");
    leftSteer = 1.5; //vary these speeds however is best
    rightSteer = 0.64;
  }

  else if (right_light_s > threshold_right && left_light_s > threshold_right) { // use this for the junction thing
    unsigned long StartTime = millis(); //initalise timer
    while (millis() - StartTime <= 3000) { //vary this time depending on how the motor turns
      myMotorLeft->run(RELEASE); //should perform a stationary left term so the robot is turned left and the left sensor is still on the white line
      
    }
  }
  
  
  else{
    leftSteer = 1.0;
    rightSteer = 1.0;
  }

  
     

 
  
}
