#include "BlackJack.h"
#include "User.h"
#include "Dealer.h"
#include "Card.h"
#include "Strategy.h"
#include <string>
#include <iostream>

using namespace std;

BlackJack::BlackJack() {}

BlackJack::BlackJack(std::string username, int balance) {
	User user(username, balance);
	this->user = user;
	inGame = true;
}

BlackJack::~BlackJack() {}

bool BlackJack::getInGame() {
	return this->inGame;
}

Dealer BlackJack::getDealer() {
	return this->dealer;
}

User BlackJack::getUser() {
	return this->user;
}

Strategy BlackJack::getStrategy() {
	return this->strat;
}

void BlackJack::setInGame(bool choice) {
	this->inGame = choice;
}

void BlackJack::setDealerHand(Card faceUpCard) {
	this->dealer.addToDealerHand(faceUpCard);
}

void BlackJack::setUserHand(Card card1, Card card2) {
	this->user.addToUserHand(card1, card2);
}

void BlackJack::setUserBalance(int amount) {
	this->user.setBalance(amount);
}

void BlackJack::userHit(Card card) {
	this->user.hit(card);
}

void BlackJack::dealerHit(Card card) {
	this->dealer.hit(card);
}

void BlackJack::stand() {
	this->user.stand();
}

void BlackJack::doubleDown(Card card) {
	this->user.doubleDown(card);
}

void BlackJack::clearCards() {
	this->user.clearHand();
	this->dealer.clearHand();
}

void BlackJack::setDefaults() {
	this->user.setToDefault();
	this->dealer.setToDefault();
}
