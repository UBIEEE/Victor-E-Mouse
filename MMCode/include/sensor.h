#pragma once

class Sensor
{
public:
    int trigPin;
    int echoPin;
    long duration;
    long cm;
    long inches;

    Sensor(int tPin, int ePin);

    int getTrig();

    int getEcho();

    long getDuration();

    long getReading();
};
    extern Sensor left;
    extern Sensor middle; //change when we have the third sensor later
    extern Sensor right;