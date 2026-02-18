#pragma once
// THANKS PETER
/**
 * @brief Initialize pins and interrupts for the drivetrain.
 */
void driveSetup();

/**
 * @brief Loop function to be called frequently for periodic drivetrain tasks.
 */
void driveLoop();

/**
 * @brief Control the speeds of the two DC motors connected to the DRV8833,
 *        with percent values (-1.0 for full speed reverse, +1.0 for full speed
 *        forward).
 *
 * @param leftPercent The speed (percent output) of the left motor.
 * @param rightPercent The speed (percent output) of the right motor.
 */
void driveSetRawSpeeds(float leftPercent, float rightPercent);

/**
 * @brief Stop both motors.
 */
void driveStop();
extern float turnrate;
// for PID
/**
 * @brief Get the distance driven by the left wheel since the last reset.
 *
 * @return Distance in user units.
 */
float driveGetLeftEncoderDistance();

/**
 * @brief Get the distance driven by the right wheel since the last reset.
 *
 * @return Distance in user units.
 */
float driveGetRightEncoderDistance();

/**
 * @brief Reset the encoder distance measurements to zero.
 */
void driveResetEncoderDistance();

/**
 * @brief Get the velocity of the left wheel.
 *
 * @return Velocity in user units per second.
 */
float driveGetLeftEncoderVelocity();

/**
 * @brief Get the velocity of the right wheel.
 *
 * @return Velocity in user units per second.
 */
float driveGetRightEncoderVelocity();
