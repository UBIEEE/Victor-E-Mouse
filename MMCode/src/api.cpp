#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <sensor.h>
#include <api.hpp>

void turnRight()
{
    straighten();
    forwardBeforeTurn();
    right90();
    forwardAfterTurn();
}

void turnLeft()
{
    straighten();
    forwardBeforeTurn();
    left90();
    forwardAfterTurn();
}

void moveForward()
{
    bool complete = false;
    while (!complete)
    {
        straighten();
        float prevLeftDist=driveGetLeftEncoderDistance();
        float prevRightDist=driveGetRightEncoderDistance();
        float targetturnleft = 10;
        float targetturnright = 10; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            leftSpeed += PIDHELPLEFT(15);
            leftSpeed+=keepCenter();
            rightSpeed-=keepCenter();
            rightSpeed += PIDHELPRIGHT(15);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        complete = true;
        
    }
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
    while (!complete)
    {
        straighten();
        float prevLeftDist=driveGetLeftEncoderDistance();
        float prevRightDist=driveGetRightEncoderDistance();
        float targetturnleft = 1.2875;
        float targetturnright = -1.2875; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            leftSpeed += PIDHELPLEFT(15);
            leftSpeed+=keepCenter();
            rightSpeed-=keepCenter();
            rightSpeed += PIDHELPRIGHT(15);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        complete = true;
        
    }
}

void left90()
{
    bool complete = false;
    while (!complete)
    {
        straighten();
        float prevLeftDist=driveGetLeftEncoderDistance();
        float prevRightDist=driveGetRightEncoderDistance();
        float targetturnleft = -1.2875;
        float targetturnright = 1.2875; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            leftSpeed += PIDHELPLEFT(15);
            leftSpeed+=keepCenter();
            rightSpeed-=keepCenter();
            rightSpeed += PIDHELPRIGHT(15);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        complete = true;
        
    }
}

void forwardBeforeTurn()
{
    bool complete = false;
    while (!complete)
    {
        straighten();
        float prevLeftDist=driveGetLeftEncoderDistance();
        float prevRightDist=driveGetRightEncoderDistance();
        float targetturnleft = 10;
        float targetturnright = 10; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            leftSpeed += PIDHELPLEFT(15);
            leftSpeed+=keepCenter();
            rightSpeed-=keepCenter();
            rightSpeed += PIDHELPRIGHT(15);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        complete = true;
        
    }
}

void forwardAfterTurn()
{
    bool complete = false;
    while (!complete)
    {
        straighten();
        float prevLeftDist=driveGetLeftEncoderDistance();
        float prevRightDist=driveGetRightEncoderDistance();
        float targetturnleft = 10;
        float targetturnright = 10; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            leftSpeed += PIDHELPLEFT(15);
            leftSpeed+=keepCenter();
            rightSpeed-=keepCenter();
            rightSpeed += PIDHELPRIGHT(15);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        complete = true;
        
    }
}

void backward()
{
    bool complete = false;
    while (!complete)
    {
        straighten();
        float prevLeftDist=driveGetLeftEncoderDistance();
        float prevRightDist=driveGetRightEncoderDistance();
        float targetturnleft = 10;
        float targetturnright = 10; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            leftSpeed += PIDHELPLEFT(15);
            leftSpeed+=keepCenter();
            rightSpeed-=keepCenter();
            rightSpeed += PIDHELPRIGHT(15);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        float rightError = driveGetRightEncoderDistance() - targetturnright;
        complete = true;
        
    }
}

void forwardToCenter()
{
    bool complete = false;
    while (!complete)
    {
        straighten();
        float prevLeftDist=driveGetLeftEncoderDistance();
        float prevRightDist=driveGetRightEncoderDistance();
        float targetturnleft = 10;
        float targetturnright = 10; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            leftSpeed += PIDHELPLEFT(15);
            leftSpeed+=keepCenter();
            rightSpeed-=keepCenter();
            rightSpeed += PIDHELPRIGHT(15);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        float rightError = driveGetRightEncoderDistance() - targetturnright;
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