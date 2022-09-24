#include "ros/ros.h"
#include <std_msgs/String.h>
#include "duckpot_door/Door_controller.h" 


class D_Server
{
private: 
	ros::NodeHandle n_; 
	ros::ServiceServer svr_;
    ros::ServiceServer svr2_;
    static bool status_flag;

public:

	D_Server() 
	{ 
		svr_ = n_.advertiseService("duckpot_open", func);
        svr2_ = n_.advertiseService("duckpot_close", func2);
	} 
	
	static bool func(duckpot_door::Door_controller::Request &req, duckpot_door::Door_controller::Response &res) 
	{
        char* status = "is_opened";
		ROS_INFO_STREAM("Duckpot door" << status);
        // ROS_INFO("status_flag : %d ", status_flag);
		return true;
	}

    static bool func2(duckpot_door::Door_controller::Request &req, duckpot_door::Door_controller::Response &res) 
	{
        char* status = "is_closed";
        // status_flag = false;
		ROS_INFO_STREAM("Duckpot door" << status);
        // ROS_INFO("status_flag : %d ", status_flag);
		return true;
	}
}; 

int main(int argc, char **argv) 
{ 
	ros::init(argc, argv, "duckpot_server"); 
	D_Server s_; 
	ROS_INFO("SERVICE NODE TEST"); 
	ros::spin(); 
	return 0; 
}