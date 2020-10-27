#include <Time.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" //necessary libraries to allow the motor to run

//motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates the adafruit object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //request the left wheel motor - should be on whatever number is inside getMotor()
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

//PID setup
float Kp = 25;  //K values to be caibrated
float Ki = 0;
float Kd = 15;
float error = 0, derivative = 0, integral = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0;
int flag = 0;

int standard_speed = 100;
float max_value = 500;
float new_speed;

//proximity
float x = 25, proximity = 30;

//"traffic light" LEDs
const int IndicatorRedLED = 13; //number of RedLED
const int IndicatorAmberLED = 10; //these numbers need to be edited
const int IndicatorGreenLED = 11; //number of GreenLED

//colour sensor




void setup() {
  // put your setup code here, to run once:
  //this will set pins up i think
  //INDICATOR LEDS
    pinMode(IndicatorAmberLED, OUTPUT);
    pinMode(IndicatorGreenLED, OUTPUT);
    pinMode(IndicatorRedLED, OUTPUT);
  //this is line follower setup (for testing)
    Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
    delay(500);
    Serial.println("Started !!");
    delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  proximity_sensor();
  while (proximity > x and time < 400) { // while no fruit, follow line
    proximity_sensor();
    motor_control(); // takes PID value and changes motor speeds to follow line 
    LED_blink_amber();
    if (proximity < x) { //this means a fruit has tripped sensor
      //stops moving by not including forward()
      LED_const_amber();
      ripe_or_unripe(); //function to blink the red test LED and take colour reading, ditto for blue, then compare colour readings and returns ripe = TRUE or FALSE
      if (ripe_or_unripe() == true) {
        green_LED_pulse(); //shows green indicator LED for <5s
        collect_fruit(); //easier to throw it all in a function
      }
      else {
        red_LED_pulse();
        go_round(); //this is going to be a fat fuction to leave line and join after unripe fruit
      }
    }
  }
}

float line_follower() {  //takes analogue values of light sensors and outputs PID_value for controlling motors 
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
    //add something like if PID_value < certain value return 0 else return new value
    return(map(PID_value,0, max_value,0,1));

    delay(500); //not sure about this

    

}

void motor_control() {
     new_speed = line_follower() * standard_speed + standard_speed; 
     myMotor->setSpeed(new_speed);
     myMotor2->setSpeed(new_speed);
     myMotor->run(FORWARD);
     myMotor2->run(FORWARD);
}


void collect_fruit() {
  
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

void green_LED_pulse(){
  digitalWrite(IndicatorGreenLED, HIGH);
  delay(5500);
  digitalWrite(IndicatorGreenLED, LOW);
}

void red_LED_pulse(){
  digitalWrite(IndicatorRedLED, HIGH);
  delay(5500);
  digitalWrite(IndicatorRedLED, LOW);
}

bool ripe_or_unripe(){
  return(true);
}

void go_round(){
  
}

/* OLD LINE FOLLOWER CODE, KEPT IN CASE STUFF GOES WRONG
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
}*/
