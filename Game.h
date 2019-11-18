#pragma once
#include "MapLoader.h"
#include "Player.h"
#include "GameObservers.h"

class Game{
private:
	MapLoader* maploader;
	Map* map;
	vector<Player*> allPlayers;
	Deck* deck;
	int* supplyBank;
	string startingGameCountry;
	const vector<string> allColors = { "red", "blue", "yellow", "green", "white" };

	vector<Phase*> observers;
	vector<string>* actionsOfPLayer;
	int playerTurn;
	View* viewObserver;

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
	void playerChooseAction(Player* playerTurn,vector<string>*);
	void destroyGame();
	void addSubscriber(Phase* observer);
	void notify();
	void setPlayerAction(int player, vector<string>* actions);
	

	bool notAlreadyUsed(vector<string> colorUsed, string color);
	bool verifyColor(vector<string> colorUsed, string colorChoose, int nbOfPlayer);
	void computeScoreG();	
	void setObserver();

	int nbOfCoin(int nbOfPlayer);
	int nbOfTurn(int nbOfPlayer);

};