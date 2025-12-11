#ifndef CONFIG_H
#define CONFIG_H

// ----------------------
// Tuning parameters
// ----------------------

// Setpoint
double SETPOINT = 225.5;

// Right side PID gains
const double KpR = 100.0;
const double KiR = 4.0;
const double KdR = 1.0;

// Left side PID gains
const double KpL = 100.0;
const double KiL = 4.0;
const double KdL = 1.0;

// Deadband (balance dead zone)
const double ANGLE_DEADBAND = 0.01;

// Minimum PWM
const int PWM_MIN = 47;

// Startup boost
const int STARTUP_PWM = 150;        // intensity
const int STARTUP_TIME_MS = 700;   // duration in ms

#endif
