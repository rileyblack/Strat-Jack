#pragma once

#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

/// @brief class which represents the playing hand of a player during a blackjack game
/// @details a hand reprsents the collection of card objects a player holds, which determines 
/// their sum, indicating the appropriate move to make during a blackjack game
///
/// @authors Sam, Michael

class Hand {
private:
	std::vector<Card> hand;
	int sum;
	int numberOfCards;
	bool hard;
	
public:

	/// @brief Constructor for the Hand object 
	/// @return a new instance of a Hand object
	Hand();
	
	/// @brief Destructor for the Hand object 
	/// @details Destroys this instance of a hand object when its existence exits its scope 
	///
	~Hand();
	
	/// @brief Getter method which gets the sum of all card ranks in hand 
	/// @details iterates through vector of cards, and sums up each rank
	///
	/// @return an integer representing a sum of all ranks
	int getSum();
	
	/// @brief Getter method which returns the number of card objects this hand object
	/// @return an integer representing the total number of cards in this Hand object 
	int getNumOfCards();
	
	/// @brief Boolean method which determines if this Hand object is Hard,
	/// @details true if it is hard, meaning that it contains an ace 
	/// which cannot be an 11, otherwise return false if it is soft, 
	/// meaning that it contains an ace which can be 1 or 11
	///
	/// @return true or false, if is hard total or not 
	bool isHard();
	
	/// @brief Setter method which resets all attributes of Hand object 
	/// @details Method is used at the end of a round, when the hand needs to be reset and 
	/// cleared for the next round 
	///
	void setToDefault();
	
	/// @brief Method which adds a card object to the hand private attribute
	/// @details Pushes Card object onto its existing vector of Card object
	///
	/// @param card represents the Card object to be pushed onto the hand vector
	void addCard(Card card);
	
	/// @brief Method which clears the hand vector attribute 
	/// @details Empties only the "hand" attribute by clearing the vectors
	///
	void clearCards();
};


#endif //  !HAND_H
