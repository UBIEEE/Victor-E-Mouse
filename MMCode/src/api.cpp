#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <sensor.h>
#include <api.hpp>
float count = 0;
float leftAdjustment = 1;
float rightAdjustment = 1;
float leftTotalError = 0;
float rightTotalError = 0;
static const float constant = .98;
float diffTotalError = 0;

/*float lprevEr=0;
float lposEr=0;
float ltotalEr=0;
float rprevEr=0;
float rposEr=0;
float rtotalEr=0;
float llast;
float rlast;
float kp=.03;
float ki=.00007;
float kd=0.015;
*/

void turnRight()
{
    forwardBeforeTurn();
    right90();
    forwardAfterTurn();
    straighten();
}

void turnLeft()
{
    forwardBeforeTurn();
    left90();
    forwardAfterTurn();
    straighten();
}

void moveForward()
{
    bool complete = false;
    driveResetEncoderDistance(); // resets distance
    while (!complete)
    {
        count = count + 1; // adds a count of distance travel functions called
        float targetturnleft = 10;
        float targetturnright = 10; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance() < targetturnleft - rightAdjustment && driveGetRightEncoderDistance() < targetturnright - leftAdjustment)
        {
            leftSpeed =+ PIDHELPLEFT(1);
            rightSpeed =+ PIDHELPRIGHT(1);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        leftTotalError = (leftTotalError + leftError); // add difference and divide
        rightTotalError = (rightTotalError + rightError);
        diffTotalError =diffTotalError+(leftTotalError-rightTotalError);
        leftAdjustment = -(diffTotalError/count) * constant;
        rightAdjustment = (diffTotalError/count) * constant;
        complete = true;
        
    }
    straighten();
}

void straighten()
{
    bool complete = false;
    while (!complete)
    {
        if (left.getReading() <= 1)
        { // adjust
            right90();
            backward();
            forwardToCenter();
            left90();
        }
        else if (right.getReading() <= 1)
        { // adjust
            left90();
            backward();
            forwardToCenter();
            right90();
        }
        else if (middle.getReading() <= 1)
        { // adjust
            left90();
            left90();
            backward();
            forwardToCenter();
        }
        complete = true;
    }
}

bool leftWall()
{
    if (left.getReading() <= 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool rightWall()
{
    if (right.getReading() <= 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool frontWall()
{
    if (middle.getReading() <= 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void right90()
{
    bool complete = false;
    driveResetEncoderDistance();
    while (!complete)
    {
        count = count + 1;
        float targetturnleft = 1.2875; // adjust
        float targetturnright = -1.2875;
        while (driveGetLeftEncoderDistance() < targetturnleft * leftAdjustment && driveGetRightEncoderDistance() < -(targetturnright * rightAdjustment))
        {
            float leftSpeed = 1;
            float rightSpeed = -1;
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft;
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        leftTotalError = (leftTotalError + leftError); // add difference and divide
        rightTotalError = (rightTotalError + rightError);
        leftAdjustment = constant * (leftTotalError / count);
        rightAdjustment = constant * (rightTotalError / count);
        complete = true;
    }
}

void left90()
{
    bool complete = false;
    driveResetEncoderDistance();
    while (!complete)
    {
        count = count + 1;
        float targetturnleft = -1.2875; // adjust
        float targetturnright = 1.2875;
        while (driveGetLeftEncoderDistance() < -(targetturnleft * leftAdjustment) && driveGetRightEncoderDistance() < targetturnright * rightAdjustment)
        {
            float leftSpeed = -1;
            float rightSpeed = 1;
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft;
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        leftTotalError = (leftTotalError + leftError); // add difference and divide
        rightTotalError = (rightTotalError + rightError);
        leftAdjustment = constant * (leftTotalError / count);
        rightAdjustment = constant * (rightTotalError / count);
        complete = true;
    }
}

void forwardBeforeTurn()
{
    bool complete = false;
    driveResetEncoderDistance();
    while (!complete)
    {
        count = count + 1;
        float targetturnleft = 0; // adjust
        float targetturnright = 0;
        while (driveGetLeftEncoderDistance() < targetturnleft * leftAdjustment && driveGetRightEncoderDistance() < targetturnright * rightAdjustment)
        {
            float leftSpeed = 1;
            float rightSpeed = 1;
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft;
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        leftTotalError = (leftTotalError + leftError); // add difference and divide
        rightTotalError = (rightTotalError + rightError);
        leftAdjustment = constant * (leftTotalError / count);
        rightAdjustment = constant * (rightTotalError / count);
        complete = true;
    }
}

void forwardAfterTurn()
{
    bool complete = false;
    driveResetEncoderDistance();
    while (!complete)
    {
        count = count + 1;
        float targetturnleft = 0; // adjust
        float targetturnright = 0;
        while (driveGetLeftEncoderDistance() < targetturnleft * leftAdjustment && driveGetRightEncoderDistance() < targetturnright * rightAdjustment)
        {
            float leftSpeed = 1;
            float rightSpeed = 1;
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft;
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        leftTotalError = (leftTotalError + leftError); // add difference and divide
        rightTotalError = (rightTotalError + rightError);
        leftAdjustment = constant * (leftTotalError / count);
        rightAdjustment = constant * (rightTotalError / count);
        complete = true;
    }
}

void backward()
{
    bool complete = false;
    driveResetEncoderDistance();
    while (!complete)
    {
        count = count + 1;
        float targetturnleft = 0; // adjust
        float targetturnright = 0;
        while (driveGetLeftEncoderDistance() < targetturnleft * leftAdjustment && driveGetRightEncoderDistance() < targetturnright * rightAdjustment)
        {
            float leftSpeed = -1;
            float rightSpeed = -1;
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft;
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        leftTotalError = (leftTotalError + leftError); // add difference and divide
        rightTotalError = (rightTotalError + rightError);
        leftAdjustment = constant * (leftTotalError / count);
        rightAdjustment = constant * (rightTotalError / count);
        complete = true;
    }
}

void forwardToCenter()
{
    bool complete = false;
    driveResetEncoderDistance();
    while (!complete)
    {
        count = count + 1;
        float targetturnleft = 0; // adjust
        float targetturnright = 0;
        while (driveGetLeftEncoderDistance() < targetturnleft * leftAdjustment && driveGetRightEncoderDistance() < targetturnright * rightAdjustment)
        {
            float leftSpeed = 1;
            float rightSpeed = 1;
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft;
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        leftTotalError = (leftTotalError + leftError); // add difference and divide
        rightTotalError = (rightTotalError + rightError);
        leftAdjustment = constant * (leftTotalError / count);
        rightAdjustment = constant * (rightTotalError / count);
        complete = true;
    }
}

void goalTurnAround()
{
    if (left.getReading() < 1)
    { // adjust
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
    else if (right.getReading() < 1)
    { // adjust
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
/*
float DistanceAccPIDishThingLeft(float target){
    count=+1;
    float now=millis();
    float setpoint=driveGetLeftEncoderDistance();
    float delta=now-llast;
    lprevEr=lposEr;
    lposEr=target-setpoint;
    float vel=(lposEr-lprevEr);
    ltotalEr=ltotalEr+lposEr;
    llast=now;
    return kp*lposEr+ki*ltotalEr+kd*vel;
}
*/