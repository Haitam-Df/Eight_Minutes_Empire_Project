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
	//array for each player how many cities they have
	//int citiesInBoard[3];

	
	

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
	
	int counters[5] = {0,0,0,0,0};
	int total=allCountries.size();
	cout << endl;
	cout << "******** LETS TAKE A LOOK OF WHICH COUNTRY IS OWNED BY WHO!!"<<endl;
	for (std::pair<string, string> element : allCountryStats) {
		cout << " 	- "<<element.first<<"  OWNED BY : "<<element.second << endl;			
		if (element.second == "red")
		{
			counters[0]++;
		}
		else if (element.second == "blue")
		{
			counters[1]++;
		}
		else if (element.second == "yellow")
		{
			counters[2]++;
		}
		else if (element.second == "green")
		{
			counters[3]++;
		}
		else if (element.second == "white")
		{
			counters[4]++;
		}
		
	}
	for (int i = 0; i < allplayers.size(); i++)
	{
		cout << "Player " << allplayers[i]->getColor() << " has the following flow chart ";
		for (int j = 0; j < counters[i]; j++)
		{
			cout << "+";
		}
		for (int j = 0; j < total; j++)
		{
			cout << "-";
		}
		cout << endl;
	}
}

void View::displayContinentStats() {
	int counters[5] = { 0,0,0,0,0 };
	int total = allContinent.size();
	cout << endl;
	cout << "******** LETS TAKE A LOOK OF WHICH CONTINENT IS OWNED BY WHO!!" << endl;
	for (std::pair<string, string> element : allContinentStats) {
		cout << " 	- " << element.first << "  OWNED BY : " << element.second << endl;
		if (element.second == "red")
		{
			counters[0]++;
		}
		else if (element.second == "blue")
		{
			counters[1]++;
		}
		else if (element.second == "yellow")
		{
			counters[2]++;
		}
		else if (element.second == "green")
		{
			counters[3]++;
		}
		else if (element.second == "white")
		{
			counters[4]++;
		}
	}
	for (int i = 0; i < allplayers.size(); i++)
	{
		cout << "Player " << allplayers[i]->getColor() << " has the following flow chart ";
		for (int j = 0; j < counters[i]; j++)
		{
			cout << "+";
		}
		for (int j = 0; j < total; j++)
		{
			cout << "-";
		}
		cout << endl;
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
	cout << "___________________________________________________________________________" << endl;
	cout << "|  Payer #  |  Cards  |  Victory  Points  |  Coins  |   Color  |" << endl;
	
	for (pair<int, int> element : playerPoint) {
		for (Player* elementplayer : allplayers) {
			if (*elementplayer->getId() == element.first) {
				cout << "|_____" << element.first << "_____|____" << elementplayer->getHand()->getHand().size() << "____|_________"<<element.second<<"_________|____"<<*elementplayer->getCoins()<<"____|_____"<< elementplayer->getColor()<< endl;
			}
		}
	}
	int valueWin = 0;
	int playerint = 0;
	int isWin = 1;
	for (pair<int, int> element : playerPoint) {
		if (element.second > valueWin) {
			valueWin = element.second;
			playerint = element.first;
			isWin = 1;
		}
		else if(element.second == valueWin){
			isWin = 0;
		}
	}
	if (isWin == 1) {
		cout << endl;
		cout << "THE WINNNER ISSSS ...... PLAYER " << playerint << " WITH " << valueWin << " POINTS" << endl;
	}
	else {
		cout << endl;
		cout << "THERE IS NO WINNER, THE RESULT IS DRAW!!!" << endl;
	}
}
