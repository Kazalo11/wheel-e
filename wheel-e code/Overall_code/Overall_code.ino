void setup() {
  // put your setup code here, to run once:
  //this will set pins up i think
}

void loop() {
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
    if (linefollowing() == left) { //therefore robot is to the right
      right_motor_scale = 1.2; //example value to make right motor spin more than left, correcting course
    }
    if (linefollowing() == right) {
      left_motor_scale = 1.2;
    }
    if (linefollowing() == centre) {
      left_motor_scale = 1;
      right_motor_scale = 1;
    }
  }
}
