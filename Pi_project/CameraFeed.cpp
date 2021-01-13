#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

#include "CameraFeed.h"

using namespace std;
using namespace cv;
	
Mat CameraFeed::read() {
	v_feed.read(frame);
	return frame;
}	

void CameraFeed::start() {
	v_feed.open(0);
	if (!v_feed.isOpened()) { 
		cout << "Camera unsucessfully opened!" << endl;
	}
}

void CameraFeed::stop() {
	v_feed.release();
	if (v_feed.isOpened()) { 
		cout << "Camera unsucessfully closed!" << endl;
	}
}
