#define echoPin 2 //attach pin D2 Arduino to pin Echo of the ultrasound
#define trigPin 3 //attach pin D3 to pin Trig of ultrasound

long duration //will store how long the sound wave takes to travel
double distance // will store distance measurement
double SoundSpeed = 0.034; //speed of sound in air (can change to be more accurate)


void setup() {
  pinMode(trigPin, OUTPUT); //trigPin is output as that sends the ultrasound wave
  pinMode(echoPin, INPUT); //echoPin is input as that detected the reflected wave
  Serial.begin(9600); //allows communication so we can output distance

  

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin,LOW);
  unsigned long StartTime = millis(); //starts a timer
  if (millis() - StartTime == 2000) {
    digitalWrite(trigPin, HIGH) //will clear the trigPin condition
  }
  if (millis() - StartTime == 12000) {
    digitalWrite(trigPin,LOW); //10 seconds between the trigPin being high and low, which means that the pulse will be activated
  }
  duration = pulseIn(echoPin, HIGH); // measures how long it took for the pulse to return
  distance = duration * SoundSpeed/2; //have to multiply time by the speed of sound divided by 2 (pulse has to go there and come back)
  Serial.print(distance); //outputs the distance
  Serial.println(" cm");
  
}
