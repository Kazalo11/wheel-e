#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()  LEFT
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //RIGHT
// sets up motor




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
    
    myMotor2->setSpeed(150);
    myMotor->run(FORWARD);
    myMotor->run(FORWARD);
    int left_light_s = analogRead(A2);
    int right_light_s = analogRead(A1);
    Serial.print("left light sensor reading = ");
    Serial.println(left_light_s);   // the raw analog reading
    Serial.print("right light sensor reading = ");
    Serial.println(right_light_s);   // the raw analog reading
    delay(2000);

}
