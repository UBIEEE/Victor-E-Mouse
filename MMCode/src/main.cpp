#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
static const int kButtonPin = 10;
static Button button;
int DIRECTION;
int X;
int Y;
static int UP=0;
static int LEFT=1;
static int DOWN=2;
static int RIGHT =3;
 class CELL {
    public:
    int x;
    int y;
    int value;
};
static CELL GRID[16][16];
static int VERTWALL[17][16];
static int HORIZWALL[16][17];



Sensor left(11, 12);
Sensor middle(38,67); //change when we have the third sensor later

// Sensor right(11, 12);
// Sensor left(9, 10);
Sensor right(14, 15);

void sensorSetup()
{
    //Senor Code 
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
    
    //Sensor Code 
    Serial.println("Left ");
    left.getReading();
    Serial.print("Right ");
    right.getReading();
    Serial.print("\n");

    
}

bool Leftwall(){
    if(left.getReading()>90){
        return false;
    } else {
        return true;
    }
}
bool Rightwall(){
    if(right.getReading()>90){
        return false;
    } else {
        return true;
    }
}
bool Topwall(){
    if(middle.getReading()>90){
        return false;
    } else {
        return true;
    }
}

void loop() {
  // Use the button to control the drivetrain for demo
  if(button.isPressed()){
    if(left.getReading()>30){
        driveSetRawSpeeds(1,1);
    }
  }
  else{
    driveStop();
  }



  static int count = 0;
  if ((++count * 10) % 250 == 0) { // Print every 250ms
    float leftEncoderDistance = driveGetLeftEncoderDistance();
    float rightEncoderDistance = driveGetRightEncoderDistance();
    float leftEncoderVelocity = driveGetLeftEncoderVelocity();
    float rightEncoderVelocity = driveGetRightEncoderVelocity();
    Serial.print("Left Distance: ");
    Serial.print(leftEncoderDistance);
    Serial.print(" Right Distance: ");
    Serial.print(rightEncoderDistance);
    Serial.print(" Left Velocity: ");
    Serial.print(leftEncoderVelocity);
    Serial.print(" Right Velocity: ");
    Serial.print(rightEncoderVelocity);
    Serial.println();

  }
  sensorLoop();
  driveLoop();

  delay(10);
}
