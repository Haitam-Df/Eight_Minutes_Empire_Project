#ifndef BIDDING_H
#define BIDDING_H

#include<iostream>


using namespace std;

class Bidding{

	public:
		Bidding();
		Bidding(int year,int totalcoin);
		void runOnce();
		void bid();
		int getBidding();
		int getRun();
		int getAge();
private:
		int* biddingCoins ;
		int* OnlyOnce = 0;
		int* age;
		int* playerTotalCoin;
	

};
#endif  