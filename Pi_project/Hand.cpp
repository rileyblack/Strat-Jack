#include "Hand.h"
#include<iostream>
#include "Card.h"

using namespace std;

Hand::Hand() {
	this->sum = 0;
	this->numberOfCards = 0;
	this->hard = 1; 
}

Hand::~Hand() {}

/*
* A getter method which returns the sum of the cards in the Hand Object
*/
int Hand::getSum() {
	return this->sum;
}

int Hand::getNumOfCards() {
	return this->numberOfCards;
}

bool Hand::isHard() {
	return this->hard;
}

void Hand::setToDefault() {		//at the end of a round reset all values of hand for player and dealer
	this->sum = 0;
	this->numberOfCards = 0;
	this->hard = 1;
}

/*
* Add card adds a Card object to the hand attribute
*/
void Hand::addCard(Card card) {
	this->hand.push_back(card);
	this->numberOfCards += 1;

	if (card.getRank() == 11) {		//if the drawn card is an 11
		if (this->sum + 11 > 21) {
			this->hard = 1;
			this->hand.at((this->hand.size()) - 1).setRank(1); ////////////////////////
			this->sum += hand.at((this->hand.size()) - 1).getRank();

			//check if there is another ace in this bitch
			if (this->sum > 21) {										//if the sum is still a bust after making the ace a 1
				for (int i = 0; i < this->numberOfCards; i++) {			//loop through and look for another ace to turn into a 1
					if (this->hand[i].getRank() == 11) {
						this->hand[i].setRank(1);								//changing the ace to a 1
						this->sum = this->sum - 10;
						if (this->sum > 21) {
							return;
						}
						for (int i = 0; i < this->numberOfCards; i++) {			//checks to see if the hand is a hard or soft total
							if (this->hand[i].getRank() == 11) {
								this->hard = 0;
								break;
							}
							else {
								this->hard = 1;
							}
						}
						return;
					}
				}
				return;
			}
			for (int i = 0; i < this->numberOfCards; i++) {			//checks to see if the hand is a hard or soft total
				if (this->hand[i].getRank() == 11) {
					this->hard = 0;
					break;
				}
				else {
					this->hard = 1;
				}
			}
			return;
		}
		else {	//if 11 and does not cause a bust
			this->hard = 0;
			this->sum += card.getRank();
			return;
		}
	}

	int tempSum = this->sum + card.getRank();
	if ((tempSum > 21) && (this->hard == 0)) {

		for (int i = 0; i < this->numberOfCards; i++) {
			if (this->hand[i].getRank() == 11) {
				this->hand[i].setRank(1);								//changing the ace to a 1
				this->sum = card.getRank() + this->sum - 10;
				if (this->sum > 21) {
				}
				break;
			}
		}

		for (int i = 0; i < this->numberOfCards; i++) {					//checks to see if the hand is a hard or soft total
			if (this->hand[i].getRank() == 11) {
				this->hard = 0;
				break;
			}
			else {
				this->hard = 1;
			}
		}
		return;
	}

	this->sum += card.getRank();
}

void Hand::clearCards() {
	this->hand.clear();
}








