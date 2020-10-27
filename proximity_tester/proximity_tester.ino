/*int echoPin = 2; //attach pin D2 Arduino to pin Echo of the ultrasound
int trigPin = 3; //attach pin D3 to pin Trig of ultrasound

long duration; //will store how long the sound wave takes to travel
double distance; // will store distance measurement
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
    digitalWrite(trigPin, HIGH); //will clear the trigPin condition
  }
  if (millis() - StartTime == 12000) {
    digitalWrite(trigPin,LOW); //10 seconds between the trigPin being high and low, which means that the pulse will be activated
  }
  duration = pulseIn(echoPin, HIGH); // measures how long it took for the pulse to return
  distance = duration * SoundSpeed/2; //have to multiply time by the speed of sound divided by 2 (pulse has to go there and come back)
  Serial.print(distance); //outputs the distance
  Serial.println(" cm");
  
}
*/

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}
