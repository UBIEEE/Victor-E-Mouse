#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <floodfill.hpp>
#include <api.hpp>
static const int kButtonPin = 10;
static Button button;

// Stuff for floodfill
static int man[16][16];
static int vert[17][16];
static int hori[16][17];
struct Position *position = new Position;
int FLAG;
int IDLE = 0;
int FINDING = 1;
int IDLEWITHPATH = 2;
int EXECUTE = 3;

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
    if(button.isPressed() && FLAG == IDLE){
       FLAG == FINDING;
    }
    else if(FLAG == FINDING){
        //put initial path finding here and have it stop where it started and set Flag to 2 at the end
        FLAG == IDLEWITHPATH;
    }
    else if(button.isPressed() && FLAG == IDLEWITHPATH){
        FLAG == EXECUTE;
    }
    else if(FLAG == EXECUTE){
        //have it run to the middle of the maze and set flag to 0 at the end
        FLAG == IDLE;
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