/** @file */


#include "BlackJack.h"
#include "Hand.h"
#include "Card.h"
#include "Dealer.h"
#include "User.h"
#include "Strategy.h"
#include "CardDetector.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;


/// @brief main function for GROUP37 Blackjack training project
/// @details implementation of blackjack trainer
///
/// @return an integer exit code, 0 on successful exit 
/// @authors Mike, Riley, Sam, Aaron

int main() {
	string name;
	int balance;
	char choice;
	int bet;
	int newBalance;
	char move = 'n';

	//prompt user to enter username
	cout << endl << endl << endl << "*******************************************************************************************";
	cout << endl << endl << endl << "WELCOME TO STRATJACK!";
	cout << endl << endl << endl << "Username: ";
	cin >> name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl;

	//username length validation
	while (name.length() > 30) {
		cout << "Invalid username input." << endl;
		cout << "Username: ";
		cin >> name;
		cout << endl;
	}
	//prompt user to enter the amount they would like to start with in their session
	cout << "Credits: ";
	cin >> balance;
	cout << endl;

	//balance input validation
	while (balance <= 0) {
		cout << "Invalid credit input." << endl;
		cout << "Credits: ";
		cin >> balance;
		cout << endl;
	}

	//creation of blackjack game and card reader
	BlackJack game(name, balance);
	CardDetector reader;
	Card dealerCard;		//dealer face up card that will be read
	Card playerCard1;		//user's first card that will be read
	Card playerCard2;		//user's second card that will be read
	Card currentCard;		//this card will be the hit or double card that is read

	//loop until user does not want to play anymore
	while (game.getInGame()) {
		cout << endl << "*******************************************************************************************" << endl << endl;
		//prompt user to enter the amount they want to bet on the current round
		cout << "Current credit balance: " << game.getUser().getBalance() << endl << endl;
		cout << "Bet: ";
		cin >> bet;
		cout << endl;

		//bet validation
		while (bet <= 0 || bet > game.getUser().getBalance()) {
			cout << "Invalid bet input." << endl;
			cout << "Bet: ";
			cin >> bet;
			cout << endl;
		}

		//update balance before round starts
		newBalance = (game.getUser().getBalance() - bet);
		game.setUserBalance(newBalance);
		
		cout << "Ready for dealer's card." << endl;
		dealerCard = reader.getErBaud();			//read dealer's card from board
		game.setDealerHand(dealerCard);				//sets the dealers hand with the previously read card
		
		cout << "Ready for your first card." << endl;		
		playerCard1 = reader.getErBaud();			//read players first card from board
		cout << "Ready for your second card." << endl;
		playerCard2 = reader.getErBaud();			//read the players second card from board
		game.setUserHand(playerCard1, playerCard2); // readCard cards
		cout << "Dealer shows: " << dealerCard.getName() << " (total = " <<  game.getDealer().getHand().getSum()  << ")" << endl;
		cout << "You have: " << playerCard1.getName() << ", " << playerCard2.getName() << " (total = " << game.getUser().getHand().getSum() << ")" << endl;
		
		if (game.getUser().getHand().getSum() == 21) {
			cout << "YOU HAVE BLACKJACK!" << endl;
			move = 's';
		}
		
		else {
			cout << "RECOMMENDATION: " << game.getStrategy().recommendation(game.getUser().getHand(), game.getDealer().getHand()) << endl;
		}

		//loop until user decides to stay or double down since they no longer can make any more moves
		while (move != 's' && move != 'd') {
			cout << "Enter move (h = hit, s = stay, d = double down): ";
			cin >> move;

			while (move != 'h' && move != 's' && move != 'd') {					//move input validation
				cout << "Enter move (h = hit, s = stay, d = double down): ";
				cin >> move;
			}

			if (move == 'h') {									//if user decides to hit
				currentCard = reader.getErBaud();
				game.userHit(currentCard);		// readCard cards
				cout << "You hit a(n): " << currentCard.getName() << " (total = " << game.getUser().getHand().getSum() << ") " << endl; 
				
				if (game.getUser().getHand().getSum() >= 21) {	//if the user busts
					break;
				}

				cout << "RECOMMENDATION: " << game.getStrategy().recommendation(game.getUser().getHand(), game.getDealer().getHand()) << endl;
			}

			else if (move == 'd') {								//if the user decides to double down
				if ((game.getUser().getBalance() < bet * 2) || (game.getUser().getHand().getNumOfCards() > 2)) {		//if user wants to double but is not allowed bc not enough money or already hit once
					cout << "Double down invalid." << endl;
					move = 'n';
					continue;		//end the user's turn by continuing with a move set to 'n'
				}

				else {		//this is if the user is allowed to double down
					
					currentCard = reader.getErBaud();	//read the next card drawn from the deck that is on the board
					game.doubleDown(currentCard);
				
					cout << "You hit a(n): " << currentCard.getName() << " (total = " << game.getUser().getHand().getSum() << ") " << endl;

					if (game.getUser().getHand().getSum() >= 21) {
						break;
					}

					newBalance = (game.getUser().getBalance() - bet);	//if the user doubles down then bet double the original bet
					game.setUserBalance(newBalance);
				}

				cout << "Recommendation: " << game.getStrategy().recommendation(game.getUser().getHand(), game.getDealer().getHand()) << endl;
			}

			else if (move == 's') {		//the user decides to stand
				cout << "You stand. (total = " << game.getUser().getHand().getSum() << ") " << endl; 
			}
		}

		if (game.getUser().getHand().getSum() > 21) {	//if the user busts 
			cout << endl << "You busted. (total = " << game.getUser().getHand().getSum() << ") " << endl << endl;
			game.setDefaults();	//clear the hands of the dealer and player as well as there associated attributes
			game.clearCards();
			
			if(game.getUser().getBalance() == 0){	//if the user has no money in their account they cannot play in this session anymore
				cout << "Balance depleted." << endl << endl;
				cout << "GOODBYE " << game.getUser().getName() << " :)" << endl;
				cout << endl << "*******************************************************************************************" << endl;
				game.setInGame(false);
				return 0;
			}
			
			cout << "Another round " << game.getUser().getName() << "? (y/n): ";
			cin >> choice;

			while (choice != 'n' && choice != 'y') {	//choice validation
				cout << "Invalid input." << endl;
				cout << "Another round " << game.getUser().getName() << "? (y/n): ";
				cin >> choice;
			}

			if (choice == 'n') {	//if the user is done playing
				cout << endl << "For reference, starting balance: " << balance << endl;
				cout << "Ending balance: " << game.getUser().getBalance() << endl << endl;
				cout << "GOODBYE " << game.getUser().getName() << " :)" << endl;
				cout << endl << "*******************************************************************************************" << endl;
				game.setInGame(false);
				return 0;
			}
			continue;
		}

		//dealer continues to hit a sum of 16 or below
		while (game.getDealer().getHand().getSum() < 17) {
			currentCard = reader.getErBaud();
			game.dealerHit(currentCard);	// readCard cards
			cout << "Dealer hits: " << currentCard.getName() << " (total = " << game.getDealer().getHand().getSum() << ") " << endl; 
		}

		//if the dealer busts then the player wins and the player makes what they had bet
		if (game.getDealer().getHand().getSum() > 21) {
			cout << endl << "Dealer busted. You win." << endl << endl;
			newBalance = (game.getUser().getBalance() + (2 * bet));
			game.setUserBalance(newBalance);
		}

		//if the player has 21 and the dealer does not then player wins
		else if ((game.getUser().getHand().getSum() == 21) && (game.getDealer().getHand().getSum() != 21)) {
			cout << endl << "You win." <<  endl << endl;
			newBalance = (game.getUser().getBalance() + (2 * bet));
			game.setUserBalance(newBalance);
		}

		//if the dealer has a sum closer to 21 and greater than the user
		else if (game.getDealer().getHand().getSum() > game.getUser().getHand().getSum()) {
			cout << endl << "Dealer wins." << endl << endl;
		}

		//if the user has a sum closer to 21 and greater than the dealer
		else if (game.getDealer().getHand().getSum() < game.getUser().getHand().getSum()) {
			cout << endl << "You win." << endl << endl;
			newBalance = (game.getUser().getBalance() + (2 * bet));
			game.setUserBalance(newBalance);
		}

		//if the user wins and doubles down then they get double their original bet
		else if ((game.getDealer().getHand().getSum() < game.getUser().getHand().getSum()) && move == 'd') {
			cout << endl << "You win." << endl << endl;
			newBalance = (game.getUser().getBalance() + (4 * bet));
			game.setUserBalance(newBalance);
		}

		//if the dealer and player have the same sum then it is a die, also called a push
		else {
			cout << endl << "You and the dealer tie (push)" << endl << endl;
			newBalance = (game.getUser().getBalance() + bet);
			game.setUserBalance(newBalance);
		}

		//this marks the end of a round
		move = 'n';
		game.setDefaults();
		game.clearCards();
		
		//check if the user has any money left in their account
		if(game.getUser().getBalance() == 0){
				cout << "Balance depleted." << endl << endl;
				cout << "GOODBYE " << game.getUser().getName() << " :)" << endl;
				cout << endl << "*******************************************************************************************";
				game.setInGame(false);
				return 0;
		}
		
		cout << "Another round " << game.getUser().getName() << "? (y/n): ";
		cin >> choice;

		while (choice != 'n' && choice != 'y') {
			cout << "Invalid input." << endl;
			cout << "Another round " << game.getUser().getName() << "? (y/n): ";
			cin >> choice;
		}

		if (choice == 'n') {
			cout << endl << "For reference, starting balance: " << balance << endl;
			cout << "Ending balance: " << game.getUser().getBalance() << endl << endl;
			cout << "GOODBYE " << game.getUser().getName() << " :)" << endl;
			cout << endl << endl << endl << "*******************************************************************************************";
			game.setInGame(false);
		}
	}
}
