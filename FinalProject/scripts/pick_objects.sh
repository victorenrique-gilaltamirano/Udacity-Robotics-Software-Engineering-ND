#!/bin/sh
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roscore" &
sleep 2
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 2
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 2
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 2
xterm -e " rosrun pick_objects pick_objects_node"
