#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <sensor.h>
#include <api.hpp>
void turnRight() {
    forwardBeforeTurn();
    right90();
    forwardAfterTurn();
    straighten();

}

void turnRight() {
    forwardBeforeTurn();
    left90();
    forwardAfterTurn();
    straighten();
}

void moveForward() {
    bool complete=false;
    driveResetEncoderDistance();
    while(!complete){
        count=count+1;
        float targetturnleft; //adjust
        float targetturnright;
        while(driveGetLeftEncoderDistance()<targetturnleft && driveGetRightEncoderDistance()<targetturnright){
            float leftSpeed=1*leftAdjustment;
            float rightSpeed=1*rightAdjustment;
            driveSetRawSpeeds(leftSpeed,rightSpeed);
        }
        driveStop();
        float leftError=driveGetLeftEncoderDistance()-targetturnleft;
        float rightError=driveGetRightEncoderDistance()-targetturnright;
        leftTotalError=(leftTotalError+leftError)/count;
        rightTotalError=(rightTotalError+rightError)/count;
        leftAdjustment=constant*leftTotalError;
        rightAdjustment=constant*rightTotalError;
        complete=true;
    }
    straighten();
}

void straighten(){
    bool complete=false;
    while(!complete){
        if(left.getReading()<=1){ // adjust
            right90();
            backward();
            forwardToCenter();
            left90();
        }
        else if(right.getReading() <= 1){ //adjust
            left90();
            backward();
            forwardToCenter();
            right90();
        }
        else if (middle.getReading()<=1){ //adjust
            left90();
            left90();
            backward();
            forwardToCenter();
        }
        complete=true;
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
void right90(){
bool complete=false;
    driveResetEncoderDistance();
    while(!complete){
        count=count+1;
        float targetturnleft; //adjust
        float targetturnright;
        while(driveGetLeftEncoderDistance()<targetturnleft && driveGetRightEncoderDistance()<targetturnright){
            float leftSpeed=1*leftAdjustment;
            float rightSpeed=-1*rightAdjustment;
            driveSetRawSpeeds(leftSpeed,rightSpeed);
        }
        driveStop();
        float leftError=driveGetLeftEncoderDistance()-targetturnleft;
        float rightError=driveGetRightEncoderDistance()-targetturnright;
        leftTotalError=(leftTotalError+leftError)/count;
        rightTotalError=(rightTotalError+rightError)/count;
        leftAdjustment=constant*leftTotalError;
        rightAdjustment=constant*rightTotalError;
        complete=true;
    }

}

void left90(){
    bool complete=false;
    driveResetEncoderDistance();
    while(!complete){
        count=count+1;
        float targetturnleft; //adjust
        float targetturnright;
        while(driveGetLeftEncoderDistance()<targetturnleft && driveGetRightEncoderDistance()<targetturnright){
            float leftSpeed=-1*leftAdjustment;
            float rightSpeed=1*rightAdjustment;
            driveSetRawSpeeds(leftSpeed,rightSpeed);
        }
        driveStop();
        float leftError=driveGetLeftEncoderDistance()-targetturnleft;
        float rightError=driveGetRightEncoderDistance()-targetturnright;
        leftTotalError=(leftTotalError+leftError)/count;
        rightTotalError=(rightTotalError+rightError)/count;
        leftAdjustment=constant*leftTotalError;
        rightAdjustment=constant*rightTotalError;
        complete=true;
    }

}

void forwardBeforeTurn(){
    bool complete=false;
    driveResetEncoderDistance();
    while(!complete){
        count=count+1;
        float targetturnleft; //adjust
        float targetturnright;
        while(driveGetLeftEncoderDistance()<targetturnleft && driveGetRightEncoderDistance()<targetturnright){
            float leftSpeed=1*leftAdjustment;
            float rightSpeed=1*rightAdjustment;
            driveSetRawSpeeds(leftSpeed,rightSpeed);
        }
        driveStop();
        float leftError=driveGetLeftEncoderDistance()-targetturnleft;
        float rightError=driveGetRightEncoderDistance()-targetturnright;
        leftTotalError=(leftTotalError+leftError)/count;
        rightTotalError=(rightTotalError+rightError)/count;
        leftAdjustment=constant*leftTotalError;
        rightAdjustment=constant*rightTotalError;
        complete=true;
    }
}

void forwardAfterTurn(){
    bool complete=false;
    driveResetEncoderDistance();
    while(!complete){
        count=count+1;
        float targetturnleft; //adjust
        float targetturnright;
        while(driveGetLeftEncoderDistance()<targetturnleft && driveGetRightEncoderDistance()<targetturnright){
            float leftSpeed=1*leftAdjustment;
            float rightSpeed=1*rightAdjustment;
            driveSetRawSpeeds(leftSpeed,rightSpeed);
        }
        driveStop();
        float leftError=driveGetLeftEncoderDistance()-targetturnleft;
        float rightError=driveGetRightEncoderDistance()-targetturnright;
        leftTotalError=(leftTotalError+leftError)/count;
        rightTotalError=(rightTotalError+rightError)/count;
        leftAdjustment=constant*leftTotalError;
        rightAdjustment=constant*rightTotalError;
        complete=true;
    }
}

void backward(){
    bool complete=false;
    driveResetEncoderDistance();
    while(!complete){
        count=count+1;
        float targetturnleft; //adjust
        float targetturnright;
        while(driveGetLeftEncoderDistance()<targetturnleft && driveGetRightEncoderDistance()<targetturnright){
            float leftSpeed=1*leftAdjustment;
            float rightSpeed=1*rightAdjustment;
            driveSetRawSpeeds(leftSpeed,rightSpeed);
        }
        driveStop();
        float leftError=driveGetLeftEncoderDistance()-targetturnleft;
        float rightError=driveGetRightEncoderDistance()-targetturnright;
        leftTotalError=(leftTotalError+leftError)/count;
        rightTotalError=(rightTotalError+rightError)/count;
        leftAdjustment=constant*leftTotalError;
        rightAdjustment=constant*rightTotalError;
        complete=true;
    }
}

void forwardToCenter(){
    bool complete=false;
    driveResetEncoderDistance();
    while(!complete){
        count=count+1;
        float targetturnleft; //adjust
        float targetturnright;
        while(driveGetLeftEncoderDistance()<targetturnleft && driveGetRightEncoderDistance()<targetturnright){
            float leftSpeed=1*leftAdjustment;
            float rightSpeed=1*rightAdjustment;
            driveSetRawSpeeds(leftSpeed,rightSpeed);
        }
        driveStop();
        float leftError=driveGetLeftEncoderDistance()-targetturnleft;
        float rightError=driveGetRightEncoderDistance()-targetturnright;
        leftTotalError=(leftTotalError+leftError)/count;
        rightTotalError=(rightTotalError+rightError)/count;
        leftAdjustment=constant*leftTotalError;
        rightAdjustment=constant*rightTotalError;
        complete=true;
    }
}

void goalTurnAround(){
    if(left.getReading()<1){ //adjust
        moveForward();
        left90();
        left90();
        backward();
        forwardToCenter();
        left90();
        backward();
        forwardToCenter();
        right90();
        moveForward();
    }
    else if(right.getReading()<1){ //adjust
        moveForward();
        right90();
        right90();
        backward();
        forwardToCenter();
        right90();
        backward();
        forwardToCenter();
        left90();
        moveForward();
    }
}