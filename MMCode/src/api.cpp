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
    bool complete=false;
    int funny;
    int funnyturnleft; //adjust
    int funnyturnright;
    while(!complete){
        while(driveGetLeftEncoderDistance()<funny && driveGetRightEncoderDistance()<funny){
            driveSetRawSpeeds(1,1);//multiply by pid proportions
        }
        driveStop();
        while(driveGetLeftEncoderDistance()<funnyturnleft && driveGetRightEncoderDistance()<funnyturnright){
            driveSetRawSpeeds(-1,1);//again multiply
        }
        driveStop();
    }
    driveResetEncoderDistance();
    DIRECTION = (DIRECTION - 1) % 4;
    delay(10);
    straighten();

}
void turnLeft() {
    bool complete=false;
    int funny;
    int funnyturnleft; //adjust
    int funnyturnright;
    while(!complete){
        while(driveGetLeftEncoderDistance()<funny && driveGetRightEncoderDistance()<funny){
            driveSetRawSpeeds(1,1);//multiply by pid proportions
        }
        driveStop();
        while(driveGetLeftEncoderDistance()<funnyturnleft && driveGetRightEncoderDistance()<funnyturnright){
            driveSetRawSpeeds(-1,1);//again multiply
        }
        driveStop();
    }
    driveResetEncoderDistance();
    DIRECTION = (DIRECTION - 1) % 4;
    delay(10);
    straighten();
}

void moveForward() {
    bool complete=false;
    int funny;
    while(!complete){
        while(driveGetLeftEncoderDistance()<funny && driveGetRightEncoderDistance()<funny){
            driveSetRawSpeeds(1,1);//multiply by pid proportions
        }
        driveStop();
        driveResetEncoderDistance();
        straighten();
    }
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
    delay(10); //ill change
}

void straighten() {
    bool complete=false;
    int funny;
    int funnyturnleft; //adjust
    int funnyturnright;
    while(!complete){
        if(left.getReading()<=1){
            //turn right
            //back up a while to striaghten
            //go back out to center
            //turn back left
        }
        else if(right.getReading() <= 1){
            driveSetRawSpeeds(0, .1);
            driveStop();
        }
        else if (middle.getReading()<=1){

    }
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