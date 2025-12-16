
#include <Wire.h>
#include <PID_v1.h>
#include <AS5600.h>

AS5600 as5600;

// -------------------------
// Timing
// -------------------------
unsigned long currentMs;
unsigned long lastMs;
const unsigned int FREE_RUN_PERIOD_MS = 5;


// Angle measurement
double sig_angle_deg;


// Motor control pins
const int motorPin1 = 10;
const int motorPin2 = 11;
const int enablePin = 9;


// PID PARAMETERS
double setpoint = 328;
double output = 0;

double Kp = 29.5;
double Ki = 5.0;
double Kd = 1;

PID myPID(&sig_angle_deg, &output, &setpoint, Kp, Ki, Kd, DIRECT);

// Balance deadband
const double ANGLE_DEADBAND = 0.01;

// PWM dead zone compensation
const int PWM_MIN = 47;

const byte ENCODER_PIN = 2;
const int PULSES_PER_REV = 330;

volatile long encoderPulses = 0;
unsigned long lastRpmMs = 0;
double motorRPM = 0;
int currentPWM = 0;

// Encoder ISR
void encoderISR() {
  encoderPulses++;
}

// Read angle from AS5600
void readAngle() {
  lastMs = currentMs;
  sig_angle_deg = (float)as5600.readAngle() * 0.0879;
}

// Setup
void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Encoder setup
  pinMode(ENCODER_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), encoderISR, RISING);
  lastRpmMs = millis();

  Wire.begin();
  as5600.begin();
  Serial.begin(9600);
  delay(2000);

  lastMs = millis();

  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(FREE_RUN_PERIOD_MS);
  myPID.SetOutputLimits(-255, 255);
}


// Main Loop
void loop() {

  currentMs = millis();

  if (currentMs - lastMs >= FREE_RUN_PERIOD_MS) {

    readAngle();
    myPID.Compute();

    double error = setpoint - sig_angle_deg;

    // 1: If angle is within deadband → stop motor
    if (fabs(error) <= ANGLE_DEADBAND) {
      analogWrite(enablePin, 0);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);

      currentPWM = 0;
      motorRPM = 0;

      Serial.print(sig_angle_deg);
      Serial.print(" ");
      Serial.print(motorRPM);
      Serial.print(" ");
      Serial.println(currentPWM);

      return;
    }

    // 2: PWM dead zone compensation
    if (output > 0 && output < PWM_MIN) output = PWM_MIN;
    else if (output < 0 && output > -PWM_MIN) output = -PWM_MIN;

    // 3: Motor direction
    if (output < 0) {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
    } 
    else {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
    }

    // 4: Apply PWM
    currentPWM = abs((int)output);
    analogWrite(enablePin, currentPWM);

    // 5: Calculate RPM every 100 ms
    const unsigned long RPM_INTERVAL_MS = 100;
    unsigned long now = currentMs;

    if (now - lastRpmMs >= RPM_INTERVAL_MS) {
      noInterrupts();
      long pulses = encoderPulses;
      encoderPulses = 0;
      interrupts();

      unsigned long dt = now - lastRpmMs;
      lastRpmMs = now;

      // RPM formula
      motorRPM = (pulses * 60000.0) / (PULSES_PER_REV * dt);
    }

    // 6: Serial output
    Serial.print(sig_angle_deg);
    Serial.print(" | ");
    Serial.print(motorRPM);
    Serial.print(" | ");
    Serial.println(currentPWM);
  }
}
