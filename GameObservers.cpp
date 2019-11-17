#include "GameObservers.h"
#include<iostream>
using namespace std;


void Phase::notify(int playerNb, vector<string>* actionsOfPLayer) {
	actionsPlayerTook[playerNb] = *actionsOfPLayer;
}

void Phase::display() {
	cout << endl;
	cout << endl;
	cout << "******* USING HAKI OF OBSERVATION, THIS IS WHAT HAPPENNED SO FAR IN THIS TURN **************";

	for (std::pair<int, vector<string>> element : actionsPlayerTook) {
		cout << endl;
		cout << "@Player " << element.first << " :" << endl;
		for (int x = 0; x < element.second.size(); x++) {
			cout << element.second[x] << endl;
		}
	}

	cout << "******* TOO MUCH HAKI WAS USE , LETS REST A LITTLE BIT **************";


}

void Phase::reset() {
	actionsPlayerTook.clear();
}



void View::notify(string country, string colorPlayer) {
	allCountryStats[country] = colorPlayer;
	updateContinent();
}


void View::displayCountryStats() {
	cout << endl;
	cout << "******** LETS TAKE A LOOK OF WHICH COUNTRY IS OWNED BY WHO!!"<<endl;
	for (std::pair<string, string> element : allCountryStats) {
		cout << " 	- "<<element.first<<"  OWNED BY : "<<element.second << endl;
	}
}

void View::displayContinentStats() {
	cout << endl;
	cout << "******** LETS TAKE A LOOK OF WHICH CONTINENT IS OWNED BY WHO!!" << endl;
	for (std::pair<string, string> element : allContinentStats) {
		cout << " 	- " << element.first << "  OWNED BY : " << element.second << endl;
	}
}

void View::displayStats() {
	cout << endl;
	cout << "********* LETS USE THE BYAKUGAN TO SEE ALL THE STATS *********" << endl;
	for (int x = 0; x < allplayers.size(); x++) {
		allplayers[x]->displayInfo();
	}

	displayCountryStats();
	displayContinentStats();

	cout << "********* TOO MUCH BYAKUGAN WAS USED, LETS REST A LITTLE BIT *********" << endl;
}
void View::updateContinent() {
	for (pair<string, string> element : allCountryStats) {
		allContinentStats[allCountries[element.first]->getContinentName()] = allContinent[allCountries[element.first]->getContinentName()]->setOwnedColor();
	}
}
void View::setAllPlayers(vector<Player*> allplayers) {
	this->allplayers = allplayers;
}
void View::setallContinent(unordered_map<string, Continent*> allContinents) {
	this->allContinent = allContinents;
}
void View::setallCountry(unordered_map<string, Country*> allCountries) {
	this->allCountries = allCountries;
}
void View::notifyPlayerPoints(int player, int point) {
	playerPoint[player] = point;
}
void View::notifyWinner(int player) {
	playerWinner = player;
}
void View::displayWin() {
	cout << endl;
	for (pair<int, int> element : playerPoint) {
		cout << "PLAYER "<<element.first << " has "<<element.second << "POINTS! "<<endl;
	}
	cout << endl;
	cout << "THE WINNNER ISSSS ...... PLAYER " << playerWinner << " WITH " << playerPoint[playerWinner];
}