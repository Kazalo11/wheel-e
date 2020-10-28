#include <Time.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

//motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

int standard_speed = 100;
float max_value = 500;
float new_speed;
float right_speed, left_speed;

//PID setup
float Kp = 25;  //K values to be caibrated
float Ki = 0;
float Kd = 15;
float error = 0, derivative = 0, integral = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0;
int flag = 0;

//proximity
#define echoPin 2 //attach pin D2 Arduino to pin Echo of the ultrasound
#define trigPin 3 //attach pin D3 to pin Trig of ultrasound

long duration; //will store how long the sound wave takes to travel
double distance; // will store distance measurement
double SoundSpeed = 0.034; //speed of sound in air (can change to be more accurate)
float x = 25, proximity = 30;

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


void setup() {
  // put your setup code here, to run once:
  //this will set pins up i think
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
}


void loop() {
  // put your main code here, to run repeatedly:
  proximity_sensor();
  while (proximity > x) { // while no fruit, follow line
    proximity_sensor();
    motor_control(); // takes line follower PID value and changes motor speeds to follow line 
    LED_blink_amber(); 
  }
  //if (proximity < x)  //this means a fruit has tripped sensor
  //stops moving by not including forward()
  LED_const_amber();
  is_ripe(); //function to blink the red test LED and take colour reading, ditto for blue, compare colour readings and return ripe = TRUE or FALSE. also lights indicator leds
  if (is_ripe() == true) {
    collect_fruit(); //easier to throw it all in a function
  }
  else {
    go_round(); //this is going to be a fat fuction to leave line and join after unripe fruit
  }
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

void collect_fruit() {
    unsigned long StartTime = millis();
  StartTime = millis();
    while(millis() - StartTime <= 2500) {
     myMotor->setSpeed(120);
     myMotor2->setSpeed(120);
     myMotor->run(FORWARD);
     myMotor2->run(FORWARD);
    }
}

void proximity_sensor() {
  proximity = 40;
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

void go_round(){
  
}

/* OLD CODE, KEPT IN CASE STUFF GOES WRONG
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

*/
