# Robotics Software Engineering Nanodegree
By Victor Enrique Gil Altamirano
## Project 3: Where Am I?

This project is the third project of Robotics Software Nanodegree program at Udacity.

I used the Udacity Workspace environment with ROS Kinetic to perform all code and testing.

## Objectives:
- Create a ROS package that launches a custom robot model in a custom Gazebo world.
- Utilize the ROS AMCL package and the Tele-Operation / Navigation Stack to localize the robot.
- Explore, add, and tune specific parameters corresponding to each package to achieve the best possible localization results.

### PGM Map File
The map ROS AMCL Package uses is a `pgm` file. A `pgm` file is a grayscale image file.
By default, AMCL package will treat 'darker' pixels as obstacle in the `pgm` map file, and 'lighter' pixels as free space. The threshold could be set as a parameter which we will cover when we are building the launch file.

- Create a `maps` folder in the package.
### PGM Map Creator
We need `libignition-math2-dev` and `protobuf-compiler` to compile the map creator:
`$ sudo apt-get install libignition-math2-dev protobuf-compiler`

Clone the package pgm_map_creator to src folder.
`$ cd /home/workspace/catkin_ws/src/`
`$ git clone https://github.com/udacity/pgm_map_creator.git`
Build package with `catkin_make`

### Create PGM Map
- Copy world file into `/world` folder. Open terminal and run `gzerver` with the map file:
`$ gzserver src/pgm_map_creator/world/Victor.world`
- In another terminal:
`$ roslaunch pgm_map_creator request_publisher.launch`

### Procedure
1. Install dependencies
`$ sudo apt-get update && sudo apt-get upgrade -y`
`$ sudo apt-get install ros-kinetic-map-server`
`$ sudo apt-get install ros-kinetic-amcl`
`$ sudo apt-get install ros-kinetic-move-base`

2. Launch world with robot inside
`$ roslaunch my_robot world.launch`

3. In another terminal, launch `amcl.launch`
`$ roslaunch my_robot amcl.launch`

4. In another terminal, run teleoperation node:
`$ rosrun teleop_twist_keyboard teleop_twist_keyboard.py`

5. Navigate the robot around the map, and the algorithm will update the particles as robot pose is updated.

### Note
`pgm` map file was too big (36MB) to upload in github.




