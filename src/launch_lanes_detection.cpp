#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "lanes_detection.h"

using namespace std;
using namespace cv;


/** @function main */
int main( int argc, char** argv ){
  //*** ROS stuff ***
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);
  int count = 0;


  //* Load video *
  VideoCapture cap( argv[1]); // open the default camera
  if(!cap.isOpened()){  // check if we succeeded
    return -1;
  }

  //* Open video to write *
  /*
  VideoWriter outputVideo;
  outputVideo.open("out.avi", VideoWriter::fourcc('P','I','M','1'), cap.get(CV_CAP_PROP_FPS), Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH), (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT)), true);
  if (!outputVideo.isOpened())
  {
  cout  << "Could not open the output video" << endl;
  return -1;
}
*/


vector<Point> lastOkFittedRight;
vector<Point> lastOkFittedLeft;
vector<Point> lastOkRightRectCenters;
vector<Point> lastOkLeftRectCenters;
vector<Point> lastFittedRight;
vector<Point> lastFittedLeft;
vector<Point2f> perspTransfInPoints;
vector<float> lastOkBetaLeft;
vector<float> lastOkBetaRight;

bool some_left = false;
bool some_right = false;
int left_bad_series = 0;
int right_bad_series = 0;
int right_ok_series = 0;
int left_ok_series = 0;
int right_similar_series = 0;
int left_similar_series = 0;

int counter = 0;


  while (ros::ok()){
    Mat src;
    cap >> src;
    int turn = detectLanes(src,lastOkFittedRight, lastOkFittedLeft, lastOkRightRectCenters, lastOkLeftRectCenters,
                          lastFittedRight, lastFittedLeft, perspTransfInPoints, lastOkBetaLeft, lastOkBetaRight,
                          some_left, some_right, left_bad_series, right_bad_series, right_ok_series,
                          left_ok_series, right_similar_series, left_similar_series, counter);

    //*** ROS send data ***
    std_msgs::String msg;
    std::stringstream ss;

    cout << "turn!!!" << endl;
    ss << turn;


    //ss << "hello world " << count;
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}
