// By: Hosamov 10/8/17
// Binary LED Display - Potentiometer
// Connect potentiometer to analog pin 0 and read its value.
// Display potentiometer value in binary on the row of LEDs
// through the shift register(s) (74HC595).

#define DATA 8   // Connect to DS/Pin 14 of SR
#define LATCH 9  // Connect to ST_CP/pin 12 of SR
#define CLOCK 10 // Connect to SH_CP/pin 11 of SR

const int potPin = 0;

int val;

void setup() {
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop() {
  val = analogRead(potPin);     // get the value of the potentiometer
  val = map(val,0,1024,0,256);  // Scale val to 256
  displayPotValue(val);         // Show value of potentiometer on LED display.
}

void displayPotValue(byte a) {
  //send the byte to be displayed on the LEDs
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, a);
  digitalWrite(LATCH, HIGH);
}


