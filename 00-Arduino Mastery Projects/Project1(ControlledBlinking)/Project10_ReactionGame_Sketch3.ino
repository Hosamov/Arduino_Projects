//////////////////////////////////////////////////
//        Created 11/26/2017 by Hosamov         //
//           "Arduino Reaction Game"            //
//////////////////////////////////////////////////
////////////////////**NOTES**/////////////////////
// In this sketch, we build a reaction game.    //
// When the LED lights up and the buzzer makes a//
// noise, the player will react by pushing the  //
// pushbutton as quickly as possible.           //
// The goal of the game is the see how fast the //
// player's reflexes are. For an extra chal-    //
// lenge, play with friends.                    //
// At the end of three tries, the best reaction //
// time will be displayed.                      //
//////////////////**PARTS LIST**//////////////////
// - 1x LED (Any color)                         //
// - 1x piezo buzzer                            //
// - 1x momentary pushbutton                    //
// - 1x 220 Ohm resistor                        //
// - 1x 10k Ohm resistor                        //
// - 1x 16x2 LCD screen w/ I2C backpack         //
// - Assorted Jumper Wires                      //
//////////////////////////////////////////////////

// Include the following libraries for the LCD screen to function:
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C init:
// Addr, en, Rw, Rs, d4, d5, d6, d7, backlightpin, polarity
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Adjust I2C address as necessary.
                                                                // Run I2C Guesser sketch if unknown.

#define buttonPin  3   // Pushbutton                         
#define buzzPin    8   // Buzzer
#define ledPin     9   // LED


// variables:
bool buzzState          = false;                 // Determines buzzer on/off state
unsigned long millisNow = 0;                     // Used to hold value of current time elapsed
long int lastPress      = 0;                     // Variable holding value of last time button pressed
int interval            = random(1000, 10000);   // (min, max) <--Random timer set
int turn                = 0;                     // Variable for keeping track of what turn it is
int try1, try2, try3;                            // variables for keeping track of button values
int trigger             = 0;                     // Global trigger, used to validate buttonState

void setup() {
  // Initialize Serial:
  // Serial.begin(9600); // Used for troubleshooting

  // Pin mode initialization
  pinMode(buttonPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // LCD Initialization
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);

  // Opening jargon:
  lcd.print("Reaction Game!");
  lcd.setCursor(0,1);
  lcd.print("By: Hosamov");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press the button");
  lcd.setCursor(0,1);
  lcd.print("when sound heard");
  delay(5000);

  // Begin game start sequence
  startup();      // Call startup() function
}

void loop() {
  int buttonState = digitalRead(buttonPin);        // Declare variable to read state of pushbutton

  if (buttonState == LOW && buzzState == false) {  // If the button is not pressed and the state of the buzzer is false(off),
    if (turn == 1) {                               // If current turn is 1,
      lcd.clear();                                 // clear the LCD screen
      lcd.print("First Try: ");                    // and display number of try.
      tryOne();                                    // Call tryOne() function
    }
    if (turn == 2) {                               // If current turn is 2,
      lcd.clear();                                 // clear the LCD screen
      lcd.print("Second Try: ");                   // and display number of try.
      tryTwo();                                    // Call tryTwo() function
    }
    if (turn == 3) {                               // If current turn is 3,
      lcd.clear();                                 // clear the LCD screen
      lcd.print("Last Try: ");                     // and display number of try.
      tryThree();                                  // Call tryThree() function
    }
    if (turn == 4) {                               // Placeholder for turn 4
      // Game Over!
    }
  }
  if (buttonState == HIGH && buzzState == true && trigger == 0) {    // If button is pressed, state of buzzer is true(on),
                                                                     // and trigger variable is 0,
    trigger = 1;                                                     // Set trigger variable to 1 in order to keep this code
                                                                     // from continuing in an endless loop.
    lastPress = millis();                          // Mark the current time                                   
    if (turn == 1) {                               // If the current turn is 1,
      try1 = lastPress - millisNow;                // calculate the reaction time from the time the buzzer sounded
      // Serial.print(millisNow / 1000);           // Total elapsed time in seconds
      lcd.setCursor(0,1);                          
      lcd.print(try1);
      lcd.print("Ms");
      buzzState = false;                           // Set the buzzState variable to false
      buzzerAndLED(buzzState);                     // and call the buzzerAndLED function to turn off the buzzer and LED.
      delay(3000);                                 // Wait some time...
      turn++;                                      // Next try...
    } else if (turn == 2) {
      try2 = lastPress - millisNow;
      // Serial.print(millisNow / 1000);           // Total elapsed time in seconds
      lcd.setCursor(0,1);
      lcd.print(try2);
      lcd.print("Ms");
      buzzState = false;
      buzzerAndLED(buzzState);
      delay(3000);
      turn++;
    } else if (turn == 3) {
      try3 = lastPress - millisNow;
      // Serial.print(millisNow / 1000);            // Total elapsed time in seconds
      lcd.setCursor(0,1);  
      lcd.print(try3);
      lcd.print("Ms");    
      buzzState = false;
      buzzerAndLED(buzzState);
      delay(3000);
      lcd.clear();
      lcd.print("Game Over!");
      delay(3000);
      turn++;
    }
    delay(100);
  }
  if (turn == 4) {                                  // If the current turn is 4,
    lcd.clear();                                    // clear the LCD screen
    if (try2 > try1 && try3 > try1) {               // Determine which reaction time was the shortest
      delay(1000);                                  
      lcd.print("Your Best Time: ");          
      lcd.setCursor(0,1);
      lcd.print(try1);                              // Display the best time in Milliseconds
      lcd.print("Ms");
      delay(5000);
    } if (try1 > try2 && try3 > try2) {
      delay(1000);
      lcd.print("Your Best Time: ");
      lcd.setCursor(0,1);
      lcd.print(try2);
      lcd.print("Ms");
      delay(5000);
    } else if (try1 > try3 && try2 > try3) {
      delay(1000);
      lcd.print("Your Best Time: ");
      lcd.setCursor(0,1);
      lcd.print(try3);
      lcd.print("Ms");
      delay(5000);
    }
    lastPress = millis();                            // Mark the current time
    if (lastPress - millisNow >= 5000) {             // Wait 5 seconds from marked time
      lcd.clear();                                   // Clear the screen          
      lcd.print("Next Player...");                   // Warn next player it's their turn
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print("Get ready!");
      delay(2000);
      turn = 0;                                       // Set turn to 0,
      startup();                                      // call startup() function, to restart game for next player
    }
  }
  trigger = 0;                                        // Set trigger variable back to zero so we can use the pushbutton again!
}



void buzzerAndLED(bool state) {                       // Function  for controlling the buzzer and LED
  if (state == true) {
    tone(buzzPin, 4000);
    digitalWrite(ledPin, HIGH);
  } else if (state == false) {
    noTone(buzzPin);
    digitalWrite(ledPin, LOW);
  }
}

void startup() {                                       // "Countdown" code to run before each turn.
  lcd.clear();
  lcd.print("Start in: ");
  delay(1000);
  lcd.print("3...");
  tone(buzzPin, 4000);
  delay(500);
  noTone(buzzPin);
  delay(500); 
  lcd.setCursor(10,0);
  lcd.print("2...");
  tone(buzzPin, 4000);
  delay(500);
  noTone(buzzPin);
  delay(500);
  lcd.setCursor(10,0);
  lcd.print("1...");
  tone(buzzPin, 4000);
  delay(500);
  noTone(buzzPin);
  delay(500);
  lcd.clear();
  lcd.print("BEGIN!");
  tone(buzzPin, 6000);
  delay(500);
  noTone(buzzPin);
  delay(500);
  turn++;
}

void tryOne() {
  delay(1000);    // leeway time (optional)
  delay(interval);
  buzzState = true;
  buzzerAndLED(buzzState);
  millisNow = millis();
}

void tryTwo() {
  delay(1000);    // leeway time (optional)
  delay(interval);
  buzzState = true;
  buzzerAndLED(buzzState);
  millisNow = millis();
}

void tryThree() {
  delay(1000);    // leeway time (optional)
  delay(interval);
  buzzState = true;
  buzzerAndLED(buzzState);
  millisNow = millis();
}

