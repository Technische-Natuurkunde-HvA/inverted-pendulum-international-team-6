#include <Wire.h>
#include <PID_v1.h>
#include <AS5600.h>
#include "config.h"   // includes the parameters defined in the main config file

AS5600 as5600;

// ----------------------
// State machine
// ----------------------
enum State {
  STATE_CONFIG,
  STATE_RUN
};

State currentState = STATE_CONFIG;

// ----------------------
// Global variables
// ----------------------
unsigned long currentMs;
unsigned long lastMs;
const unsigned int FREE_RUN_PERIOD_MS = 5;
double sig_angle_deg;

// Motor
const int motorPin1 = 10;
const int motorPin2 = 11;
const int enablePin = 9;

// PID outputs
double outputRight, outputLeft;

// PID objects (gains come from config.h)
PID pidRight(&sig_angle_deg, &outputRight, &SETPOINT, KpR, KiR, KdR, DIRECT);
PID pidLeft (&sig_angle_deg, &outputLeft,  &SETPOINT, KpL, KiL, KdL, REVERSE);

// Startup impulse
bool startupImpulseDone = false;

// ----------------------
// Helper functions
// ----------------------
void readAngle() {
  lastMs = currentMs;
  sig_angle_deg = (float)as5600.readAngle() * 0.0879;
}

void driveMotor(bool right, int pwm) {
  if (right) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  } else {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }
  analogWrite(enablePin, pwm);
}

void startupImpulse() {
  if (!startupImpulseDone) {
    // right impulse
    driveMotor(true, STARTUP_PWM);
    delay(STARTUP_TIME_MS);
    // left impulse
    driveMotor(false, STARTUP_PWM);
    delay(STARTUP_TIME_MS);
    // stop
    analogWrite(enablePin, 0);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    startupImpulseDone = true;
  }
}

// ----------------------
// Setup
// ----------------------
void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  Wire.begin();
  as5600.begin();
  Serial.begin(9600);
  delay(2000);

  lastMs = millis();
}

// ----------------------
// Main loop
// ----------------------
void loop() {
  switch (currentState) {

    case STATE_CONFIG:
      // PID configuration
      pidRight.SetMode(AUTOMATIC);
      pidRight.SetSampleTime(FREE_RUN_PERIOD_MS);
      pidRight.SetOutputLimits(0, 255);

      pidLeft.SetMode(AUTOMATIC);
      pidLeft.SetSampleTime(FREE_RUN_PERIOD_MS);
      pidLeft.SetOutputLimits(0, 255);

      currentState = STATE_RUN;
      break;

    case STATE_RUN:
      currentMs = millis();
      if (currentMs - lastMs >= FREE_RUN_PERIOD_MS) {
        readAngle();
        double error = SETPOINT - sig_angle_deg;

        if (!startupImpulseDone) startupImpulse();

        // Balance
        if (fabs(error) <= ANGLE_DEADBAND) {
          analogWrite(enablePin, 0);
          digitalWrite(motorPin1, LOW);
          digitalWrite(motorPin2, LOW);
          Serial.print(sig_angle_deg);
          Serial.print(" ");
          Serial.println(0);
          return;
        }

        // Choose PID
        if (error > 0) {
          pidRight.Compute();
          int pwm = (outputRight < PWM_MIN) ? PWM_MIN : outputRight;
          driveMotor(true, pwm);
          Serial.print(sig_angle_deg);
          Serial.print(" ");
          Serial.println(pwm);
        } else {
          pidLeft.Compute();
          int pwm = (outputLeft < PWM_MIN) ? PWM_MIN : outputLeft;
          driveMotor(false, pwm);
          Serial.print(sig_angle_deg);
          Serial.print(" ");
          Serial.println(-pwm);
        }
      }
      break;
  }
}
