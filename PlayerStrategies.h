#ifndef STRAT_H
#define STRAT_H

#include<iostream>
#include "Cards.h"

using namespace std;

class PlayerStrategies
{

public:
	int HumanPlayer(vector<Cards*> gameHand);
	int GreedyCPU(vector<Cards*> gameHand);
	int ModerateCPU(vector<Cards*> gameHand);
	int play(vector<Cards*> gameDeck);
	string getAction();
	void setAction(string newAction);
	bool changeStrat();
	PlayerStrategies(int strat);
	int* getStrategy();
	void setStrategy(int strat);
	bool getChangeStrat();
	void setChangeStrat(bool change);
	PlayerStrategies();
	~PlayerStrategies();
private:
	int* strategy;
	string plays;
	bool changeStratForever;
};
#endif  