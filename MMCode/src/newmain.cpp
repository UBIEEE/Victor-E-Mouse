#include <Arduino.h>
#include<sensor.h>
#include <Button.hpp>
#include <Drive.hpp>

static const int kButtonPin = 4;
static Button button;

void setup() {
  Serial.begin(9600);

  driveSetup();
  button.setupDefaultLow(kButtonPin, true);
}
static Sensor left(6,7); //pins are now 1 and 2 for now you can change them later

void loop() {
  // Use the button to control the drivetrain for demo
  if (button.isPressed()) {
    if(left.getReading()<1000){
        driveSetRawSpeeds(0,.5);
    }
    else {driveStop();}
  } else {
    driveStop();
  }

  driveLoop();

  delay(10);

  static int count = 0;
  if ((++count * 10) % 250 == 0) { // Print every 250ms
    float leftEncoderDistance = driveGetLeftEncoderDistance();
    float rightEncoderDistance = driveGetRightEncoderDistance();
    float leftEncoderVelocity = driveGetLeftEncoderVelocity();
    float rightEncoderVelocity = driveGetRightEncoderVelocity();

    Serial.print("Left Distance: ");
    Serial.print(leftEncoderDistance);
    Serial.print(" Right Distance: ");
    Serial.print(rightEncoderDistance);
    Serial.print(" Left Velocity: ");
    Serial.print(leftEncoderVelocity);
    Serial.print(" Right Velocity: ");
    Serial.print(rightEncoderVelocity);
    Serial.println();
  }
}
