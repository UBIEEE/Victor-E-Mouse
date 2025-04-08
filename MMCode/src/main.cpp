#include <Arduino.h>
#include <sensor.h>

/*
created by Rui Santos,
Complete Guide for Ultrasonic Sensor HC-SR04*
  Ultrasonic sensor Pins:
      VCC: +5VDC
      Trig : Trigger (INPUT) - Pin11
      Echo: Echo (OUTPUT) - Pin 12
      GND: GND
*/

//Test to push to GitHub - Haley 
// another comment from Haley 

//Motor Shield Code

// Rotary Encoder Inputs




Sensor left(11, 12);
Sensor right(9, 10);

// Sensor right(11, 12);
// Sensor left(9, 10);
Sensor middle(7, 6);

void setup()
{
    // Serial Port begin
    Serial.begin(9600);
    // Define inputs and outputs
    pinMode(right.getTrig(), OUTPUT);
    pinMode(right.getEcho(), INPUT);
    pinMode(left.getTrig(), OUTPUT);
    pinMode(left.getEcho(), INPUT);
    pinMode(middle.getTrig(), OUTPUT);
    pinMode(middle.getEcho(), INPUT);
}

void loop()
{
    /* If reading distance > threshold:
            timer for amount of time
            stop
            turn
            drive forward */

    Serial.print("Left ");
    left.getReading();
    Serial.print("Middle ");
    middle.getReading();
    Serial.print("Right ");
    right.getReading();
    Serial.print("\n");

}// test for conor