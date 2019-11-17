#pragma once
#include<unordered_map>
#include <string>
#include "Player.h"
#include "map.h"

using namespace std;
class Continent;
class Country;
class Player;
class Phase {
private :
	unordered_map<int, vector<string>> actionsPlayerTook;

public:
	void notify(int playerNb, vector<string>* actionsOfPLayer);

	void display();
	void reset();
};

class View {
private:
	vector<Player*> allplayers;
	unordered_map<string,string> allCountryStats;
	unordered_map<string, string> allContinentStats;
	unordered_map<string, Continent*> allContinent;
	unordered_map<string, Country*> allCountries;
	unordered_map<int, int> playerPoint;
	int playerWinner;


public:

	void notify(string country, string playerColor);
	void notifyPlayerPoints(int player, int point);
	void notifyWinner(int player);
	void updateContinent();
	void displayContinentStats();
	void displayCountryStats();
	void displayStats();
	void displayWin();
	void setAllPlayers(vector<Player*> allplayers);
	void setallContinent(unordered_map<string, Continent*> allContinents);
	void setallCountry(unordered_map<string, Country*> allCountries);

};