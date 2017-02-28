/*
  Home Automation with Arduino,Android,Bluetooth

  Created 5 Dec 2016
  by Sayan Seth
  */
#include <Servo.h>

Servo myservo;

#define ledPin1 13
#define ledPin2 12
#define servoPin 9
#define thresh 500
int state = 0;
int flag=0;   //check if led 1 is changing state.If it is in auto mode, check the lighting condition in every loop. If it is not, don't.
void auto_light();
void setup() 
{
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
  myservo.attach(servoPin);
  Serial.begin(9600);     // Default communication rate of the Bluetooth module
}
void loop() {
  if(Serial.available() > 0)  // Checks whether data is comming from the serial port
  {                       
  state = Serial.read();  // Reads the data from the serial port
  }
  if (state == '2') 
 {
  digitalWrite(ledPin1, LOW); // Turn LED OFF
  state = 0;
  flag=1;                     //We are chnging state of LED 1, no need to run the auto function
 }
  if (state == '1') 
 {
  digitalWrite(ledPin1, HIGH); // Turn LED ON
  state = 0;
  flag=1;                      // We are changing state of LED 1, no need to run the auto function
 }
  if (state == '4') 
  {
  digitalWrite(ledPin2, LOW);
  state = 0;
 
 }
  if (state == '3') 
 {
  digitalWrite(ledPin2, HIGH);
  state = 0;
 }
  if (state == '5') 
 {
  myservo.write(10);
  delay(1000);
  state = 0;
 }
  if (state == '6') 
 {
  myservo.write(90);
  delay(1000);
  state = 0;
 }
  if (state == '7') 
 {
  myservo.write(170);
  delay(1000);
  state = 0;
 }
  if (state == '8' || flag==2) //Auto mode is activated, run the auto function 
 {
  auto_light();
  state = 0;
 }
}
void auto_light()
  {
   
    int val;
    flag=2; // signifies that auto mode is on
    val = analogRead(A0);
    if(val>=thresh)
    {
      digitalWrite(ledPin1,LOW);
    }
    else
      digitalWrite(ledPin1, HIGH);
      
    
    }


