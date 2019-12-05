#include <Servo.h>
Servo name_servo;
int servo_position = 0;

void setup() {

  Serial.begin(9600);
  // declaring the pin
  name_servo.attach (9);

}

void loop() {
  //rotate angle
name_servo.write (180);
}  
