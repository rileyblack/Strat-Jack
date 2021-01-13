#pragma once
#include "Hand.h"

#ifndef DEALER_H
#define DEALER_H

/// @brief A class which represents a dealer Object
/// @details creates arepresentation for a dealer in abackjack game
/// the dealer plays against the user,and their hand is compared to 
/// the users,in order to determine a winner (if user does not bust)
///
/// @authors Sam, Michael

class Dealer{
private:
	Hand hand;
public:

	/// @brief Constructor for the Dealer class 
	/// @return a dealer object 
	Dealer();
	
	/// @brief Destructor for the Dealer class, destroys this dealer object when the object goes out of scope
	~Dealer();
	
	
	/// @brief Getter method which returns the private Hand attribute 
	/// @return a Hand object, wich represents this Dealer's Hand of Cards
	Hand getHand();
	
	/// @brief Adds the initial card of a blackjack round to the dealers hand, which is face up
	/// @param faceUpCard represents the card face up throughout the duration of a round that is added to the Dealers Hand attribute
	void addToDealerHand(Card faceUpCard);
	
	/// @brief A function which represents the move "Hit"; to hit is to request another card, given that their current, Hand attribute is lower than 21
	/// @param card represents the new card object which is drawn and pushed onto the Hand attribute
	void hit(Card card);
	
	/// @brief a method which clears the hand attribute and resets it to fits default configuration upon its construction 
	void clearHand();
	
	/// @brief Setter method which resets all attributes of Hand object 
	/// @details Method is used at the end of a round, when the Dealer's hand needs to be reset and 
	/// cleared for the next round 
	///
	void setToDefault();
};

#endif // !DEALER_H


