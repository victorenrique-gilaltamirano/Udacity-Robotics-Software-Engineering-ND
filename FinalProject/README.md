# Robotics Software Engineering Nanodegree
By Victor Enrique Gil Altamirano
## Final Project: Home service robot

This project is the final project of Robotics Software Nanodegree program at Udacity, all knowledge from the course is applied in this porject.

I used the Udacity Workspace environment with ROS Kinetic to perform all code and testing.

## Before starting
This project requires some packages to work properly.
- Instal the xterm terminal manager with `sudo apt-get install xterm`
- Inside `workspace/catkin_ws/src` folder, install packages:
`$ git clone https://github.com/ros-perception/slam_gmapping.git`
`$ git clone  https://github.com/turtlebot/turtlebot.git`
`$ git clone https://github.com/turtlebot/turtlebot_interactions.git`
`$ git clone https://github.com/turtlebot/turtlebot_simulator.git`
- Install dependencies for packages:
`$ sudo apt-get update && sudo apt-get upgrade -y`
`$ sudo apt-get install ros-kinetic-map-server`
`$ sudo apt-get install ros-kinetic-amcl`
`$ sudo apt-get install ros-kinetic-move-base`
`$ sudo apt-get install ros-kinetic-slam-gmapping`

IMPORTANT: always in a new terminal, locate to `$ cd home/workspace/catkin_ws/` and source `$ source devel/setup.bash`.

## 1. SLAM TESTING
To run this first task,
Go to `$ cd workspace/catkin_ws/src/scripts/`
Then, execute the bash file `$ ./test_slam.sh`
With the i,j,l,< keys navigate the robot for SLAM.
### How it works
A map is created by the robot which estimates its position relative to the map.
`test_slam.sh` launches the files:
-`turtlebot_world.launch` for spawning turtle bot in my world.
-`gmapping_demo.launch` for mapping the current world by turtlebot.
-`view_navigation.launch` RViz GUI for visualizing robot's perception.
-`keyboard_teleop.launch` for manually teleoperate the robot.
### NOTE
By default, `turtlebot_world.launch` will launch the turtlebot in the default world, in order to make the turtlebot appear in my own world, I had to change the lines in `turtlebot_simualtor/turtlebot_gazebo/launch/turtlebot_world.launch`:
from `<arg name="world_file" default="$(env TURTLEBOT_GAZEBO_WORLD_FILE)" />`
Into:
 `<arg name="world_file" default="$(find my_robot)/worlds/JGworld.world"/>`

## 2. LOCALIZATION AND NAVIGATION TESTING
To run this second task,
Go to `$ cd workspace/catkin_ws/src/scripts/`
Then, execute the bash file `$ ./test_navigation.sh`
The robot will find its location according to the map generated. And will obey when the user manually determines a 2D navigation goal in RViz by generating a path using the Djikstra algorithm.
### How it works
The robot uses AMCL localization algorithm to estimate its pose relative to the map while reaching a manually set goal in RViz.
`test_navigation.sh` launches the files:
-`turtlebot_world.launch` for spawning turtle bot in my world.
-`amcl_demo.launch` for localization, and path planning.
-`view_navigation.launch` RViz GUI for visualizing robot's perception.
### NOTE
By default, `amcl_demo.launch` will launch the map determined by default world, in order to make the turtlebot know that its in my own map, I had to change the lines in `turtlebot_simualtor/turtlebot_gazebo/launch/amcl_demo.launch`:
from `<arg name="map_file" default="$(env TURTLEBOT_GAZEBO_MAP_FILE)"/>`
Into:
 `<arg name="map_file" default="$(find my_robot)/maps/JGmap.yaml"/>`
which was generated with the `pgm_map_creator` package.
## 3. NAVIGATION GOAL NODE
To run this third task,
Go to `$ cd workspace/catkin_ws/src/scripts/`
Then, execute the bash file `$ ./pick_objects.sh`
The robot will generate the path from its current pose to a goal known as Pick up Point (COLLECT), then the robot will generate a second path to go form teh Pick up Point, to the Drop Off Point (DELIVER).
### How it works
The robot uses AMCL localization algorithm to estimate its pose relative to the map while reaching goals defined in the `pick_objects_node.cpp` node by using the djikstra algorithm.
`pick_objects.sh` launches the files:
-`turtlebot_world.launch` for spawning turtle bot in my world.
-`amcl_demo.launch` for localization, and path planning.
-`view_navigation.launch` RViz GUI for visualizing robot's perception.
-`pick_objects_node` send the Collect and Delivery goals. this node sends the collection goal point, and delivery goal point  to the turtlebot, and confirms with it was succeeded or not, using ROS Actions.

## 4. VIRTUAL OBJECTS
To run this fourth task,
Go to `$ cd workspace/catkin_ws/src/scripts/`
Then, execute the bash file `$ ./add_markers.sh`
First, one marker (green cube) at the collection point will appear in the RViz GUI.
Then, wait for 5 seconds bfore disappearing.
Then, the marker (red cube) will appear again, but at the delivery point.
### How it works
The markers appear thanks to the publsiher `marker_pub`.

`add_markers.sh` launches the files:
-`turtlebot_world.launch` for spawning turtle bot in my world.
-`amcl_demo.launch` for localization, and path planning.
-`view_navigation.launch` RViz GUI for visualizing robot's perception.
-`add_markers_timebase_node` sequence of marker appearing, disappearing, and reappearing.
## Note
There is no turtlebot's movement involved in this task. Just marker's appearance.

## 5. YOUR HOME SERVICE ROBOT
To run this fifth and final task,
Go to `$ cd workspace/catkin_ws/src/scripts/`
Then, execute the bash file `$ ./home_service.sh`
First, the turtlebot will go form the start position to the Collection point, where the marker (green cube) will be waiting for it. Once the turtlebot approaches tot he marker, it disappears (as the obect is collected).
Then, the turtlebot goes to the delivery goal, and then the robot is near to the delivery point, the marker (red cube) reappears (as object delivered). 

### How it works
The markers appear thanks to the node `add_markers.cpp` which is different from the #4 rubric.
The way for knowing when the robot is near the collection/delivery point, I used a "rectangle vs point" approach, where the robot is the point (odom values for position) and teh collection/delivery area is a square surrounding the collection/delivery point.


`home_service.sh` launches the files:
-`turtlebot_world.launch` for spawning turtle bot in my world.
-`amcl_demo.launch` for localization, and path planning.
-`view_navigation.launch` RViz GUI for visualizing robot's perception.
-`add_markers__node` for appearing/disappearing markers when robot is near.
-`pick_objects_node` for sending to the turtlebot the collection and delivery goals.
## Overall Note
I got the error of "plate_simple.stl", but it was solved and continued working by indictions of this post:
https://knowledge.udacity.com/questions/516430

THANK YOU SO MUCH!!

