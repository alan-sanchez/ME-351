/*
 Lab 2 part 2 Sign Off
*/

// digital pin 2 has a thermistor attached to it.
int Thermo = 2;
float R2 = 10000.0;
float Vi = 5.0;

// the setup routine runs once when you press reset:
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // make the thermistor's pin an input:
  pinMode(Thermo, INPUT);

  // print top line
  Serial.println(" Time (ms), Temp (C)");
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input on analog pin 0:
  float Vo = analogRead(A0)*.0049;

  // Compute Resistance of Thermo
  float R1 = (Vi / Vo * R2) - R2;
  // read the current time
  int time = millis(); 
  
  // print out the value you read:
  Serial.print(time);
  Serial.print(",");
  Serial.println(R1);  
  delay(10);        // delay in between reads for stability
}
