// By: Hosamov 10/8/17
// Binary LEDs using Serial as Input.
// Write a number in the console to see LEDs write in binary.

#define DATA 8   // Connect to DS/Pin 14 of SR
#define LATCH 9  // Connect to ST_CP/pin 12 of SR
#define CLOCK 10 // Connect to SH_CP/pin 11 of SR

int number = 0;
int answer = 0;

void setup() {
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  Serial.begin(9600);
}

void displayNumber(byte a) {
  //send the byte to be displayed on the LEDs
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, a); 
  // if using 2nd shift register:
  // shiftOut(DATA, CLOCK, MSBFIRST, a); 
  digitalWrite(LATCH, HIGH);
}

void getAnswer() {
  // receive the answer from the user
  int z = 0;
  Serial.flush();
  while (Serial.available() == 0) {
    //do nothing until something comes into serial buffer
  }
  while (Serial.available() > 0) {
    // move any previous digit to the enxt column on the left; in
    // other words, 1 becomes 10 while there is data in the buffer
    answer = answer * 10;
    // Read the next number in the buffer and subtract the chacter '0'
    // from it to convert it to the actual integer number
    z = Serial.read() - '0';
    // add this digi into the accumulating value
    answer = answer + z;
    // allow a short delay for any more numbers to come into Serial.available
    delay(5);
  }
  Serial.print("You entered: ");
  Serial.println(answer);
}

void checkAnswer(){
  // check the answer from the user and show results
  Serial.print("Num: ");
  Serial.print(answer);
  Serial.print(" Binary: ");
  Serial.print(answer, BIN);
  Serial.println();
  delay(1000);
  answer = 0;
}

void loop() {
  Serial.println("Type a number");
  getAnswer();
  displayNumber(answer);
  delay(10);
  checkAnswer(); 
}



