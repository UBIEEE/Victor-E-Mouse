#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <floodfill.hpp>
#include <api.hpp>

int hori[16][17];
int vert[17][16];
int man[16][16];
char *goal;
struct Position *position;



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
const int FORCEIDLE=0;


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

    float leftspeed=0.00000;
    float rightspeed=0.00000;
/*
    void loop()
{   
    
    driveLoop();
    sensorLoop();
    if(smallButton.isPressed() && FLAG==0){
        delay(500);
        FLAG=1;
    }
    if (FLAG==1){
        firstForward();       
        moveForward();
        moveForward();
        moveForward();
        forwardBeforeTurn();
        right90();
        FLAG=2;
    }
    else {
        driveStop();
    }

    driveLoop();
    sensorLoop();
    //leftspeed+=PIDHELPLEFT(3);
    //rightspeed+=PIDHELPRIGHT(3);
    //driveSetRawSpeeds(leftspeed,rightspeed);
    static int count=0;
    if(count++ % 50 == 0){
        Serial.print("left");
        //Serial.print(leftspeed);
        Serial.println();
        Serial.print("right");
        //Serial.print(rightspeed);
        Serial.println();
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
        Serial.print("Left ");
        int leftsens=left.getReading();
        Serial.print(leftsens);
        Serial.print(" Right ");
        int rightsens=right.getReading();
        Serial.print(rightsens);
        Serial.print(" Middle");
        int middlesens=middle.getReading();
        Serial.print(middlesens);
    }
        */




    /*static float leftSpeed=.24;
    static float rightSpeed=.24;
    driveLoop();
    sensorLoop();
    leftSpeed +=PIDHELPLEFT(20);
    static int count=0;
    if(count++ % 2500 == 0){
    Serial.print("left");
    Serial.print(leftSpeed);
    Serial.println();
    Serial.print("right");
    Serial.print(rightSpeed);
    Serial.println();
    }
    rightSpeed +=PIDHELPRIGHT(20);
    driveSetRawSpeeds(leftSpeed,rightSpeed);
    */
   /*static int count = 0;
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
    if (smallButton.isPressed() && FLAG==IDLE)
    {
        FLAG=FINDING;
        driveLoop();
        sensorLoop();
    }
    if (FLAG == FINDING){
        driveLoop();
        sensorLoop();
        left90();

    }
        // put initial path finding here and have it stop where it started and set Flag to 2 at the end
    if ( FLAG == IDLEWITHPATH)
    {
        driveLoop();
        sensorLoop();
        FLAG = EXECUTE;
    }
    if (FLAG == EXECUTE)    
    {
        driveLoop();
        sensorLoop();
        FLAG=IDLE;    // have it run to the middle of the maze and set flag to 0 at the end
    }
    if(bigButton.isPressed()){
        driveLoop();
        sensorLoop();
        driveStop();
    }
    sensorLoop();
    driveLoop();
    delay(10);
    */
//}

//main loop not for testing
void loop(){
    driveLoop();
    sensorLoop();
    if(smallButton.isPressed() && FLAG==IDLE){
        FLAG=FINDING;
    }
    if(FLAG==FINDING){
        floodfill(hori,vert,man, goal);
        FLAG=IDLEWITHPATH;
    }
    if(smallButton.isPressed() && FLAG==IDLEWITHPATH){
        FLAG=EXECUTE;
    }
    if(FLAG==EXECUTE){
        move(position,hori,vert,man,goal);
        FLAG==IDLE;
    }
    if(bigButton.isPressed()){
        driveStop();
        FLAG=FORCEIDLE;
    }
}