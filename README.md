# Projectile-Motion-Control
Projectile Motion Control is a C++ simulation project that allows users to control initial velocity, launch angle, and gravity. It calculates trajectory, maximum height, range, and time of flight, while visually simulating projectile movement and helping users understand the principles of projectile motion.

📌 Project Overview

Projectile Motion Control is a C++-based simulation project that demonstrates the principles of projectile motion. The user can control parameters such as initial velocity, launch angle, and gravity and observe how they affect the projectile's trajectory.

🎯 Objectives

Understand projectile motion using C++.
Calculate the projectile's trajectory mathematically.
Determine maximum height, range, and time of flight.
Allow users to experiment with different velocities and angles.
Provide a simple simulation of projectile movement.

⚙️ Features

User-controlled initial velocity.
User-controlled launch angle.
Gravity input.
Calculation of:
Time of Flight
Maximum Height
Horizontal Range
X and Y positions
Projectile trajectory simulation.
Interactive experimentation with different values.

🧮 Physics Equations

For initial velocity u, angle θ, and gravitational acceleration g:

Time of Flight:

T = (2 × u × sin(θ)) / g

Maximum Height:

H = (u² × sin²(θ)) / (2 × g)

Horizontal Range:

R = (u² × sin(2θ)) / g

Horizontal Position:

x = u × cos(θ) × t

Vertical Position:

y = u × sin(θ) × t - ½ × g × t²

🛠️ Technologies Used

C++
Mathematical functions
Object-Oriented Programming
Optional: SFML for graphical visualization

▶️ How to Run

Install a C++ compiler such as G++.
Clone or download the project.
Open the project in VS Code, Code::Blocks, or another C++ IDE.
Compile the source code.
Run the executable.
Enter the required velocity and angle values.

📂 Project Structure

ProjectileMotion/
│
├── src/
│   └── main.cpp
│
├── include/
│   └── Projectile.h
│
├── README.md
└── data/

🔮 Future Improvements

Add a real-time graphical interface.
Add targets and obstacles.
Add collision detection.
Compare multiple projectile trajectories.
Add keyboard controls.
Save previous simulation results.

👩‍💻 Author

Pavani Thulasi Swarna
B.Tech – Computer Science & Engineering
SRM University AP
B.Tech – Computer Science & Engineering
SRM University AP
