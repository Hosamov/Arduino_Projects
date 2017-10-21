// 10/21/2017, by: Hosamov
// "Cylon Lights"

// Setup input pin(s):
#define potPin 0

void setup() {
  // Setup LED pins as outputs:
  // LEDs: 1-6, Digital pins: 8-13
  pinMode(8, OUTPUT);  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  bool trigger = 1;

  // Have LEDs shift to right
  while (trigger == true) {
    for (int cylon = 0; cylon < 5; cylon++) {
      int cylonMap = map(cylon, 0, 5, 8, 13);    // In this while loop, map cylon with pin values
      int potVal = analogRead(potPin);           // Define variable for potVal
      int potMap = map(potVal, 0, 1024, 0, 255); // In this while loop, map actual values with potVal
      digitalWrite(cylonMap, HIGH);
      delay(potMap);
      digitalWrite(cylonMap, LOW);
      delay(potMap);

      if (cylon == 4) {       // If cylon reaches 5th LED... 
        trigger = 0;          // Set trigger to false, run next while loop
        break;                // break from this while loop
      }
    }
    // Now have LEDs shift back to the left
    while (trigger == false) {
      for (int cylon = 5; cylon <= 5; cylon--) {
        int cylonMap = map(cylon, 0, 5, 8, 13);      // In this while loop, map cylon to pin values   
        int potVal = analogRead(potPin);             // Define variable for potVal
        int potMap = map(potVal, 0, 1024, 0, 255);   // In this while loop, map actual values to potVal
        digitalWrite(cylonMap, HIGH);
        delay(potMap);
        digitalWrite(cylonMap, LOW);
        delay(potMap);

        if (cylon == 1) {      // If cylon reaches 1st LED...
          trigger = 1;         // Set trigger to true, run next while loop
          break;               // break from this while loop
        }
      }
    }
  }
}

