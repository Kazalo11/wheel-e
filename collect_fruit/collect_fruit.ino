#include <Time.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run
#include <Servo.h>

int servoPin = 5; //pin where the servo will be attach
Servo myservo; //creates a variable of the Servo object

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(2);


void setup() {
  // put your setup code here, to run once:
  AFMS.begin(); //activates the adafruit motor
  Serial.begin(9600);
  myservo.attach(servoPin); //links the servo variable to the pin which will control the action
  myservo.write(180); //should be door shut (might need changing)
  
}

void loop() {
  // put your main code here, to run repeatedly:
  collect_fruit();
}

void collect_fruit() {
  myservo.write(90); //open door
  unsigned long StartTime = millis();
  StartTime = millis();
    while(millis() - StartTime <= 2500) {
     myMotorLeft->setSpeed(120);
     myMotorRight->setSpeed(120);
     myMotorLeft->run(FORWARD);
     myMotorRight->run(FORWARD);
    }
  myservo.write(180); //shut door
}
