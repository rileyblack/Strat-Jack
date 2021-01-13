#include "Dealer.h"
#include "Hand.h"

#include<vector>

Dealer::Dealer() {}

Dealer::~Dealer() {}

Hand Dealer::getHand() {
	return this->hand;
}

void Dealer::addToDealerHand(Card faceUpCard) {
	this->hand.addCard(faceUpCard);
}

void Dealer::hit(Card card) {
	this->hand.addCard(card);
}

void Dealer::clearHand() {
	this->hand.clearCards();
}

void Dealer::setToDefault() {
	this->hand.setToDefault();
}
