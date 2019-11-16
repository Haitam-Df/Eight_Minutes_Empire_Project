#pragma once
#include<iostream>
#include "Bidding.h"
#include "map.h"
#include "Cards.h"
#include  "PlayerStrategies.h"
#include <unordered_map>

using namespace std;
class Country;
class Continent;
class Player 
{ 
private:
	int* coins;
	int* id;
	Bidding* bidding;
	Hand* hand;
	string colorArmy;
	bool* isCPU;
	PlayerStrategies* userStrategy;
	unordered_map<string, Country*> ownCountry;
	vector<Country*> armiesInBoard;
	vector<Country*> citiesInBoard;
	const int MAX_ARMIES = 14;
	const int MAX_CITIES = 3;

public:

	Player(int year, Deck* deck, int money, int Id);
	Player(int year, Deck* deck, int money, int Id, bool CPU, int strat);
	Player();

	void placeNewArmies(string action, Country* startingPoint);
	//void moveArmiesOverSea(string action, Country* startingPoint);
	void moveArmies(string action, Country* startingPoint);
	//	void moveOverLand(string action);
	void buildCity(string action, Country* startingPoint);
	void destroyArmy(string action, vector<Player*> allPlayers);
	bool Ignore();
	string AndOrAction(string action, int part);
	void makeAction(string actionTook, Country* startingPoint, vector<Player*> AllPlayers);
	void addOwnCountry(string name,Country* countries);
	void PayCoin(int cost);
	void setColor(string color);
	void addArmy(Country* country);
	void addCity(Country* country);
	void DestroyArmy(Country* country);
	int* getId();
	bool* getStatus();
	void displayInfo();


	int computeScoreP(unordered_map<string, Continent*> allContient);
	int numArmiesOnBoard;
	int controlledRegions;

	Hand* getHand();
	string getColor();
	int* getCoins();
	Bidding* getBiddingInstance();
	PlayerStrategies* getUserStrat();



};