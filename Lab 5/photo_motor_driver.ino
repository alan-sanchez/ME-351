// Lab 5 Part 3 (remote version). Using a photocell to increase the speed of a DC motor as the light level increases.

int photoPin = A0;
int photoValue;
int PWM;

#define ENABLE 5
#define DIRA 3
#define DIRB 4

void setup() {
  Serial.begin(9600);
  
  pinMode(photoPin, INPUT);
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  //read in analog value from photocell
  photoValue = analogRead(photoPin);

  //map photocell value to a PWM output to the motor from 0-1023 to 0-255
  PWM = map(photoValue, 0, 1023, 0, 255);
  
  analogWrite(ENABLE,PWM); //turn motor on
  digitalWrite(DIRA,HIGH); //selected arbitrary direction
  digitalWrite(DIRB,LOW);
  
  delay(200); //arbitrary delay, started with 200, seemed to work fine
}
