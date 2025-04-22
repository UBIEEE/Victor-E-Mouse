#pragma once

class Motor{
    public: 

    int directionPin = 12;
    int pwmPin = 3; 
    int brakePin = 9;

    bool directionState;

    void move(); 

    


};