#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
ros::Publisher pub;
sensor_msgs::PointCloud2 pcd_data;
/*void 
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{ 
    // Container for original & filtered data
  pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
  pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  pcl::PCLPointCloud2 cloud_filtered;
    // Convert to PCL data type
  pcl_conversions::toPCL(*cloud_msg, *cloud);

  // Perform the actual filtering
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
  sor.setInputCloud (cloudPtr);
  sor.setLeafSize (0.1, 0.1, 0.1);
  sor.filter (cloud_filtered);

    // Convert to ROS data type
  sensor_msgs::PointCloud2 output;
  pcl_conversions::fromPCL(cloud_filtered, output);
  
  // Publish the data.
  pub.publish (output);

}*/

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "pub_a_pcd_data");
  ros::NodeHandle nh;
  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("pcd_data", 1);
	
  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());
    ros::Rate loop_rate(50);
  while(ros::ok())
  {
  // Fill in the cloud data
  pcl::PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read ("/home/cby/motion_planning/motion_planning_ws/src/my_pcl_tutorial/pcd_files/table_scene_lms400.pcd", *cloud); // Remember to download the file first!
  //sensor_msgs::PointCloud2 pcd_data;
  pcl_conversions::fromPCL(*cloud, pcd_data);
  pcd_data.header.frame_id = "odom1";
  pub.publish (pcd_data);
  // Spin
  loop_rate.sleep();
  }
      return 0;
}
/*
#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include<pcl_conversions/pcl_conversions.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl/io/pcd_io.h>//which contains the required definitions to load and store point clouds to PCD and other file formats.
 
main (int argc, char **argv)
{
  ros::init (argc, argv, "UandBdetect");
  ros::NodeHandle nh;
  ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_output1", 1);
  pcl::PointCloud<pcl::PointXYZ> cloud;
  sensor_msgs::PointCloud2 output;
  pcl::io::loadPCDFile ("/home/cby/motion_planning/motion_planning_ws/src/my_pcl_tutorial/pcd_files/table_scene_lms400.pcd", cloud);
  //Convert the cloud to ROS message
  pcl::toROSMsg(cloud, output);
  output.header.frame_id = "odom1";//this has been done in order to be able to visualize our PointCloud2 message on the RViz visualizer
  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    pcl_pub.publish(output);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}*/

