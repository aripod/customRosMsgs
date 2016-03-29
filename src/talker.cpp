#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include <custom/objectsData.h> //package_name/msg
custom::objectsData obj;    //package_name/msg

#include <custom/objectsArray.h> //package_name/msg
custom::objectsArray array;    //package_name/msg

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Publisher array_pub = n.advertise<custom::objectsArray>("array", 100);

  ros::Rate loop_rate(2);   //in Hz.

  int count = 0, i, size = 2;
  array.object.resize(size);

  while (ros::ok())
  {

    std_msgs::String msg;

    /*obj.x = 1;
    obj.y = 2;
    obj.z = 3;
    array.object.push_back(obj);*/
    for(i=0; i<size; i++)
    {
        array.object[i].x = count*1;
        array.object[i].y = count*2;
        array.object[i].z = count*3;
    }
    array.header.stamp = ros::Time::now();

    if(count == 10)
    {
        size += 2;
        array.object.resize(size);
    }

    if(count == 20)
    {
        size -= 2;
        array.object.resize(size);
    }

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);
    array_pub.publish(array);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
