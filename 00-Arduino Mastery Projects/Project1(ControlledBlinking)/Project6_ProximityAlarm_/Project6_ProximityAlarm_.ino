// Proximity Alarm Sketch, by Hosamov
// 10/28/2017

#define redPin 3    // RGB LED Red Pin
#define greenPin 5  // RGB LED Green Pin
#define bluePin 6   // RGB LED Blue Pin 
#define buzzPin 8   // Buzzer Pin
#define trigPin 13  // HC-SR04 Trigger Pin
#define echoPin 12  // HC-SR04 Echo pin

void setup() {
  Serial.begin(9600);
  // Use these three pins to drive the LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // Use these two pins to drive Ultrasonic Sensor:
  pinMode(trigPin, OUTPUT);        // Set HC-SR04 Trigger pin as output
  pinMode(echoPin, INPUT);         // Set HC-SR04 Echo pin as input
}

void loop() {
  long duration, distanceCm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Distance measurement logic:
  duration = pulseIn(echoPin, HIGH);
  distanceCm = (duration / 2) / 29.1;      // Magic formula for finding distance in Cm

  if (distanceCm > 200 || distanceCm <= 0) {
    Serial.println("Not in range!");
  } else {
    Serial.println("In Range");
  }
  
  
  if(distanceCm > 20){                                   // If distance sensed is greater than 20cm,
    noTone(buzzPin);                                     // Turn the buzzer off
    analogWrite(redPin,0);                               // turn off Red LED
    analogWrite(greenPin,255);                           // turn ON the Green LED
    analogWrite(bluePin,0);                              // turn off Blue LED

  } else if(distanceCm >= 10 && distanceCm <= 20){       // If Distance is between 10cm and 20cm
    noTone(buzzPin);
    analogWrite(redPin, 0);                              // turn off Red LED
    analogWrite(greenPin, 0);                            // turn off Green LED
    analogWrite(bluePin, 255);                           // turn ON blue LED
    tone(buzzPin,500);                                   // Turn buzzer ON... tone 1000
  } else if(distanceCm < 10){                            // if Distance is less than 10Cm,
    noTone(buzzPin);                                     // Turn the buzzer off   
    analogWrite(redPin,255);                             // turn ON the red LED
    analogWrite(greenPin,0);                             // turn off Green LED
    analogWrite(bluePin,0);                              // turn off Blue LED
    tone(buzzPin,1500);                                  // turn buzzer ON... higher pitch
    delay(500);                                          // flash red
    analogWrite(redPin,0);
    delay(500);
  }
}
