#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>
sensor_msgs::PointCloud2 depth_point;
sensor_msgs::Image depth_image;
using std::cout;
using std::endl;
void depthCallback(const sensor_msgs::PointCloud2& msg)
{
    depth_point = msg;
    cout<<"blala"<<endl;
    for (int i = 0; i < 32; i++)
        cout << (int)msg.data[i] << endl;
    cout << ((float*)msg.data.data())[0 * 8 + 0] << " " << ((float*)msg.data.data())[0 * 8 + 1] << " " << ((float*)msg.data.data())[0 * 8 + 2] << endl;
    cout << ((float*)msg.data.data())[1000 * 8 + 0] << " " << ((float*)msg.data.data())[1000 * 8 + 1] << " " << ((float*)msg.data.data())[1000 * 8 + 2] << endl;
}
void imageCallback(const sensor_msgs::Image& msg)
{
    depth_image = msg;
    cout << ((float*)depth_image.data.data())[0] << " " << endl;
    cout << ((float*)depth_image.data.data())[1000] << " " << endl;
}
int main(int argc, char* argv[])
{
    ros::init(argc, argv, "listenerforgazebo");
    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe("/camera/depth/points", 10, &depthCallback);
    ros::Subscriber sub2 = node.subscribe("/camera/depth_registered/image_raw", 10, &imageCallback);
    ros::spin();
    return 0;
}
