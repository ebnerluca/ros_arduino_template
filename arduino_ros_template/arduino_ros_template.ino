/*
 * Author: Luca Ebner
 * Date: November 2019
 */


////// ARDUINO + ROS --- TEMPLATE////
 

#include <ros.h>
#include <std_msgs/String.h>
#include <std_srvs/Trigger.h>


//config
char serviceTopic[] = "arduino_service";
char publisherTopic[] = "arduino_publisher";



// ROS 
ros::NodeHandle nh;

std_msgs::String msg;
ros::Publisher arduinoPublisher(publisherTopic, &msg);

void serviceCallback(const std_srvs::Trigger::Request & request, std_srvs::Trigger::Response & response){
  response.success = true;                          //Note: A bug in the rosserial package results in an error message, saying the service could not be processed.
  response.message = "Service call successful!";    //However, the service works fine and the callback function gets called.
}

ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response> arduinoServer(serviceTopic, &serviceCallback);


void setup(){

  nh.initNode();
  nh.advertise(arduinoPublisher);
  nh.advertiseService(arduinoServer);

  msg.data = "Initialized";
  
}


void loop(){
  
  arduinoPublisher.publish(&msg);
  nh.spinOnce();
  delay(50);
  
}
