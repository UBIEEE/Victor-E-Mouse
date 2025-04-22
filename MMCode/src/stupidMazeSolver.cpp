#include <Arduino.h>
#include <sensor.h>
#include <motorEncoder.h>

// Getting Sensor Data

void loop()
{

    while (true)
    {
        if (right.getReading() < 10 && left.getReading() < 10)
        {
            // move forward
        }
        else if (right.getReading() < 10 && middle.getReading())
        {
            // turn left
        }
        else
        {
            // turn right
        }
    }
}