
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);



void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
  int left_light_s = analogRead(A1);
  int right_light_s = analogRead(A0);
  
  Serial.print("left light sensor reading = ");
  Serial.println(left_light_s);   // the raw analog reading
    
      // We'll have a few threshholds, qualitatively determined
    
    
   Serial.print("right light sensor reading = ");
   Serial.println(right_light_s);   // the raw analog reading
   delay(2000);

}
