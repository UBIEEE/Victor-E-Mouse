#include <Arduino.h>
#include <motorEncoder.h>

void motorEncoder::motorEncoderSetup(){

    // Set encoder pins as inputs
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);

  // Set LED pins as outputs
  pinMode (ledCW,OUTPUT);
  //pinMode (ledCCW,OUTPUT);

  // Setup Serial Monitor
  Serial.begin (9600);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK); 
}


void motorEncoder::motorEncoderLoop(){
     // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occurred
  if (currentStateCLK != previousStateCLK){

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      counter--;
      encdir ="CCW";
      digitalWrite(ledCW, LOW);
      //digitalWrite(ledCCW, HIGH);

    } else {
      // Encoder is rotating clockwise
      counter++;
      encdir ="CW";
      digitalWrite(ledCW, HIGH);
      //digitalWrite(ledCCW, LOW);

    }
    /*
    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" -- Value: ");
    Serial.println(counter);
    */
   
  }
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}

