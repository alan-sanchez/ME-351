/*
 Lab 2 part 3 Sign Off
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
  
 
  float eps = 8/5.0;
  


  Serial.println(eps);  
  delay(100);        // delay in between reads for stability
}
