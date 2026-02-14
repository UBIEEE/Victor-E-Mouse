#pragma once

struct Position {
    int x, y, direction;
};

void straighten();

bool leftWall();

bool rightWall();

bool frontWall();

void turnRight();

void turnLeft();

void moveForward();