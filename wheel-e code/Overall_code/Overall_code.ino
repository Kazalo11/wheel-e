//PID setup
float Kp = 25;
float Ki = 0;
float Kd = 15;
float error = 0, derivative = 0, integral = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0;
int flag = 0;

void setup() {
  // put your setup code here, to run once:
  //this will set pins up i think

  //this is line follower setup (for testing)
    Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
    delay(500);
    Serial.println("Started !!");
    delay(1000);
}

void loop() {
  line_follower(); //takes analogue values of light sensors and outputs PID_value for controlling motors 
  // put your main code here, to run repeatedly:
  while (proximity() > x and linefollowing() == centre and time < 400) { //robot is moving forward following the line as default
    forward();
    LED_blink_amber();
    if (proximity() < x) { //this means a fruit has tripped sensor
      //stops moving by not including forward()
      LED_const_amber();
      red_LED_test(); //this function will blink the red test LED and take colour reading
      blue_LED_test(); //ditto for blue
      ripe_or_not(); //function to compare colour readings and returns ripe = TRUE or FALSE
      if (ripe == true) {
        green_LED_pulse(); //shows green LED for <5s
        flap(1);
        forward(10); //this syntax is almost certainly wonky, should move forward 10cm (collecting ripe)
        flap(0);
      }
      else {
        go_round(); //this is going to be a fat fuction to leave line and join after unripe fruit
      }
    }
    //below is pseudocode using output of Line_follower, PID_value. 
    //It is probably beter to use PId_value directly to scale motors for more proportional controlthan this method below
    if (PID_value == *left value*) { //therefore robot is to the right
      right_motor_scale = 1.2; //example value to make right motor spin more than left, correcting course
    }
    if (PID_value == *right value*) {
      left_motor_scale = 1.2;
    }
    if (PID_value == *centre value*) {
      left_motor_scale = 1;
      right_motor_scale = 1;
    }
  }
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
