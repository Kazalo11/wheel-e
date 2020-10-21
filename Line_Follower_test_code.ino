void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // reads the input on analog pin A0 (value between 0 and 1023)
  int left_light_s = analogRead(A0);
  int right_light_s = analogRead(A1);

  Serial.print("left light sensor reading = ");
  Serial.print(left_light_s);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (left_light_s < 10) {
    Serial.println(" - L_Dark");
  } else if (left_light_s < 200) {
    Serial.println(" - L_Dim");
  } else if (left_light_s < 500) {
    Serial.println(" - L_Light");
  } else if (left_light_s < 800) {
    Serial.println(" - L_Bright");
  } else {
    Serial.println(" - L_Very bright");
  }

  Serial.print("right light sensor reading = ");
  Serial.print(right_light_s);   // the raw analog reading
  
  if (right_light_s < 10) {
    Serial.println(" - R_Dark");
  } else if (right_light_s < 200) {
    Serial.println(" - R_Dim");
  } else if (right_light_s < 500) {
    Serial.println(" - R_Light");
  } else if (right_light_s < 800) {
    Serial.println(" - R_Bright");
  } else {
    Serial.println(" - R_Very bright");
  }

  
  delay(500);
}
