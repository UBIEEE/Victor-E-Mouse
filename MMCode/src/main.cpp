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
#define inputCLK 4
#define inputDT 5 

// LED Outputs
#define ledCW 8
//#define ledCCW 9

int counter = 0;
int currentStateCLK;
int previousStateCLK;

String encdir ="";

void setup() {
  // Set encoder pins as inputs
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);

  // Set LED pins as outputs
  pinMode (ledCW,OUTPUT);
  //pinMode (ledCCW,OUTPUT);

  // Setup Serial Monitor
  Serial.begin (9600);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

}

void loop() {
 // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occurred
  if (currentStateCLK != previousStateCLK){

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      counter--;
      encdir ="CCW";
      digitalWrite(ledCW, LOW);
      //digitalWrite(ledCCW, HIGH);

    } else {
      // Encoder is rotating clockwise
      counter++;
      encdir ="CW";
      digitalWrite(ledCW, HIGH);
      //digitalWrite(ledCCW, LOW);

    }
    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" -- Value: ");
    Serial.println(counter);
  }
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}

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