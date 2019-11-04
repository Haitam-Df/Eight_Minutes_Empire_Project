#include "stdafx.h"
#include "Bidding.h"

#include<iostream>


using namespace std;


Bidding::Bidding() {};

Bidding::Bidding(int year,int totalCoin)
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
void Bidding::runOnce()
{
	if (OnlyOnce == 0) {
		bid();
		OnlyOnce++;
	}
	else {
		cout << "This player has already made a bid" << endl;
	}

}

// give the player access to one bidding
void Bidding::bid()
{
	int selectedCoin;
	while (true) {
		cout << endl;
		cout << "how many coins do you want to bid ?" << endl;
		cin >> selectedCoin;
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



