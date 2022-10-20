#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO #1: Request a service and pass the velocities to it to drive the robot
	ball_chaser::DriveToTarget srv;
	
	//storing data into the request
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	//call service and pas teh requested linx and angz
	if(!client.call(srv))
		ROS_ERROR("Failed on calling service /ball_chaser/command_robot");
	//END OF TODO #1
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO #2: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

	bool ball_is_here = false; //flag that ball is here
	int location = 0;
	//steps on 3 by 3, because checking each of the 3 RGB layers (Rp1,Gp1,Bp1),(Rp2,Gp2,Bp2),(Rp3,Gp3,Bp3),...
	for(int i=0; i<img.height*img.width*3; i+=3)
	{
		//image type has codification in RGB, checking for pixel (255,255,255)
		if((img.data[i] == white_pixel) && (img.data[i+1] == white_pixel)&& (img.data[i+2] == white_pixel))
		{
			location = i % img.step; //knowing the x position of the i-th iteration
			if (location < img.step*0.35)
			{
				drive_robot(0.2,0.4); //left
			}
			else if (location < img.step*0.65)
			{
				drive_robot(0.4,0.0); //center
			}
			else
			{
				drive_robot(0.2,-0.4); //right
			}
			ball_is_here = true; // CORRECTION FOR 2nd SUBMISSION -> flag is outside the if's statements
			break;
		}// end if RGB
	}//end FOR	

	if (ball_is_here == false)
		drive_robot(0.0,0.0);
	//END OF TODO #2
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
