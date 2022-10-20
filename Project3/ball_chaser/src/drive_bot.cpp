#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

/////// TODO #1: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities
bool handle_drive_request_callback(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{
	//variables
	std::vector<float> values = {(float)req.linear_x,(float)req.angular_z};
	ROS_INFO("DriveToTargetRequest Recevied: linear_x = %1.2f angular_z = %1.2f",(float)req.linear_x,(float)req.angular_z);

	//using the geometry Twist message definition
	//creating instance of the variable with definition Twist
	geometry_msgs::Twist motor_command;
	
	//storing data inside the motor_command variable
	motor_command.linear.x = values[0];
	motor_command.angular.z = values[1];

	//publish the data into the robot
	motor_command_publisher.publish(motor_command);


	//response message
	res.msg_feedback = "Robot is moving at linear_x:"+std::to_string(values[0])+" and angular_z:"+std::to_string(values[1]);
	//send feedback to console
	ROS_INFO_STREAM(res.msg_feedback);
	
	return true;
}
///////END OF TODO #1

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO #2: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot",handle_drive_request_callback);
    //END OF TODO #2


    // TODO #3: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
//    while (ros::ok()) {
//        // Create a motor_command object of type geometry_msgs::Twist
//        geometry_msgs::Twist motor_command;
//        // Set wheel velocities, forward [0.5, 0.0]
//        motor_command.linear.x = 0.5;
//        motor_command.angular.z = 0.0;
//        // Publish angles to drive the robot
//        motor_command_publisher.publish(motor_command);
//    }    //END OF TODO #3  (just commented this)

    // TODO #4: Handle ROS communication events (just uncommented)
    ros::spin();

    return 0;
}
