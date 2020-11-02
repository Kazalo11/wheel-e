float leftSteer = 1.0;
float rightSteer = 1.0;
float threshold_right = 70;
float threshold_left = 80; //vary these 2 parameters depending on lighting
unsigned long EndTime = 0;


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(2);

// sets up motor

const byte trigPin = 2;
const byte echoPin = 4;

unsigned long time;

unsigned long timeLastJunction;
bool onJunction = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started");

//  pinMode(DistTrigger, OUTPUT);
 // pinMode(DistEcho, INPUT);

  AFMS.begin();

}

/* NOT NEEDED, PROXIMITY IS IN DIFFERENT FUNCTION
float readDistanceSensor() {
  digitalWrite(trigPin, LOW);
  unsigned long StartTime = millis();
// Sets the trigPin on HIGH state for 10 micro seconds
  if (StartTime - EndTime >=  2000) {
    digitalWrite(trigPin, HIGH);
}
  if (StartTime - EndTime >=12000) {
    digitalWrite(trigPin, LOW);
}
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance= duration*0.034/2 + 1;
// Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(2000);
} */
void loop(){
  line_follower();
}

void line_follower() {
  myMotorLeft->setSpeed(150*leftSteer);
  myMotorRight->setSpeed(150*rightSteer);
  myMotorLeft->run(BACKWARD);
  myMotorRight->run(BACKWARD);


  
  int left_light_s = analogRead(A1);
  int right_light_s = analogRead(A0);
  
  Serial.print("Left Light reading: ");
  Serial.println(left_light_s);
  Serial.print("Right Light reading: ");
  Serial.println(right_light_s); 
  delay(200);
  
  
  if ((left_light_s < threshold_left)) { //if left is below threshold then must have gone off the line, vary right
    Serial.println("Steer Right");
    leftSteer = 1.5; //vary these speeds however is best
    rightSteer = 0.64;
  }

  else if ((right_light_s < threshold_right)) { //if left is below threshold then must have gone off the line, vary right
    Serial.println("Steer Right");
    leftSteer = 0.64; //vary these speeds however is best
    rightSteer = 1.5;
  }
  /*
  else if (right_light_s > threshold_right && left_light_s > threshold_right) { // use this for the junction thing
    onJunction = true;
    
    if (
    while (millis() - StartTime <= 3000) { //vary this time depending on how the motor turns
      //myMotorLeft->run(RELEASE); //should perform a stationary left term so the robot is turned left and the left sensor is still on the white line
      
    }
  }
  */
  else{
      leftSteer = 1.0;
      rightSteer = 1.0;
  }
/*
  float distance = readDistanceSensor();
  
  * THIS IS NOT NEEDED, FUNCTION IN WHILE LOOP IN MAIN CODE
    if ((distance<4.5)){
    leftSteer = 0.0;
    rightSteer = 0.0; 
    Serial.println(distance);
    } */ 
  
  

}
