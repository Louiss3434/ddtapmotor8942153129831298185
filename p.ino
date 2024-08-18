bool firstClick = false;
unsigned long firstClickTime = 0;
bool ledState = LOW;

//change this value
#define inputPullup 4
#define outputPin 0
#define delayBetweenClick 500

void setup() {
  pinMode(inputPullup, INPUT_PULLUP); // Assuming the button is connected to pin inputPullup with a pull-up resistor
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW); // Ensure the LED starts in the LOW state
}

void loop() {
  // Check if the button is pressed (active-low, so LOW means pressed)
  if (digitalRead(inputPullup) == LOW) {
    delay(50); // Debounce delay

    // Check again to ensure it's not noise
    if (digitalRead(inputPullup) == LOW) {
      // If this is the first click
      
      if(ledState == HIGH ){
        ledState = LOW;
        digitalWrite(outputPin, ledState);
      }
      
      if (!firstClick) {
        firstClick = true;                // Mark that the first click has happened
        firstClickTime = millis();         // Record the time of the first click
      } else {
        // If this is the second click
        int elapsedTime = (millis() - firstClickTime);
        if (elapsedTime < delayBetweenClick) {
          // Toggle the LED state
          ledState = !ledState;
          digitalWrite(outputPin, ledState);
        }
        firstClick = false; // Reset after the second click
      }
      // Wait for the button to be released
      while(digitalRead(inputPullup) == LOW);
      delay(50); // Additional debounce delay after release
    }
  } 
  
  // Reset the first click if more than 1000ms passes without a second click
  if (firstClick && (millis() - firstClickTime) >= delayBetweenClick) {
    firstClick = false; // Reset firstClick after timeout
  }
}
