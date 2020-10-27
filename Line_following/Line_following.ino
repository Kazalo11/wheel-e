/*this is the code to be implemented in overall_code for line following. 
 *The changing of motor speeds is not included as it would be more readable 
 *in a seperate function that takes PID_Value to control motor. 
  */
//PID setup
float Kp = 25;
float Ki = 0;
float Kd = 15;
float error = 0, derivative = 0, integral = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0;
int flag = 0;
//need input data from line followers




void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
    delay(500);
    Serial.println("Started !!");
    delay(1000);
}

void loop() { 
    line_follower(); //set this PID_value returned
    //multiply PID_Value by motor speed to get new motor speed
    
}


void line_follower() {
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

    delay(500); //not sure about this

    //return PID_value

}
