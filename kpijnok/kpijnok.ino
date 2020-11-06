
int IndicatorAmberLED = 1;
int ledState = LOW;
float previousMillis = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(IndicatorAmberLED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 500) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(IndicatorAmberLED, ledState);
}
}
