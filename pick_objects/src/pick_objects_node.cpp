#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


// COLLECT GOAL at (x=-3.8,y=4.5)
float collect[] = {-3.8,4.5};
//DELIVER GOAL at (x=3.6,y=-1.45)
float deliver[] = {3.6,-1.45};

void move_robot_to(MoveBaseClient & ac,float x, float y)
{
	move_base_msgs::MoveBaseGoal goal;
	
	// set up the frame parameters
	goal.target_pose.header.frame_id = "map";  //CHANGED frame_id to MAP
	goal.target_pose.header.stamp = ros::Time::now();

	// Define a position and orientation for the robot to reach PICK UP GOAL
	goal.target_pose.pose.position.x = x;
	goal.target_pose.pose.position.y = y;
	goal.target_pose.pose.orientation.w = 1.0; //QUATERNION
	
	// Send the goal position and orientation for the robot to reach
	ROS_INFO("Sending goal");
	ac.sendGoal(goal);
	
	// Wait an infinite time for the results
	ac.waitForResult();
	
	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		ROS_INFO("Goal reached");
	}
	else
	{
		ROS_INFO("Fail to reach the goal");
	}
}


int main(int argc, char** argv)
{
  	// Initialize the simple_navigation_goals node /NODE NAME CHANGED
  	ros::init(argc, argv, "pick_objects");
	
	MoveBaseClient ac("move_base", true);
	
	// Wait 5 sec for move_base action server to come up
	while(!ac.waitForServer(ros::Duration(5.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	
	
	
	//move robot to collection point
	move_robot_to(ac,collect[0],collect[1]);
	//wait 5 secs
	ros::Duration(5).sleep(); //WAIT 5 secs after reaching
	//move robot to delivery point if collected
	if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		move_robot_to(ac,deliver[0],deliver[1]);
	}
	
	
	return 0;
}
