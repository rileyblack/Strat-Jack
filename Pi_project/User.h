#pragma once

#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include "Hand.h"

/// @brief Class which represents the User during a blackack game who interacts with the system
/// @details A user object is used to represent a player of the game, containing methods and atributes 
/// for modifying and maniulating the user's hand and currency
///
/// @author Riley

class User{

private:
	int balance;
	std::string name;
	Hand hand;

public:

	/// @brief default Constructor for the User object 
	/// @return a new User object
	/// @authors  Sam, Aaron
	User();
	
	/// @brief Constructor for the User object 
	/// @param username represents the Username attribute of the User object 
	/// @param balance is an integer which represents the balance that the user will begin with at the beginning of their session
	/// @author Riley, Michael
	User(std::string username, int balance);
	
	/// @brief Destructor for the User object 
	/// @details destroys the instance of this User object, once the object goes out of the scope 
	///
	/// @author Riley, Michael
	~User();
	
	/// @brief Getter method which returns the private Hand attribute 
	/// @return Hand object, wich represents this User's Hand of Cards
	/// @author Riley, Michael
	Hand getHand();
	
	/// @brief Getter method which allows access to the private balance attribute 
	/// @return integer representing the current balance of this User object 
	/// @author Riley, Michael
	int getBalance();
	
	/// @brief Getter method which allows access to the private name attribute 
	/// @return a string representing the username this User object 
	/// @author Riley
	std::string getName();
	
	/// @brief Setter method which changes the value of this User's balance 
	/// @details Invoked after a blackjack round, increases if the User won their bet, decreases by that amount otherwise 
	///
	/// @author Michael
	void setBalance(int amount);
	
	/// @brief Adds the initial two cards of a blackjack round to the User's hand 
	/// @details indicates the first card tha the Dealer draws at the beginning of the round 
	///
	/// @param card1 represents the first card which is traditionally face up throughout the durationod a round 
	/// @param card2 represents the second face up card for the initial User's hand
	/// @author Riley
	void addToUserHand(Card card1, Card card2);
	
	/// @brief function which represents the move "Hit" in a Blackjack round
	/// @details To hit is to request another card, given that their current Hand attribute is lower than 21
	///
	/// @param card represents the new card object which is drawn and pushed onto the Hand attribute
	/// @author Riley, Michael
	void hit(Card card);
	
	/// @brief method which represents the move "Stay" in a blackjack round 
	/// @details To stand is to request that the user's turn is over, and control is given to the dealer to deal their cards to determine a winner
	///
	/// @author Riley, Michael
	void stand();
	
	/// @brief method which represents the move "Double Down in a backjack round"
	/// @details To double down is to do a hit and also double the user's bet for the current round of blackjack
	///
	/// @param bet represents the integer of the users current bet, which will doubled and updated accodringly 
	/// @param card represents the card which will be drawn from the "hit" portion of a double down move 
	/// @author Sam, Aaron
	void doubleDown(Card card);
	
	/// @brief method which clears the hand attribute and resets it to its default configuration upon its construction 
	/// @author  Sam, Aaron
	void clearHand();
	
	/// @brief Setter method which resets all attributes of Hand object 
	/// @details Method is used at the end of a round, when the User's hand needs to be reset and 
	/// cleared for the next round 
	///
	void setToDefault();

};

#endif // !USER_H
