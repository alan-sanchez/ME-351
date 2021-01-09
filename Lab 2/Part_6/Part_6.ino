// PIN SETUP
//  Pin variables are "const" because they should not change - they are set in hardware.
//  Pin variables are "byte" because they are small values (between 0 and 255).
//    "byte" (8 bits) is smaller than "int" (16 bits), which is smaller than "long" (32 bits).
const byte PIN_BUTTON_INTERRUPT = 2;

// VARIABLE SETUP
//  Variables changed within the interrupt function must be labeled "volatile"
//    This tells the Arduino IDE that these variables may change in an interrupt
//  States and flags are "bool", or true/false values. However, "bools" are still 8 bits.


// Time is best represented as "unsigned", or only positive values. This gives us twice the range.
volatile unsigned long time_interrupt = 0;


// setup() runs ONE TIME when the Arduino is powered on, reset, or the serial monitor is started.
void setup() {
  // Setup button pins as inputs
  pinMode(PIN_BUTTON_INTERRUPT, INPUT);

  // Setup the interrupt
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_INTERRUPT), button_interrupt, RISING);

  // Set up serial communication and print a message
  Serial.begin(9600);
  Serial.println("Starting Count!");
}

// loop() runs after setup and runs over and over until the board stops for some reason
void loop() {
  
}

// this function runs when the button is pressed and the interrupt is triggered
void button_interrupt() {
 
}
