
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" // need to include libraries to use the motor



const int AmberLEDPin = 13; //sets the amberLEDPin to be assigned to digital pin 13 - can change
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates Adafruit_MotorShield object
Adafruit_DCMotor *MotorWheelLeft = AFMS.getMotor(1); //requests the motor which should be connected to M1, should be the wheel motor on the left
Adafruit_DCMotor *MotorWheelRight = AFMS.getMotor(2); //requests the motor which should be connected to M1, should be the wheel motor on the left



void setup() {
  // put your setup code here, to run once:
  pinMode(AmberLEDPin, OUTPUT);
  AFMS.begin();
  MotorWheelLeft->setSpeed(20);
  MotorWheelRight->setSpeed(20);
  myMotor-> run(FORWARD);
  
  
  

  

}

void loop() {
  
  //something like: while motor is running and nothing in ultrasound scanner, then run: 
  moving_light();
  //when the robot is within 5cm of the fruit
  found_fruit();
}



void moving_light() { //used to display the flashing light every 0.5s
  digitalWrite(AmberLEDPin, (millis()/500) % 2); 
}

void found_fruit() { //when the fruit is found, a for loop is used to display the amber light for 5 seconds
  digitalWrite(AmberLEDPin, HIGH);
  delay(1000); //backup in case robot doesn't stop
  digitalWrite(AmberLEDPin, LOW);
  
}
