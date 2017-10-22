// 10/22/2017, by Hosamov
// "Environment Monitor"

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_Sensor.h> //Must include this when using DHT.h library :P

// DHT Setup:
#define DHTPIN 2       // what pin we're connected to
#define DHTTYPE DHT22  //DHT11 or DHT22 

DHT dht(DHTPIN, DHTTYPE);

// LCD I2C init:
// Addr, en, Rw, Rs, d4, d5, d6, d7, backlightpin, polarity
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Setup pin(s) for additional sensors:
const int inputPin = 10;
const int ldrPin = A0;

int trigger = 0;
int controller = 1;

//Time vars:
unsigned long millis_now = 0;
int interval_one = 3000;
long int a_lastRun = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin();                    // Init I2C Interface
  dht.begin();                     // Init DHT Sensor
  float t = dht.readTemperature(); // Used to read temperature in Celsius while in the setup function    
  
  lcd.begin(16, 2);                // Init 16x2 LCD screen

  // LCD Setup:
  lcd.backlight();
  // Placeholder for current temperature, on line 2:
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(t);
  lcd.print(" *C");

  pinMode(inputPin, INPUT);    // Set button pin as an input
}

void loop() {
  // Setup vars to read humidity and temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();     // Temperature in Celsius
  float fTemp = t * 1.8 + 32.0;        // Temperature in Fahrenheit

  // Setup vars for LDR & pushbutton:
  int ldrVal = analogRead(ldrPin);     // var for LDR

  //Check and see if DHT is connected:
  if (isnan(t) || isnan(h)) {                    // If not connected,
    Serial.println("Failed to read from DHT");   // tell us.
  } else {
    lcd.setCursor(0, 0);
    lcd.print("H: ");
    if (h >= 99.99) {
      lcd.print("99.99 % | ");
    } else {
      lcd.print(h);
      lcd.print("% | ");
    }
    // Use LDR to determine whether it is "Lite" or "Dark"
    if (ldrVal >= 150) {    //Adjust this value to change darkness resistance       
      lcd.print("LITE");
    } else {
      lcd.print("DARK");
    }
    // Placeholder for current temperature, on line 2:
    lcd.setCursor(0, 1);
    lcd.print("T: ");

    while (controller == 1) {
      // Setup a timer to break the while loop in order to read other sensor values:
      millis_now = millis();
      Serial.print("Millis_now: ");
      Serial.println(millis());
         if (millis_now >= a_lastRun + interval_one) {
         a_lastRun = millis();
         Serial.println("Broke from While Loop");
         break;         
        }       
      if (digitalRead(inputPin) == HIGH && trigger == 0) {         // if pushbutton is pushed and trigger is FALSE,
        lcd.setCursor(3, 1);                                       // Set cursor position
        lcd.print(fTemp);                                          // Set temp to Fahrenheit
        lcd.print(" *F     ");
        delay(500);
        trigger = 1;
      } else if (digitalRead(inputPin) == HIGH && trigger == 1) {  // If pushbutton is pushed and trigger is TRUE,
        lcd.setCursor(3, 1);                                       // Set cursor position
        lcd.print(t);                                              // Set temp to Celsius
        lcd.print(" *C     ");
        delay(500);
        trigger = 0;
      }
    }
  }
  delay(1000);  //Insert a 1-sec delay between readings
}
