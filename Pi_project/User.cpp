#include "User.h"
#include "Hand.h"

#include<iostream>
using namespace std;

User::User() {}

User::User(string username, int balance) {
	this->name = username;
	this->balance = balance;
}

User::~User() {
}

Hand User::getHand() {
	return this->hand;
}

int User::getBalance() {
	return this->balance;
}

string User::getName() {
	return this->name;
}

void User::setBalance(int balance) {
	this->balance = balance;
}

void User::addToUserHand(Card card1, Card card2) { 
	this->hand.addCard(card1);
	this->hand.addCard(card2);
}

void User::clearHand() {
	this->hand.clearCards();
}

void User::hit(Card card) {
	this->hand.addCard(card);
}

void  User::stand(){}

void User::doubleDown(Card card) {
		this->hand.addCard(card);
}

void User::setToDefault() {
	this->hand.setToDefault();
}
