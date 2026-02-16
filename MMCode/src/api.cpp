#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <sensor.h>

int DIRECTION;
int X;
int Y;
static int UP = 0;
static int LEFT = 1;
static int DOWN = 2;
static int RIGHT = 3;

void turnRight() {
    driveSetRawSpeeds(1, 0); // might have to make it go straight first depending on the sensors
    delay(10); // ;( (Imma tweak)
    DIRECTION = (DIRECTION + 1) % 4;
    driveStop();
    straighten();
    driveResetEncoderDistance();

}
void turnLeft() {
    driveSetRawSpeeds(0, 1);
    delay(10); // ;( (Imma tweak)
    DIRECTION = (DIRECTION - 1) % 4;
    driveStop();
    straighten();
    driveResetEncoderDistance();
}

void moveForward() {
    driveSetRawSpeeds(1, 1);
    delay(10); // ill tweak and probably use encoders
    driveStop();
    if(DIRECTION == LEFT){
        X = X - 1;
    }
    else if(DIRECTION == RIGHT){
        X = X + 1;
    }
    else if(DIRECTION == UP){
        Y = Y + 1;
    }
    else if(DIRECTION == DOWN){
        Y = Y - 1;
    }
    straighten();
    driveResetEncoderDistance();
}

void straighten() {
    if(left.getReading() <= 1){
        driveSetRawSpeeds(.1, 0);
        driveStop();
    }
    else if(right.getReading() <= 1){
        driveSetRawSpeeds(0, .1);
        driveStop();
    }
}

bool leftWall() {
    if(left.getReading() <= 10){
        return true;
    }
    else {
        return false;
    }
}

bool rightWall() {
    if(right.getReading() <= 10){
        return true;
    }
    else {
        return false;
    }
}

bool frontWall() {
    if(middle.getReading() <= 10){
        return true;
    }
    else {
        return false;
    }
}