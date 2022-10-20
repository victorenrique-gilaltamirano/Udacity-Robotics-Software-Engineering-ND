#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
/* this node will create a green sube in the collection zone, 
	then wait for 5 seconds, disappear it,
	then wait for 5 seconds, appear it in Delivery zone. */
	
	

// COLLECT GOAL at (x=-3.8,y=4.5)
float collect[] = {-3.8,4.5};
//DELIVER GOAL at (x=3.6,y=-1.45)
float deliver[] = {3.6,-1.45};


int main( int argc, char** argv )
{
	ros::init(argc, argv, "add_markers_timebase"); //NODE NAME add_markers_timebase
  //FROM TUTORIAL "RVIZ MARKERS BASIC SHAPES"
  	ros::NodeHandle n;
  	ros::Rate r(1);
  	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

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


	////////////////// CREATE GREEN MARKER AT COLLECTION ZONE //////////////////
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
	marker_pub.publish(marker);
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
	
//////////////// CREATE GREEN MARKER IN DELIVERY ZONE/////////		
		marker.pose.position.x = collect[0];
		marker.pose.position.y = collect[1];
        	marker.color.r = 0.0f; 
  		marker.color.g = 1.0f; //green cube
  		marker.color.b = 0.0f;
  		marker.color.a = 1.0;
		marker.action = visualization_msgs::Marker::ADD; //respawn object in deliver point
		marker_pub.publish(marker);

	///////////////// DELETE MARKER AFTER 5 SECONDS ////////////////////////
		ros::Duration(5.0).sleep();
		marker.action = visualization_msgs::Marker::DELETE;
		marker_pub.publish(marker);
	//////////////// CREATE RED MARKER IN DELIVERY ZONE AFTER 5 SECONDS /////////		
      		ros::Duration(5.0).sleep();
		marker.pose.position.x = deliver[0];
		marker.pose.position.y = deliver[1];
        	marker.color.r = 1.0f; //red cube
  		marker.color.g = 0.0f;
  		marker.color.b = 0.0f;
  		marker.color.a = 1.0;
		marker.action = visualization_msgs::Marker::ADD; //respawn object in deliver point
		marker_pub.publish(marker);
		ros::Duration(5.0).sleep();
		///////////////////// end of sequence //////////////////
		
		
		ros::spinOnce();
	} //end of WHILE ROS OK
	
	return 0;
}// end of int main
