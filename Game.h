#pragma once
#include "MapLoader.h"
#include "Player.h"

class Game{
private:
	MapLoader* maploader;
	Map* map;
	vector<Player*> allPlayers;
	Deck* deck;
	int* supplyBank;
	string startingGameCountry;
	const vector<string> allColors = { "red", "blue", "yellow", "green", "white" };

public:
	Game();
	void loadPlayer();
	void createDeck();
	void playerBid();
	void draw6cards();
	void showDeckHand();
	void addSupply(int money);
	void playerChooseColor(int nbOfPlayer);
	void if2Players();
	void setMap(Map* map);
	void setStartingGameCountry();
	void displayCountry();
	void startGame();
	void playerChooseAction(Player* playerTurn);
	

	bool notAlreadyUsed(vector<string> colorUsed, string color);
	bool verifyColor(vector<string> colorUsed, string colorChoose, int nbOfPlayer);
	void computeScoreG();	

	int nbOfCoin(int nbOfPlayer);
	int nbOfTurn(int nbOfPlayer);

};