# Robotics Software Engineering Nanodegree
By Victor Enrique Gil Altamirano
## Project 2: Go Chase It!

This project is the second project of Robotics Software Nanodegree program at Udacity.

I used the Udacity Workspace environment with ROS Kinetic to perform all code and testing.

## Objectives:
1. Create a robot using Gazebo and Xacros, add camera and Lidar Plugins in order to make it chase a white-colored ball in its range of vision. 
2. Create 2 ROS packages inside `catkin_ws/src`. 
- `drive_bot`:
-- Create a `my_robot` ROS package to hold the robot, the white ball, and the world.
-- Design a differential drive robot with the Unified Robot Description Format (urdf). Add two sensors to your robot: a lidar and a camera. Add Gazebo plugins for the robot’s differential drive, lidar, and camera. The robot's design should be significantly different from the one presented in the project lesson. Minimum required changes are adjusting the color, wheel radius, and chassis dimensions. 
-- Create a new world, which is different from the world you built in the Build My World project and house your robot inside that world.
-- Add a white-colored ball to your Gazebo world and save a new copy of this world.
-- The world.launch file should launch your world with the white-colored ball and your robot.

- `ball_chaser`:
-- Create a ball_chaser ROS package to hold the C++ nodes.
-- Write a `drive_bot` C++ node that will provide a `ball_chaser/command_robot` service to drive the robot by controlling its linear x and angular z velocities. The service should publish to the wheel joints and return back the requested velocities.
-- Write a `process_image` C++ node that reads your robot’s camera image, analyzes it to determine the presence and position of a white ball. If a white ball exists in the image, your node should request a service via a client to drive the robot towards it.
-- The `ball_chaser.launch` should run both the `drive_bot` and the `process_image` nodes.

## Content
- `my_robot` package, with `/launch`, `/meshes`, `urdf`, and `world` folders.
- `ball_chaser` package containing `ball_chaser.launch`, `drive_bot.cpp`, `process_images.cpp` files, and `DriveToTarget.srv` service definition.



