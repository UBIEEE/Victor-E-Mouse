#include <Arduino.h>
int directionPin = 12;

int pwmPin = 3;

int brakePin = 9;


//uncomment if using channel B, and remove above definitions

//int directionPin = 13;

//int pwmPin = 11;

//int brakePin = 8;


//boolean to switch direction

bool directionState;


void setup() {

  

//define pins

pinMode(directionPin, OUTPUT);

pinMode(pwmPin, OUTPUT);

pinMode(brakePin, OUTPUT);


}


void loop() {


//change direction every loop()

directionState = !directionState;


//write a low state to the direction pin (13)

if(directionState == false){

  digitalWrite(directionPin, LOW);

}


//write a high state to the direction pin (13)

else{

  digitalWrite(directionPin, HIGH);

}



//release breaks

digitalWrite(brakePin, LOW);


//set work duty for the motor

analogWrite(pwmPin, 30);


delay(2000);


//activate breaks

digitalWrite(brakePin, HIGH);


//set work duty for the motor to 0 (off)

analogWrite(pwmPin, 0);


delay(2000);
}