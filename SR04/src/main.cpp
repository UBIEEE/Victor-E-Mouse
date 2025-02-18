#include <Arduino.h>

/*
created by Rui Santos,
Complete Guide for Ultrasonic Sensor HC-SR04*
  Ultrasonic sensor Pins:
      VCC: +5VDC
      Trig : Trigger (INPUT) - Pin11
      Echo: Echo (OUTPUT) - Pin 12
      GND: GND
*/

class Sensor
{

public:
  int trigPin;
  int echoPin;
  long duration;
  long cm;
  long inches;

  Sensor(int tPin, int ePin)
  {
    trigPin = tPin;
    echoPin = ePin;
  }

  int getTrig()
  {
    return trigPin;
  }

  int getEcho()
  {
    return echoPin;
  }

  long getDuration()
  {
    return duration;
  }

  void getReading()
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
    delay(250);
  }
};

Sensor right(11, 12);
Sensor left(9, 10);
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
  Serial.print("Right ");
  right.getReading();
  Serial.print("Left ");
  left.getReading();
  Serial.print("Middle ");
  middle.getReading();
  Serial.print("\n");
}