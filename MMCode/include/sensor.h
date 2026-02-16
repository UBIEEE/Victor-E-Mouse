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
extern Sensor left(11, 12);
extern Sensor middle(38,67); //change when we have the third sensor later
extern Sensor right(14, 15);