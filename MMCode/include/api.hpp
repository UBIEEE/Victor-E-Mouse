#pragma once

class CELL {
    public:
    int x;
    int y;
    int value;
};

void straighten();

bool leftWall();

bool rightWall();

bool frontWall();

void turnRight();

void turnLeft();

void moveForward();