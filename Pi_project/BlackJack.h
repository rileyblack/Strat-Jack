#pragma once

#include "User.h"
#include "Dealer.h"
#include "Strategy.h"

#ifndef BLACK_JACK_H
#define BLACK_JACK_H

/// @brief Class to represent a game of blackjack
/// @details contains all internal logic implemented in methods required for playing
/// a game of blackjack
/// @authors Mike, Sam
class BlackJack {

private:
	Strategy strat;
	Dealer dealer;
	User user;
	bool inGame;	

public:

	/// @brief Constructor for the BlackJack object 
	/// @return a new User object
	BlackJack();
	
	/// @brief Destructor for the BlackJack object 
	/// @details destroys the instance of this BlackJack object, once the object goes out of the scope 
	~BlackJack();
	
	/// @brief Constructor for the BlackJack object 
	/// @param username represents the identity of the User for the BlackJack game  
	/// @param balance is an integer which represents the balance that the user will begin with at the beginning of the BlackJack
	BlackJack(std::string username, int balance);
	
	/// @brief Boolean Method which determined if BlackJack object is in game or not 
	/// @details if the blackjack game is in session, then it is true, determining if a game is in session
	/// @return true if there is a current BlackJack game in session
	bool getInGame();
	
	/// @brief Getter method which returns the Dealer object form BlackJack game 
	/// @return Dealer object from this BlackJack object 
	Dealer getDealer();
	
	/// @brief Getter method which returns the User object form BlackJack game 
	/// @return User object from this BlackJack object 
	User getUser();
	
	/// @brief Getter method which returns the Strategy object form BlackJack game 
	/// @return Strategy object from this BlackJack object 
	Strategy getStrategy();
	
	/// @brief Setter method which changes the boolean attribute inGame 
	/// @details This is used to switch the BlackJack object to being in a game (at the beginning of a session)
	/// or at the !inGame (if the session is over, or before session has begun)
	/// @param choice represensts the boolean value determining if BlackJack is in game or not 
	void setInGame(bool choice);
	
	/// @brief Adds the initial card of a blackjack round to the dealer attribute's hand, which is face up
	/// @param faceUpCard represents the card face up throughout the duration of a round that is added to the Dealers Hand attribute
	void setDealerHand(Card faceUpCard);
	
	/// @brief Adds the initial two cards of a blackjack round to the User attribute's hand 
	/// @details indicates the first card tha the Dealer draws at the beginning of the round 
	/// @param card1 represents the first card which is traditionally face up throughout the durationod a round 
	/// @param card1 represents the second face up card for the initial User's hand
	void setUserHand(Card card1, Card card2);
	
	/// @brief Setter method which changes the value of Use attribute's balance 
	/// @details Invoked after a blackjack round, increases if the User won their bet, decreases by that amount otherwise 
	void setUserBalance(int amount);
	
	/// @brief function which represents the move "Hit" for User attribute in a Blackjack round
	/// @details To hit is to request another card, given that their current Hand attribute is lower than 21
	/// @param card represents the new card object which is drawn and pushed onto the Hand attribute of the User 
	void userHit(Card card);
	
	/// @brief function which represents the move "Hit" for Dealer attribute in a Blackjack round
	/// @details To hit is to request another card, given that their current Hand attribute is lower than 21
	/// @param card represents the new card object which is drawn and pushed onto the Hand attribute of the Dealer
	void dealerHit(Card card);
	
	/// @brief method which represents the move "Stay" in a blackjack round 
	/// @details To stand is to request that the user's turn is over, and control is given to the dealer to deal their cards to determine a winner
	void stand();
	
	/// @brief method which represents the move "Double Down in a backjack round"
	/// @details To double down is to do a hit and also double the user attribute's bet for the current round of blackjack
	/// @param bet represents the integer of the users current bet, which will doubled and updated accodringly 
	/// @param card represents the card which will be drawn from the "hit" portion of a double down move 
	void doubleDown(Card card);
	
	/// @brief method which clears the hand attribute of User and Dealer attributes 
	/// @details resets Dealer and Userto its default configuration upon its construction 
	void clearCards();
	
	/// @brief resets board
	/// @details sets blackjack board configuration to defaults
	void setDefaults();
};

#endif // !BLACK_JACK_H
