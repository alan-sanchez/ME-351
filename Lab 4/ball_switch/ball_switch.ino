// Derived from example code provided by www.elegoo.com

// Define pins
const byte LED_PIN = LED_BUILTIN; // LED_BUILTIN = 13 on the Uno
const byte SENSOR_PIN = 2;
int state = 0;
volatile int count = 0;
int prev_state = 0;

void setup() {
  // Set up pins
  pinMode(LED_PIN, OUTPUT);//initialize the ledPin as an output
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  state = digitalRead(SENSOR_PIN);
  Serial.print(state);
  Serial.print(", ");

  // Check the sensor state and act accordingly
  if (state == HIGH && prev_state == LOW) {
    count = count + 1;
    prev_state = HIGH;
  }

  else if (state == LOW) {
    prev_state = LOW;
  }
  Serial.println(count);

  delay(100);
}
