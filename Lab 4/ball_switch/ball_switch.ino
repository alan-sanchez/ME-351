// Derived from example code provided by www.elegoo.com

// Define pins
const byte LED_PIN = LED_BUILTIN; // LED_BUILTIN = 13 on the Uno
const byte SENSOR_PIN = 2;
int state = 0;

void setup() {
  // Set up pins
  pinMode(LED_PIN, OUTPUT);//initialize the ledPin as an output
  pinMode(SENSOR_PIN, INPUT_PULLUP);
}

void loop() {
  state = digitalRead(SENSOR_PIN);
  // Check the sensor state and act accordingly
  if (state == HIGH) {
    // Disconnected; turn the LED off
    digitalWrite(LED_PIN, HIGH);
  } else {
    // Connected; turn the LED on
    digitalWrite(LED_PIN, LOW);
  }
}
