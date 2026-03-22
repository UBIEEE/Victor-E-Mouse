#include <Arduino.h>
#include <sensor.h>
#include <Button.hpp>
#include <Drive.hpp>
#include <sensor.h>
#include <api.hpp>
#include <math.h>

void turnRight()
{
    //straighten();
    forwardBeforeTurn();
    right90();
    forwardAfterTurn();
}

void turnLeft()
{
    //straighten();
    forwardBeforeTurn();
    left90();
    forwardAfterTurn();
}

void moveForward()
{
        driveLoop();
        sensorLoop();
        //straighten();
        float targetturnleft = 15;
        float targetturnright = 15; // values for distance wanted to travel per wheel
        float rightSpeed=0;
        float leftSpeed=0;
        float beganleft=driveGetLeftEncoderDistance();
        float beganright=driveGetLeftEncoderDistance();
        float leftGoal=0;
        float rightGoal=0;
        int count=0;

        while (driveGetLeftEncoderDistance() < beganleft+targetturnleft || driveGetRightEncoderDistance() < beganright+targetturnright)
        {

            driveLoop();
            sensorLoop();
            Serial.println();
            Serial.print("leftgoal");
            Serial.print(leftGoal);
            Serial.print("rightGoal");
            Serial.print(rightGoal);
            leftGoal=trapazoidLeftStraight(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance());
            rightGoal=trapazoidRightStraight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance());
            count+=1;
            float leftadjust=0;
            float rightadjust=0;
            if(count%50==0){
                leftadjust=keepCenter()*leftGoal;
                rightadjust=keepCenter()*rightGoal;
            }
            leftSpeed += PIDHELPLEFT(leftGoal=trapazoidLeftStraight(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance())+leftadjust);
            rightSpeed += PIDHELPRIGHT(rightGoal=trapazoidRightStraight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance())-rightadjust);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        delay(10);
        
        //float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        //float rightError = driveGetRightEncoderDistance() - targetturnright;
        
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
        driveLoop();
        sensorLoop();
        //straighten();
        float targetturnleft = 14.8;
        float targetturnright = -14.8; // values for distance wanted to travel per wheel
        float rightSpeed=0;
        float leftSpeed=0;
        float beganleft=driveGetLeftEncoderDistance();
        float beganright=driveGetLeftEncoderDistance();
        float leftGoal=0;
        float rightGoal=0;

        while (driveGetLeftEncoderDistance() < beganleft+targetturnleft && driveGetRightEncoderDistance() > beganright+targetturnright)
        {
            
            Serial.print("leftgoal");
            Serial.print(leftGoal);
            Serial.print("rightGoal");
            Serial.print(rightGoal);
            driveLoop();
            sensorLoop();
            leftSpeed += PIDHELPLEFT(leftGoal=trapazoidLeft(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance()));
            rightSpeed += PIDHELPRIGHT(rightGoal=trapazoidRight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance()));
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        delay(10);
        
        //float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        //float rightError = driveGetRightEncoderDistance() - targetturnright;
        
}

void left90()
{
        driveLoop();
        sensorLoop();
        //straighten();
        float targetturnleft = -14.8;
        float targetturnright = 14.8; // values for distance wanted to travel per wheel
        float rightSpeed=0;
        float leftSpeed=0;
        float beganleft=driveGetLeftEncoderDistance();
        float beganright=driveGetLeftEncoderDistance();
        float leftGoal=0;
        float rightGoal=0;

        while (driveGetLeftEncoderDistance() > beganleft+targetturnleft && driveGetRightEncoderDistance() < beganright+targetturnright)
        {

            driveLoop();
            sensorLoop();
            leftSpeed += PIDHELPLEFT(leftGoal=trapazoidLeft(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance()));
            rightSpeed += PIDHELPRIGHT(rightGoal=trapazoidRight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance()));
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        delay(10);
        
        //float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        //float rightError = driveGetRightEncoderDistance() - targetturnright;
        
}

void forwardBeforeTurn()
{
        driveLoop();
        sensorLoop();
        //straighten();
        float targetturnleft = 1;
        float targetturnright = 1; // values for distance wanted to travel per wheel
        float rightSpeed=0;
        float leftSpeed=0;
        float beganleft=driveGetLeftEncoderDistance();
        float beganright=driveGetLeftEncoderDistance();
        float leftGoal=0;
        float rightGoal=0;
        int count=0;

        while (driveGetLeftEncoderDistance() < beganleft+targetturnleft || driveGetRightEncoderDistance() < beganright+targetturnright)
        {

            driveLoop();
            sensorLoop();
            Serial.println();
            Serial.print("leftgoal");
            Serial.print(leftGoal);
            Serial.print("rightGoal");
            Serial.print(rightGoal);
            leftGoal=trapazoidLeftStraight(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance());
            rightGoal=trapazoidRightStraight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance());
            count+=1;
            float leftadjust=0;
            float rightadjust=0;
            if(count%50==0){
                leftadjust=keepCenter()*leftGoal;
                rightadjust=keepCenter()*rightGoal;
            }
            leftSpeed += PIDHELPLEFT(leftGoal=trapazoidLeft(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance())+leftadjust);
            rightSpeed += PIDHELPRIGHT(rightGoal=trapazoidRight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance())-rightadjust);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        delay(10);
        
        //float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        //float rightError = driveGetRightEncoderDistance() - targetturnright;
        
}

void forwardAfterTurn()
{
        driveLoop();
        sensorLoop();
        //straighten();
        float targetturnleft = 13;
        float targetturnright = 13; // values for distance wanted to travel per wheel
        float rightSpeed=0;
        float leftSpeed=0;
        float beganleft=driveGetLeftEncoderDistance();
        float beganright=driveGetLeftEncoderDistance();
        float leftGoal=0;
        float rightGoal=0;
        int count=0;

        while (driveGetLeftEncoderDistance() < beganleft+targetturnleft || driveGetRightEncoderDistance() < beganright+targetturnright)
        {

            driveLoop();
            sensorLoop();
            Serial.println();
            Serial.print("leftgoal");
            Serial.print(leftGoal);
            Serial.print("rightGoal");
            Serial.print(rightGoal);
            leftGoal=trapazoidLeftStraight(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance());
            rightGoal=trapazoidRightStraight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance());
            count+=1;
            float leftadjust=0;
            float rightadjust=0;
            if(count%50==0){
                leftadjust=keepCenter()*leftGoal;
                rightadjust=keepCenter()*rightGoal;
            }
            leftSpeed += PIDHELPLEFT(leftGoal=trapazoidLeftStraight(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance())+leftadjust);
            rightSpeed += PIDHELPRIGHT(rightGoal=trapazoidRightStraight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance())-rightadjust);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        delay(10);
        
        //float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        //float rightError = driveGetRightEncoderDistance() - targetturnright;
        
}
void firstForward()
{
        driveLoop();
        sensorLoop();
        //straighten();
        float targetturnleft = 12;
        float targetturnright = 12; // values for distance wanted to travel per wheel
        float rightSpeed=0;
        float leftSpeed=0;
        float beganleft=driveGetLeftEncoderDistance();
        float beganright=driveGetLeftEncoderDistance();
        float leftGoal=0;
        float rightGoal=0;
        int count=0;

        while (driveGetLeftEncoderDistance() < beganleft+targetturnleft || driveGetRightEncoderDistance() < beganright+targetturnright)
        {

            driveLoop();
            sensorLoop();
            Serial.println();
            Serial.print("leftgoal");
            Serial.print(leftGoal);
            Serial.print("rightGoal");
            Serial.print(rightGoal);
            leftGoal=trapazoidLeftStraight(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance());
            rightGoal=trapazoidRightStraight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance());
            count+=1;
            float leftadjust=0;
            float rightadjust=0;
            if(count%50==0){
                leftadjust=keepCenter()*leftGoal;
                rightadjust=keepCenter()*rightGoal;
            }
            leftSpeed += PIDHELPLEFT(leftGoal=trapazoidLeftStraight(targetturnleft,leftGoal,beganleft,driveGetLeftEncoderDistance())+leftadjust);
            rightSpeed += PIDHELPRIGHT(rightGoal=trapazoidRightStraight(targetturnright,rightGoal,beganright,driveGetRightEncoderDistance())-rightadjust);
            driveSetRawSpeeds(leftSpeed, rightSpeed);
        }
        driveStop();
        delay(10);
        
        //float leftError = driveGetLeftEncoderDistance() - targetturnleft; // difference between target and value traveled
        //float rightError = driveGetRightEncoderDistance() - targetturnright;
        
}

void backward()
{
    bool complete = false;
    while (!complete)
    {
        float prevLeftDist=driveGetLeftEncoderDistance();
        float prevRightDist=driveGetRightEncoderDistance();
        float targetturnleft = 5;
        float targetturnright = 5; // values for distance wanted to travel per wheel
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            //leftSpeed+= PIDHELPLEFT(15);
            //leftSpeed+=keepCenter();
            //rightSpeed-=keepCenter();
            //rightSpeed+= PIDHELPRIGHT(15);
            //driveSetRawSpeeds(leftSpeed, rightSpeed);
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
        float targetturnleft =2;
        float targetturnright = 2; // values for distance wanted to travel per wheel
        float rightSpeed=.24;
        float leftSpeed=.24;
        while (driveGetLeftEncoderDistance()-prevLeftDist < targetturnleft && driveGetRightEncoderDistance()-prevRightDist < targetturnright)
        {
            leftSpeed += PIDHELPLEFT(15);
            leftSpeed += keepCenter();
            rightSpeed -=keepCenter();
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

float trapazoidLeft(float targetDist, float numberItAddsTo, float began, float currentDist){
    driveLoop();
    float split=targetDist/2;
    float distThrough=currentDist-began;
    float ret;
    float vMax=3;
    if(targetDist>0){
    if(distThrough<split){
        ret= numberItAddsTo + ((pow(vMax,2))/(2*split))/80;
    }
    //else if (distThrough>=split && distThrough<split){
      //  ret=vMax;
    //}
    else{
        ret=numberItAddsTo - ((pow(vMax,2))/(2*split))/80;
    }
    return ret;
}
else {
    if(distThrough>split){
        ret= numberItAddsTo - ((pow(vMax,2))/(2*split))/80;
    }
    //else if (distThrough>=split && distThrough<split){
        //ret=vMax;
    //}
    else{
        ret=numberItAddsTo + ((pow(vMax,2))/(2*split))/80;
    }
    return ret;
}
}

float trapazoidRight(float targetDist, float numberItAddsTo, float began,float currentDist){
    driveLoop();
    float split=targetDist/2;
    float distThrough=currentDist-began;
    float ret;
    float vMax=3;
    if(targetDist>0){
    if(distThrough<split){
        ret= numberItAddsTo + ((pow(vMax,2))/(2*split))/80;
    }
    //else if (distThrough>=split && distThrough<split){
      //  ret=vMax;
    //}
    else{
        ret=numberItAddsTo - ((pow(vMax,2))/(2*split))/80;
    }
    return ret;
}
else {
    distThrough=distThrough*-1;
    if(distThrough<split){
        ret= numberItAddsTo - ((pow(vMax,2))/(2*split))/80;
    }
    //else if (distThrough>=split && distThrough<split){
        //ret=vMax;
    //}
    else{
        ret= numberItAddsTo + ((pow(vMax,2))/(2*split))/80;
    }
    return ret;
}
}

float trapazoidLeftStraight(float targetDist, float numberItAddsTo, float began, float currentDist){
    driveLoop();
    float split=targetDist/2;
    float distThrough=currentDist-began;
    float ret;
    float vMax=3;
    if(targetDist>0){
    if(distThrough<split){
        ret= numberItAddsTo + ((pow(vMax,2))/(2*split))/25;
    }
    //else if (distThrough>=split && distThrough<split){
      //  ret=vMax;
    //}
    else{
        ret=numberItAddsTo - ((pow(vMax,2))/(2*split))/25;
    }
    return ret;
}
else {
    distThrough=distThrough*-1;
    if(distThrough<split){
        ret= numberItAddsTo - ((pow(vMax,2))/(2*split))/25;
    }
    //else if (distThrough>=split && distThrough<split){
        //ret=vMax;
    //}
    else{
        ret= numberItAddsTo + ((pow(vMax,2))/(2*split))/25;
    }
    return ret;
}
}

float trapazoidRightStraight(float targetDist, float numberItAddsTo, float began, float currentDist){
    driveLoop();
    float split=targetDist/2;
    float distThrough=currentDist-began;
    float ret;
    float vMax=3;
    if(targetDist>0){
    if(distThrough<split){
        ret= numberItAddsTo + ((pow(vMax,2))/(2*split))/25;
    }
    //else if (distThrough>=split && distThrough<split){
      //  ret=vMax;
    //}
    else{
        ret=numberItAddsTo - ((pow(vMax,2))/(2*split))/25;
    }
    return ret;
}
else {
    if(distThrough>split){
        ret= numberItAddsTo + ((pow(vMax,2))/(2*split))/25;
    }
    //else if (distThrough>=split && distThrough<split){
        //ret=vMax;
    //}
    else{
        ret=numberItAddsTo - ((pow(vMax,2))/(2*split))/25;
    }
    return ret;
}
}
bool wallRight(){
    if (getFilterLeft()>28){
        return false;
    }
    else return true;
}

bool wallLeft(){
    if (getFilterRight()>28){
        return false;
    }
    else return true;
}

bool wallFront(){
    if (getFilterMiddle()>20){
        return false;
    }
    else return true;
}