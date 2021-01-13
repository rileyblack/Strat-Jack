#pragma once
#include <string>
#include "Hand.h"

#ifndef STRATEGY_H
#define STRATEGY_H

/// @brief Class which determines the approprate strategyon agiven turn
/// during a blakjack game
/// @details Strategy object contains two matrices where each index is a blackjack move,
/// the sum of the User and Dealer hands indicate the approriate x and y index respectively 
/// the appropriate strategy grid is used, depending on if the hand type is a hard total or soft total
///
/// @author Aaron


class Strategy {

private:

	char hardStrategy[9][10] = { 
	{ 'H','D','D','D','D','H','H','H','H','H' },
	{ 'D','D','D','D','D','D','D','D','H','H' },
	{ 'D','D','D','D','D','D','D','D','D','D' },
	{ 'H','H','S','S','S','H','H','H','H','H' },
	{ 'S','S','S','S','S','H','H','H','H','H' },
	{ 'S','S','S','S','S','H','H','H','H','H' },
	{ 'S','S','S','S','S','H','H','H','H','H' },
	{ 'S','S','S','S','S','H','H','H','H','H' },
	{ 'S','S','S','S','S','S','S','S','S','S' } };
	//REMEMBER IF HARD AND 8 OR LESS THEN ALL HITS!!
	//[VALUE-9][VALUE - 2]

	char softStrategy[9][10] = {
	{ 'H','H','H','D','D','H','H','H','H','H' },
	{ 'H','H','H','D','D','H','H','H','H','H' },
	{ 'H','H','H','D','D','H','H','H','H','H' },
	{ 'H','H','D','D','D','H','H','H','H','H' },
	{ 'H','H','D','D','D','H','H','H','H','H' },
	{ 'H','D','D','D','D','H','H','H','H','H' },
	{ 'D','D','D','D','D','S','S','H','H','H' },
	{ 'S','S','S','S','D','S','S','S','S','S' },
	{ 'S','S','S','S','S','S','S','S','S','S' } };
	//[VALUE-9][VALUE - 2]

public:
	
	/// @brief Constructor for the Strategy object 
	/// @details constructon instantiates two 2d arrays, which represent strategy with any
	/// possible combination of cars. one matrix is for reccomendations given it is a soft total,
	/// and the other given that it is a hard total
	///
	/// @return a strategy object 
	Strategy();
	
	/// @brief Destructor for the Strategy object 
	/// @details Destroys object automatically when the object goes out of scope 
	///
	~Strategy();
	
	/// @brief Method which reccomends the best move to make given a players hand, and dealers up card
	/// @details takes into consideration the User and Dealer object's 
	/// hand, and reccomends the best possible to make. It does so by taking the 
	/// total of the User's hand object, and the value of the Dealer's upcard
	/// it then uses these totals and subtracts 9 and 2 repsecitvely in order to find the 
	/// appropriate index in the hard or soft strategy matrix (depending on if User's hand is 
	/// a hard total or soft total)
	///
	/// @return String representing the reccomended move for the user to make at their turn
	std::string recommendation(Hand userHand, Hand dealerHand);
};


#endif //  !STRATEGY_H

