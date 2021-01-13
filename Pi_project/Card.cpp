//
// Created by Sam Silverstein on 2019-10-27.
//

#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() {}

Card::Card(int val, int name) {
	this->rank = val;
	this->name = name;
}

Card::~Card() {}

string Card::getName()
{
	string Result;
	if (name == 1)
	{
		Result = "Two";
	}
	else	if (name == 2)
	{
		Result = "Three";
	}
	else	if (name == 3)
	{
		Result = "Four";
	}
	else	if (name == 4)
	{
		Result = "Five";
	}
	else	if (name == 5)
	{
		Result = "Six";
	}
	else	if (name == 6)
	{
		Result = "Seven";
	}
	else	if (name == 7)
	{
		Result = "Eight";
	}
	else	if (name == 8)
	{
		Result = "Nine";
	}
	else	if (name == 9)
	{
		Result = "Ten";
	}
	else	if (name == 10)
	{
		Result = "Jack";
	}
	else	if (name == 11)
	{
		Result = "Queen";
	}
	else	if (name == 12)
	{
		Result = "King";
	}
	else	if (name == 13)
	{
		Result = "Ace";
	}
	return Result;
}

int Card::getRank(){
	return this->rank;
}

void Card::setRank(int rank) {
	this->rank = rank;
}
