
const int RedLED = 13; //number of RedLED
const int BlueLED = 12; //number of BlueLED

const int IndicatorRedLED = 0; //number of RedLED
const int IndicatorGreenLED = 2; //number of GreenLED

const int LDR = A0; // number pin for ColourSensor
int BrightnessRed[] = {};
int BrightnessBlue[] = {}; // 2 empty arrays which will store all the LDR values from reading from colour sensor


void setup() {
  // put your setup code here, to run once:
  pinMode(IndicatorGreenLED, OUTPUT);
  pinMode(IndicatorRedLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  
  Serial.begin(9600);  

}

float average(int * array) { //finds the average of an array of numbers
  long sum = 0;
  int len = sizeof(array)/sizeof(array[0]); // number of elements in an array
  for (int j = 0; j < len ; j++) {
    sum+= array[j];
  }
  return(float(sum/len));
}


void loop() {
  // put your main code here, to run repeatedly:
  
  int i = 0;
  int interval = 500;
  unsigned long EndTime = 0; //inital start time so can measure interval
  unsigned long StartTime = millis();
  
  while (StartTime - EndTime <= interval) {
    digitalWrite(RedLED,HIGH);
    BrightnessRed[i] = analogRead(LDR);
     //for 3s, the brightness level will be recorded and stored within an array
  }
  digitalWrite(RedLED,LOW); //turn red led off
  delay(1000);
  EndTime = 0; //inital start time so can measure interval
  StartTime = millis();
  
  while (StartTime - EndTime <= interval) {
    digitalWrite(BlueLED,HIGH);
    BrightnessBlue[i] = analogRead(LDR);
     //for 3s, the brightness level will be recorded and stored within an array
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
  }
  else {
    digitalWrite(IndicatorGreenLED,HIGH);
  }
  }
