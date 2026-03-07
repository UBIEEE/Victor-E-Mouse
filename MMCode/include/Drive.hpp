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

float PIDHELPLEFT(float target);
float PIDHELPRIGHT(float target);

class PIDController {
  // Proportional
  float m_kp;
  // Integral
  float m_ki;
  // Derivative
  float m_kd;

  // Time delta
  const float m_dt;

  const float m_min_integral;
  const float m_max_integral;

  float m_pos_error = 0.f;
  float m_vel_error = 0.f;

  float m_prev_error = 0.f;
  float m_total_error = 0.f;

 public:
  PIDController(float kp,
                float ki,
                float kd,
                float dt,
                float min_integral = -1.f,
                float max_integral = 1.f);
  };