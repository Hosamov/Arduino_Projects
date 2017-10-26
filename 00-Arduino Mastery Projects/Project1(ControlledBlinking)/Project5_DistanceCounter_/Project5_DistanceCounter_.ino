// 10/23/2017, by Hosamov
// "Distance Counter"

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C init:
// Addr, en, Rw, Rs, d4, d5, d6, d7, backlightpin, polarity
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Set Echo and Trigger Pins for HC-SR04:
const int trigPin = 13;
const int echoPin = 12;

// Setup pin(s) for additional sensor:
const int inputPin = 2;


int trigger = 0;
int oldButtonState = LOW;

// Time vars:
unsigned long millis_now = 0;
int interval_one = 3000;
long int a_lastRun = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin();                    // Init I2C Interface
  lcd.begin(16,2);                 // Setup LCD Screen
  lcd.backlight();
  // Define I/O pins used:
  pinMode(inputPin, INPUT);        // Set button pin as an input
  pinMode(trigPin, OUTPUT);        // Set HC-SR04 Trigger pin as output
  pinMode(echoPin, INPUT);         // Set HC-SR04 Echo pin as input  // LCD Setup:

}

void loop() {
  long duration, distanceCm, distanceIn, distanceFt, distanceM;      
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Distance measurement logic:
  duration = pulseIn(echoPin, HIGH);
  distanceCm = (duration / 2) / 29.6;      // Magic formula for finding distance in Cm
  distanceM = distanceCm * 0.01;           // Convert distanceCm into meters
  distanceIn = distanceCm / 2.54;          // Convert distance Cm into Inches
  distanceFt = distanceCm * 0.0328084 ;    // Convert distanceCm into Feet
  

  //Is the button pressed?
  int newButtonState = digitalRead(inputPin);
  delay(50);
  
  if (distanceCm > 200 || distanceCm <= 0) {
    lcd.setCursor(0, 0);
    lcd.print("Not In Range");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Toggle Cm/In     ");
  }
  if (newButtonState == LOW && oldButtonState == LOW){
    lcd.setCursor(0,1);
    lcd.print(distanceCm);
    lcd.print("   ");
    lcd.setCursor(5,1);
    lcd.print("Cm, ");
    lcd.setCursor(9,1);
    lcd.print(distanceM,DEC);
    lcd.print("  ");
    lcd.setCursor(11,1);
    lcd.print("M ");
  } else if (newButtonState == HIGH && oldButtonState == LOW){
    lcd.setCursor(0,1);
    lcd.print(distanceIn);
    lcd.print("   ");
    lcd.setCursor(5,1);
    lcd.print("In, ");
    lcd.setCursor(9,1);
    lcd.print(distanceFt,DEC);
    lcd.print("  ");
    lcd.setCursor(11,1);
    lcd.print("Ft ");
    oldButtonState = HIGH;
  } else if (newButtonState == LOW && oldButtonState == HIGH){
    lcd.setCursor(0,1);
    lcd.print(distanceIn);
    lcd.print("   ");
    lcd.setCursor(5,1);
    lcd.print("In, ");
    lcd.setCursor(9,1);
    lcd.print(distanceFt,DEC);
    lcd.print("  ");
    lcd.setCursor(11,1);
    lcd.print("Ft ");
  } else if (newButtonState == HIGH && oldButtonState == HIGH){
    lcd.setCursor(0,1);
    lcd.print(distanceCm);
    lcd.print("   ");
    lcd.setCursor(5,1);
    lcd.print("Cm, ");
    lcd.setCursor(9,1);
    lcd.print(distanceM,DEC);
    lcd.print("  ");
    lcd.setCursor(11,1);
    lcd.print("M ");
    oldButtonState = LOW;
  }
  delay(100);  //Insert a 1-sec delay between readings
}
