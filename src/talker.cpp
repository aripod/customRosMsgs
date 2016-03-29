#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include <custom/objectsData.h> //package_name/msg
custom::objectsData obj;    //package_name/msg

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n, m;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Publisher chatter_obj = m.advertise<custom::objectsData>("chatter_obj", 10);

  ros::Rate loop_rate(5);   //in Hz.

  int count = 0;
    int x;
  while (ros::ok())
  {

    std_msgs::String msg;

    obj.x = 1;
    obj.y = 2;
    obj.z = 3;
    obj.header.stamp = ros::Time::now();

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);
    chatter_obj.publish(obj);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
