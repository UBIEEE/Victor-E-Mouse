#pragma once

struct Position
{
    int x, y, direction;
};

bool wallRight();

bool wallLeft();

bool wallFront();

void turnRight();

void turnLeft();

void moveForward();

void changeDir(Position *position, char direction);

void movePositionForward(Position *position);

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

extern float count;
extern float leftAdjustment;
extern float rightAdjustment;
extern float leftTotalError;
extern float rightTotalError;
extern float constant;