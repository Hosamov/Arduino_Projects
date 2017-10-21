
// Set positions of LED pin(s):
#define ledPin1 8
#define ledPin2 9
#define ledPin3 10
#define ledPin4 11
#define ledPin5 12
#define ledPin6 13

// Setup input pin(s):
#define potPin 0

void setup() {
  // Setup LED pins as outputs
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);
  pinMode(ledPin6,OUTPUT);
}

void loop() {
  int potVal = analogRead(potPin);        //Define variable for potVal
  int potMap = map(potVal,0,1024,0,255);  // Map the values in order to have more control over LED speed
  digitalWrite(ledPin1,HIGH);
  delay(potMap);
  digitalWrite(ledPin1,LOW);
  delay(potMap);
  digitalWrite(ledPin2,HIGH);
  delay(potMap);
  digitalWrite(ledPin2,LOW);
  delay(potMap);
  digitalWrite(ledPin3,HIGH);
  delay(potMap);
  digitalWrite(ledPin3,LOW);
  delay(potMap);
  digitalWrite(ledPin4,HIGH);
  delay(potMap);
  digitalWrite(ledPin4,LOW);
  delay(potMap);
  digitalWrite(ledPin5,HIGH);
  delay(potMap);
  digitalWrite(ledPin5,LOW);
  delay(potMap);
  digitalWrite(ledPin6,HIGH);
  delay(potMap);
  digitalWrite(ledPin6,LOW);
  delay(potMap);
  digitalWrite(ledPin5,HIGH);
  delay(potMap);
  digitalWrite(ledPin5,LOW);
  delay(potMap);
  digitalWrite(ledPin4,HIGH);
  delay(potMap);
  digitalWrite(ledPin4,LOW);
  delay(potMap);
  digitalWrite(ledPin3,HIGH);
  delay(potMap);
  digitalWrite(ledPin3,LOW);
  delay(potMap);
  digitalWrite(ledPin2,HIGH);
  delay(potMap);
  digitalWrite(ledPin2,LOW);
  delay(potMap);

}
