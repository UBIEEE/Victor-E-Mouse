#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <floodfill.hpp>
#include <api.hpp>

static const int kButtonPin = D10;
static const int kfunnyButtonPin=A5;
static Button smallButton;
static Button bigButton;
// Stuff for floodfill
// Equivalent of first half of mms main code
// static int man[16][16];
// static int vert[17][16];
// static int hori[16][17];
// struct Position *position = new Position;

// Flag values
const int IDLE = 0;
const int FINDING = 1;
const int IDLEWITHPATH = 2;
const int EXECUTE = 3;
int FLAG = IDLE;
float leftSpeed=.4;
float rightSpeed=.4;


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

void setup()
{
    Serial.begin(9600);
    sensorSetup();
    driveSetup();
    smallButton.setupDefaultLow(kButtonPin, true);
    bigButton.setupDefaultHigh(kfunnyButtonPin,true);
    sensorSetup();
}


void loop()
{   
   static int count = 0;
    if ((++count * 10) % 250 == 0){
        Serial.print("\n");
        Serial.print("Left Distance: ");
        Serial.print(driveGetLeftEncoderDistance());
        Serial.print(" Right Distance: ");
        Serial.print(driveGetRightEncoderDistance());
        Serial.print(" Left Velocity: ");
        Serial.print(driveGetLeftEncoderVelocity());
        Serial.print(" Right Velocity: ");
        Serial.print(driveGetRightEncoderVelocity());
        Serial.println();
        Serial.print("Button: ");
        Serial.print(bigButton.isPressed());
        Serial.println();
        Serial.print(" Flag: ");
        Serial.print(FLAG);
        Serial.println();
    }
    // Use the button to control the drivetrain for demo
    if (bigButton.isPressed() && FLAG==IDLE)
    {
        FLAG = FINDING;
    }
    if (FLAG == FINDING)
    {
        while(driveGetLeftEncoderDistance()<100 && driveGetRightEncoderDistance()<100){
            leftSpeed += PIDHELPLEFT(15);
            rightSpeed += PIDHELPRIGHT(15);
            leftSpeed+=keepCenter();
            rightSpeed-=keepCenter();
            Serial.print("left speed");
            Serial.println(leftSpeed);
            Serial.println();
            Serial.print("right speed");
            Serial.print(rightSpeed);
            Serial.println();
            driveSetRawSpeeds(leftSpeed, rightSpeed);
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
        FLAG=IDLEWITHPATH;
        // put initial path finding here and have it stop where it started and set Flag to 2 at the end
    }
    if ( FLAG == IDLEWITHPATH)
    {
        driveStop();
        FLAG = EXECUTE;
    }
    if (FLAG == EXECUTE)
    {
        // have it run to the middle of the maze and set flag to 0 at the end
    }
    sensorLoop();
    driveLoop();
    delay(10);
}
