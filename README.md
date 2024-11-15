# Car Control Project

This project is part of the Elec1601 course.

This project uses C++ code that I wrote myself to control the movement of a car. While the code implementation is relatively straightforward, the logical challenges involved are complex and required careful consideration. There are several significant difficulties, particularly in managing the loop function during a 90-degree turn.

### Challenges Faced

In this project, I faced multiple technical and logical challenges while using C++ and Servo library functions to control the car's movement. Below are the main challenges encountered:

1. **Turning 90 Degrees**: The car needs to make fine adjustments before turning, and then detect the wall in front. This sequence can easily lead to incorrect status and cause the car to hit the wall. Achieving a smooth 90-degree turn without collisions was a major challenge.

2. **End Point Rotation**: At the endpoint, the car must rotate 720 degrees and stop before reaching the red line. This 720-degree turn was extremely prone to hitting walls, which made it even more difficult. This was another significant difficulty. Ensuring that the car could rotate without hitting obstacles while precisely stopping in the correct location required considerable effort.

3. **Continuous Turns**: The car needed to handle multiple continuous turns, which had to be executed with precision to avoid errors. My approach involved using `flag1` and `flag2` to determine whether the car should turn left or right, helping in smoothly handling consecutive turns.

### My Solution

The following solution was implemented in C++ using the Servo library and infrared sensors to navigate the car through obstacles and achieve accurate positioning.

The core of my solution revolves around the car's directional control. I used the direction of the previous fine-tuning to determine the direction of the next 90-degree rotation. Specifically, the car only uses the front infrared sensor to detect walls during each turn, and I record the data at each step. For the 720-degree rotation at the endpoint, I ensured that the car could make a complete circle without hitting the wall, which was particularly challenging.

To stop the car precisely before the red line, I consulted with my tutors and ended up using a hardcoded approach. I recorded the final sequence of turns—for example, there were ten left turns—and measured the time it took to complete each segment. When the car reaches the designated stop point, the program executes `exit(0)` to terminate.

### Summary

This project involved a combination of hardware and software challenges, and my solution demonstrates the integration of C++ code with precise movement control. The performance evaluation ranked my project in the top ten.

My performance in this project ranked in the top 10.

This project was an interesting mix of relatively simple code implementation and challenging logic. Proper handling of the car's continuous turns, rotations, and stopping mechanisms required a lot of trial and error and fine-tuning. The main breakthrough was leveraging the previous turn data to guide future movements and hardcoding critical timing values to ensure precision.

