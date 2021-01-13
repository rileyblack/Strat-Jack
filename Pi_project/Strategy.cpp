#include <iostream>
#include "Strategy.h"
#include "User.h"

using namespace std;

Strategy::Strategy()
{
}

Strategy::~Strategy()
{
}

string Strategy::recommendation(Hand userHand, Hand dealerHand) {

	//if the user is busted
	if (userHand.getSum() > 21) {
		return "busted";
	}

	//if the user has a hard hand
	else if (userHand.isHard()) {
		if (userHand.getSum() <= 8) {
			return "hit";
		}
		
		else if (userHand.getSum() > 17){
				return "stay";
		}

		else if (this->hardStrategy[userHand.getSum() - 9][dealerHand.getSum() - 2] == 'D' && userHand.getNumOfCards() > 2) {
			return "hit";
		}

		else {
			if ((hardStrategy[userHand.getSum() - 9][dealerHand.getSum() - 2]) == 'H') {
				return "hit";
			}

			else if ((hardStrategy[userHand.getSum() - 9][dealerHand.getSum() - 2]) == 'D') {
				return "double down";
			}

			else if ((hardStrategy[userHand.getSum() - 9][dealerHand.getSum() - 2]) == 'S') {
				return "stay";
			}
		}
	}

	//if the user has a soft hand
	else {
		if (this->softStrategy[userHand.getSum() - 9][dealerHand.getSum() - 2] == 'D' && userHand.getNumOfCards() > 2) {
			return "hit";
		}

		else if ((softStrategy[userHand.getSum() - 9][dealerHand.getSum() - 2]) == 'H') {
			return "hit";
		}

		else if ((softStrategy[userHand.getSum() - 9][dealerHand.getSum() - 2]) == 'D') {
			return "double down";
		}

		else if ((softStrategy[userHand.getSum() - 20][dealerHand.getSum() - 2]) == 'S') {
			return "stay";
		}
	}
}
