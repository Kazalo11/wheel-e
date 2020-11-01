


const int trigPin = 2;
const int echoPin = 4;
unsigned long EndTime = 0;
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
}
