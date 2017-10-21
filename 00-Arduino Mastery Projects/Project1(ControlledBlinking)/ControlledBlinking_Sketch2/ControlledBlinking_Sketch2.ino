#define ledPin 13
#define potPin 0

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  int potVal = analogRead(potPin);
  int potMapped = map(potVal,0,512,0,255);
  digitalWrite(ledPin, HIGH);   
  delay(potMapped);                       
  digitalWrite(ledPin, LOW);    
  delay(potMapped);     
}                  

