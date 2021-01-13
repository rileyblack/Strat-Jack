#ifndef CAMFEED_H
#define CAMFEED_H


#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

/// @brief class for camera
/// @details object for representing live feed of PiCam and fetching frames
///
/// @author Aaron
class CameraFeed {
	
private:
	
	cv::VideoCapture v_feed;
	cv::Mat frame;
	
public:

	/// @brief initializes camera feed from PiCam
	/// @details starts camera
	///
	void start();
	
	/// @brief get frame from camera feed
	/// @return PiCam frame encoded in a Mat
	cv::Mat read();
	
	/// @brief stop camera feed
	/// @details closes VideoCapture object
	///
	void stop();
};


#endif
