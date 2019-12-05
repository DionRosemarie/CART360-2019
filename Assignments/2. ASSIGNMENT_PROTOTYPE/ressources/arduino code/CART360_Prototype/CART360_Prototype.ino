#include <Servo.h>
Servo name_servo;


#define touchpin 3
int servo_position = 0;
int soundSensor = A0;

int greenLED = 8;
int blueLED =9;
int brightness = 0;
int fadeAmount = 5;
int i=0;

int buttonPin = 4;  
int buttonState = 0;
int threshold = 1000;
int value = 0;

int mode = 0; 
int buttonStatePrev = 0;
 
void setup() {

  Serial.begin(9600);
  pinMode(touchpin, INPUT);
  
  pinMode(soundSensor,INPUT);
  
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  name_servo.attach (9);

}

void loop() {
 light();
int touchValue = digitalRead(touchpin); //reads the touch sensor signal
  if (touchValue == HIGH){      //if sensor is HIGH
activate();
  }

}  

void activate() {
 //print the value and line wrap //

   for (servo_position = 0; servo_position <=150; servo_position +=1) {
   name_servo.write(servo_position);
   delay(50);
  }
   for (servo_position =150; servo_position >=0; servo_position -=1) {
   name_servo.write(servo_position);
   delay(50);    
  }
 
   
 }

 void light() {
  value = analogRead(soundSensor);  //set the value as the value read from A0
  Serial.println(value);

    
if (value >= threshold ) {
  digitalWrite(ledPin,HIGH);
  delay(100);
}
else{
  digitalWrite(ledPin ,LOW);

}

  }
