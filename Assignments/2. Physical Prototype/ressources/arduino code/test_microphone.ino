int sensorPin =A0 ;  // define analog port A0   //set value to 0
int LED1 = 2;
int LED2 = 0;
int LED3 = 1;
int threshold = 1000;
int value = 0;


void setup() 
{
 Serial.begin(9600); //set the baud rate to 9600
 pinMode(sensorPin, INPUT);
 pinMode(LED1,OUTPUT);
 pinMode(LED2,OUTPUT);
 pinMode(LED3,OUTPUT);
 
} 

void loop() 
{
value = analogRead(sensorPin);  //set the value as the value read from A0
Serial.println(value); //print the value and line wrap //

if (value >= threshold ) {
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,HIGH);
  delay(100);
}
else{
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,LOW);
}

}
