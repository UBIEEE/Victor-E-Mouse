#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <api.hpp>
static const int kButtonPin = 10;
static Button button;

static CELL GRID[16][16];
static int VERTWALL[17][16];
static int HORIZWALL[16][17];
int FLAG;

Sensor left(11, 12);
Sensor middle(38,67); //change when we have the third sensor later
Sensor right(14, 15);

void sensorSetup()
{
    // Sensor Code 
    // Serial Port begin
    // Define inputs and outputs
    pinMode(right.getTrig(), OUTPUT);
    pinMode(right.getEcho(), INPUT);
    pinMode(left.getTrig(), OUTPUT);
    pinMode(left.getEcho(), INPUT);
}

void setup() {
  Serial.begin(9600);
  sensorSetup();
  driveSetup();
  button.setupDefaultLow(kButtonPin, true);
  sensorSetup();
}

void sensorLoop(){
    // Sensor Code 
    Serial.println("Left ");
    left.getReading();
    Serial.print("Right ");
    right.getReading();
    Serial.print("\n");
}

void loop() {
    // Use the button to control the drivetrain for demo
    if(button.isPressed() && FLAG==0){
       FLAG==1;
    }
    else if(FLAG==1){
        //put initial path finding here and have it stop where it started and set Flag to 2 at the end
        FLAG==2;
    }
    else if(button.isPressed() && FLAG==2){
        FLAG==3;
    }
    else if(FLAG==3){
        //have it run to the middle of the maze and set flag to 0 at the end
        FLAG==0;
    }

  static int count = 0;
  if ((++count * 10) % 250 == 0) { // Print every 250ms
    Serial.print("Left Distance: ");
    Serial.print(driveGetLeftEncoderDistance());
    Serial.print(" Right Distance: ");
    Serial.print(driveGetRightEncoderDistance());
    Serial.print(" Left Velocity: ");
    Serial.print(driveGetLeftEncoderVelocity());
    Serial.print(" Right Velocity: ");
    Serial.print(driveGetRightEncoderVelocity());
    Serial.println();
  }
  sensorLoop();
  driveLoop();
  delay(10);
}