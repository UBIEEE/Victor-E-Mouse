#include <sensor.h>
#include <Arduino.h>

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