#include <Arduino.h>
#include <Drive.hpp>
#include <math.h>
////////////////////////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////////////////////////
// Arduino pins connected to the DRV8833 motor driver. Must all be PWM-capable.
static const pin_size_t kLeftMotorPin1 =D2;
static const pin_size_t kLeftMotorPin2 =D3;
static const pin_size_t kRightMotorPin1 = D4; 
static const pin_size_t kRightMotorPin2 = D5; 

// Arduino pins connected to the encoders. 'A' pins must be interrupt-capable.
static const pin_size_t kLeftEncoderPinA = D7;
static const pin_size_t kLeftEncoderPinB = D6;
static const pin_size_t kRightEncoderPinA = D9; 
static const pin_size_t kRightEncoderPinB = D8; 

// Motor directions
static const int kLeftDirectionMultiplier = -1;
static const int kRightDirectionMultiplier = 1;

// Encoder Constants

/**
 * Adjust this value based on your robot's gear ratio, number of radial poles of
 * the encoder magnet, and wheel diameter. Distance can be in any unit, we
 * recommend meters.
 *
 * Currently the units of distance are _wheel rotations_ for an encoder with 6
 * radial poles and a 50:1 gear ratio.
 */
static const float kDistancePerTick = ((1.f / (6.f * 50.f))*(25.13))*(10/21.61);

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
static unsigned long deltaTimeMs;
float angularSpeed;

float lprevEr=0;
float lposEr=0;
float ltotalEr=0;
float rprevEr=0;
float rposEr=0;
float rtotalEr=0;
float llast;
float rlast;
float lkp=.002;
float lki=.00000005;
float lkd=0.0000000000;
float rkp=.002;
float rki=.00000005;
float rkd=0.0000000000;

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////
// class from peter
PIDController::PIDController(float kp,
                             float ki,
                             float kd,
                             float dt,
                             float min_integral,
                             float max_integral)
    : m_kp(kp),
      m_ki(ki),
      m_kd(kd),
      m_dt(dt),
      m_min_integral(min_integral),
      m_max_integral(max_integral) {}



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
  deltaTimeMs = currentTimeMs - lastLoopTimeMs;

  // Update encoder velocities
  {
    const long currentLeftEncoderTicks = leftEncoderTicks;
    const long currentRightEncoderTicks = rightEncoderTicks;

    const long deltaLeftTicks =
        currentLeftEncoderTicks - lastLoopLeftEncoderTicks;
    const long deltaRightTicks =
        currentRightEncoderTicks - lastLoopRightEncoderTicks;

    leftEncoderTicksPerSecond = (deltaLeftTicks * 100.f) / deltaTimeMs;
    rightEncoderTicksPerSecond = (deltaRightTicks * 100.f) / deltaTimeMs;

    lastLoopLeftEncoderTicks = currentLeftEncoderTicks;
    lastLoopRightEncoderTicks = currentRightEncoderTicks;
  }

  lastLoopTimeMs = currentTimeMs;

  //angularSpeed=(driveGetLeftEncoderVelocity()-driveGetRightEncoderVelocity())/10.8;

  // In the future, add PID control or other periodic drivetrain tasks.
  delay(3);
}
float PIDHELPLEFT(float setpoint){
    float now=millis();
    float measurement=driveGetLeftEncoderVelocity();
    float delta=now-llast;
    lprevEr=lposEr;
    lposEr=setpoint-measurement;
    float vel=(lposEr-lprevEr)/delta;
    ltotalEr=ltotalEr+lposEr*delta;
    llast=now;
    return lkp*lposEr+lki*ltotalEr+lkd*vel;
}
float PIDHELPRIGHT(float setpoint){
    float now=millis();
    float measurement=driveGetRightEncoderVelocity();
    float delta=now-rlast;
    rprevEr=rposEr;
    rposEr=setpoint-measurement;
    float vel=(rposEr-rprevEr)/delta;
    rtotalEr=rtotalEr+rposEr*delta;
    rlast=now;
    return rkp*rposEr+rki*rtotalEr+rkd*vel;
}
float getAngularSpeed(){
    return angularSpeed*(180/PI);
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