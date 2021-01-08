/*
 Lab 2 part 2 Sign Off
*/

// digital pin 2 has a photoresistor attached to it.
int photo = 2;

// the setup routine runs once when you press reset:
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // make the potentiometer's pin an input:
  pinMode(photo, INPUT);

  // print top line
  Serial.println(" Time (ms), Input Value (V)");
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input on analog pin 0:
  float sensorValue = analogRead(A0)*.0049;
  
  // read the current time
  int time = millis(); 
  
  // print out the value you read:
  Serial.print(time);
  Serial.print(",");
  Serial.println(sensorValue);  
  delay(10);        // delay in between reads for stability
}
