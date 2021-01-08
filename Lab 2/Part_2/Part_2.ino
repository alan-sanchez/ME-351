/*
 Lab 2 part 2 Sign Off
*/
// digital pin 2 has a pushbutton attached to it. Give it a name:
int pot = 2;

// the setup routine runs once when you press reset:
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // make the potentiometer's pin an input:
  pinMode(pot, INPUT);

  // print top line
  Serial.println(" Time (ms), Input Value (V), Input Value (digital)");
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0)*.00488;
  
  // read the input on digital pin 2:
  int buttonState = digitalRead(pot);

  // read the current time
  int time = millis(); 
  
  // print out the value you read:
  Serial.print(time);
  Serial.print(",");
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println(buttonState);
  
  delay(100);        // delay in between reads for stability
}
