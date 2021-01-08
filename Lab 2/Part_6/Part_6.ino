// PIN SETUP
//  Pin variables are "const" because they should not change - they are set in hardware.
//  Pin variables are "byte" because they are small values (between 0 and 255).
//    "byte" (8 bits) is smaller than "int" (16 bits), which is smaller than "long" (32 bits).
const byte PIN_BUTTON_INTERRUPT = 2;
const byte PIN_BUTTON_POLLING = 3;
const byte PIN_LED_INTERRUPT = 4;
const byte PIN_LED_POLLING = 5;

// VARIABLE SETUP
//  Variables changed within the interrupt function must be labeled "volatile"
//    This tells the Arduino IDE that these variables may change in an interrupt
//  States and flags are "bool", or true/false values. However, "bools" are still 8 bits.
volatile bool state_interrupt = false;
bool state_polling = false;
// Time is best represented as "unsigned", or only positive values. This gives us twice the range.
volatile unsigned long time_interrupt = 0;
unsigned long time_polling = 0;
// Flags let us know if something has happened already.
bool flag_interrupt = false;
bool flag_polling = false;

// setup() runs ONE TIME when the Arduino is powered on, reset, or the serial monitor is started.
void setup() {
  // Setup button pins as inputs
  pinMode(PIN_BUTTON_INTERRUPT, INPUT);
  pinMode(PIN_BUTTON_POLLING, INPUT);
  
  // Setup LED pins as outputs
  pinMode(PIN_LED_INTERRUPT, OUTPUT);
  pinMode(PIN_LED_POLLING, OUTPUT);

  // Setup the interrupt
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_INTERRUPT), button_interrupt, RISING);

  // Set up serial communication and print a message
  Serial.begin(9600);
  Serial.println("Begin the race!");
}

// loop() runs after setup and runs over and over until the board stops for some reason
void loop() {
  // An easy organizing method is to: 
  //    At the top of the loop, read/check everything
  //    In the middle of the loop, process things (math and logic)
  //    At the end, iterate/tick anything that needs to and delay if wanted
  
  // Check the button with polling
  state_polling = digitalRead(PIN_BUTTON_POLLING);

  // If it's on, measure the time and turn on the light (so we don't wait for printing)
  //    Normally, we'd have a statement like x > 5 in the if statement.
  //    Since we're using bool, we can just put the variable into it instead.
  //    Putting in other types of variables will return true if it is not empty or 0. 
  //  Don't do this again if we've already printed the polling time.
  if (state_polling && !flag_polling) {
    time_polling = millis();
    digitalWrite(PIN_LED_POLLING, HIGH);
  }

  // If the interrupt triggered and we haven't printed before, print.
  if (state_interrupt && !flag_interrupt) {
    Serial.print("Interrupt triggered! time: ");
    Serial.println(time_interrupt);

    // Then, set the flag to true so that we don't print again.
    flag_interrupt = true;
  }

  // If polling found the button on and we haven't printed before, print.
  if (state_polling && !flag_polling) {
    Serial.print("Polling triggered! time: ");
    Serial.println(time_polling);
    
    // Then, set the flag to true so that we don't print again.
    flag_polling = true; //so it only prints once
    Serial.print("Difference: ");
    Serial.println(time_polling - time_interrupt);
  }

  // SET DELAY HERE FOR LAB

  delay(100);
}

// this function runs when the button is pressed and the interrupt is triggered
void button_interrupt() {
  if (!state_interrupt) {
      state_interrupt = true;
      time_interrupt = millis();
      digitalWrite(PIN_LED_INTERRUPT, HIGH);
  }
}
