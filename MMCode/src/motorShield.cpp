#include <Arduino.h>
#include <motorMovement.h>

Motor::Motor(int dPin, int pPin, int bPin){
    directionPin = dPin; 
    pwmPin = pPin; 
    brakePin = bPin; 
    bool directionState; //boolean to switch direction

    
    // int directionPin = 12;
    // int pwmPin = 3; 
    // int brakePin = 9;


}

void Motor::motorSheildSetup() {

//define pins

pinMode(directionPin, OUTPUT);

pinMode(pwmPin, OUTPUT);

pinMode(brakePin, OUTPUT);


}


void Motor::motorSheildloop() {
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

void Motor::move(){
    //release breaks
    return digitalWrite(brakePin, LOW);
}


