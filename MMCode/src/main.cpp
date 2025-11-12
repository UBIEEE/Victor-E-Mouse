/*
#include <Arduino.h>
#include <sensor.h>


Sensor left(11, 12);
Sensor right(9, 10);

// Sensor right(11, 12);
// Sensor left(9, 10);
<<<<<<< HEAD
Sensor middle(6, 7);

void sensorSetup()
{
    //Senor Code 
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

<<<<<<< HEAD
void sensorLoop()
=======
void loop()
>>>>>>> d5673a26f331b5fc9fa8bf3dbb29815abde60134
{
    
    //Sensor Code 
    Serial.print("Left ");
    left.getReading();
    Serial.print("Middle ");
    middle.getReading();
    Serial.print("Right ");
    right.getReading();
    Serial.print("\n");

}// test for conor
*/