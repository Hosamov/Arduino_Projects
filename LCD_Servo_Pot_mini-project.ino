////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Controlling a servo position using a potentiometer, and printing the potentiometer value to an LCD I2C device. //
////////////////////////////////////////////// Matt Coale's Solution////////////////////////////////////////////////
// Most code in this sketch was copied from Peter Dalamaris (and others), and was compiled by Matt Coale, for the //
// purpose of completing the mini-project in Lecture 52 of "Arduino Step by Step" taught by Peter Dalamaris.      //
// For an image of the completed circuit, please visit: https://imgur.com/Ac5CxM2                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <VarSpeedServo.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

VarSpeedServo myServo;              //Create servo object to control a servo

//Addr, en, Rw, Rs, d4, d5, d6, d7, backlightpin, polarity
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);
               
const int servoPin = 9;              //Declare digital pin used for servo   
const int potPin = 0;                //Declare pin used for Potentiometer
int val;                 

void setup() {
  Wire.begin();
  myServo.attach(servoPin);         //attaches the servo on pin 9 to servo object
  
  Serial.begin(9600);               
  
  lcd.begin(16,2);                  //Setup LCD screen (size)
  lcd.backlight();                  
  lcd.setCursor(0,0);       
  lcd.print("Servo Angle: ");       //Add user-friendliness (Permanent during program run)          
}

void loop() {
  val = analogRead(potPin);         //Reads value of potentiometer
  val = map(val,0,1023,0,180);      //scale it to use with the servo
  myServo.write(val);               //Set servo position
  Serial.println(val);              //Send pot value to Serial Monitor
  delay(15);
              
  lcd.setCursor(13,0);
  lcd.print(val);                   //Show current servo position on LCD screen            

  if (val <= 99){                   //Clear 3rd digit from screen if servo pos falls below 100
    lcd.setCursor(15,0);            //Allows numbers to remain the same darkness without flickering
                                    //on and off very rapidly.
    lcd.print(" "); }
  
  if (val <= 9){                    //Clear 2nd digit from screen if servo pos falls below 10
    lcd.setCursor(14,0);          
    lcd.print("  "); }

}


