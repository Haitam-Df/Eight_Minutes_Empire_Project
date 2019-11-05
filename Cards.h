#pragma once
#include <vector>
#include <string>

using namespace std;

class Cards {
public:
	Cards(string action, string good);
	string good;
	string action;

private:

};

class Deck {
private:
	vector<Cards*> deckOfCard;
	vector<Cards*> hand;
public:
	Deck();
	void draw();
	void removeCard(int position);
	void showHand();


	vector<Cards*> getHand();

	
private:
};

class Hand {
public:
	void exchange(int position);
	vector<Cards*> getHand();
	Hand(Deck * x);
	int getCostCard(int position);
	Hand();

private:
	Deck* deck;
	vector<Cards*> playerHand;
};

