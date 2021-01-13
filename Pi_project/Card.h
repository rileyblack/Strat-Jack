#pragma once
//
// Created by Sam Silverstein on 2019-10-27.
//

#ifndef CARD_H
#define CARD_H

#include <string>

/// @brief class for representing a playing card
/// @details object containing attributes on the rank of a card
///
/// @author Sam

class Card {
private:
	int name;
	int rank;

public:

	/// @brief default Constructor for the Card object 
	/// @return a Card object 
	Card();

	/// @brief Constructor for the Card Object
	/// @param val represents the initialized rank of this Card obect 
	/// @return a Card object 
	Card(int val, int name);


	/// @brief Destructor for the Card object 
	/// @details Destroys the object when it goes out of scope 
	///
	~Card();
	
	/// @brief gets the name of the card
	/// @return the name of the card as a string
	std::string getName();
	
	/// @brief Getter method which gets the private rank attribute of this Card object 
	/// @return an Integer representing the rank of this Card object 
	int getRank();

	/// @brief Setter method which can change the rank of this Card object 
	/// @details this method is in the event of it needing to be changed (like with an ace from 11 to 1)
	/// 
	/// @param rank represents the new rank 
	void setRank(int rank);
};


#endif // !CARD_H
