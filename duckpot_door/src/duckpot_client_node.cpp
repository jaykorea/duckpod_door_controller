#include "ros/ros.h" 
#include "duckpot_door/Door_controller.h"
#include <thread>
#include <string>

using std::this_thread::sleep_for;
using namespace std;

constexpr int TIME_TO_SLEEP = 50;
class D_Client 
{ 
private: 
	ros::NodeHandle n_; 
	ros::ServiceClient clt_;
	ros::ServiceClient clt2_;  
	
public: 
	D_Client() 
	{ 
		clt_ = n_.serviceClient<duckpot_door::Door_controller>("duckpot_door_open");
		clt2_ = n_.serviceClient<duckpot_door::Door_controller>("duckpot_door_close");  
	} 
	
	void duckpot_open_cb(duckpot_door::Door_controller &srv) 
	{ 
		clt_.call(srv); 
	}
	void duckpot_close_cb(duckpot_door::Door_controller &srv) 
	{ 
		clt2_.call(srv); 
	}  
}; 

int main(int argc, char **argv) 
{ 

	ros::init(argc, argv, "service_client");
    if (argc != 2)
	{
    	ROS_INFO("Cmd Example: rosrun duckpot_door duckpot_client_node 'door_open' or 'door_close'");
    	return 1;
    } 
	D_Client c_; 
	duckpot_door::Door_controller srv; 
	
	if ((strcmp(argv[1], "door_open"))==0)
	{
		c_.duckpot_open_cb(srv);
		ROS_INFO("Duckpot door opened");
		sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
	}

	else if ((strcmp(argv[1], "door_close"))==0)
	{
		c_.duckpot_close_cb(srv);
		ROS_INFO("Duckpot door closed");
		sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
	}

	return 0; 
}