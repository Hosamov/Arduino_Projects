// 10/17/2017, by Hosamov
// "Electronic Dice"

// LED pins & Placement:
int topLeft = 2;
int topRight = 3;
int middleLeft = 4;
int middle = 8;
int middleRight = 5;
int bottomLeft = 6;
int bottomRight = 7;

// Controller
int trigger = 0;

// Define variable for controlling random() function
long r;

//Button pin:
int inputPin = 10;

void setup() {
  randomSeed(analogRead(0));  //Ensure the code has a random seed to work with

  // Declare LED pins as outputs
  pinMode(topLeft, OUTPUT);
  pinMode(topRight, OUTPUT);
  pinMode(middleLeft, OUTPUT);
  pinMode(middle, OUTPUT);
  pinMode(middleRight, OUTPUT);
  pinMode(bottomLeft, OUTPUT);
  pinMode(bottomRight, OUTPUT);
  
  // Declare button pin as an input
  pinMode(inputPin, INPUT);
}

void loop() {
  if (digitalRead(inputPin) == HIGH && trigger == 0) {  // Cross-check the button with the controller variable
    trigger = 1;                                        // Set controller("trigger") variable to value of 1 so code within if statement can continue to run
    r = random(1, 7);                                   // Get a random number between 1 and 7

    // Rolling effect:
    int rolling;                                        
    for (rolling = 0; rolling < 100; rolling++) {       // Roll through the dice 100 times, randomly, before landing on the final number
    randomRoll(50);                                     // Call on randomRoll() function. Set delay.
    }


    if (r == 1) {
      one();
    }
    if (r == 2) {
      two();
    }
    if (r == 3) {
      three();
    }
    if (r == 4) {
      four();
    }
    if (r == 5) {
      five();
    }
    if (r == 6) {
      six();
    }
    delay(6000);
    clearPins();
    trigger = 0;
  }
}

// Set all OUTPUT pins to LOW when this function is called
void clearPins() {
  digitalWrite(topLeft, LOW);
  digitalWrite(topRight, LOW);
  digitalWrite(middleLeft, LOW);
  digitalWrite(middle, LOW);
  digitalWrite(middleRight, LOW);
  digitalWrite(bottomLeft, LOW);
  digitalWrite(bottomRight, LOW);
}

void one() {
  digitalWrite(middle, HIGH);
}

void two() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void three() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void four() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void five() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void six() {
  digitalWrite(topLeft, HIGH);
  digitalWrite(topRight, HIGH);
  digitalWrite(middleLeft, HIGH);
  digitalWrite(middleRight, HIGH);
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
}

// Rolling effect
void randomRoll(int roll) {
  int r;
  r = random(1, 8);
  digitalWrite(r, HIGH);
  if (roll > 0) {       
    delay(roll);
  }
  else if (roll == 0) {
    do {}
    while (1);
  }
  digitalWrite(r, LOW);
}





