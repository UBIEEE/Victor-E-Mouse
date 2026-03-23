#include <sensor.h>
#include <Arduino.h>
#include <Drive.hpp>

/*
 * created by Rui Santos, https://randomnerdtutorials.com
 *
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
float cprevEr=0;
float cposEr=0;
float ctotalEr=0;
float clast=0;
float ckp=.05;
float cki=.00000;
float ckd=0.00000000;

float distanceWhenLeftWallChange;
float distanceWhenRightWallChange;
int last1LeftReading=0;
int last2LeftReading=0;
int last3LeftReading=0;
int last1RightReading=0;
int last2RightReading=0;
int last3RightReading=0;
int last1MiddleReading=0;
int last2MiddleReading=0;
int last3MiddleReading=0;
int filteredLeft=0;
int filteredRight=0;
int filteredMiddle=0;

Sensor::Sensor(int tPin, int ePin)
{
    trigPin = tPin;
    echoPin = ePin;
}
Sensor left(A1, A0);
Sensor middle(A4, A3); // change when we have the third sensor later
Sensor right(D12, D11);

int Sensor::getTrig()
{
    return trigPin;
}

int Sensor::getEcho()
{
    return echoPin;
}

long Sensor::getDuration()
{
    return duration;
}

long Sensor::getReading()
{
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    duration = pulseIn(echoPin, HIGH);

    // Convert the time into a distance
    cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
    inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135
   /* Serial.print("in ");
    Serial.print(inches);
    Serial.print(" cm ");
    Serial.print(cm);
    Serial.println();
    */
    return cm;
}
float keepCenter(){
    float wallExists=9;
    float measurement=0;
    if(left.getReading()<wallExists && right.getReading()<wallExists){
        measurement=left.getReading()-right.getReading();
    }
    else if(left.getReading()<wallExists){
        measurement=left.getReading()-7;
    }
    else if (right.getReading()<wallExists){
        measurement=7-right.getReading();
    }
    float now=millis();
    float setpoint=0;
    float delta=now-clast;
    cprevEr=cposEr;
    cposEr=setpoint-measurement;
    float vel=(cposEr-cprevEr)/delta;
    ctotalEr=ctotalEr+cposEr*delta;
    clast=now;
    return ckp*cposEr+cki*ctotalEr+ckd*vel;
}
void sensorLoop()
{
    // Sensor Code
    driveLoop();
        if(filteredLeft!=0 && left.getReading()-filteredLeft>=25){
            distanceWhenLeftWallChange=driveGetLeftEncoderDistance();
        }
        if(filteredRight!=0 && right.getReading()-filteredRight>=25){
            distanceWhenRightWallChange=driveGetRightEncoderDistance();
        }
        last1LeftReading=left.getReading();
        last2LeftReading=last1LeftReading;
        last3LeftReading=last2LeftReading;
        last1RightReading=right.getReading();
        last2RightReading=last1RightReading;
        last3RightReading=last2RightReading;
        last1MiddleReading=middle.getReading();
        last2MiddleReading=last1RightReading;
        last3MiddleReading=last2RightReading;
        if(last1LeftReading<=last2LeftReading<=last3LeftReading || last3LeftReading<=last2LeftReading<=last1LeftReading){
            filteredLeft=last2LeftReading;
        }
        else if (last2LeftReading<=last1LeftReading<=last3LeftReading || last3LeftReading<=last1LeftReading<=last2LeftReading){
            filteredLeft=last1LeftReading;
        }
        else {
            filteredLeft=last3LeftReading;
        }
        if(last1RightReading<=last2RightReading<=last3RightReading || last3RightReading<=last2RightReading<=last1RightReading){
            filteredRight=last2RightReading;
        }
        else if (last2RightReading<=last1RightReading<=last3RightReading || last3RightReading<=last1RightReading<=last2RightReading){
            filteredRight=last1RightReading;
        }
        else {
            filteredRight=last3RightReading;
        }
        if(last1MiddleReading<=last2MiddleReading<=last3MiddleReading || last3MiddleReading<=last2MiddleReading<=last1MiddleReading){
            filteredMiddle=last2MiddleReading;
        }
        else if (last2MiddleReading<=last1MiddleReading<=last3MiddleReading || last3MiddleReading<=last1MiddleReading<=last2MiddleReading){
            filteredMiddle=last1MiddleReading;
        }
        else {
            filteredMiddle=last3MiddleReading;
        }
        /*
        Serial.print("Left ");
        lastLeftReading=left.getReading();
        Serial.print(lastLeftReading);
        Serial.print(" Right ");
        lastRightReading=right.getReading();
        Serial.print(lastRightReading);
        Serial.print(" Middle");
        lastMiddleReading=middle.getReading();
        Serial.print(lastMiddleReading);
        */
       delay(40);
}
float GetDistWhenLeftWallChange(){
    return distanceWhenLeftWallChange;
}

float GetDistWhenRightWallChange(){
    return distanceWhenRightWallChange;
}

int getFilterLeft(){
   return filteredLeft;
}
int getFilterRight(){
   return filteredRight;
}
int getFilterMiddle(){
   return filteredMiddle;
}