## Inverted Pendulum Project ##

# 1. Project Motivation

The inverted pendulum project is interesting because it takes something that is naturally unstable and tries to balance it using intelligence and control. Imagine trying to keep a broomstick standing upright on your fingertip—it constantly wants to fall, so you must react quickly and precisely. Our project does the same thing, but with a small 3D-printed structure, sensors, electronics, and an Arduino program.

In simple terms, the system works by constantly measuring the pendulum’s angle and then using a motor to correct its movement. When the pendulum starts to fall to one side, the motor spins a 3D-printed wheel to generate the force needed to push it back toward the vertical position. This process repeats many times per second.

The control theory behind it is based on predicting how the pendulum will move and applying just the right amount of force at the right moment to keep it balanced. Instead of reacting randomly, the controller follows a mathematical strategy (implemented in code) that decides how strong and how fast the motor should respond.

Overall, the project is a practical demonstration of how engineers use mechanics, electronics, and smart algorithms to stabilize systems that would otherwise be impossible to balance on their own.

# 2. The Setup

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

# Diagram of all the connections 

![Diagram](https://github.com/Technische-Natuurkunde-HvA/inverted-pendulum-international-team-6/blob/main/visuals/figures/Diagram%20of%20electrical%20connections.png)

# 3. Implementation




