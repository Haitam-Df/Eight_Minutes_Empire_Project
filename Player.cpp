
#include "stdafx.h"
#include "Player.h"
#include "map.h"
#include "Game.h"
#include <iostream>
#include <sstream> 
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

Player::Player(int year,Deck* deck,int money, int Id)
{
	bidding = new Bidding(year,money);
	hand = new Hand(deck);
	coins = new int(money);
	id =new int(Id);
}
Bidding* Player::getBiddingInstance() {
	return bidding;
}

void Player::setColor(string color) {
	colorArmy = color;
}

string Player::getColor() {
	return colorArmy;
}

int* Player::getId() {
	return id;
}

void Player::addOwnCountry(string regionsName, Country* country) 
{
	ownCountry[regionsName] = country;
	cout << endl;
	cout << regionsName <<" is now yours beware of the ennemies !" << endl;
}


int Player::computeScoreP(unordered_map<string, Continent*> allContinent)
{
	vector <Country*> Carr;
	int scoreP = 0;
	int crystal = 0;
	int ore = 0;
	int anvil = 0;
	int carrot = 0;
	int tree = 0;

	//calculating the countries/regions owned 
	for (int i = 0; i < armiesInBoard.size(); i++)
	{
		bool check = false;
		for (int j = 0; j < Carr.size(); j++)
		{
			if (armiesInBoard[i]->getCountryName() == Carr[j]->getCountryName())
			{
				check = true;
			}
		}
		if (check)
		{
		}
		else
		{
			Carr.push_back(armiesInBoard[i]);
			scoreP += Carr[i]->computeScoreR(colorArmy);
		}
	}
	numArmiesOnBoard = armiesInBoard.size();
	controlledRegions = Carr.size();

	//calculating goods owned
	for (int i = 0; i < hand->getHand().size(); i++) 
	{
		if (hand->getHand()[i]->good == "Crystal")
		{
			crystal++;
		}
		else if (hand->getHand()[i]->good == "Anvil")
		{
			anvil++;
		}else if (hand->getHand()[i]->good == "Forest")
		{
			tree++;
		}else if (hand->getHand()[i]->good == "Ore")
		{
			ore++;
		}else if (hand->getHand()[i]->good == "Carrot")
		{
			carrot++;
		}
	}

	switch (crystal) 
	{
	case 1:
		scoreP += 1; break;
	case 2:
		scoreP += 2; break;
	case 3:
		scoreP += 3; break;
	case 4:
	case 5:
	case 7:
	case 8:
		scoreP += 5; break;
	}
	
	switch (anvil)
	{
	case 2:
	case 3:
		scoreP += 1; break;
	case 4:
	case 5:
		scoreP += 2; break;
	case 6:
		scoreP += 3; break;
	case 7:
		scoreP += 5; break;
	}

	switch (ore)
	{
	case 2:
		scoreP += 1; break;
	case 3:
		scoreP += 2; break;
	case 4:
		scoreP += 3; break;
	case 5:
	case 6:
	case 7:
	case 8:
		scoreP += 5; break;
	}

	switch (tree)
	{
	case 2:
	case 3:
		scoreP += 1; break;
	case 4:
		scoreP += 2; break;
	case 5:
		scoreP += 3; break;
	case 6:
	case 7:
	case 8:
		scoreP += 5; break;
	}

	switch (carrot)
	{
	case 3:
	case 4:
		scoreP += 1; break;
	case 5:
	case 6:
		scoreP += 2; break;
	case 7:
		scoreP += 3; break;
	case 8:
		scoreP += 5; break;
	}

	//calculating continents owned
	for (std::pair<std::string, Continent*> element : allContinent) 
	{
		scoreP += element.second->computeScoreC(colorArmy);
	}

	cout << endl;
	cout << colorArmy << " HAS : " << scoreP << " POINTS! " << endl;
	return scoreP;
}


void Player::PayCoin(int cost) {
	*coins -= cost;
	cout << endl;
	cout << *coins << " coins are left in the Player Bank" << endl;
}
void Player::displayInfo() {
	cout << endl;
	cout << endl;
	cout << *getId()<< " [PLAYER]" << endl;
	cout << *getCoins()<< " [COINS]" << endl;
	cout << *coins << endl;

}

int* Player::getCoins() 
{
	return coins;
}

void Player::addArmy(Country* country) {
	armiesInBoard.push_back(country);
}


void Player::addCity(Country* country) {
	citiesInBoard.push_back(country);
}

Hand* Player::getHand() {
	return hand;
}

void Player::moveArmies(string action, Country* startingPoint) {

	string color = getColor();
	int move;
	int current = 0;
	string answer;
	string start;
	string userAnswer;
	bool real = false;
	unordered_map<string, Country*> temp;
	unordered_map<string, Country*> tempStart;

	string tmp;
	stringstream ss(action);
	ss >> tmp >> move;

	cout << " You have an army in these countries :" << endl;
	for (int i = 0; i < armiesInBoard.size(); i++) {

	
		cout << armiesInBoard.at(i)->getCountryName() << endl;
	}

	cout << "Please select the starting country to move an army" << endl;
	cin >> answer;
	start = answer;

	for (int i = 0; i < armiesInBoard.size(); i++) {
		
		if (armiesInBoard.at(i)->getCountryName() == answer) {
			current = i;
		}
	}

	cout << "here is the list of country related to " << armiesInBoard.at(current)->getCountryName() << endl;

	temp = armiesInBoard.at(current)->getEdgeCountry();
	tempStart = temp;
	cout << " List of edge countries : " << endl;

	for (auto it = temp.begin(); it != temp.end(); ++it) {
		cout << " " << it->first << endl;

	}

	do {
			if ((move-1) == 0) {
				cout << "you have to pick a country to move the army because you have no more move left" << endl;
				userAnswer = "move";
				cout << "Select a country to move the army" << endl;
				cin >> answer;
				move -= 1;
			}
	
			else {
				cout << " do you want to move armies or explore the map to find a country? (explore or move) REMEMBER YOU HAVE "
					<< move << " MOVES LEFT" << endl;
				cin >> userAnswer;
			}
			

			if (userAnswer == "explore") {
				move -= 1;
				cout << "Which Country do you want to explore?"<<endl;
				cin >> answer;

				temp = temp.at(answer)->getEdgeCountry();

				cout << " List of edge countries : " << endl;

				for (auto it = temp.begin(); it != temp.end(); ++it) {
					cout << " " << it->first << endl;
				}

				if (move == 0) {
					userAnswer = "move";
				}
			}
		
			else if(userAnswer =="move") {
				
				if (move > 1) {
					cout << "To which country do you want to move an army ?" << endl;
					cin >> answer;
					move -= 1;
				}
				
				for (int i = 0; i < armiesInBoard.size(); i++) {

					if (armiesInBoard.at(i)->getCountryName() == start) {
						armiesInBoard.at(i)->DestroyArmies(color);
						armiesInBoard.erase(armiesInBoard.begin() + i);
						addArmy(temp.at(answer));
						break;
					}
				}
				
				temp.at(answer)->addArmies(color, 1);


				if (move != 0) {
					cout << " You have an army in these countries :" << endl;
					for (int i = 0; i < armiesInBoard.size(); i++) {


						cout << armiesInBoard.at(i)->getCountryName() << endl;
					}

					cout << "Please select the starting country to move an army" << endl;
					cin >> answer;
					start = answer;

					for (int i = 0; i < armiesInBoard.size(); i++) {

						if (armiesInBoard.at(i)->getCountryName() == answer) {
							current = i;
						}
					}

					cout << "here is the list of country related to " << armiesInBoard.at(current)->getCountryName() << endl;

					temp = armiesInBoard.at(current)->getEdgeCountry();
					tempStart = temp;
					cout << " List of edge countries : " << endl;

					for (auto it = temp.begin(); it != temp.end(); ++it) {
						cout << " " << it->first << endl;

					}

				}


			}
			else {

				 if ((move - 1) == 0) {
					 cout << "You dont have enough moves to explore" << endl;
				 }
				 else {
					 cout << "Please write explore or move" << endl;
				 }
			}

		} while (move != 0);

	
	

}

void Player::placeNewArmies(string action, Country* startingPoint)
{

	if (armiesInBoard.size() == 14) {
		cout << " you have 14 armies , you cannot have more" << endl;

		return;
	}

	// get number of armies
	string tmp;
	int armies;
	stringstream ss(action);
	ss >> tmp >> armies;

	string answer;

	int nb = 0;

	string color = getColor();

	while (armies != 0) {
		if (citiesInBoard.size() == 0) {
			cout << " You don't have any cities , so armies are added to the starting point !" << endl;
			for (int i = 0; i < armies; i++) {
				if (armiesInBoard.size() == 14) {
					cout << " you have 14 armies , you cannot have more" << endl;
					return;
				}
				addArmy(startingPoint);
			}
			startingPoint->addArmies(color, armies);
			armies = 0;
			break;
		}
		else {
			cout << " You do have  cities ,However would you like to add armies to the starting point (y/n)" << endl;
			cin >> answer;

			if (answer == "y") {
				while (!(nb <= armies && nb >= 1)) {
					cout << "how many armies do you want between 1 and " << armies << endl;
					cin >> nb;
				}
				for (int i = 0; i < nb; i++) {
					if (armiesInBoard.size() == 14) {
						cout << " you have 14 armies , you cannot have more" << endl;
						return;
					}
					addArmy(startingPoint);
					startingPoint->addArmies(color, 1);
					armies = armies - 1;
				}			
			}
			nb = 0;
		}


		for (int i = 0; i < citiesInBoard.size(); i++) {

			if (armiesInBoard.size() == 14) {
				cout << " you have 14 armies , you cannot have more" << endl;
				return;
			}

			if (armies == 0) {
				break;
			}
			citiesInBoard.at(i)->displayInfo();
			cout << "Do you want to add an army ( " << armies << " lefts) , y or n ?" << endl;
			cin >> answer;

			if (answer == "y") {

				while (!(nb <= armies && nb >= 1)) {
					cout << "how many armies do you want between 1 and " << armies << endl;
					cin >> nb;
				}



				for (int j = 0; j < nb; j++) {
					if (armiesInBoard.size() == 14) {
						cout << " you have 14 armies , you cannot have more" << endl;
						return;
					}
					addArmy(citiesInBoard.at(j));
					citiesInBoard.at(j)->addArmies(color, nb);
					armies = armies - 1;
				}

			}
			nb = 0;
		}
		
	}

	cout << "You still have to place " << armies << " armies";
	cout << endl;
	cout << "For now , theses are the armies you have ";

	for (int i = 0; i < armiesInBoard.size(); i++) {

		armiesInBoard.at(i)->displayInfo();
		
	}
	cout << endl;

}

/*void Player::moveArmiesOverSea(string action, Country* startingPoint)
{
	string color = getColor();
	bool real = true;
	string answer;
	string country;
	unordered_map<string, Country*> temp;
	Country* tempCountry;

	if (citiesInBoard.size() == 0) {

		cout << "here is the list of country related to " << startingPoint->getCountryName() << endl;


		temp = startingPoint->getEdgeCountry();

		cout << " List of edge countries : " << endl;

		for (auto it = temp.begin(); it != temp.end(); ++it) {
			cout << " " << it->first << endl;
		}

	}

	while (real) {
		cout << " do you want to build a city or explore the map to find a country? (build or explore)";
		cin >> answer;

		if (answer == "explore") {

			cout << "Which Country do you want to explore?";
			cin >> answer;

			temp = temp.at(answer)->getEdgeCountry();

			cout << " List of edge countries : " << endl;

			for (auto it = temp.begin(); it != temp.end(); ++it) {
				cout << " " << it->first << endl;
			}

		}
		else {
			real = false;
		}
	}



	cout << " Where do you want to build a city ( choose a country) ?";
	cin >> country;

	while (real) {

		for (auto it = temp.begin(); it != temp.end(); ++it) {

			if (country == (it->first)) {


				tempCountry = it->second;

				tempCountry->addCities(color, 1);
				//citiesInBoard

				real = false;
			}

		}




	}


}

void Player::moveOverLand(string action)
{
	cout << "Currently doing action : " << action << endl;
}
*/
void Player::buildCity(string action, Country* startingPoint)
{
	string color = getColor();	
	string newCity;
	Country* temp;
	bool existantCountry = false;

	for (int i = 0; i < armiesInBoard.size(); i++) {
		cout << "You have at least one army in theses countries :" << endl;
		cout << armiesInBoard.at(i)->getCountryName() << endl;
	}
	
	while (!existantCountry)
	{
		cout << " Where do you want to add a city ( choose a country) " << endl;
		cin >> newCity;

		for (int j = 0; j < armiesInBoard.size(); j++) {

			if (armiesInBoard.at(j)->getCountryName() == newCity && !existantCountry) {			
				addCity(armiesInBoard.at(j));
				armiesInBoard.at(j)->addCities(color, 1);
				existantCountry = true;
			}
		}
	}
	cout << " You currently have theses cities for the color : " << color << endl;
	for (int i = 0; i < citiesInBoard.size(); i++) {
		cout << citiesInBoard.at(i)->getCountryName() << endl;

	}


}

void Player::destroyArmy(string action, vector <Player*> allPlayers)
{
	string answer;
	string color = getColor();
	int sizeArmy;
	int playerId;
	string armyName;
	string colorDestroy;
	bool existantCountry = false;

	cout << "Here is the list of armies for each player" << endl;

	for (int i = 0; i < allPlayers.size(); i++) {

		sizeArmy = allPlayers.at(i)->armiesInBoard.size();

		if ((allPlayers.at(i)->getColor()) != (color)) {

			cout << " Player " << (i + 1) << endl;
			cout << " has the following armies" << endl;
			cout << " and has the following color : " << allPlayers.at(i)->getColor() << endl;
			for (int j = 0; j < sizeArmy; j++) {
				allPlayers.at(i)->armiesInBoard.at(j)->displayInfo();
			}

		}

	}

	cout << "from which player do you which to delete an army " << endl;
	cin >> playerId;


	colorDestroy = allPlayers.at(playerId)->getColor();

	while (!existantCountry)
	{
		cout << "which army do you wish to delete " << endl;
		cin >> armyName;	

		for (int j = 0; j < armiesInBoard.size(); j++) {
			
			if (allPlayers.at(playerId-1)->armiesInBoard.at(j)->getCountryName() == armyName && !existantCountry) {
				
				allPlayers.at(playerId-1)->armiesInBoard.at(j)->DestroyArmies(colorDestroy);
				allPlayers.at(playerId-1)->armiesInBoard.erase(armiesInBoard.begin() + j);

				cout << " You destroyed an army in " << armyName << " for the color " << colorDestroy << endl;
				existantCountry = true;
			}
		}		
	}

	for (int i = 0; i < allPlayers.size(); i++) {
		sizeArmy = allPlayers.at(i)->armiesInBoard.size();
		if ((allPlayers.at(i)->getColor()) != (color)) {
			cout << " Player " << (i + 1) << endl;
			cout << " has the following armies" << endl;
			cout << " and has the following color : " << allPlayers.at(i)->getColor() << endl;
			for (int j = 0; j < sizeArmy; j++) {
				allPlayers.at(i)->armiesInBoard.at(j)->displayInfo();
			}
		}
	}
}


bool Player::Ignore() {

	bool decision = false;
	string choice;
	cout << " Do you want to ignore this turn ? (Ignore or No) " << endl;
	cin >> choice;



	if (choice == "No") {
		decision = true;
	}

	return decision;

}

string Player::AndOrAction(string action, int part) {

	string answerP1;
	string answerP2;
	string answerWater;

	if (action.find("water") != string::npos) {

		return "lol";
	}
	else {


		if (part == 1) {

			answerP1 = action.substr(0, 13);
			cout << answerP1;
			return answerP1;
		}

		else {
			 answerP2 = action.substr(16, action.size()-1);
			 return answerP2;
		}
	}
	

}


void Player::makeAction(string actionTook, Country* startingPoint , vector<Player*> AllPlayers ) {

	string choice;

	if (Ignore()) {
		// ----------------------ADD ARMIES-------------------------
		if (actionTook == "Add 1 Army" || actionTook == "Add 3 Armies" || actionTook == "Add 3 Armies" || actionTook == "Add 2 Armies") {
			placeNewArmies(actionTook, startingPoint);
		}

		// ----------------------SPECIAL CASE-------------------------
		if (actionTook == "Destroy 1 Army or Build city") {
			cout << endl;
			cout << "Do you want to Destroy or Build ? (Destroy/Build)" << endl;
			cin >> choice;

			if (choice == "Destroy") {
				destroyArmy(actionTook, AllPlayers);
			}
			if (choice == "Build") {
				buildCity(actionTook, startingPoint);
			}
		}

		if (actionTook == "Add 2 Armies or Move 3 Armies" || actionTook == "Add 4 Armies or Move 2 Armies" || actionTook == "Add 3 Armies or Move 4 Armies" || actionTook == "Add 3 Armies or Move 3 Armies") {
			cout << endl;
			cout << "Do you want to Add or Move ? (Add/Move)" << endl;
			cin >> choice;

			if (choice == "Add") {
				actionTook = AndOrAction(actionTook, 1);
				placeNewArmies(actionTook, startingPoint);
			}
			if (choice == "Move") {
				actionTook = AndOrAction(actionTook, 2);
				moveArmies(actionTook,startingPoint);
			}
		}
		if (actionTook == "Move 2 Armies" || actionTook == "Move 6 Armies" || actionTook == "Move 3 armies" || actionTook == "Move 4 Armies" || actionTook == "Move 5 Armies" || actionTook == "Move 3 Armies via Ship (move over land and/or water)" || actionTook == "Move 4 Armies via Ship (move over land and/or water)" || actionTook == "Move 4 Armies" || actionTook == "Move 2 Armies via Ship (move over land and/or water)") {
			moveArmies(actionTook, startingPoint);
		}
		if (actionTook == "Build City") {
			buildCity(actionTook, startingPoint);
		}
		if (actionTook == "Destroy 1 Army and Add 1 Army") {
			destroyArmy(actionTook,AllPlayers);
			placeNewArmies(actionTook, startingPoint);
		}
	}


}