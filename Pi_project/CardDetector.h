#ifndef CDHEADER_H
#define CDHEADER_H

#include "CameraFeed.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "Card.h"

/// @brief class for recognizing the ranks of captured playing cards
/// @details obtains images encoded into Mat objects, and then finds and extracts
/// the top left corner of the captured image and compares it to local images of 
/// playing cards to determine the strongest match and if the match is sufficiently strong
/// Code Heavily Influenced from github.com/arslanxone/playingCardsDetection/blob/master/BVPoker.cpp
/// 
/// @authors Aaron, Riley

class CardDetector {

private:

	CameraFeed c_feed;

	cv::Rect Corner; //rectangle created by 4 corners
	cv::Mat quad; //quadrilateral created by 4 sides 
	
	/// @brief This function returns the maximum of three doubles
	/// @param number1 first number
	/// @param number2 second number
	/// @param number3 third number
	/// @return largest number of all the arguments passed
	static double maximum(double number1, double number2, double number3);
	
	/// @brief determines if two numbers are within a given threshold
	/// @details This function determines if two numbers are considered to be
	/// "equal enough" to be considered equal in the context of this
	/// program, based on the specified EPSILON value defined above
	///
	/// @param number1 first number
	/// @param number2 second number
	/// @return boolean indicating if arguments are within predefined threshold
	static bool almostEqual(double number1, double number2);
	
	/// @brief determines if two lines intersect
	/// @details This function determines if two lines described 2 sets of 2 points
	/// have an intersection
	///
	/// @param a1 first coordinates first line
	/// @param b1 first coordinates second line
	/// @param a2 second coordinates first line
	/// @param b2 second coordinates second line
	/// @param intersection intersection of lines
	/// @return boolean indicating if the two lines intersect each other
	static bool lineIntersection(const cv::Point2f& a1, const cv::Point2f& b1, const cv::Point2f& a2, const cv::Point2f& b2, cv::Point2f& intersection);
	
	/// @brief structure used to compare norms
	/// @details This function simply works to determine if one vector length is
	/// greater than another vector length
	///
	struct vector_sorter;
	

	/// @brief This function works to align the corners of the cards
	/// @param corners reference to vector of points defining corners which is to be sorted
	void sortCorners(std::vector<cv::Point2f>& corners);
	
	/// @brief compares encoded image to local images to determine a best match, and if the match is sufficiently strong
	/// @details This function works to match captured image to a rank based on which
	/// precaptured rank pictures matches the best
	///
	/// @param rnk encoded image
	/// @return integer value corresponding to one of thirteen different playing card values
	int rankMatcher(cv::Mat rnk);
	
	/// @brief crops encoded image to contain only rank information from topleft corner
	/// @details This function recieves a picture of the rank of the card and then 
	/// further crops the rank photo in such a way that it can be properly
	/// compared to the stock rank photos used to decide similarity.
	/// then returns the value obtained by calling rankMatcher on the cropped image
	///
	/// @param r encoded image
	/// @return rank of encoded image of playing card r
	int standardizeRank(cv::Mat r);
	
	/// @brief isolates rank in image for comparison
	/// @details This function recieves a picture of the top left hand corner of the
	/// card and then isolates the rank icon within this corner, and crops
	/// out the suit because for the game of BlackJack suit is irrelevant. 
	/// This rank picture is then passed to standardizeRank to further process 
	/// image.
	///
	/// @param islo encoded image
	/// @return result of comparison after standardizing the rank
	int getRank(cv::Mat islo);
	
	/// @brief locates top left corner of card in image
	/// @details This function locates the top left hand corner of the card because
	/// this is where the rank (number) resides on the card. This new cropped
	/// picture is also filtered to make rank easier to find. Then getRank is
	/// called to furthar process image.
	///
	/// @param Card encoded image
	/// @return result of comparison after finding regions of intersection
	int getCorner(cv::Mat Card);
	
	/// @brief returns value corresponding to the rank of the card in the image
	/// @details This function works to process the picture taken by the PiCam and 
	/// ultimately returns the value of the card depicted in the picture. 
	/// First, the original photo is processed to more easily find the 
	/// photo contours aka the card edges, where the picture is the cropped
	/// to just be the card, and then sent to getCorner to furthar process
	/// the card to find the rank. 
	///
	/// @param src encoded image
	/// @return value corresponding to card in encoded image
	int getValue(cv::Mat src);

public:
	
	/// @brief constructor for the class
	/// 
	CardDetector();
	
	/// @brief destructor for the class
	///
	~CardDetector();

	/// @brief returns Card object corresponding to that identified
	/// @details This function works to trigger the PiCam to actually take the 
	/// photo of the card on the table. Then, it send the photo to the 
	/// chain of processing functions. If the processing functions do not
	/// find a satisfactory match, then a new photo is taken and the 
	/// process is started again. This process continues until a suitable
	/// match is found.
	///
	/// @return card object consistent with recognized card from image
	Card getErBaud();

};

#endif
