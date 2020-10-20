
const int RedLED = 13; //number of RedLED
const int BlueLED = 12; //number of BlueLED
const int ColourSensor = 11; // number pin for ColourSensor

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  /*AFMS.begin();
  MotorWheelLeft->setSpeed(20);
  MotorWheelRight->setSpeed(20);
  myMotor-> run(FORWARD); */
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(ColourSesnsor, INPUT);
  
  
  

  

}

void loop() {
  
  //something like: while motor is running and nothing in ultrasound scanner, then run: 
  moving_light();
  //when the robot is within 5cm of the fruit
  
}



void moving_light() { //used to display the flashing light every 0.5s
  digitalWrite(LED_BUILTIN, (millis()/500) % 2); 
}

void ripe_or_unripe() {
  
  
}
