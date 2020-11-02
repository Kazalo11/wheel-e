#include <Time.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run
#include <Servo.h>

int servoPin = 5; //pin where the servo will be attach
Servo myservo; //creates a variable of the Servo object

//motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(2);
float leftSteer = 1.0;
float rightSteer = 1.0;
float threshold_right = 70;
float threshold_left = 80; //vary these 2 parameters depending on lighting


void setup() {
  // put your setup code here, to run once:
    AFMS.begin();
    Serial.begin(9600);
    myservo.attach(servoPin); //links the servo variable to the pin which will control the action
    myservo.write(180); //should be door shut (might need changing)
}

void loop() {
  // put your main code here, to run repeatedly:
  reverse_at_end();
}


void reverse_at_end(){ //first, straight reverse with door open to remove fruit
  myservo.write(90); //open door
  
  unsigned long StartTime = millis();
  while (millis() - StartTime <= 1000){ // straight reverse
  myMotorLeft->setSpeed(150);
  myMotorRight->setSpeed(150);
  myMotorLeft->run(BACKWARD);
  myMotorRight->run(BACKWARD);
  }
  StartTime = millis();
  while (millis() - StartTime <= 2000){ //rotate to face finish line, value will need to be changed
  myMotorLeft->setSpeed(90);
  myMotorRight->setSpeed(90);
  myMotorLeft->run(FORWARD);
  myMotorRight->run(BACKWARD);
  }

  while (millis() - StartTime <= 10000){ // straight FORWARDS TO START LINE (value needs to be changed
  myMotorLeft->setSpeed(150);
  myMotorRight->setSpeed(150);
  myMotorLeft->run(FORWARD);
  myMotorRight->run(FORWARD);
  }
  
}
