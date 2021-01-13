#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "CardDetector.h"
#include "CameraFeed.h"

#include <iostream>
#include <vector>
#include <algorithm>

#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

const double EPSILON = 1e-5;

const int IM_WIDTH = 1280; //default image width
const int IM_HEIGHT = 720; //default image height

const int CORNER_WIDTH = 27; //cropped top lefthand corner image width
const int CORNER_HEIGHT = 75; //cropped top lefthand corner image height

int RANK_WIDTH = 70; //cropped rank (number) image width
int RANK_HEIGHT = 125; //cropped rank (number) image height


double CardDetector::maximum(double number1, double number2, double number3) {
	return std::max(std::max(number1, number2), number3);
}

bool CardDetector::almostEqual(double number1, double number2) {
	return (std::abs(number1 - number2) <= (EPSILON * maximum(1.0, std::abs(number1), std::abs(number2))));
}

bool CardDetector::lineIntersection(const cv::Point2f& a1, const cv::Point2f& b1, const cv::Point2f& a2, const cv::Point2f& b2, cv::Point2f& intersection) {
	double A1 = b1.y - a1.y; //vertical line length of line 1
	double B1 = a1.x - b1.x; //horizontal line length of line 1
	double C1 = (a1.x * A1) + (a1.y * B1); //needed for determinant

	double A2 = b2.y - a2.y; //vertical line length of line 2
	double B2 = a2.x - b2.x; //horizontal line length of line 2
	double C2 = (a2.x * A2) + (a2.y * B2); //needed for determinant

	double det = (A1 * B2) - (A2 * B1); //calculate determinant

	if (!almostEqual(det, 0)) { //if the determinant is not (close to) 0
		//then intersection exists, find x, y intersection coordinates
		intersection.x = static_cast<float>(((C1 * B2) - (C2 * B1)) / (det));
		intersection.y = static_cast<float>(((C2 * A1) - (C1 * A2)) / (det));

		return true;
	}
	//if determinant is close to zero, no intersection exists
	return false;
}

struct CardDetector::vector_sorter {
	bool operator ()(const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
		double dist_a = norm(a[0] - a[1]); //compute normal distance of a
		double dist_b = norm(b[0] - b[1]); //compute normal distance of b
		return dist_a > dist_b; //compare 
	}
};

void CardDetector::sortCorners(std::vector<cv::Point2f>& corners) {
	std::vector<cv::Point2f> top, bot; //vectors of points for top and bottom
	cv::Point2f center; //center point

	// loop to calculate the center based on four corners
	for (int i = 0; i < corners.size(); i++) { //for each corner
		center += corners[i]; //add each corner value
	}
	center *= (1. / corners.size()); //divide by number of corners (average)

	//organize points into top and bottom vectors
	for (int i = 0; i < corners.size(); i++) { //for each corner
		if (corners[i].y < center.y) { //if corner y value is less (more)
									 //then the centre y, add to top
			top.push_back(corners[i]);
		}
		else {//othewise, add to bottom
			bot.push_back(corners[i]);
		}
	}
	corners.clear();

	if (top.size() == 2 && bot.size() == 2) { //if we have proper rectangle (2 top corners, 2 bottom corners)
		cv::Point2f tl = top[0].x > top[1].x ? top[1] : top[0]; //find top left
		cv::Point2f tr = top[0].x > top[1].x ? top[0] : top[1]; //find top right
		cv::Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0]; //find bottom left
		cv::Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1]; //find bottom right

		corners.push_back(tl); //add top left to 4 corner vector
		corners.push_back(tr); //add top right to 4 corner vector
		corners.push_back(br); //add bottom right to 4 corner vector
		corners.push_back(bl); //add bottom left to 4 corner vector
	}
}

int CardDetector::rankMatcher(Mat rnk) {
	Mat img; //image of precaptured rank picture being compared
	Mat dst; //image of contrasted picture (contrast between rank pic and our pic)
	int qualities[13]; //array to hold the quality of match to each rank
	int minindex = 0; //index of the best match

	//array of strings of location of precaptured rank pictures
	string file[] = { "/home/pi/Desktop/test/Card_Imgs/Ranks/2.jpg","/home/pi/Desktop/test/Card_Imgs/Ranks/3.jpg" ,"/home/pi/Desktop/test/Card_Imgs/Ranks/4.jpg" , "/home/pi/Desktop/test/Card_Imgs/Ranks/5.jpg" ,
		"/home/pi/Desktop/test/Card_Imgs/Ranks/6.jpg" , "/home/pi/Desktop/test/Card_Imgs/Ranks/7.jpg" , "/home/pi/Desktop/test/Card_Imgs/Ranks/8.jpg" ,
		"/home/pi/Desktop/test/Card_Imgs/Ranks/9.jpg" , "/home/pi/Desktop/test/Card_Imgs/Ranks/10.jpg" , "/home/pi/Desktop/test/Card_Imgs/Ranks/jack.jpg" ,
		"/home/pi/Desktop/test/Card_Imgs/Ranks/queen.jpg" , "/home/pi/Desktop/test/Card_Imgs/Ranks/king.jpg" , "/home/pi/Desktop/test/Card_Imgs/Ranks/ace.jpg" };

	for (int i = 0; i < 13; i++) { //for each rank
		int match_quality = 0; //match quality of current rank picture
		img = imread(file[i]); //load picture of current rank being compared
		cvtColor(img, img, COLOR_BGR2GRAY); //convert to black and white
		img = img > 120;

		resize(img, img, Size(RANK_WIDTH, RANK_HEIGHT)); //resizing based on defined constants

		absdiff(img, rnk, dst); //contrast our image and rank image, store in dst picture

		//for each pixel in dst picture
		for (int y = 0; y < dst.rows; y++) { //for each row
			for (int x = 0; x < dst.cols; x++) { //for each column
				if (dst.at<uchar>(y, x) == 255) { //if pixel is white
					match_quality++; //rank picture and our picture match
				}					 //for this pixel, so increase match 
			} 						 //quality
		}
		qualities[i] = match_quality; //put match quality in proper index
		//cout << "Match Quality with " << i+1 << ": " << match_quality << endl;
	}
	int min = qualities[0]; //begin by assuming minimum is first rank

	for (int j = 0; j < 13; j++) { //for each rank
		if (qualities[j] < min) { //if current rank is less than minimum
			min = qualities[j]; //new minimum is current 
			minindex = j; //save index of minimum
		}
	}
	minindex += 1; //change from index actual value (ie. index 0 to position 1)
	if (min > 1500) {
		minindex = -1;
	}
	return minindex; //return index of the best match 
}

int CardDetector::standardizeRank(Mat r) {
	vector<vector<Point> > r_cnts; //contour for ranks (vector of points)

	Rect r_boundbox; //rectangle bounding the rank

	Mat r_copy = r.clone(); //create copy of picture to manipulate

	//locate the contours 
	findContours(r_copy, r_cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	//sort rank contours
	sort(r_cnts.begin(), r_cnts.end(), [](const vector<Point>& c1, const vector<Point>& c2) {return contourArea(c1, false) < contourArea(c2, false); });

	//create bounding rectangle based on rank contours
	r_boundbox = boundingRect(r_cnts[r_cnts.size() - 1]);

	Mat rr; //photo of ROI (top left corner cropped)

	rr = r(r_boundbox); //populate rr photo based on bounding rectangle

	resize(rr, rr, Size(RANK_WIDTH, RANK_HEIGHT)); //resize based on defined dimensions
	//cout << "Test2" << endl;
	//imshow(" ", rr);
	//if (waitKey(0) >= 0)  {}
	//cout << "Test2 complete" << endl;
	//not sure if you can do this because if picture is bad then rr cannot be created

	int rnk_ID = rankMatcher(rr); //retrieve rank from ROI (top left corner cropped)

	return rnk_ID;
}

int CardDetector::getRank(Mat islo) {
	Rect rank; //rectangle created for top left hand quarter
	rank.x = 10; rank.y = 10; //starting anchor corner of rectangle
	rank.height = 175; //rectangle height was at 150
	rank.width = 92; //rectangle width
	Mat rnk; //cropped picture of top left hand corner

	rnk = islo(rank); //populate picture
	//cout << "Test3" << endl;
	//imshow(" ", rnk);
	//if (waitKey(0) >= 0)  {}
	//cout << "Test3 complete" << endl;
	return standardizeRank(rnk); //send to findROI for furthar cropping
}

int CardDetector::getCorner(Mat Card) {
	Corner.x = 5; //top left hand corner of card x coordinate 
	Corner.y = 2; //top left hand corner of card y coordinate 
	Corner.width = CORNER_WIDTH; //width of cropped corner section
	Corner.height = CORNER_HEIGHT; //height of cropped corner section
	rectangle(Card, Corner, Scalar(0, 0, 255), 1, 8); //create rectangle of specified size
	Mat ROI = Card(Corner); //create cropped picture 
	cvtColor(ROI, ROI, COLOR_BGR2GRAY); //convert to black and white
	resize(ROI, ROI, Size((ROI.cols * 4), (ROI.rows * 4))); //resize
	GaussianBlur(ROI, ROI, Size(5, 5), 0); //blur distinct contours
	threshold(ROI, ROI, 155, 255, THRESH_BINARY_INV); //saturate contours
	//cout << "Test4" << endl;
	//imshow(" ", ROI);
	//if (waitKey(0) >= 0)  {}
	//cout << "Test4 complete" << endl;
	return getRank(ROI); //send to isolation for further cropping
}

int CardDetector::getValue(Mat src) {

	Mat edges; //photo of "edges" of picture
	if (src.empty()) {//check if photo exists
		src = Mat(400, 400, CV_8UC3, Scalar(127, 127, 127));
		rectangle(src, Rect(20, 200, 150, 50), Scalar(0, 0, 255), 8);
		rectangle(src, Rect(200, 200, 50, 50), Scalar(0, 0, 255), 8);
	}

	resize(src, src, Size(IM_WIDTH, IM_HEIGHT)); //resize to specified standard

	cvtColor(src, edges, COLOR_BGR2GRAY); //make black and white
	GaussianBlur(edges, edges, Size(5, 5), 1.5, 1.5); //blur prominent contours

	erode(edges, edges, Mat());  //erode edges
	dilate(edges, edges, Mat()); //dilate edges
	dilate(edges, edges, Mat()); //dilate edges
	erode(edges, edges, Mat()); //erode edges

	Canny(edges, edges, 50, 150, 3); //canny edges

	//cv::waitKey(1); //postpone

	vector<Point> selected_points; //contour of interest
	vector<vector<Point> > contours; //vector of contours where each contour
									 //is a vector of points

	findContours(edges, contours, RETR_LIST, CHAIN_APPROX_SIMPLE); //locate contours of photo

	for (size_t i = 0; i < contours.size(); i++) { //for each contour
		Rect minRect = boundingRect(contours[i]); //create rectangle for contour

		//check if contour rectangle is of expected size 
		if ((minRect.width > src.cols / 6) | (minRect.height > src.rows / 6)) {
			//if expected size, select this contour
			selected_points.insert(selected_points.end(), contours[i].begin(), contours[i].end());
		}
	}
	//convert selected contour to 32F form
	vector<Point2f> selected_points_f;
	vector<Point2f> corners;
	Mat(selected_points).convertTo(selected_points_f, CV_32F);

	//hull photo
	Mat hull;
	convexHull(selected_points_f, hull, true, true);

	RotatedRect RRect = minAreaRect(hull); //rectangle representing card
	std::vector<cv::Point2f> RR_corners; //rectangle corners as vector of points
	Point2f four_points[4];
	RRect.points(four_points);
	RR_corners.push_back(four_points[0]);
	RR_corners.push_back(four_points[1]);
	RR_corners.push_back(four_points[2]);
	RR_corners.push_back(four_points[3]);

	for (int j = 0; j < 4; j++) { //for each point in rectangle
		//compute distance from hull to corner
		Point2f pt = RR_corners[j];
		Point2f nearest_pt = hull.at<Point2f>(j, 0);
		float dist = norm(pt - nearest_pt);

		//finding nearest point to hull
		for (int k = 1; k < hull.rows; k++) { //for each row in hull
			Point2f hull_point = hull.at<Point2f>(k, 0);
			if (norm(pt - hull_point) < dist) { //if current point is closer than closest
				dist = norm(pt - hull_point);
				nearest_pt = hull_point; //current is now nearest
			}
		}
		corners.push_back(nearest_pt); //add to vector
	}
	sortCorners(corners); //organize corners in CW order

	Mat(corners).convertTo(selected_points, CV_32S); //convert to 32F form

	Rect r = boundingRect(corners); //create card bounding rectangle

	//create quadrilateral based on corners
	quad = cv::Mat::zeros(norm(corners[1] - corners[2]), norm(corners[2] - corners[3]), CV_8UC3);

	std::vector<cv::Point2f> quad_pts;
	quad_pts.push_back(cv::Point2f(0, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
	quad_pts.push_back(cv::Point2f(0, quad.rows));

	cv::Mat transmtx = cv::getPerspectiveTransform(corners, quad_pts);
	cv::warpPerspective(src, quad, transmtx, quad.size());

	//resize to defined standard card size
	resize(quad, quad, Size(200, 300));
	//cout << "Test5" << endl;
	//imshow(" ", quad);
	//if (waitKey(0) >= 0)  {}
	//cout << "Test5 complete" << endl;
	return getCorner(quad); //send to getCorner to zoom in on corner
}

CardDetector::CardDetector() {}

CardDetector::~CardDetector() {}

Card CardDetector::getErBaud() {
	cout << "Enter 'r' to read card: ";
	char read;
	cin >> read;
	while (read != 'r') {
		cout << endl << "Invalid. Enter 'r' to read card: " << endl;
		cin >> read;
	}
	
	int value = -1;
	while (value == -1) {
		c_feed.start();
		//cout << "Getting new pic... \n" << endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		Mat picture = c_feed.read();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//cout << "Test1" << endl;
		//imshow(" ", picture);
		//if (waitKey(0) >= 0)  {}
		//cout << "Test1 complete" << endl;
		value = getValue(picture);
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		c_feed.stop();
	}
	int card_value = 0; //value of card in blackjack based on rank found 
	if (value < 9) { //if rank is from 2-9, the value is simply the rank of card
		card_value = value + 1; //+1 because index 1 represents 2 and so on
	}
	else if (value == 13) { //if rank is an ace, default value of 11
		card_value = 11;
	}
	else { //if rank is 10-king, all have value of 10
		card_value = 10;
	}
	Card card(card_value, value);
	return card;
}
