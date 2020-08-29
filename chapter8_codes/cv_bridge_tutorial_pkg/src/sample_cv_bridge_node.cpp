#include <ros/ros.h>
#include <ros/time.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/thread.hpp>

static const std::string OPENCV_WINDOW = "Raw Image Window";
static const std::string OPENCV_WINDOW_1 = "Edge Detection";
static boost::once_flag cv_thread_flag = BOOST_ONCE_INIT;
static const double IMG_SUB_WAIT = 2.0;

static void startWindowThreadLocal()
{
  cv::startWindowThread();
}

class EdgeDetector
{
public:
  EdgeDetector() : it_(nh_)
  {
    image_sub_ = it_.subscribe("/image_raw", 1, &EdgeDetector::imageCB, this);
    image_pub_ = it_.advertise("/edge_detector/raw_image", 1);
    boost::call_once(&startWindowThreadLocal, cv_thread_flag);
    cv::namedWindow(OPENCV_WINDOW);
    img_sub_time_ = ros::Time::now().toSec();
  }

  ~EdgeDetector()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCB(const sensor_msgs::ImageConstPtr& msg)
  {
    ROS_INFO("imageCB");
    cv_bridge::CvImagePtr cv_ptr;
    double cur_time = ros::Time::now().toSec();

    namespace enc = sensor_msgs::image_encodings;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, enc::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    if (cv_ptr->image.rows > 0 and cv_ptr->image.cols > 0)
    {
      DetectEdges(cv_ptr->image);
      image_pub_.publish(cv_ptr->toImageMsg());
      img_sub_time_ = cur_time;
    }
    else if (IMG_SUB_WAIT <= cur_time - img_sub_time_)
    {
      cv::destroyAllWindows();
      ros::shutdown();
      return;
    }
  }

  void DetectEdges(cv::Mat img)
  {
    cv::Mat src, src_gray;
    cv::Mat dst, detected_edges;

    const int edgeThresh = 1;
    const int lowThresh = 200;
    const int highThresh = 300;
    const int kernelSize = 5;

    img.copyTo(src);

    cv::cvtColor(img, src_gray, CV_BGR2GRAY);
    cv::blur(src_gray, detected_edges, cv::Size(5, 5));
    cv::Canny(detected_edges, detected_edges, lowThresh, highThresh, kernelSize);

    dst = cv::Scalar::all(0);
    img.copyTo(dst, detected_edges);
    dst.copyTo(img);

    cv::imshow(OPENCV_WINDOW, src);
    cv::imshow(OPENCV_WINDOW_1, dst);
    cv::waitKey(3);
  }

private:
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  double img_sub_time_;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "EdgeDetector");
  EdgeDetector ic;
  ros::spin();
  return 0;
}
