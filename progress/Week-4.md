# Week 4

## 1. Progress description
This week we managed to stabilise the pendulum using and when it is stable, the position of the arm is almost perfectly vertical. 
The pendulum will also restabilise itself after you give it a little push (see visuals/videos/Pendulum_stable_V1.mp4).

## 2. Code
The code had been changed so that it can stabilise the pendulum using the magnetic sensor to state the current position.
The 3 values for our parameters differ between the Dutch and Portugese group, since we have different wheels (at least for now).

Here are the parameters for the spare wheel used in Portugal (`visuals/videos/WhatsApp Video 2025-12-2 at 14.23.48.mp4`):
```
K_p = 30.0
K_i = 5.0
K_d = 1.5
```

And these are the parameters for our official wheel (`visuals/videos/Pendulum_stable_V1.mp4`):
```
K_p = 35.0
K_i = 1.0
K_d = 1.0
```

The code that we used to implement this PID values is:
```python

// for more information on the PID library: 
// http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/

#include <Wire.h>
#include <PID_v1.h>
#include <AS5600.h>

AS5600  as5600;  //create sensor object

unsigned long currentMs;  
unsigned long lastMs;     
const unsigned int FREE_RUN_PERIOD_MS = 5; 
double sig_angle_deg;  

// Motor control pins
const int motorPin1 = 10; 
const int motorPin2 = 11; 
const int enablePin = 9;  

double setpoint = 225.5; 
double output = 0;

// PID parameters
double Kp = 31.0;
double Ki = 5.0;
double Kd = 1.0;
PID myPID(&sig_angle_deg, &output, &setpoint, Kp, Ki, Kd, DIRECT);

// zona morta de equilíbrio (graus)
const double ANGLE_DEADBAND = 0.01;

// limites de PWM para remover dead zone
const int PWM_MIN = 47;   // mínimo permitido para o motor se mover

void readAndPrintAngle();

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  Wire.begin();
  as5600.begin();
  lastMs = millis();
  Serial.begin(9600);
  delay(2000);

  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(FREE_RUN_PERIOD_MS);
  myPID.SetOutputLimits(-255, 255);
}

void loop() {

  currentMs = millis();
  if (currentMs - lastMs >= FREE_RUN_PERIOD_MS) {

    readAndPrintAngle();

    myPID.Compute(); 

    double error = setpoint - sig_angle_deg;

    // 1) SE ESTÁ EM EQUILÍBRIO → MOTOR PARADO
    if (fabs(error) <= ANGLE_DEADBAND) {
      analogWrite(enablePin, 0);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);

      Serial.print(sig_angle_deg);
      Serial.print(" ");
      Serial.println(0);
      return;
    }

    // 2) APLICAR DEAD ZONE NO PWM DO MOTOR
    // output > 0 → garantir mínimo +47
    if (output > 0 && output < PWM_MIN) {
      output = PWM_MIN;
    }
    // output < 0 → garantir mínimo -47
    else if (output < 0 && output > -PWM_MIN) {
      output = -PWM_MIN;
    }

    // 3) CONFIGURAR DIREÇÃO DO MOTOR
    if (output > 0) {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
    } 
    else {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
    }

    // 4) ESCRITA DO PWM (valor absoluto)
    analogWrite(enablePin, abs(output));

    // Debug
    Serial.print(sig_angle_deg);
    Serial.print(" ");
    Serial.println(output);
  }
}

void readAndPrintAngle() {
  lastMs = currentMs;
  sig_angle_deg = (float)as5600.readAngle() * 0.0879; 
}
```

## 3. Results
Our results have been shown in the code section above, furthermore we have not decided which additional challenge we are going to choose for next week.



## 4. Reflection 
This week we achieved stabilising the pendulum and this went a lot faster than expected.
