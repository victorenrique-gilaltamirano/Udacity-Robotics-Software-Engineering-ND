#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>


// COLLECT GOAL at (x=-3.8,y=4.5)
float collect[] = {-3.8,4.5};
//DELIVER GOAL at (x=3.6,y=-1.45)
float deliver[] = {3.6,-1.45};

//init current_pose vector
float current_pose[] = {0,0};

// Define callback function for odometry
void get_pose(const nav_msgs::Odometry::ConstPtr& msg) 
{
	current_pose[0] = msg->pose.pose.position.x; //current pose in x
	current_pose[1] = msg->pose.pose.position.y; //current pose in y
} ///End of Get Pose Callback



int main( int argc, char** argv )
{
	ros::init(argc, argv, "add_markers"); //NODE NAME add_markers
  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	ros::NodeHandle n;
  	ros::Rate r(1);
  	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  	// Subscribe to odometry values
  	ros::Subscriber where_am_i = n.subscribe("/odom", 10, get_pose); //get pose from robot from /odom TOPIC 

  	// Set our initial shape type to be a cube //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	uint32_t shape = visualization_msgs::Marker::CUBE;

  	// Initialize marker instance //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	visualization_msgs::Marker marker;

  	// Frame ID name  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	marker.header.frame_id = "map";
  	marker.header.stamp = ros::Time::now();

  	// Set the namespace and id for this marker.  This serves to create a unique ID
  	// Any marker sent with the same namespace and id will overwrite the old one
  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	marker.ns = "basic_shapes";
  	marker.id = 0;

  	// Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	marker.type = shape;

  	// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	marker.action = visualization_msgs::Marker::ADD;

    	// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header 
  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES": respawn marker in collect point
	marker.pose.position.x = collect[0];
  	marker.pose.position.y = collect[1];
  	marker.pose.position.z = 0;
  	marker.pose.orientation.x = 0.0;
  	marker.pose.orientation.y = 0.0;
  	marker.pose.orientation.z = 0.0;
  	marker.pose.orientation.w = 1.0;
  
  	// Set the scale of the marker -- 1x1x1 here means 1m on a side
  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES": make a smaller cube
  	marker.scale.x = 0.3;
  	marker.scale.y = 0.3;
  	marker.scale.z = 0.3;
	
  	// Set the color -- be sure to set alpha to something non-zero!
  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	marker.color.r = 0.0f;
  	marker.color.g = 1.0f; //green cube
  	marker.color.b = 0.0f;
  	marker.color.a = 1.0;
	

	
	marker.lifetime = ros::Duration();   //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
	//FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES": publish the marker
  	while (ros::ok())
  	{
		// Publish the marker
		while (marker_pub.getNumSubscribers() < 1)
		{
			if (!ros::ok())
			{
				return 0;
			}
			ROS_WARN_ONCE("Please create a subscriber to the marker");
			sleep(1);
		} // end of publish the marker
		

	/** sequence to delete cube when robot is near collection point and create again in delivery point **/
   
      float accepted_range = 0.2;
      //if robot is near collection point: disappear green cube
			//dist btw (robotx and collectx) <0.2	and dist btw(roboty and collecty<0.2)
		if((abs(current_pose[0]-collect[0]) < accepted_range)&&(abs(current_pose[1]-collect[1]) < accepted_range))
		{
			marker.action = visualization_msgs::Marker::DELETE;
			ROS_INFO("Cube COLLECTED");
			ROS_INFO("i am at %f, %f",current_pose[0],current_pose[1]);
			ros::Duration(1.0).sleep();
		}
      	//if robot is near delivery point, create red cube
			//dist btw (robotx and deliverx) <0.2	and dist btw(roboty and delivery<0.2)
        	if((abs(current_pose[0]-deliver[0]) < accepted_range)&&(abs(current_pose[1]-deliver[1]) < accepted_range))
		{
			ROS_INFO("i am at %f, %f",current_pose[0],current_pose[1]);
			marker.pose.position.x = deliver[0];
			marker.pose.position.y = deliver[1];
            		marker.color.r = 1.0f; //red cube
  			marker.color.g = 0.0f;
  			marker.color.b = 0.0f;
  			marker.color.a = 1.0;
			marker.action = visualization_msgs::Marker::ADD; //respawn object in deliver point
			ROS_INFO("Cube DROPPED");
			ros::Duration(2.0).sleep();
		}
		///////////////////// end of sequence //////////////////
		marker_pub.publish(marker);
		
		ros::spinOnce();
	} //end of WHILE ROS OK
	
	return 0;
}// end of int main
