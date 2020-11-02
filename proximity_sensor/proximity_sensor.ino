// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;
unsigned long EndTime = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}


void loop() {
  // put your main code here, to run repeatedly:
  proximity_sensor();
}


float proximity_sensor() {
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
  return distance;
}



/*OLD CODE 
float proximity_sensor() {
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
  Serial.print("Distance: "); // Prints the distance on the Serial Monitor
  Serial.println(distance);
  
  return distance;
}
*/
