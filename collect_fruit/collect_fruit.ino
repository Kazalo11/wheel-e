#include <Time.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);


void setup() {
  // put your setup code here, to run once:
  AFMS.begin(); //activates the adafruit motor
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  collect_fruit();
}

void collect_fruit() {
    unsigned long StartTime = millis();
  StartTime = millis();
    while(millis() - StartTime <= 2500) {
     myMotor->setSpeed(120);
     myMotor2->setSpeed(120);
     myMotor->run(FORWARD);
     myMotor2->run(FORWARD);
    }
}
