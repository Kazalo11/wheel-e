#include <Time.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run
#include <Servo.h>

//motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(2);
float leftSteer = 1.0;
float rightSteer = 1.0;
float threshold_right = 100;
float threshold_left = 90; //vary these 2 parameters depending on lighting
float threshold_junction = 70; 
bool onJunction = false;

int servoPin = 5; //pin where the servo will be attach
Servo myservo; //creates a variable of the Servo object

/*int standard_speed = 100;
float max_value = 500;
float new_speed;
float right_speed, left_speed; */

/*//PID setup 
float Kp = 25;  //K values to be caibrated
float Ki = 0;
float Kd = 15;
float error = 0, derivative = 0, integral = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0;
int flag = 0; */

//proximity
const int trigPin = 9;
const int echoPin = 10;
long duration; //will store how long the sound wave takes to travel
double distance; // will store distance measurement
const int x = 5; //this is the proximity threshold
unsigned long EndTime = 0;

//"Indicator" LEDs
const int IndicatorRedLED = 13; //number of RedLED
const int IndicatorAmberLED = 10; //these numbers need to be edited
const int IndicatorGreenLED = 11; //number of GreenLED

//colour sensor
const int RedLED = 13; //number of RedLED
const int BlueLED = 12; //number of BlueLED
const int GreenLED = 11; //number of GreenLED
const int LDR = A0; // number pin for ColourSensor
int BrightnessRed[] = {};
int BrightnessBlue[] = {}; // 2 empty arrays which will store all the LDR values from reading from colour sensor

//goround setup
float leftscale = 1.5;
float rightscale = 1; //adjust these

void setup() {
  // put your setup code here, to run once:
  //INDICATOR LEDS
  pinMode(IndicatorAmberLED, OUTPUT);
  pinMode(IndicatorGreenLED, OUTPUT);
  pinMode(IndicatorRedLED, OUTPUT);
  //colour sensor LEDs 
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  //this is line follower setup (for testing)
  Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
  delay(500);
  Serial.println("Started !!");
  delay(1000);
  AFMS.begin();
  //Proximity setup
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  //servo door shut at start
  myservo.attach(servoPin); //links the servo variable to the pin which will control the action
  myservo.write(180); //should be door shut (might need changing)
}


void loop() {
  // put your main code here, to run repeatedly:
  proximity_sensor();
  while (proximity_sensor() > x) { // while no fruit, follow line
    proximity_sensor();
    line_follower();
    //motor_control(); // takes line follower PID value and changes motor speeds to follow line 
    LED_blink_amber(); 
  }
  //if (proximity_sensor() < x), this means a fruit has tripped sensor so stops moving by not including forward()
  LED_const_amber();
  is_ripe(); //function to blink the red test LED and take colour reading, ditto for blue, compare colour readings and return ripe = TRUE or FALSE. also lights indicator leds
  if (is_ripe() == true) {
    collect_fruit(); //easier to throw it all in a function
  }
  else {
    go_round(); //this is going to be a fat fuction to leave line and join after unripe fruit
  }
  if(millis() > 9999999999) { //end of line condition need discussion, this is a dummy
  reverse_at_end();
  exit(0); //this stops the loop function (hopefully back at start line with full points woooo)
  }
  
}

void line_follower() {
  myMotorLeft->setSpeed(150*leftSteer);
  myMotorRight->setSpeed(150*rightSteer);
  myMotorLeft->run(BACKWARD);
  myMotorRight->run(BACKWARD);


  
  int left_light_s = analogRead(A1);
  int right_light_s = analogRead(A0);
  
  Serial.print("Left Light reading: ");
  Serial.println(left_light_s);
  Serial.print("Right Light reading: ");
  Serial.println(right_light_s); 
  delay(200);
  
  
  if ((left_light_s < threshold_left)) { //if left is below threshold then must have gone off the line, vary right
    Serial.println("Steer Right");
    leftSteer = 1.5; //vary these speeds however is best
    rightSteer = 0.64;
  }

  else if ((right_light_s < threshold_right)) { //if left is below threshold then must have gone off the line, vary LEFT
    Serial.println("Steer LEFT");
    leftSteer = 0.64; //vary these speeds however is best
    rightSteer = 1.5;
  }
  else if (right_light_s < threshold_junction && left_light_s < threshold_junction) { // use this for the junction thing
    onJunction = true;
    unsigned long StartTime = millis();
    while (StartTime - EndTime <= 3000) {
      myMotorLeft->run(RELEASE);
    }
    EndTime = StartTime;
  }
  else{
      leftSteer = 1.0;
      rightSteer = 1.0;
  }
} 

void collect_fruit() {
  myservo.write(90); //open door
  unsigned long StartTime = millis();
  StartTime = millis();
    while(millis() - StartTime <= 2500) {
     myMotorLeft->setSpeed(120);
     myMotorRight->setSpeed(120);
     myMotorLeft->run(FORWARD);
     myMotorRight->run(FORWARD);
    }
  myservo.write(180); //shut door
}

float proximity_sensor() {
  digitalWrite(trigPin, LOW);
  unsigned long StartTime = millis();
// Sets the trigPin on HIGH state for 10 micro seconds
  if (StartTime - EndTime >=  2000) { //should this be while???
    digitalWrite(trigPin, HIGH);
}
  if (StartTime - EndTime >=12000) { //ditto
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

void LED_blink_amber(){
  digitalWrite(IndicatorAmberLED, HIGH);
  delay(500);
  digitalWrite(IndicatorAmberLED, LOW);
  delay(500);
}

void LED_const_amber(){
  digitalWrite(IndicatorAmberLED, HIGH);
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

void go_round() {
  
  left_turn();
  
  //RIGHT ARC
  bool off_line = true; //so while loop starts
  unsigned long StartTime = millis();
  while (millis() - StartTime <= 1000 /*or off_line = true*/) { // will start arc NOT looking at sensor (as it moves off line) then after a time will continue arc till reaches line again
    int left_light_s = analogRead(A1);
    int right_light_s = analogRead(A0);
   
    myMotorLeft->setSpeed(106*leftscale); //right turn arc around fruit (hopefully), adjust scales to arc around tighter/looser
    myMotorRight->setSpeed(100*rightscale);
    myMotorLeft->run(FORWARD);
    myMotorRight->run(FORWARD);
  
    if (left_light_s >200 and right_light_s >200) { //adjust for actual values
      off_line = false;
    }
  }
  //leaves while loop when line found again, so needs to turn left again (this might be unneeded if line follower good enough)
  left_turn();

  
}

void left_turn(){ // for goround, if line follower problems then will need for line follow too
  unsigned long StartTime = millis();
  while (millis() - StartTime <= 3000) { //adjust to end at left turn
  myMotorLeft->setSpeed(106); //taken from line follower new for straight forwards, reversed one to spin on a point
  myMotorRight->setSpeed(100);
  myMotorLeft->run(BACKWARD);
  myMotorRight->run(FORWARD);
  }
}

void reverse_at_end(){ //first, straight reverse with door open to remove fruit
  myservo.write(90); //open door
  
  unsigned long StartTime = millis();
  while (millis() - StartTime <= 1000){ // straight reverse
  myMotorLeft->setSpeed(150);
  myMotorRight->setSpeed(150);
  myMotorLeft->run(BACKWARD);
  myMotorRight->run(BACKWARD);
  }
  StartTime = millis();
  while (millis() - StartTime <= 2000){ //rotate to face finish line, value will need to be changed
  myMotorLeft->setSpeed(90);
  myMotorRight->setSpeed(90);
  myMotorLeft->run(FORWARD);
  myMotorRight->run(BACKWARD);
  }

  while (millis() - StartTime <= 10000){ // straight FORWARDS TO START LINE (value needs to be changed
  myMotorLeft->setSpeed(150);
  myMotorRight->setSpeed(150);
  myMotorLeft->run(FORWARD);
  myMotorRight->run(FORWARD);
  }
  
}

/* OLD CODE, KEPT IN CASE STUFF GOES WRONG

void line_follower() {
  myMotorLeft->setSpeed(106*leftSteer);
  myMotorRight->setSpeed(100*rightSteer);
  myMotorLeft->run(FORWARD);
  myMotorRight->run(FORWARD);
  
  int left_light_s = analogRead(A1);
  int right_light_s = analogRead(A0); 
  
  if (left_light_s < threshold_left) { //if left is below threshold then must have gone off the line, vary right
    Serial.println("Steer Right");
    leftSteer = 1.5; //vary these speeds however is best
    rightSteer = 0.64;
  }
  else if (right_light_s > threshold_right && left_light_s > threshold_right) { // use this for the junction thing
    unsigned long StartTime = millis(); //initalise timer
    while (millis() - StartTime <= 3000) { //vary this time depending on how the motor turns
      myMotorLeft->run(RELEASE); //should perform a stationary left term so the robot is turned left and the left sensor is still on the white line
      
    }
  }
  else{
    leftSteer = 1.0;
    rightSteer = 1.0;
  } 


void line_follower() { //takes analogue values of light sensors and outputs PID_value for controlling motors 
    // reads the input on analog pin A0 (value between 0 and 1023)
    int left_light_s = analogRead(A0);
    int right_light_s = analogRead(A1);
    error = (left_light_s - right_light_s) * 0.5; //if right light greater, robot is too far left, number is negitive and vice versa 
    P = Kp * error;
    integral = integral + error;
    I = Ki * integral;

    derivative = error - previous_error;
    D = Kd * derivative;

    Serial.print("left light sensor reading = ");
    Serial.print(left_light_s);   // the raw analog reading
    Serial.print("right light sensor reading = ");
    Serial.print(right_light_s);   // the raw analog reading
    previous_error = error;

    PID_value = P + I + D;
}

void red_LED_pulse(){
  digitalWrite(IndicatorRedLED, HIGH);
  delay(5500);
  digitalWrite(IndicatorRedLED, LOW);
}

void green_LED_pulse(){
  digitalWrite(IndicatorGreenLED, HIGH);
  delay(5500);
  digitalWrite(IndicatorGreenLED, LOW);
}

float line_follower() {
    // reads the input on analog pin A0 (value between 0 and 1023)
    int left_light_s = analogRead(A3);
    int right_light_s = analogRead(A4);
    error = (left_light_s - (right_light_s + 300)) * 0.5; //if right light greater, robot is too far left, number is negative and vice versa ####THIS NEEDS A CONST  (currently 300) TO OFFSET SENSORS SO ERROR IS ZERO WHEN LEFT SENSOR IS LIGHT AN RIGHT IS DARK. IF THIS DOESNT WORK I WILL WRITE TURN LEFT FUNCTION.
    P = Kp * error;

    integral = integral + error;
    I = Ki * integral;

    derivative = error - previous_error;
    D = Kd * derivative;

    Serial.print("left light sensor reading = ");
    Serial.println(left_light_s);   // the raw analog reading
    Serial.print("right light sensor reading = ");
    Serial.println(right_light_s);   // the raw analog reading
    delay(500);
    previous_error = error;
    
    PID_value = P + I + D;
    //add something like if PID_value < certain value return 0 else return new value
    return(map(PID_value,0, max_value,0,1));
}

void motor_control() {
     right_speed = standard_speed + line_follower() * standard_speed; //if pid negative, this should be smaller
     left_speed = standard_speed - line_follower() * standard_speed;
     myMotor->setSpeed(left_speed); //LEFT
     myMotor2->setSpeed(right_speed); //RIGHT
     myMotor->run(FORWARD);
     myMotor2->run(FORWARD); //this may be reversed if wheels spinning in opposite direction
}

*/
