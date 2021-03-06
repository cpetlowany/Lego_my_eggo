#include <ros/ros.h>
#include <contact_control.h>
#include <string>
#include <vector>
#include <math.h>
#include <future>
#include <collision_interface/collision_interface.h>
#include <grasp_interface/rs_gripper_interface.h>
#include <netft_utils_lean.h>
#include "stdio.h"
#include "linux/input.h"
#include <sys/stat.h>
#include <std_msgs/Float32.h>
#include <ros/ros.h>
#include <iostream>
#include "sia5_hri_fsm/Handover.h"

class MoveDown
{
public:
  MoveDown(ros::NodeHandle nh);
  ~MoveDown();
  // Action method evaluates commands that have been received and calls appropriate method
  bool initialize();
  void run();
  void cleanup();
  void moveDown();

  bool handover(sia5_hri_fsm::Handover::Request &req,
         sia5_hri_fsm::Handover::Response &res);
  
private:
  // Node handle
  ros::NodeHandle n;                                // ROS node handle
  ros::Subscriber sub_;
  // Move interface
  ContactControl cc;                                // Interface for contact control tasks
  MoveInterface* mi;                                // Interface for Moveit moves
  CollisionInterface* oi;                           // Interface to add objects to planning scene
  RSGripperInterface* gi;                           // Gripper interface
  ros::Publisher markerPub;
  std::vector<double> bowlPos;
  tf::TransformBroadcaster broadcaster;
  tf::TransformListener tf_listener;

  // Gripper functions
  void activateGripper();
  void openGripper();
  void flushInput();
  bool moveWithInput(std::vector<double> joints, std::string name, bool pause = true);
  void closeGripper(bool slow = false);
  void moveToPose(float x, float y, float z,
  float xr, float yr, float zr);
  geometry_msgs::Pose createPose(double x, double y, double z,
    double ww, double xx, double yy, double zz);
  // ROS publisher
  ros::Publisher gripperPub;
  void showArrow(geometry_msgs::PoseStamped tempPose);
  void publishPoseAsTransform(geometry_msgs::PoseStamped tempPose,
    std::string frame_name);

  // Pose class variable
  geometry_msgs::PoseStamped lego_pose_;
};

