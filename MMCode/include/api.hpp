#pragma once


bool wallRight();

bool wallLeft();

bool wallFront();

void turnRight();

void turnLeft();

void moveForward();


void firstTurnLeft();

void firstTurnRight();

void goalTurnAround();

// ignore past move foward
void right90();

void left90();

void forwardBeforeTurn();

void forwardAfterTurn();

void backward();

void straighten();

void forwardToCenter();

void firstForward();
float trapazoidRight(float targetDist, float numberItAddsTo, float startingDist, float currentDist);
float trapazoidLeft(float targetDist, float numberItAddsTo, float startingDist,  float currentDist);
float trapazoidRightStraight(float targetDist, float numberItAddsTo, float startingDist, float currentDist);
float trapazoidLeftStraight(float targetDist, float numberItAddsTo, float startingDist, float currentDist);