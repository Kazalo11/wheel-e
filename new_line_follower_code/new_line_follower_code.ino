float leftSteer = 1.0;
float rightSteer = 1.0;
float threshold_right = 10;
float threshold_left =10; //vary these 2 parameters depending on lighting
float threshold_junction = 12; //threshold for making a turn at the junction
unsigned long EndTime = 0;


const int IndicatorAmberLED = 4; //these numbers need to be edited

const int trigPin = 9;
const int echoPin = 8;

int ledState = LOW;
float displacement;
// defines variables
long duration;
int distance;

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(2);

// sets up motor

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


void loop() {
  myMotorLeft->setSpeed(255*leftSteer);
  myMotorRight->setSpeed(255*rightSteer);
  myMotorLeft->run(FORWARD);
  myMotorRight->run(FORWARD);


  
  int left_light_s = analogRead(A0);
  int right_light_s = analogRead(A1);
  
  Serial.print("Left Light reading: ");
  Serial.println(left_light_s);
  Serial.print("Right Light reading: ");
  Serial.println(right_light_s); 
 
  
  int displacement = distance_measurer();
  if (displacement < 7) {
    myMotorLeft->run(RELEASE);
    myMotorRight->run(RELEASE);
  }
  if ((left_light_s < threshold_left)) { //if left is below threshold then must have gone off the line, vary right
    Serial.println("Steer Left");
    leftSteer = 0.5; //vary these speeds however is best
    rightSteer = 1;
  }

  else if ((right_light_s > threshold_right)) { //if left is below threshold then must have gone off the line, vary right
    Serial.println("Steer Right");
    leftSteer = 1; //vary these speeds however is best
    rightSteer = 0.5;
  }
  /*
  else if (right_light_s < threshold_junction && left_light_s < threshold_junction) { // use this for the junction thing
    onJunction = true;
    unsigned long StartTime = millis();
    while (StartTime - EndTime <= 3000) {
      myMotorLeft->run(RELEASE);
    }
    EndTime = StartTime;
  }
  */
  
  else{
      leftSteer = 1;
      rightSteer = 1;
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
float distance_measurer() {

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
distance= duration*0.034/2 ;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
return distance;


}
