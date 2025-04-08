#include <Arduino.h>
#include <sensor.h>


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