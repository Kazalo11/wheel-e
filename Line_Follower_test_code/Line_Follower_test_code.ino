


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

int threshold = 500; //can change this depending on reading, i think it should be the reading when from when the sensor is on the edge of the line



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // reads the input on analog pin A0 (value between 0 and 1023)
  unsigned long startTime = millis();
  while (millis() - startTime <= 10000) { //will run for 10s
    myMotor->setSpeed(125); //left motor is bit wonky so must run faster
    myMotor2->setSpeed(100);
    myMotor->run(FORWARD);
    myMotor2->run(BACKWARD);
    
    int left_light_s = analogRead(A3);
    int right_light_s = analogRead(A4);
  
    Serial.print("left light sensor reading = ");
    Serial.println(left_light_s);   // the raw analog reading
  
    // We'll have a few threshholds, qualitatively determined
  
  
    Serial.print("right light sensor reading = ");
    Serial.println(right_light_s);   // the raw analog reading
    if (left_light_s < threshold) {
      Serial.println("Steer Left");
    }
    else if (right_light_s > threshold) {
      Serial.println("Steer Right");
    
  }
    
  }
  
  /*
  if (right_light_s < 10) {
    Serial.println(" - R_Dark");
  } else if (right_light_s < 200) {
    Serial.println(" - R_Dim");
  } else if (right_light_s < 500) {
    Serial.println(" - R_Light");
  } else if (right_light_s < 800) {
    Serial.println(" - R_Bright");
  } else {
    Serial.println(" - R_Very bright");
  } */

  
  

  

  
  delay(2000);
}
