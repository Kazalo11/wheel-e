#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);



const int IndicatorAmberLED = 4; //these numbers need to be edited

const int trigPin = 9;
const int echoPin = 8;
unsigned long EndTime = 0;
int ledState = LOW;
float displacement;
// defines variables
long duration;
int distance;
void setup() {
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
   float displacement = distance_measurer();
   while (displacement > 7) {
   unsigned long currentMillis = millis();

  if (currentMillis - EndTime >= 500) {
    // save the last time you blinked the LED
    EndTime = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(IndicatorAmberLED, HIGH);
}
  

}
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
