
# Mechanical Setup #

The mechanical structure is fully 3D-printed and designed to support an inverted pendulum stabilized by a reaction wheel. Its main components include:
 
- ## Pendulum Arm with Angle Encoder

The pendulum arm is a lightweight 3D-printed part mounted on a pivot.

Attached to this pivot is a dedicated angle encoder, which continuously measures the pendulum’s angular position. This sensor provides precise information about how far the pendulum is leaning and in which direction, which is essential for real-time control.

- ## Reaction Wheel

A large 3D-printed reaction wheel is mounted at the top of the system.

Metal bolts or weights are equally spaced around its outer rim to increase its moment of inertia, allowing it to generate stronger corrective torque when the motor accelerates or decelerates.

- ## Mounting Structure

All components are mounted on a rigid 3D-printed frame clamped to a table.

The goal is to minimize unwanted movement or vibrations while the wheel spins at high speed.

---
# Electronic Setup #

The electronic system provides sensing, computing, power control, and safety.

- ## Arduino (Main Controller)

An Arduino serves as the central processing unit.

It receives data from both encoders, runs the control algorithm, and commands the motor through the driver board.

- ## DC Motor (JGA25-370, 12 V)

The reaction wheel is directly driven by a JGA25-370 12 V DC motor.
This motor includes a built-in encoder, used to read the rotational speed and direction of the wheel. This information allows the control system to know exactly how much torque the wheel is producing at any moment.

- ## Encoders

There are two separate encoders, each with a specific function:

- ## Motor Encoder (built into the JGA25-370)

Measures the reaction wheel’s rotation speed and direction. This allows precise control of the wheel’s acceleration, which is what generates the stabilizing torque.

- ## Pendulum Arm Encoder

Measures the real-time angle of the pendulum arm. This is the primary feedback signal used to determine whether the pendulum is falling and how the system should react.

- ## L298N Motor Driver

The motor is powered and controlled via an L298N dual H-bridge driver.

This module allows the Arduino to:

· Control the motor’s direction

· Adjust the motor’s speed using PWM

· Provide adequate current to the 12 V motor

- Power Electronics

A 12 V power supply feeds the motor driver and motor, while the Arduino is powered either through USB or a regulated 5 V source.

#
