
# 1. Project Motivation

The inverted pendulum project is interesting because it takes something that is naturally unstable and tries to balance it using intelligence and control. Imagine trying to keep a broomstick standing upright on your fingertip—it constantly wants to fall, so you must react quickly and precisely. Our project does the same thing, but with a small 3D-printed structure, sensors, electronics, and an Arduino program.

In simple terms, the system works by constantly measuring the pendulum’s angle and then using a motor to correct its movement. When the pendulum starts to fall to one side, the motor spins a 3D-printed wheel to generate the force needed to push it back toward the vertical position. This process repeats many times per second.

The control theory behind it is based on predicting how the pendulum will move and applying just the right amount of force at the right moment to keep it balanced. Instead of reacting randomly, the controller follows a mathematical strategy (implemented in code) that decides how strong and how fast the motor should respond.

Overall, the project is a practical demonstration of how engineers use mechanics, electronics, and smart algorithms to stabilize systems that would otherwise be impossible to balance on their own.

---
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

- ## Motor Encoder

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

<img width="1118" height="566" alt="image" src="https://github.com/user-attachments/assets/8afae4e3-e047-412a-b5a0-9903caf99b37" />


# Pendulum Assembly #

<img width="1536" height="2048" alt="image" src="https://github.com/user-attachments/assets/2e315fd5-0aca-4de8-a0f7-1c980f76232a" />

---
# 3. Implementation

## 3.1 Arduino Control Software (`code/Progress_Codes/`)

The Arduino control software is located in the `code/` directory and is responsible for the real-time control of the inverted pendulum system. The main program is implemented in the file `main.ino`, while the controller parameters and system constants are defined in `config.h`.

A PID controller is implemented to stabilize the pendulum around its unstable equilibrium point. The proportional, integral, and derivative gains, as well as the reference setpoint, deadband, and actuator limits, are defined in the configuration file. This separation allows systematic tuning of the controller parameters and improves code readability.

To understand how the PID works use this ilustration:

<img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/1aeaa95d-6887-4f19-bd52-fe6e013f7f9a" />

> ⚠️ **Important:**
> The ilustration above is a graphic that represents of how changing the PID values will chance the force exerted by the engine over time. 

At each control cycle, the Arduino reads the pendulum angle from the sensor and computes the control error with respect to the setpoint. The control law generates a control signal that is converted into a PWM output and applied to the motor through a motor driver. A minimum PWM threshold is used to compensate for motor dead zones and ensure reliable actuation.

For monitoring and experimental analysis, the measured pendulum angle is transmitted to a host computer via serial communication at a baud rate of 9600 bps. This data stream enables external observation of the system dynamics without affecting the real-time control loop.


## 3.2 Python Tools (`code/Python/`)

Python is used as a post-processing and visualization tool for the inverted pendulum experiments. The script `Code_to_create_Graphs.py`, located in the `code/` directory, establishes a serial connection with the Arduino using the `pyserial` library.

The script continuously receives the pendulum angle values sent by the Arduino and associates them with time stamps generated on the host computer. Basic data validation is performed to discard invalid serial data during acquisition.

After the acquisition is stopped by the user, the recorded data is plotted using the `Matplotlib` library. The resulting angle-versus-time plots provide a clear representation of the system response and allow qualitative evaluation of stability and control performance. These results support further physical interpretation and analysis of the inverted pendulum dynamics.


# 4. Experiments and results 

This section presents the experimental evaluation of the inverted pendulum system. Several tests were conducted to assess the controller’s ability to stabilize the pendulum under different conditions.

The folowing graph is a angle vs time experiment with pendulum stabilization to see how the AS5600 works:

<img width="1600" height="782" alt="image" src="https://github.com/user-attachments/assets/46d1c12b-a394-4a30-960d-66528d814e05" />

The Results obtained after 4 weeks can be seen in the next videos:

<div style="position: relative; padding-bottom: 56.25%; height: 0;">
  <iframe
    src="https://www.youtube.com/embed/1MtrXlssoLU"
    style="position: absolute; top:0; left:0; width:100%; height:100%;"
    frameborder="0"
    allowfullscreen>
  </iframe>
</div>


<div style="position: relative; padding-bottom: 56.25%; height: 0; overflow: hidden;">
  <iframe
    src="https://www.youtube.com/embed/tHJFZTiYXPw"
    title="YouTube video player"
    frameborder="0"
    allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
    allowfullscreen
    style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;">
  </iframe>
</div>

As it can be seen in the video after approximately 4 weeks the main objective of the project was sucessfully achived. Because of that the team discussed and decided that the from the additional challenges given the next target would be to make the pendulum stabelize without counterweight. After a week of progress the results achieved can be seen in the next video:

<div style="position: relative; padding-bottom: 56.25%; height: 0; overflow: hidden;">
  <iframe
    src="https://www.youtube.com/embed/hepXmcbHj-w"
    title="YouTube video player"
    frameborder="0"
    allowfullscreen
    style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;">
  </iframe>
</div>

Some other challenges that were selected by the team were:
- Improvement of Design;
- Data Analysis;
- Creation of a Second PID (This challenge was applied in the no counterweight case and the achivement of completing that challenge was part from the creation of the second pid, for better stabilization).

The results of this three challenges can be seen in the next section.

# 5. Additional Challenges

For the improvement of the design it was created new parts that then were printed in a 3D Printer. This new parts give the pendulum more stabilization because of its design, and there are some extras, such as, to spaces to put the arduino and the L298N.

<script type="module"
  src="https://unpkg.com/@google/model-viewer/dist/model-viewer.min.js">
</script>

<div style="max-width: 900px; margin: 1rem auto; padding: 0 1rem;">
  <div style="position: relative; width: 100%; height: min(70vh, 650px); border-radius: 12px; overflow: hidden;">
    <model-viewer
      src="https://raw.githubusercontent.com/Technische-Natuurkunde-HvA/inverted-pendulum-international-team-6/main/visuals/files_newparts/Braco%20pendulo.STL"
      alt="Braço do pêndulo"
      camera-controls
      auto-rotate
      rotation-per-second="20deg"
      shadow-intensity="1"
      style="width: 100%; height: 100%; background: #f5f5f5;">
    </model-viewer>
  </div>
</div>


<script type="module"
  src="https://unpkg.com/@google/model-viewer/dist/model-viewer.min.js">
</script>

<div style="max-width: 900px; margin: 1rem auto; padding: 0 1rem;">
  <div style="position: relative; width: 100%; height: min(70vh, 650px); border-radius: 12px; overflow: hidden;">
    <model-viewer
      src="https://raw.githubusercontent.com/Technische-Natuurkunde-HvA/inverted-pendulum-international-team-6/main/visuals/files_newparts/base.STL"
      alt="Base (STL)"
      camera-controls
      auto-rotate
      rotation-per-second="20deg"
      shadow-intensity="1"
      style="width: 100%; height: 100%; background: #f5f5f5;">
    </model-viewer>
  </div>
</div>

The data Analysis challenge it was quite simple the team just created a new code that can be acessed by this link ([link](https://github.com/Technische-Natuurkunde-HvA/inverted-pendulum-international-team-6/tree/main/code/Additional_Challenges/Code%20Data%20Analysis))

The creation of a second PID was basically dividing the PID in two, in the left side of the up right position there is a PID and on the right it's the same. The team decided to do this because some time in some experiments it could be seen that the wheel going to one side had more force than going to the other side. The code for this challenge can be acessed by the link ([link](https://github.com/Technische-Natuurkunde-HvA/inverted-pendulum-international-team-6/tree/main/code/Additional_Challenges/Code%20Pendulum%20Without%20Counterweight))

# 6. Team and Credits

## The students:
- Duarte Anastácio
- Angelo Russo
- Nuno Mota
- Ricardo Alves
- Abdu Shehab

## Supervisors 
- Prof. Pedro Patrício
- Prof. Manfred Niehus
- Prof. Mark Bosman

## Collaborating Institutions

<img width="374" height="232" alt="image" src="https://github.com/user-attachments/assets/07495b6b-3467-4336-ac16-9d3e6c35de2e" />


<img width="600" height="301" alt="image" src="https://github.com/user-attachments/assets/e998bc3b-7ccf-4e0d-904b-552eeb3bff31" />

# 7. Repository

Project Repository:

- [GitHub: inverted-pendulum-international-team-6](https://github.com/Technische-Natuurkunde-HvA/inverted-pendulum-international-team-6)
