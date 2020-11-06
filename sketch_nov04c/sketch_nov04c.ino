const int RedLED = 13; //number of RedLED
const int BlueLED = 12; //number of BlueLED

const int IndicatorRedLED = 3; //number of RedLED
const int IndicatorGreenLED = 5; //number of GreenLED

const int LDR = A2; // number pin for ColourSensor
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

void loop(){
  digitalWrite(IndicatorRedLED,LOW);
  digitalWrite(IndicatorGreenLED,LOW);
  digitalWrite(BlueLED,HIGH);
  delay(250);
  int blueValue = analogRead(LDR);
  delay(250);
  digitalWrite(BlueLED,LOW);
  delay(250);
  digitalWrite(RedLED,HIGH);
  delay(250);
  int redValue = analogRead(LDR);
  delay(250);
  digitalWrite(RedLED,LOW);
  Serial.println(blueValue);
  Serial.println(redValue);
  int delta = abs(blueValue-redValue);
  if (delta>50){
    digitalWrite(IndicatorRedLED,HIGH);
    digitalWrite(IndicatorGreenLED,LOW);
  }
  else{
    digitalWrite(IndicatorGreenLED,HIGH);
    digitalWrite(IndicatorRedLED,LOW);
  }
  delay(3000);
  
}
