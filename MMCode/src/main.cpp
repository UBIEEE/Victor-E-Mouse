#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <main.hpp>
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
int FLAG;


Sensor left(11, 12);
Sensor middle(38,67); //change when we have the third sensor later
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
void turnRight(){
    driveSetRawSpeeds(1,0); // might have to make it go straight first depending on the sensors
    delay(10); // ;( (Imma tweak)
    DIRECTION=(DIRECTION+1)%4;
    driveStop();
    straighten();
    driveResetEncoderDistance();

}
void turnLeft(){
    driveSetRawSpeeds(0,1);
    delay(10); // ;( (Imma tweak)
    DIRECTION=(DIRECTION-1)%4;
    driveStop();
    straighten();
    driveResetEncoderDistance();

}

void moveForward(){
    driveSetRawSpeeds(1,1);
    delay(10); // ill tweak and probably use encoders
    driveStop();
    if(DIRECTION==LEFT){
        X=X-1;
    }
    else if(DIRECTION==RIGHT){
        X=X+1;
    }
    else if(DIRECTION==UP){
        Y=Y+1;
    }
    else if(DIRECTION==DOWN){
        Y=Y-1;
    }
    straighten();
    driveResetEncoderDistance();
}
Sensor left(11, 12);
Sensor middle(38,67);
Sensor right(14, 15);
void straighten(){
    if(left.getReading()<=1){
        driveSetRawSpeeds(.1,0);
        driveStop();
    }
    else if(right.getReading()<=1){
        driveSetRawSpeeds(0,.1);
        driveStop();
    }
    else{

    }
}
bool leftWall(){
    if(left.getReading()<=10){
        return true;
    }
    else {
        return false;
    }
}
bool rightWall(){
    if(right.getReading()<=10){
        return true;
    }
    else {
        return false;
    }
}
bool frontWall(){
    if(middle.getReading()<=10){
        return true;
    }
    else {
        return false;
    }
}

