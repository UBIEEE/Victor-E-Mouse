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
float ckp=.000018;
float cki=.00000;
float ckd=0.00000000;

long lastLeftReading;
long lastRightReading;
long lastMiddleReading;
float distanceWhenLeftWallChange;
float distanceWhenRightWallChange;

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
    Serial.print("in ");
    Serial.print(inches);
    Serial.print(" cm ");
    Serial.print(cm);
    Serial.println();
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
    static int count = 0;
    if ((++count * 10) % 250 == 0){
        if(lastLeftReading!=0 && left.getReading()-lastLeftReading>=6){
            distanceWhenLeftWallChange=driveGetLeftEncoderDistance();
        }
        if(lastRightReading!=0 && right.getReading()-lastRightReading>=6){
            distanceWhenRightWallChange=driveGetRightEncoderDistance();
        }
        Serial.print("Left ");
        lastLeftReading=left.getReading();
        Serial.print(lastLeftReading);
        Serial.print(" Right ");
        lastRightReading=right.getReading();
        Serial.print(lastRightReading);
        Serial.print(" Middle");
        lastMiddleReading=middle.getReading();
        Serial.print(lastMiddleReading);
    }
}