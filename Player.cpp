
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

Player::Player(int year, Deck* deck, int money, int Id)
{
	bidding = new Bidding(year, money);
	hand = new Hand(deck);
	coins = new int(money);
	id = new int(Id);
}
Player::Player(int year, Deck* deck, int money, int Id, bool CPU, int strat)
{
	bidding = new Bidding(year, money);
	hand = new Hand(deck);
	coins = new int(money);
	id = new int(Id);
	isCPU = new bool(CPU);
	userStrategy = new PlayerStrategies(strat);
}
Bidding* Player::getBiddingInstance() {
	return bidding;
}
PlayerStrategies* Player::getUserStrat() {
	return userStrategy;
}

void Player::setStatus(bool change)
{
	delete isCPU;
	isCPU = new bool(change);
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
bool* Player::getStatus() {
	return isCPU;
}

void Player::addOwnCountry(string regionsName, Country* country)
{
	ownCountry[regionsName] = country;
	cout << endl;
	cout << regionsName << " is now yours beware of the ennemies !" << endl;
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
		}
		else if (hand->getHand()[i]->good == "Forest")
		{
			tree++;
		}
		else if (hand->getHand()[i]->good == "Ore")
		{
			ore++;
		}
		else if (hand->getHand()[i]->good == "Carrot")
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
	cout  << "[PLAYER] " << *getId() << endl;
	cout  << "[COINS] " << *getCoins() << endl;
	cout << "[COLOR] :" << getColor() << endl;
	cout << "[ARMIES ON MAP] " << endl;
	for (int x = 0; x < armiesInBoard.size(); x++) {
		cout << "  - "<<armiesInBoard[x]->getCountryName() << endl;
	}
	cout << "[CITIES ON MAP] " << endl;
	for (int x = 0; x < citiesInBoard.size(); x++) {
		cout << "  - " << citiesInBoard[x]->getCountryName() << endl;
	}

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

// This method is used to move armies from a starting contry to another contry, the string action is the full card string that will be used to extract how many moves a player has.
// The method uses the concept of move and explore, if you decide to move this is the location that your army will be move.  However you can also decide to explore, which will give you option to hope from one country to another X times
// before you eventually settle down and move.  The function will not let the user explore if he only has 1 move left.
void Player::moveArmies(string action, Country* startingPoint) {

	string color = getColor();
	int move;
	int current = 0;
	int answer;
	int debut;
	string start;
	string userAnswer;
	bool real = false;
	unordered_map<string, Country*> temp;
	unordered_map<string, Country*> tempStart;
	vector<Country*> currentEdge;
	int j;
	string tmp;
	stringstream ss(action);
	ss >> tmp >> move;


	cout << "You have an army in these countries :" << endl;
	for (int i = 0; i < armiesInBoard.size(); i++) {

		// we get the name of each country that the player has an army in
		cout <<(i+1)<<")"<< armiesInBoard.at(i)->getCountryName() << endl;
	}
	cout << endl;

	cout << "Please select the starting country to move an army (write the number)" << endl;
	cin >> answer;


	start = armiesInBoard.at(answer-1)->getCountryName();   // we want to keep the first country in a string because we are going to delete the army from there and move it to the new location
	debut = answer - 1;   // we also keep the location of the starting point to remove it after


	cout << "here is the list of country related to " << armiesInBoard.at(answer-1)->getCountryName() << endl;

	temp = armiesInBoard.at(answer - 1)->getEdgeCountry();
	tempStart = temp;
	currentEdge.clear();
	cout << " List of edge countries : " << endl;               // this will print the edge countries of the chosen one
	j = 1;
	for (auto it = temp.begin(); it != temp.end(); ++it) {
		currentEdge.push_back(it->second);
		cout <<j<<") " << it->first << endl;
		j++;
	}

	do {
		if ((move - 1) == 0) {   // if you only have one move , we will force you to  select a Country to move to
			cout << "you have to pick a country to move the army because you have no more move left" << endl;
			userAnswer = "move";
			cout << endl;
			cout << endl;
			cout << "Select a country to move the army (write the number) " << endl;
			cin >> answer;
			move -= 1;
		}

		else {                  // explore or move , you select if you want to go further or to move to that country
			cout << " do you want to move armies or explore the map to find a country? (explore or move) REMEMBER YOU HAVE "
				<< move << " MOVES LEFT" << endl;
			cin >> userAnswer;
			cout << endl;
			cout << endl;
		}


		if (userAnswer == "explore") {
			move -= 1;
			cout << "Which Country do you want to explore? (write the number)" << endl;
			cin >> answer;
			cout << endl;
			cout << endl;
			
			temp = temp.at(currentEdge.at(answer - 1)->getCountryName())->getEdgeCountry();            // we get the new unordered map of edge countries to print it

			cout << " List of edge countries of "<< currentEdge.at(answer - 1)->getCountryName() <<": " << endl;
			currentEdge.clear();

			j = 1;
			for (auto it = temp.begin(); it != temp.end(); ++it) {
				currentEdge.push_back(it->second);
				cout << j << ") " << it->first << endl;
				j++;
			}

			if (move == 0) {
				userAnswer = "move";
			}
		}

		// if they move, we have to remove the armies from the country vector and also , from the player ArmiesInBoard vector
		else if (userAnswer == "move") {

			if (move > 1) {
				cout << "To which country do you want to move an army  (write the number)?" << endl;
				cin >> answer;
				move -= 1;
			}


			for (int i = 0; i < armiesInBoard.size(); i++) {

				if (armiesInBoard.at(i)->getCountryName() == start) {      // we kept the starting country so we can remove it from both arrays
					armiesInBoard.at(i)->DestroyArmies(color);
					armiesInBoard.erase(armiesInBoard.begin() + i);
					addArmy(currentEdge.at(answer-1));                         // at the same time we can the new army in ArmyInBoard
					break;
				}
			}

			temp.at(currentEdge.at(answer - 1)->getCountryName())->addArmies(color, 1);               // add an army to the vector of that Country
			currentEdge.clear();

			if (move != 0) {                // same as the one before , we select which army we want to move , etc
				cout << " You have an army in these countries :" << endl;
				for (int i = 0; i < armiesInBoard.size(); i++) {


					cout <<(i+1)<<") "<<armiesInBoard.at(i)->getCountryName() << endl;
				}

				cout << "Please select the starting country to move an army  (write the number)" << endl;
				cin >> answer;
				cout << endl;
				cout << endl;

				start = armiesInBoard.at(answer - 1)->getCountryName(); 
				debut = answer - 1; 


				cout << "here is the list of country related to " << armiesInBoard.at(answer-1)->getCountryName() << endl;

				temp = armiesInBoard.at(answer - 1)->getEdgeCountry();
				tempStart = temp;
				cout << " List of edge countries : " << endl;
				j = 1;
				for (auto it = temp.begin(); it != temp.end(); ++it) {
					currentEdge.push_back(it->second);
					cout << j << ") " << it->first << endl;
					j++;
				}

			}


		}
		else {
			// if they write anything else than , explore or move
			if ((move - 1) == 0) {
				cout << "You dont have enough moves to explore" << endl;
			}
			else {
				cout << "Please write explore or move" << endl;
			}
		}

	} while (move != 0);


	// final result 
	cout << endl << endl;
	cout << "Here is your current number of armies and where they are : " << endl;
	cout << " You have " << armiesInBoard.size() << " armies" << endl;
	cout << " List of armies: " << endl;
	for (int i = 0; i < armiesInBoard.size(); i++) {

		// we get the name of each country that the player has an army in
		cout << armiesInBoard.at(i)->getCountryName() << endl;
	}
	cout << endl;
	cout << endl;

}


// This method is used to place new armies either at the starting point or in a country where you have built a city,the string action is the full card string that will be used to extract how many armies can be placed by the  player 
// The method will verify that the player never has more than 14 armies in play.
// whenever an army is added  
void Player::placeNewArmies(string action, Country* startingPoint)
{
	// if the size of armies is 14 , we cannot place new armies
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

		//the player dosent have cities it will automatically add the armies at the starting point
		if (citiesInBoard.size() == 0) {
			cout << " You don't have any cities , so armies are added to the starting point !" << endl;
			for (int i = 0; i < armies; i++) {
				if (armiesInBoard.size() == 14) {
					cout << " you have 14 armies , you cannot have more" << endl;
					return;
				}
				addArmy(startingPoint);            // add to the vector of the player
			}
			startingPoint->addArmies(color, armies);                  // add to the vector of the country
			armies = 0;
			break;
		}
		// user has cities however, he can decide to iadd new armies to the starting point if he prefers
		else {
			cout << " You do have  cities ,However would you like to add armies to the starting point (y/n)" << endl;
			if (*this->getStatus()) {
				answer = "y";
				cout << answer;
			}
			else {
				cin >> answer;
			}
			if (answer == "y") {
				while (!(nb <= armies && nb >= 1)) {
					cout << "how many armies do you want between 1 and " << armies << endl;
					if (*this->getStatus()) {
						nb = armies;
					}
					else { cin >> nb; }
				}
				for (int i = 0; i < nb; i++) {
					// each time that we add an army , we verify that we dont exceed 14
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

		// if the player has cities  , we will display each one and ask the player if he wants to add a number of armies in that city.

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
			else {
				cout << "You still have to place " << armies << " armies";
				cout << endl;
			}

			nb = 0;
		}

	}


	cout << "For now , theses are the armies you have " << endl << endl;

	for (int i = 0; i < armiesInBoard.size(); i++) {

		armiesInBoard.at(i)->displayInfo();
	}
	cout << endl;

}

// Both functions have been replaced with moveArmies as per the instruction by the professor 

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


// this method is used to build a city in a country where a player has an army 

void Player::buildCity(string action, Country* startingPoint)
{
	string color = getColor();
	string newCity;
	Country* temp;
	bool existantCountry = false;

	// we print the countries that we have the armies in.
	cout << "You have at least one army in theses countries :" << endl;
	for (int i = 0; i < armiesInBoard.size(); i++) {

		cout << armiesInBoard.at(i)->getCountryName() << endl << endl;

	}
	
	while (!existantCountry)
	{
		cout << " Where do you want to add a city ( choose a country) " << endl;
		if (*this->getStatus()) {newCity = armiesInBoard.at(0)->getCountryName();}
		else {
			getline(cin, newCity);
			getline(cin, newCity);
		}
		// we verify in  which  country the player wants to create a city 
		for (int j = 0; j < armiesInBoard.size(); j++) {
			if (armiesInBoard.at(j)->getCountryName() == newCity && !existantCountry) {
				addCity(armiesInBoard.at(j));
				armiesInBoard.at(j)->addCities(color, 1);
				existantCountry = true;
			}
		}

		if (!existantCountry) {
			cout << " You made a mistake when entering the country" << endl;
		}

	}
	// print out to the user the cities he has 
	cout << " You currently have theses cities for the color : " << color << endl;
	for (int i = 0; i < citiesInBoard.size(); i++) {
		cout << citiesInBoard.at(i)->getCountryName() << endl;

	}


}

// This method is used to  destroy armies of another player  ,the string action is the full card string that will be used to extract how many armies can be destroyed by the  player 
void Player::destroyArmy(string action, vector <Player*> allPlayers)
{
	string answer;
	string color = getColor();
	int sizeArmy;
	int playerId;
	string armyName;
	string colorDestroy;
	bool existantCountry = false;
	vector<Country*> temp;
	int random = 0;
	cout << "Here is the list of armies for each player" << endl;

	// print out the list of armies for each player 
	for (int i = 0; i < allPlayers.size(); i++) {

		sizeArmy = allPlayers.at(i)->armiesInBoard.size();

		if ((allPlayers.at(i)->getColor()) != (color)) {
			cout << endl << endl;
			cout << " Player " << (i + 1) << endl;
			cout << " has the following armies" << endl;
			cout << " and has the following color : " << allPlayers.at(i)->getColor() << endl;
			for (int j = 0; j < sizeArmy; j++) {
				allPlayers.at(i)->armiesInBoard.at(j)->displayInfo();
			}

		}

	}
	if (allPlayers.size() == 1){
		random = 1;
	}
	if (allPlayers.size() > 1){
		random = rand() % (allPlayers.size())+1;
	}
	// user input on which army the player wishes to destroy 
	cout << "from which player do you which to delete an army " << endl;
	if (*this->getStatus()) {
		playerId = random;
		cout << playerId << endl;;
	}else{ cin >> playerId; }
	
	temp = allPlayers.at(playerId - 1)->armiesInBoard;

	colorDestroy = allPlayers.at(playerId - 1)->getColor();

	// in this while loop, 
	// we select the army that we want to delete from the player choosen before, then we make sure to delete from his vector of armies and also from the vector of the country
	while (!existantCountry)
	{
		cout << "which army do you wish to delete " << endl;
		if (*this->getStatus()) {
			armyName = allPlayers.at(playerId - 1)->armiesInBoard.at(0)->getCountryName();
			cout << armyName<<endl;
		}
		else {
			getline(cin, armyName);
			getline(cin, armyName);

		}
		for (int j = 0; j < armiesInBoard.size(); j++) {

			if (allPlayers.at(playerId - 1)->armiesInBoard.at(j)->getCountryName() == armyName && !existantCountry) {

				allPlayers.at(playerId - 1)->armiesInBoard.at(j)->DestroyArmies(colorDestroy);
				temp.erase(temp.begin() + j);
				(allPlayers.at(playerId - 1)->armiesInBoard) = temp;

				cout << " You destroyed an army in " << armyName << " for the color " << colorDestroy << endl;
				existantCountry = true;
			}
		}
	}
	// print out the armies for each player 
	for (int i = 0; i < allPlayers.size(); i++) {
		sizeArmy = allPlayers.at(i)->armiesInBoard.size();
		if ((allPlayers.at(i)->getColor()) != (color)) {
			cout << " Player " << (i + 1) << endl;
			cout << " has the following armies" << endl;
			cout << " and has the following color : " << allPlayers.at(i)->getColor() << endl;
			for (int j = 0; j < sizeArmy; j++) {
				allPlayers.at(i)->armiesInBoard.at(j)->displayInfo();
				cout << endl << endl;
			}
			cout << endl << endl << endl << endl;
		}
	}
}

// with this nethod , the user will be able to pick a card , keep it in his hand and skip his turn
bool Player::Ignore(vector<string>* actions) {

	bool decision = false;
	string choice;

	while (!decision) {


		if (*this->getStatus()) {
			choice = this->getUserStrat()->getAction();
			
		}
		else {
			cout << " Do you want to ignore this turn ? (Ignore or No) " << endl;
			cin >> choice;
		}

		if (choice == "No" || choice == "no") {
			decision = true;
		}
		else if (choice == "Ignore" || choice == "ignore") {
			cout << "You will ignore this turn " << endl;
			actions->push_back("- Chose to ignore this turn");
			cout << endl;
			cout << endl;
			return false;
		}

	}

	return decision;

}
// this method is used to let the user choose the action between the AND/OR of a card
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
			answerP2 = action.substr(16, action.size() - 1);
			return answerP2;
		}
	}


}


void Player::makeAction(string actionTook, Country* startingPoint , vector<Player*> AllPlayers, vector<string>* actions) {

	string choice;
	bool goodSelect = true;
	actions->push_back("- " + actionTook);
	while (goodSelect) {
		choice;
		if (Ignore(actions)) {
			// ----------------------ADD ARMIES-------------------------
			if (actionTook == "Add 1 Army" || actionTook == "Add 3 Armies" || actionTook == "Add 3 Armies" || actionTook == "Add 2 Armies") {
				placeNewArmies(actionTook, startingPoint);
				goodSelect = false;
			}

			// ----------------------SPECIAL CASE-------------------------
			if (actionTook == "Destroy 1 Army or Build city") {
				cout << endl;
				cout << "Do you want to Destroy or Build ? (Destroy/Build)" << endl;

				if (*this->getStatus()) {
					choice = "destroy";
					cout << choice << endl;
				}
				else {
					cin >> choice;
				}

				cout << endl;
				cout << endl;
				if (choice == "Destroy" || choice == "destroy") {
					actions->push_back("- Chose to Destroy");
					destroyArmy(actionTook, AllPlayers);
					goodSelect = false;
				}
				if (choice == "Build" || choice == "build") {
					actions->push_back("- Chose to Build");
					buildCity(actionTook, startingPoint);
					goodSelect = false;
				}
				else if (goodSelect) {
					cout << " Please write Destroy or Build" << endl;

				}
			}

			if (actionTook == "Add 2 Armies or Move 3 Armies" || actionTook == "Add 4 Armies or Move 2 Armies" || actionTook == "Add 3 Armies or Move 4 Armies" || actionTook == "Add 3 Armies or Move 3 Armies") {
				cout << endl;
				cout << "Do you want to Add or Move ? (Add/Move)" << endl;

				if (*this->getStatus()) {
					choice = "add";
					cout << choice << endl;
				}
				else {
					cin >> choice;
				}
				cout << endl;
				cout << endl;
				if (choice == "Add" || choice == "add") {
					actions->push_back("- Chose to Add armies");
					actionTook = AndOrAction(actionTook, 1);
					placeNewArmies(actionTook, startingPoint);
					goodSelect = false;
				}
				if (choice == "Move" || choice == "move") {
					actions->push_back("- Chose to Move armies");
					actionTook = AndOrAction(actionTook, 2);
					moveArmies(actionTook, startingPoint);
					goodSelect = false;
				}
				else if (goodSelect) {
					cout << " Please write Add or Move" << endl;

				}
			}
			if (actionTook == "Move 2 Armies" || actionTook == "Move 6 Armies" || actionTook == "Move 3 armies" || actionTook == "Move 4 Armies" || actionTook == "Move 5 Armies" || actionTook == "Move 3 Armies via Ship (move over land and/or water)" || actionTook == "Move 4 Armies via Ship (move over land and/or water)" || actionTook == "Move 4 Armies" || actionTook == "Move 2 Armies via Ship (move over land and/or water)") {
				moveArmies(actionTook, startingPoint);
				goodSelect = false;
			}
			if (actionTook == "Build City") {
				buildCity(actionTook, startingPoint);
				goodSelect = false;
			}
			if (actionTook == "Destroy 1 Army and Add 1 Army") {
				destroyArmy(actionTook, AllPlayers);
				placeNewArmies(actionTook, startingPoint);
				goodSelect = false;
			}
		}
		else { goodSelect = false; }

	}
}