#include "stdafx.h"
#include "Bidding.h"

#include<iostream>


using namespace std;


Bidding::Bidding() {};

Bidding::Bidding(int year, int totalCoin)
{
	age = new int(year);
	playerTotalCoin = new int(totalCoin);
};

int  Bidding::getBidding()
{
	return  (*biddingCoins);
}

int Bidding::getRun()
{
	return *OnlyOnce;
}
int Bidding::getAge()
{
	return *age;
}

// you can only bid one time
void Bidding::runOnce(bool CPU)
{
	if (OnlyOnce == 0) {
		bid(CPU);
		OnlyOnce++;
	}
	else {
		cout << "This player has already made a bid" << endl;
	}

}

// give the player access to one bidding
void Bidding::bid(bool CPU)
{
	int selectedCoin;
	while (true) {
		cout << endl;
		if (!CPU) {
			cout << "how many coins do you want to bid ?" << endl;
			cin >> selectedCoin;
		}
		else {
			selectedCoin = rand() % 10;
			cout << " The CPU bid for ";
			cout << selectedCoin;
			cout << " coins" << endl << endl;
		}
		if (selectedCoin <= *playerTotalCoin && selectedCoin >= 0) {
			biddingCoins = new int(selectedCoin);
			break;
		}
		else {
			cout << endl;
			cout << "Maximum bidding is : " << *playerTotalCoin << endl;
		}
	}


}



