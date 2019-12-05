 #include <Servo.h>
 Servo name_servo;
 int servo_position;
 int soundSensor = A0;
 
 #define touchpin 11
 int mode = 0; 
 int buttonStatePrev = 0;
 int buttonState =0;
 
 int greenLED = 10;
 int blueLED =8;

 int brightness = 0;
 int fadeAmount = 5;
 int i=0;

 int threshold = 1000;
 int value = 0;

void setup() {

  pinMode(touchpin, INPUT);
  pinMode(soundSensor,INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  name_servo.attach (9);

}

void loop() {
  chooseMode();
  selectMode();
}

/************************ CHOOSE MODE ****************************/
void chooseMode() {

// checking at which state the mode button is 
  buttonState = digitalRead(touchpin);

// checking the button state 
  if (buttonState != buttonStatePrev) {
// if the button was pressed
    if (buttonState == HIGH) {
// changing the mode and make it goes back to the first one
    mode = (mode + 1) % 4;
    }
    buttonStatePrev = buttonState;
  }

}

/************************ SELECT MODE ****************************/

void selectMode()
{
  if (mode == 0) {
    reset();
  }
  else if (mode == 1) {
    openUp();
  }
  else if (mode == 2) {
    breathIn();
  }

  else if (mode == 3) {
    music();
  }
}

/************************ RESET MODE ****************************/

void reset()
{
name_servo.write(0);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);
}

/************************ OPEN UP MODE ****************************/

void openUp()
{
name_servo.write(150);
digitalWrite(blueLED, HIGH);
}

/************************ BREATH IN MODE ****************************/

void breathIn()
{
// BLUE LED//
for (int i=0; i <255; i++) {
  analogWrite(blueLED, i);
  delay(100);
}

for (int i=255; i > 0; i--) {
  analogWrite(blueLED, i);
  delay(100);
}

delay(50);

// GREEN LED
for (int i=0; i <255; i++) {
  analogWrite(greenLED, i);
  delay(100);
}

for (int i=255; i > 0; i--) {
  analogWrite(greenLED, i);
  delay(100);
}
}

/************************ MUSIC MODE ****************************/

void music()
{
 value = analogRead(soundSensor);  //set the value as the value read from A0
 Serial.println(value);

   for (servo_position = 0; servo_position <=150; servo_position +=1) {
   name_servo.write(servo_position);
   delay(50);
  }
   for (servo_position =150; servo_position >=0; servo_position -=1) {
   name_servo.write(servo_position);
   delay(50);    
  }

    
if (value >= threshold ) {
  digitalWrite(blueLED,HIGH);
  delay(100);
}
else{
  digitalWrite(blueLED ,LOW);

}

}
