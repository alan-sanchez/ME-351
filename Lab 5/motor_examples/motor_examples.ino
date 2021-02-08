// Derived from example code provided by www.elegoo.com

// Define pins connecting to the L293D
const byte ENABLE_PIN = 5;
const byte DIR_PIN_A = 3;
const byte DIR_PIN_B = 4;

void setup() {
  // Set up pins as outputs for controlling the motor
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(DIR_PIN_A, OUTPUT);
  pinMode(DIR_PIN_B, OUTPUT);

  // Set up communication
  Serial.begin(9600);
}

void loop() {
  // Loop through a series of behaviors

  // Behavior 1: go back and forth
  Serial.println("One way, then reverse.");
  // Enable the motor driver (turn on the motor)
  digitalWrite(ENABLE_PIN, HIGH);
  // Loop through this 5 times
  for (int i = 0; i < 3; i++) {
    // Set motor direction forwards
    digitalWrite(DIR_PIN_A, HIGH);
    digitalWrite(DIR_PIN_B, LOW);
    delay(500);
    // Set motor direction reversed
    digitalWrite(DIR_PIN_A, LOW);
    digitalWrite(DIR_PIN_B, HIGH);
    delay(500);
  }

  // Disable the motor driver (turn off the motor)
  Serial.println("Off.");
  digitalWrite(ENABLE_PIN, LOW);
  delay(2000);

  // Behavior 2: coasting to a stop vs. braking
  Serial.println("Stopping by coasting...");
  // Set motor direction forwards
  digitalWrite(DIR_PIN_A, HIGH);
  digitalWrite(DIR_PIN_B, LOW);
  // Enable the motor driver (turn on the motor)
  digitalWrite(ENABLE_PIN, HIGH);
  delay(2000);
  // Disable the motor driver (turn off the motor, coasting to a stop)
  Serial.println("Off.");
  digitalWrite(ENABLE_PIN, LOW);
  delay(2000);

  // Enable the motor driver (turn on the motor)
  Serial.println("Stopping by braking...");
  // Set motor direction forwards
  digitalWrite(DIR_PIN_A, HIGH);
  digitalWrite(DIR_PIN_B, LOW);
  // Enable the motor driver (turn on the motor)
  digitalWrite(ENABLE_PIN, HIGH);
  delay(2000);
  // Set motor direction to braking (both LOW or HIGH)
  Serial.println("Braking.");
  digitalWrite(DIR_PIN_A, LOW);
  delay(2000);

  // Disable the motor driver (turn off the motor)
  Serial.println("Off.");
  digitalWrite(ENABLE_PIN, LOW);
  delay(2000);

  Serial.println("Driving at different speeds.");
  // Set motor direction forwards
  digitalWrite(DIR_PIN_A, HIGH);
  digitalWrite(DIR_PIN_B, LOW);
  // Drive at full speed (255/255 PWM)
  analogWrite(ENABLE_PIN, 255); //enable on
  delay(2000);
  // Drive at various partial speeds (x/255 PWM)
  analogWrite(ENABLE_PIN, 180);
  delay(2000);
  analogWrite(ENABLE_PIN, 128);
  delay(2000);
  analogWrite(ENABLE_PIN, 50);
  delay(2000);
  analogWrite(ENABLE_PIN, 128);
  delay(2000);
  analogWrite(ENABLE_PIN, 180);
  delay(2000);
  analogWrite(ENABLE_PIN, 255);
  delay(2000);

  // Disable the motor driver (turn off the motor)
  Serial.println("Off.");
  digitalWrite(ENABLE_PIN, LOW);
  delay(2000);
}
