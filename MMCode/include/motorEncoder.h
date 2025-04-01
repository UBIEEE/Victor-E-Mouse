#pragma once
#include <string> 

class motorEncoder{

    public: 
        // Rotary Encoder Inputs
        #define inputCLK 4
        #define inputDT 5 

        // LED Outputs
        #define ledCW 8
        //#define ledCCW 9

        int counter = 0;
        int currentStateCLK;
        int previousStateCLK;

        std::string encdir ="";

        
        void motorEncoderSetup(); 

        void motorEncoderLoop(); 



}; 