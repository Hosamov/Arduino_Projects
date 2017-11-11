// Intruder Alert Sketch, by Hosamov
// 11/11/2017

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define buzzPin 8              // Buzzer pin
#define sensorPin 3            // Sensor pin (PIR)
#define buttonPin 10            // Button pin

int pirState = true;           // assume no motion detected
int val = 0;                   // variable for reading pin status
int minSecAfterPIRLow = 5000;  // if sensor reports low, remain HIGH for this many milliseconds
boolean buzzState = false;     // Initial state of buzz pin
long pressCounter = 0;          // variable for storing how many times button has been pressed
int trigger = 0;

long unsigned int timeTurnedLow;
boolean takeLowTime; // This variable is used to record event where sensor turns off

// the time we give the sensor to calibrate(10-60 secs accroding to datashet)
int calibrationTime = 30;  // Time in seconds

// LCD I2C init:
// Addr, en, Rw, Rs, d4, d5, d6, d7, backlightpin, polarity
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void setup() {
  Serial.begin(9600);        // Init serial
  Wire.begin();              // Init I2C interface
  
  // Define pins:
  pinMode(buzzPin, OUTPUT);  // Define buzzer as output
  pinMode(sensorPin, INPUT); // Define sensor pin as input
  pinMode(buttonPin, INPUT); // Define button pin as input

  // LCD Setup
  lcd.begin(16,2);           // Setup 16x2 LCD screen
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Detected: ");
  lcd.print(pressCounter);

  Serial.println("Waiting for sensor to calibrate.");
  //delay(calibrationTime * 1000); // Convert the time from seconds to milliseconds
  Serial.println("SENSOR ACTIVE!");

}

void loop() {
  val = digitalRead(sensorPin);  // Read input data
  int buttonVal = digitalRead(buttonPin);

  if (val == HIGH) {
    trigger = 1;     // Set trigger to value: 1, so button can be pressed
    alarm(true);     // turn alarm on
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH) {
      // We have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
    if (buttonVal == HIGH && val == LOW && trigger == 1) {          // If button is pressed, and motion is not detected detected,
      alarm(false);                                 // Turn alarm off
      Serial.println("Button press detected!");
      Serial.println("Alarm: OFF");
      trigger = 0;
      pressCounter++; 
      lcd.setCursor(10,0);
      lcd.print(pressCounter);
    }
   
  }
  delay(1000);
}

void alarm(bool state){
  if (state == true) {          // If buzzState is true,
    tone(buzzPin, 4000);        // Project a tone
  } else if (state == false) {  // Or, if buzzState is false,
    noTone(buzzPin);            // Turn stop buzzer
  }
}

