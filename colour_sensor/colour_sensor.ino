

#include <Servo.h> //libraries to control the motors + servos

const int RedLED = 13; //number of RedLED
const int BlueLED = 12; //number of BlueLED
const int GreenLED = 11; //number of GreenLED
const int LDR = A0; // number pin for ColourSensor
int BrightnessRed = [];
int BrightnessBlue = []; // 2 empty arrays which will store all the LDR values from reading from colour sensor

int servoPin = 9; //pin where the servo will be attach
Servo myservo; //creates a variable of the Servo object




void setup() {
  // put your setup code here, to run once:
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  //sets the RedLED, GreenLED and BlueLED to output

  myservo.attach(servoPin) //links the servo variable to the pin which will control the action
  
}

void loop() {
  // put your main code here, to run repeatedly:
  ripe_or_unripe();

}

void ripe_or_unripe() {
  int i = 0;
  int interval = 3000;
  unsigned long StartTime = millis(); //inital start time so can measure interval
  while (millis() - StartTime <= interval) {
    digitalWrite(RedLED,HIGH);
    BrightnessRed[i] = analogRead(LDR);
    i++; //for 3s, the brightness level will be recorded and stored within an array
  }
  digitalWrite(RedLED,LOW); //turn red led off
  StartTime = millis();
  i = 0;
  while (millis() - StartTime <= interval) {
    digitalWrite(BlueLED,HIGH);
    BrightnessBlue[i] = analogRead(LDR);
    i++; //for 3s, the brightness level will be recorded and stored within an array
  }
  digitalWrite(BlueLED,LOW); //turn blue led off
  float averageRed = average(BrightnessRed);
  float averageBlue = average(BrightnessBlue); //works out the average of each of the brightnesses

  if (averageRed < averageBlue) { //more red light returned hence bottom must be blue
    StartTime = millis();
    while(millis() - StartTime <= 5500) {
      digitalWrite(GreenLED, HIGH);
    }
    servo.write(90);
    //open door using servo motor
    //move forward collect fruit then close door
  }
  else if (averageRed > averageBlue) { //more blue light returned hence bottom must be red
    StartTime = millis();
    while(millis() - StartTime <= 5500) {
      digitalWrite(RedLED, HIGH);
    }
    //back away, semicircle around it
}

}


float average(int arr) { //finds the average of an array of numbers
  long sum = 0;
  int len = sizeof(arr)/sizeof(arr[0]); // number of elements in an array
  for (int j = 0; j < len ; i++) {
    sum+= arr[j];
  }
  return(float(sum/len));
}
