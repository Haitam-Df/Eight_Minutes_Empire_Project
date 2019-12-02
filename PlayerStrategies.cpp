#include "stdafx.h"
#include "PlayerStrategies.h"
#include<iostream>


using namespace std;


PlayerStrategies::PlayerStrategies(int strat)
{
	strategy = new int(strat);
	plays;
	changeStratForever = false;
}
PlayerStrategies::PlayerStrategies()
{
}

PlayerStrategies::~PlayerStrategies()
{
}

int* PlayerStrategies::getStrategy() {
	return strategy;
}
void PlayerStrategies::setStrategy(int strat) {

	delete strategy;
	strategy = new int(strat);
	

}

bool PlayerStrategies::getChangeStrat() {
	return changeStratForever;
}

void PlayerStrategies::setChangeStrat(bool change) {
	changeStratForever = change;
}

int PlayerStrategies::play(vector<Cards*> gameHand) {

	int* action = this->getStrategy();

	if (*action == 0) {
		return HumanPlayer(gameHand);
	}
	else if (*action == (1)) {
		return GreedyCPU(gameHand);
	}
	else if (*action == (2)) {
		return ModerateCPU(gameHand);
	}
	return  1;
}

string PlayerStrategies::getAction()
{
	return plays;
}
void PlayerStrategies::setAction(string newAction)
{
	plays = newAction;

}
bool PlayerStrategies::changeStrat() {
	
		string answer;
		int changeStrat;
		if (getChangeStrat()) {
			return NULL;
		}
		else {

			cout << "Do you want to change strategies before the next turn (y or n) ? ( Write NO to never be bothered again)" << endl;
			while (true) {
				cin >> answer;
				if (answer == "y") {

					cout << " Which Strategy do you want for this player to adopt?" << endl;
					cout << "1) Human Player" << endl;
					cout << "2) Greedy Player" << endl;
					cout << "3) Moderate Player" << endl;

					while (true) {
						cin >> changeStrat;
						if (changeStrat == 1) {	
							setStrategy(changeStrat - 1);
							return false;
							break;
						}
						if (changeStrat == 2 || changeStrat == 3) {
							setStrategy(changeStrat - 1);
							return true;
							break;
						}
					}
					break;
				}

				if (answer == "n") { setChangeStrat(false); return NULL; break; }
				if (answer == "NO") { setChangeStrat(true); return NULL;  break; }
				cout << "Do you want to change strategies before the next turn (y or n) ? ( Write NO to never be bothered again)" << endl;
			}

		}


}

int PlayerStrategies::HumanPlayer(vector<Cards*> gameHand)
{
	int  action;
	while (true) {
		cout << endl;
		cout << "Select an option" << endl;
		cin >> action;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			if (action > 0 && action <= gameHand.size()) {
				break;
			}
		}
	}

	return action;
}

int PlayerStrategies::GreedyCPU(vector<Cards*> gameHand)
{
	for (int i = 0; i < gameHand.size(); i++) {

		if (gameHand.at(i)->action.find("Destroy") != std::string::npos) { plays = "no";  return (i + 1); }
		if (gameHand.at(i)->action.find("Build") != std::string::npos) { plays = "no"; return (i+1); }

	}
	plays = "ignore";
	return 1;
}
int PlayerStrategies::ModerateCPU(vector<Cards*> gameHand)
	{

		for (int i = 0; i < gameHand.size(); i++) {

			if (gameHand.at(i)->action.find("Add") != std::string::npos) { plays = "no";  return (i + 1); }


		}
	
		plays = "ignore";
		return 1;
	}

