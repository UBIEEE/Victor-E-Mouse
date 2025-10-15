#include <Arduino.h>
#include <Drive.hpp>

////////////////////////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////////////////////////

// Arduino pins connected to the DRV8833 motor driver. Must all be PWM-capable.
static const pin_size_t kLeftMotorPin1 = 5;
static const pin_size_t kLeftMotorPin2 = 6;
static const pin_size_t kRightMotorPin1 = 9;
static const pin_size_t kRightMotorPin2 = 10;

// Arduino pins connected to the encoders. 'A' pins must be interrupt-capable.
static const pin_size_t kLeftEncoderPinA = 2;
static const pin_size_t kLeftEncoderPinB = 3;
static const pin_size_t kRightEncoderPinA = 18;
static const pin_size_t kRightEncoderPinB = 19;

// Motor directions
static const int kLeftDirectionMultiplier = +1;
static const int kRightDirectionMultiplier = -1;

// Encoder Constants

/**
 * Adjust this value based on your robot's gear ratio, number of radial poles of
 * the encoder magnet, and wheel diameter. Distance can be in any unit, we
 * recommend meters.
 *
 * Currently the units of distance are _wheel rotations_ for an encoder with 6
 * radial poles and a 50:1 gear ratio.
 */
static const float kDistancePerTick = 1.f / (6.f * 50.f);

////////////////////////////////////////////////////////////////////////////////
// Static function prototypes
////////////////////////////////////////////////////////////////////////////////

static void leftEncoderPinAChanged();
static void rightEncoderPinAChanged();

////////////////////////////////////////////////////////////////////////////////
// Static variables
////////////////////////////////////////////////////////////////////////////////

// Volatile because they are modified in an interrupt
static volatile long leftEncoderTicks = 0;
static volatile long rightEncoderTicks = 0;

static long lastLoopLeftEncoderTicks = 0;
static long lastLoopRightEncoderTicks = 0;
static unsigned long lastLoopTimeMs = 0;

static float leftEncoderTicksPerSecond = 0.f;
static float rightEncoderTicksPerSecond = 0.f;

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

void driveSetup() {
  // DRV8833
  pinMode(kLeftMotorPin1, OUTPUT);
  pinMode(kLeftMotorPin2, OUTPUT);
  pinMode(kRightMotorPin1, OUTPUT);
  pinMode(kRightMotorPin2, OUTPUT);

  // Encoders
  pinMode(kLeftEncoderPinA, INPUT);
  pinMode(kLeftEncoderPinB, INPUT);
  pinMode(kRightEncoderPinA, INPUT);
  pinMode(kRightEncoderPinB, INPUT);

  const pin_size_t leftEncoderPinAInterrupt =
      digitalPinToInterrupt(kLeftEncoderPinA);
  const pin_size_t rightEncoderPinAInterrupt =
      digitalPinToInterrupt(kRightEncoderPinA);

  attachInterrupt(leftEncoderPinAInterrupt, leftEncoderPinAChanged, CHANGE);
  attachInterrupt(rightEncoderPinAInterrupt, rightEncoderPinAChanged, CHANGE);
}

void driveLoop() {
  const unsigned long currentTimeMs = millis();
  const unsigned long deltaTimeMs = currentTimeMs - lastLoopTimeMs;

  // Update encoder velocities
  {
    const long currentLeftEncoderTicks = leftEncoderTicks;
    const long currentRightEncoderTicks = rightEncoderTicks;

    const long deltaLeftTicks =
        currentLeftEncoderTicks - lastLoopLeftEncoderTicks;
    const long deltaRightTicks =
        currentRightEncoderTicks - lastLoopRightEncoderTicks;

    leftEncoderTicksPerSecond = (deltaLeftTicks * 1000.f) / deltaTimeMs;
    rightEncoderTicksPerSecond = (deltaRightTicks * 1000.f) / deltaTimeMs;

    lastLoopLeftEncoderTicks = currentLeftEncoderTicks;
    lastLoopRightEncoderTicks = currentRightEncoderTicks;
  }

  lastLoopTimeMs = currentTimeMs;

  // In the future, add PID control or other periodic drivetrain tasks.
}

void driveSetRawSpeeds(float leftPercent, float rightPercent) {
  leftPercent = constrain(leftPercent, -1.f, 1.f) * kLeftDirectionMultiplier;
  rightPercent = constrain(rightPercent, -1.f, 1.f) * kRightDirectionMultiplier;

  // Control the two DC motors connected to the DRV8833 Dual H-Bridge motor
  // driver

  const int leftSpeed = static_cast<int>(fabs(leftPercent * 255.f));
  const int rightSpeed = static_cast<int>(fabs(rightPercent * 255.f));

  if (leftPercent >= 0.f) {
    analogWrite(kLeftMotorPin1, leftSpeed);
    analogWrite(kLeftMotorPin2, 0);
  } else if (leftPercent < 0.f) {
    analogWrite(kLeftMotorPin1, 0);
    analogWrite(kLeftMotorPin2, leftSpeed);
  }

  if (rightPercent >= 0.f) {
    analogWrite(kRightMotorPin1, rightSpeed);
    analogWrite(kRightMotorPin2, 0);
  } else if (rightPercent < 0.f) {
    analogWrite(kRightMotorPin1, 0);
    analogWrite(kRightMotorPin2, rightSpeed);
  }
}

void driveStop() { driveSetRawSpeeds(0.f, 0.f); }

float driveGetLeftEncoderDistance() {
  return leftEncoderTicks * kDistancePerTick;
}

float driveGetRightEncoderDistance() {
  return rightEncoderTicks * kDistancePerTick;
}

void driveResetEncoderDistance() {
  leftEncoderTicks = 0;
  rightEncoderTicks = 0;
}

float driveGetLeftEncoderVelocity() {
  return leftEncoderTicksPerSecond * kDistancePerTick;
}

float driveGetRightEncoderVelocity() {
  return rightEncoderTicksPerSecond * kDistancePerTick;
}

////////////////////////////////////////////////////////////////////////////////
// Static function definitions
////////////////////////////////////////////////////////////////////////////////

void leftEncoderPinAChanged() {
  const bool A = digitalRead(kLeftEncoderPinA);
  const bool B = digitalRead(kLeftEncoderPinB);

  if (A == B) { // B leads A
    leftEncoderTicks += kLeftDirectionMultiplier;
  } else { // A leads B
    leftEncoderTicks -= kLeftDirectionMultiplier;
  }
}

void rightEncoderPinAChanged() {
  const bool A = digitalRead(kRightEncoderPinA);
  const bool B = digitalRead(kRightEncoderPinB);

  if (A == B) { // B leads A
    rightEncoderTicks += kRightDirectionMultiplier;
  } else { // A leads B
    rightEncoderTicks -= kRightDirectionMultiplier;
  }
}
