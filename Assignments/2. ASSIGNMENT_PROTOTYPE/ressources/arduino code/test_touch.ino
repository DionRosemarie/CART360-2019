#define touchpin 4 // sets the capactitive touch sensor @pin 4
int ledPin = 2; // sets the LED @pin 2
int motorPin = (5,6);

void setup() {
  Serial.begin(9600);
  pinMode(touchpin, INPUT); //sets the touch sensor as input
  //pinMode(ledPin, OUTPUT);  //sets the led as output
  pinMode(motorPin, OUTPUT);
}
void loop() {
  int touchValue = digitalRead(touchpin); //reads the touch sensor signal
  if (touchValue == HIGH){      //if sensor is HIGH
    digitalWrite(motorPin, HIGH);   //LED will turn ON
    Serial.println(touchValue);
  }
  else{       //otherwise
    digitalWrite(motorPin,LOW); //LED is turned OFF
  } 
  delay(300);   //delay of 300milliseconds
 
}
