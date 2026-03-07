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
float leftSpeed=.2;
float rightSpeed=.2;

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

void sensorLoop()
{
    // Sensor Code
    Serial.print("Left ");
    left.getReading();
    Serial.print(" Right ");
    right.getReading();
    Serial.print(" Middle");
    middle.getReading();
    Serial.print("\n");
}

void loop()
{
      Serial.print("Button: ");
    Serial.print(bigButton.isPressed());
    Serial.println();
    Serial.print(" Flag: ");
    Serial.print(FLAG);
    Serial.println();
    // Use the button to control the drivetrain for demo
    if (bigButton.isPressed() && FLAG==IDLE)
    {
        /*while(driveGetLeftEncoderDistance()<1000 && driveGetRightEncoderDistance()<1000){
        float leftSpeed = PIDHELPLEFT(1);
        float rightSpeed = PIDHELPRIGHT(1);
        Serial.print("left speed");
        Serial.println(leftSpeed);
        Serial.println();
        Serial.print("right speed");
        Serial.print(rightSpeed);
        Serial.println();
        driveSetRawSpeeds(leftSpeed, rightSpeed);
         static int count = 0;
    if ((++count * 10) % 250 == 0)
    { // Print every 250ms
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
        */
        FLAG = FINDING;
    }
    else if (FLAG == FINDING)
    {
    leftSpeed += PIDHELPLEFT(70);
    //leftSpeed=((leftSpeed/255)/1000)*(300);
        rightSpeed += PIDHELPRIGHT(70);
        //rightSpeed=((rightSpeed/255)1000)*(300);
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
        Serial.println();;
        // put initial path finding here and have it stop where it started and set Flag to 2 at the end
    }
    else if (bigButton.isPressed() && FLAG == FINDING)
    {
        driveStop();
        FLAG = EXECUTE;
    }
    else if (FLAG == EXECUTE)
    {
        // have it run to the middle of the maze and set flag to 0 at the end
        FLAG = IDLE;
    }
/*    static int count = 0;
    if ((++count * 10) % 250 == 0)
    { // Print every 250ms
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
    */
    sensorLoop();
    driveLoop();
    delay(10);
}