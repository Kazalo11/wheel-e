

//#include <Servo.h> //libraries to control the motors + servos

const int RedLED = 13; //number of RedLED
const int BlueLED = 12; //number of BlueLED
const int GreenLED = 11; //number of GreenLED
const int IndicatorRedLED = 10; //number of RedLED
const int IndicatorGreenLED = 9; //number of GreenLED
const int LDR = A0; // number pin for ColourSensor
int BrightnessRed[] = {};
int BrightnessBlue[] = {}; // 2 empty arrays which will store all the LDR values from reading from colour sensor

//int servoPin = 9; //pin where the servo will be attach
//Servo myservo; //creates a variable of the Servo object




void setup() {
  // put your setup code here, to run once:
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  //sets the RedLED, GreenLED and BlueLED to output

//  myservo.attach(servoPin); //links the servo variable to the pin which will control the action
  Serial.begin(9600);
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  is_ripe();

}

bool is_ripe() {
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
  Serial.print("Average red brightness: ");
  Serial.println(averageRed);
  Serial.print("Average blue brightness: ");
  Serial.println(averageBlue);


  if (averageRed < averageBlue) { //more red light returned hence bottom must be blue. UNRIPE
    StartTime = millis();
    while(millis() - StartTime <= 5500) {
      digitalWrite(IndicatorRedLED, HIGH);
    }
    return(false);
  }
  else { //more blue light returned hence bottom must be red OR ambiguous, better to collect than leave. RIPE
    StartTime = millis();
    while(millis() - StartTime <= 5500) {
      digitalWrite(IndicatorGreenLED, HIGH);
    }  
  return(true);
  }
}


float average(int * array) { //finds the average of an array of numbers
  long sum = 0;
  int len = sizeof(array)/sizeof(array[0]); // number of elements in an array
  for (int j = 0; j < len ; j++) {
    sum+= array[j];
  }
  return(float(sum/len));
}
