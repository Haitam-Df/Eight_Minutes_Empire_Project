#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include<string>
#include "map.h"
#include <cstdlib>
using namespace std;

//Continent implementation
Continent::Continent(string name) {
	continentName = name;
	unordered_map<string, Country*> subCountry;
}
Continent::~Continent() {

}
// add country to the continent object only if the country is not already added
void Continent::addSubCountry(string name,Country* country) {
	if (!isSubCountryExist(name)) {
		subCountry[name] = country;
		cout << "" << endl;
		cout << "Perfect Captain! , We added (" + name + ") in the continent ("+ country->getContinentName() + ")" << endl;
	}
	else {
		cout << "" << endl;
		cout << "Captain! , This Country (" + name + ") is already in (" +country->getContinentName() + ")" << endl;
	}
}


bool Continent::isSubCountryExist(string name) {
	return !(subCountry.find(name) == subCountry.end());
}

void Continent::displayInfo() {
	cout << "" << endl;
	cout << "" << endl;
	cout << "@@[" + continentName + "]" << endl;
	for (std::pair<std::string, Country*> element : subCountry) {
		element.second->displayInfo();
	}
}
string Continent::getName() {
	return continentName;
}
unordered_map<string, Country*> Continent::getSubCountry() {
	return subCountry;
}
//check if it exist a path that connect all country in the continent
bool Continent::recursiveCheckTree(unordered_map<string, int> arrOfEdgeCountry, queue<Country *> queueOfCountry) {
	arrOfEdgeCountry[queueOfCountry.front()->getCountryName()] = 1;
	for (std::pair<std::string, Country*> element : queueOfCountry.front()->getEdgeCountry()) {
		if (isSubCountryExist(element.first) && arrOfEdgeCountry[element.first] == 0) {
			queueOfCountry.push(element.second);
		}
	}
	queueOfCountry.pop();
	if (queueOfCountry.size() == 0) {
		bool allchecked = true;
		for (std::pair<std::string, int> element2 : arrOfEdgeCountry) {
			if (element2.second == 0) {
				allchecked = false;
				break;
			}
		}
		return allchecked;
	}
	else {
		return recursiveCheckTree(arrOfEdgeCountry, queueOfCountry);
	}
}

bool Continent::isConnectedContinent() {
	if (subCountry.size() < 2) {
		cout << "" << endl;
		cout << "Captain!, the continent (" + continentName + ") is a connected Continent graph!" << endl;
		return 1;
	}
	else {
		unordered_map<string, int> subCountryToCompare;
		for (std::pair<std::string, Country*> element : subCountry) {
			subCountryToCompare[element.first] = 0;
		}
		queue<Country *> queueOfCountry;

		for (std::pair<std::string, Country*> element2 : subCountry) {
			queueOfCountry.push(element2.second);
			break;
		}

		if (recursiveCheckTree(subCountryToCompare, queueOfCountry)) {
			cout << "" << endl;
			cout << "Captain!, the continent (" + continentName + ") is a connected Continent graph!" << endl;
			return 1;
		}
		cout << "" << endl;
		cout << "Captain!, the continent (" + continentName + ") is a NOT A connected Continent graph!" << endl;
		return 0;
	}
}

int Continent::computeScoreC(string colorP)
{
	int red = 0;
	int blue = 0;
	int yellow = 0;
	int green = 0;
	int white = 0;
	int colorArr[] = { red,blue,yellow,green ,white};
	int domColorn = 0;
	string domColor = "NONE";
	unordered_map<string, Country*> ownedCountries;
	
	// initialize the array of countries being owned (having armies on it with no repetions)
	for (std::pair<std::string, Country*> element : subCountry)
	{
		bool check = false;
		for (std::pair<std::string, Country*> element2 : ownedCountries) 
		{
			if (element.first == element2.first)
			{
				check = true;
			}
		}

		if (check)
		{
		}
		else 
		{
			if (element.second->hasOwner()) {
				ownedCountries[element.first] = element.second;
			}
		}
	}

	// Sums up the number of countries owned for each Player color
	for (std::pair<std::string, Country*> element : ownedCountries) 
	{
		element.second->setOwnedColor();

		if (element.second->getOwnerColor() == "red") 
		{
			colorArr[0]++;
		}
		else if (element.second->getOwnerColor() == "blue")
		{
			colorArr[1]++;
		}
		else if (element.second->getOwnerColor() == "yellow")
		{
			colorArr[2]++;
		}
		else if(element.second->getOwnerColor() == "green")
		{
			colorArr[3]++;
		}
		else if (element.second->getOwnerColor() == "white") 
		{
			colorArr[4]++;
		}
	}

	// Sets the dominant Player color based on the above calculation
	for (int i = 0; i < sizeof(colorArr); i++)
	{
		if (colorArr[i] > domColorn)
		{
			domColorn = colorArr[i];
			switch (i)
			{
			case 0:
				domColor = "red"; 
				break;
			case 1:
				domColor = "blue"; 
				break;
			case 2:
				domColor = "yellow"; 
				break;
			case 3:
				domColor = "green"; 
				break;
			case 4:
				domColor = "white"; 
				break;
			}
		}
	}
	if (colorP == domColor) {
		return 1;
	}
	else {
		return 0;
	}
}




//Country implementation
Country::Country(string name) {
	countryName = name;
	continentName = "";
	unordered_map<string, Country*> edgeCountry;
	armies["red"] = new int(0);
	armies["blue"] = new int(0);
	armies["green"] = new int(0);
	armies["yellow"] = new int(0);
	armies["white"] = new int(0);

	cities["red"] = new int(0);
	cities["blue"] = new int(0);
	cities["green"] = new int(0);
	cities["yellow"] = new int(0);
	cities["white"] = new int(0);
}
Country::~Country() { 

}
// add country to the edge of the Country object if this country is not already an edge country
void Country:: addEdgeCountry(string name,Country* country) {
	if (!isEdgeCountryExist(name)) {
		edgeCountry[name] = country;
		cout << "" << endl;
		cout << "Perfect Captain! , We connected ("+name+") to ("+ getCountryName()+")" << endl;
	}
	else {
		cout << "" << endl;
		cout << "Captain! , This Country ("+name+") is already connected to ("+ getCountryName()+")" << endl;
	}
}
unordered_map<string, Country*> Country::getEdgeCountry() {
	return edgeCountry;
}
void Country::setContinentName(string name) {
	continentName = name;
}

bool Country::hasOwner() {
	for (std::pair<std::string, int*> element : armies) {
		if (*element.second > 0) {
			return 1;
		}
	}
	return 0;
}

void Country::setOwnedColor() {
	string colorDom = "";
	int armyDom = 0;

	for (std::pair<std::string, int*> element : armies) {
		if (*element.second > armyDom)
		{
			armyDom = *element.second;
			colorDom = element.first;
		}
	}
	ownerColor = colorDom;

	cout << endl;
	cout << countryName << " IS OWNED BY : " << ownerColor;
}

void Country::addArmies(string color, int nbOfArmies) {
	*armies[color] += nbOfArmies;
}
void Country::addCities(string color, int nbOfCities) {
	*cities[color] += nbOfCities;
}
void Country::DestroyArmies(string color) {
	*armies[color] -= 1;
}

void Country::displayInfo() {
	cout << "" << endl;
	cout << "@["+countryName+"]" << endl;
	cout << "[Continent]" << endl;
	cout << "-" + getContinentName() << endl;
	if (edgeCountry.size() > 0) {
		cout << "[Edge Countries]" << endl;
		for (std::pair<std::string, Country*> element : edgeCountry) {
			cout << "-" + element.first << endl;;
		}
	}
	cout << "[Armies]" << endl;
	for (std::pair<std::string, int*> element : armies) {
		cout << "-" + element.first << " :: "<<*element.second<< endl;;
	}
	cout << "[Cities]" << endl;
	for (std::pair<std::string, int*> element : cities) {
		cout << "-" + element.first << " :: " << *element.second << endl;;
	}
}
void Country::setOwner(string player) {
	ownerColor = player;
}
bool Country::isEdgeCountryExist(string name) {
	return !(edgeCountry.find(name) == edgeCountry.end());
}
string Country::getCountryName() {
	return countryName;
}
string Country::getContinentName() {
	return continentName;
}
int Country::getEdgeCountrySize() {
	return edgeCountry.size();
}

//sets the owner of the country (most armies) and test wheter the Player owns it or not
int Country::computeScoreR(string colorP)
{
	
	setOwnedColor();

	return (ownerColor == colorP);

}

string Country::getOwnerColor()
{
	return ownerColor;
}


Map* Map::m_instance = NULL;

Map* Map::getInstance()
{
	if (m_instance == NULL) {
		m_instance = new Map();
	}
	else {
		cout << " There is already an map in this game ! " << endl;
		return m_instance;
	}
	return(m_instance);
}
void Map::releaseInstance()
{
	if (m_instance != NULL) {
		delete Map::m_instance;
		m_instance = NULL;
	}
}



//Map implementation
Map::Map() {
	unordered_map<string, Country*> allCountry;
	unordered_map<string, Continent*> allContinent;
}
Map::~Map() {
}

void Map::displayAllCountry() {
	cout << endl;
	cout << "This is all Country" << endl;
	for (std::pair<std::string, Country*> element : allCountry) {
		
		cout << "- " << element.first << endl;
	}
}
//create continent if does not already exist
bool Map::createContinent(string continentName) {
	if (!isContinentExist(continentName)) {
		Continent* continent = new Continent(continentName);
		allContinent[continentName] = continent;
		cout << "" << endl;
		cout << "Captain ! , This continent ("+continentName+") is now created!" << endl;
		return 1;
	}
	else {
		cout << "" << endl;
		cout << "Captain ! , This continent ("+continentName+") already exist!" << endl;
		return 0;
	}
}

string Map::getRandomCountry() {
	int randomNumber = rand() % allCountry.size();
	int counter = 0;
	for (std::pair<std::string, Country*> element : allCountry) {
		if (counter == randomNumber) {
			return element.first;
		}
		counter++;
	}
}
bool Map::displayContinentInfo(string ContinentName) {
	if (isContinentExist(ContinentName)) {
		allContinent[ContinentName]->displayInfo();
		return 1;
	}
	else {
		cout << "" << endl;
		cout << "Captain!, this continent does not exist" << endl;
		return 0;
	}
}
Country* Map::getCountryByName(string countryName) {
	return allCountry[countryName];
}

bool Map::displayCountryInfo(string countryName) {
	if (isCountryExist(countryName)) {
		allCountry[countryName]->displayInfo();
		return 1;
	}
	else {
		cout << "" << endl;
		cout << "Captain!, this country does not exist" << endl;
		return 0;
	}
}
void Map::addArmyToCountry(string countryName, string color, int nbOfArmy) {
	if (isCountryExist(countryName)) {
		allCountry[countryName]->addArmies(color, nbOfArmy);
		cout << endl;
		cout << nbOfArmy << " " << color << " (army/armies) have been added to " << countryName << endl;
	}
}
void Map::addCityToCountry(string countryName, string color, int nbOfCity) {
	if (isCountryExist(countryName)) {
		allCountry[countryName]->addCities(color, nbOfCity);
		cout << endl;
		cout << nbOfCity << " " << color << " (city/cities) have been added to " << countryName << endl;
	}
}
// connect a country to a continent (Every Country needs a Continent)
bool Map::connectToContinent(string continentName,string countryName){
	if (isContinentExist(continentName)) {
		if (allCountry[countryName]->getContinentName() == "") {
			allCountry[countryName]->setContinentName(continentName);
			allContinent[continentName]->addSubCountry(countryName, allCountry[countryName]);
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}
void Map::deleteMap() {
	for (std::pair<std::string, Continent*> element : allContinent) {
		delete element.second;
		element.second = NULL;
	}
	

	for (std::pair<std::string, Country*> element : allCountry) {
		delete element.second;
		element.second = NULL;
	}
}

bool Map::createCountry(string countryName) {
	if (!isCountryExist(countryName)) {
		Country* country = new Country(countryName);
		allCountry[countryName] = country;
		cout << "" << endl;
		cout << "Captain ! , This Country (" + countryName + ") is now created!" << endl;

		return 1;
	}
	else {
		cout << "" << endl;
		cout << "Captain ! , This Country (" + countryName + ") ALREADY EXIST!" << endl;
		return 0;
	}
}

void Map::showMap() {
	for (std::pair<std::string, Continent*> element : allContinent) {
		element.second->displayInfo();
	}
}

//Connect a country to another country, this method allow the AddEdgecountry to be use
bool Map::connectToCountry(string countryFrom,string countryTo) {
	if (!allCountry[countryFrom]->isEdgeCountryExist(countryTo)) {
		allCountry[countryFrom]->addEdgeCountry(countryTo,allCountry[countryTo]);
		return 1;
	}
	else {
		cout << "" << endl;
		cout << "Captain! , ("+countryFrom+") and ("+countryTo+") are already connected!";
		return 0;
	}
}
Continent* Map::getContinent(string name) {
	return allContinent[name];
}
Country* Map::getCountry(string name) {
	return allCountry[name];
}
bool Map::isCountryExist(string name) {
	return !(allCountry.find(name) == allCountry.end());
}
bool Map::isContinentExist(string name) {
	return !(allContinent.find(name) == allContinent.end());
}

void Map::startGame() {
	cout << "" << endl;
	cout << "The GAME CAN START" << endl;
}
bool Map::isConnectedMap() {
	bool checked = true;
	for (std::pair<std::string, Continent*> element : allContinent) {
		if (element.second->isConnectedContinent() == 0) {
			checked = false;
			break;
		}
	}
	if (!checked) {
		cout << "" << endl;
		cout << "Captain! This is not a Connected Graph MAP" << endl;
		
		return 0;
	}
	else {
		unordered_map<string, int> subCountryToCompare;
		for (std::pair<std::string, Country*> element : allCountry) {
			subCountryToCompare[element.first] = 0;
		}
		queue<Country *> queueOfCountry;
		for (std::pair<std::string, Country*> element2 : allCountry) {
			queueOfCountry.push(element2.second);
			break;
		}
		if (recursiveCheckTree(subCountryToCompare, queueOfCountry)) {
			cout << "" << endl;
			cout << "Captain!, we have a full Connected Graph Map!" << endl;
			return 1;
		}
		else {
			cout << "" << endl;
			cout << "Captain!, This is NOT A Connected Graph Map!" << endl;
			return 0;
		}
	}
}
bool Map::recursiveCheckTree(unordered_map<string, int> arrOfCountry, queue<Country *> queueOfCountry) {
	arrOfCountry[queueOfCountry.front()->getCountryName()] = 1;
	for (std::pair<std::string, Country*> element : queueOfCountry.front()->getEdgeCountry()) {
		if (arrOfCountry[element.first] == 0) {
			queueOfCountry.push(element.second);
		}
	}
	queueOfCountry.pop();
	if (queueOfCountry.size() == 0) {
		bool allchecked = true;
		for (std::pair<std::string, int> element2 : arrOfCountry) {
			if (element2.second == 0) {
				allchecked = false;
				break;
			}
		}
		return allchecked;
	}
	else {
		return recursiveCheckTree(arrOfCountry, queueOfCountry);
	}

}

unordered_map<string, Continent*> Map::getAllContinent() {
	return allContinent;
}

//Main question to Manually create a Map
void Map::askBuildMapQuestion() {

	while (true) {
		cout << "" << endl;
		cout << "" << endl;
		cout << "What do you want to do ?" << endl;
		cout << "1) Create Continent" << endl;
		cout << "2) Create Country" << endl;
		cout << "3) Connect Country" << endl;
		cout << "4) Get Continent info" << endl;
		cout << "5) Get Country info" << endl;
		cout << "6) Show Map" << endl;
		cout << "7) Is the map connected?" << endl;
		cout << "8) End" << endl;

		int value;
		cin >> value;

		switch (value) {
		case 1: {
			cout << "" << endl;
			cout << "What is the name of the continent?" << endl;
			string name;
			cin >> name;

			createContinent(name);
			break;
		}
		case 2:
			cout << "" << endl;
			if (allContinent.size() != 0) {
				cout << "What is the name of the country?" << endl;
				string countryName;
				cin >> countryName;

				if (createCountry(countryName)) {


					while (true) {
						cout << "" << endl;
						cout << countryName + " is in which continent?" << endl;
						for (std::pair<std::string, Continent*> element : allContinent) {
							cout << "-" + element.first << endl;
						}
						string continentName;
						cin >> continentName;
						if (connectToContinent(continentName, countryName)) {
							if (allContinent[continentName]->getSubCountry().size() > 1) {
								while (true) {
									cout << "" << endl;
									cout << countryName + " is connected to which country?" << endl;
									for (std::pair<std::string, Country*> element : allContinent[continentName]->getSubCountry()) {
										cout << "-" + element.first << endl;
									}
									string countrySelected;
									cin >> countrySelected;
									if (countryName == countrySelected) {
										cout << "" << endl;
										cout << "AHAHHA Captain, I think you drunk to much Tequila, you cannot connect a country to itself!";
										continue;
									}
									else {
										if (allContinent[continentName]->isSubCountryExist(countrySelected)) {
											if (connectToCountry(countryName, countrySelected) && connectToCountry(countrySelected,countryName)) {
												break;
											}
										}
										else {
											cout << "" << endl;
											cout << "Captain! this country does not exist in this continent!";
										}
									}
								}
								break;
							}
							else {
								break;
							}
						}
						else {
							continue;
						}


					}

				}

			}
			else {
				cout << "" << endl;
				cout << "Captain! , you need to create a continent first!" << endl;
			}
			break;
		case 3:
			if (allCountry.size() > 1) {
				while (true) {
					cout << "" << endl;
					cout << "Captain!, which country you want to create connection?" << endl;
					for (std::pair<std::string, Country*> element : allCountry) {
						cout << "-" + element.first << endl;
					}
					string countrySelected;
					cin >> countrySelected;
					if (isCountryExist(countrySelected)) {
						cout << "" << endl;
						cout << "Captain!,  (" + countrySelected + ") is connected with which country?" << endl;
						for (std::pair<std::string, Country*> element : allCountry) {
							cout << "-" + element.first << endl;
						}
						string countrySelected2;
						cin >> countrySelected2;
						if (countrySelected == countrySelected2) {
							cout << "" << endl;
							cout << "AHAHHA Captain, I think you drunk to much Tequila, you cannot connect a country to itself!" << endl;
							continue;
						}
						else {
							if (isCountryExist(countrySelected2)) {
								if (connectToCountry(countrySelected, countrySelected2) && connectToCountry(countrySelected2,countrySelected)) {
									break;
								}
							}
						}
					}
				}
			}
			else {
				cout << "" << endl;
				cout << "Captain!, you need at least 2 countries in the map to make connection!" << endl;
			}
			break;
		case 4:

			if (allContinent.size() > 0) {
				while (true) {
					cout << "" << endl;
					cout << "Captain!, give me a continent and I'll bring you the info" << endl;
					for (std::pair<std::string, Continent*> element : allContinent) {
						cout << "-" + element.first << endl;
					}
					string continentSelected;
					cin >> continentSelected;
					if (displayContinentInfo(continentSelected)) {
						break;
					}
				}
			}
			else {
				cout << "" << endl;
				cout << "Captain!, you need to create a continent first!" << endl;
			}
			break;
		case 5:
			if (allCountry.size() > 0) {
				while (true) {
					cout << "" << endl;
					cout << "Captain!, give me a country and I'll bring you the info" << endl;
					for (std::pair<std::string, Country*> element : allCountry) {
						cout << "-" + element.first << endl;
					}
					string countrySelected;
					cin >> countrySelected;
					if (displayCountryInfo(countrySelected)) {
						break;
					}
				}
			}
			else {
				cout << "" << endl;
				cout << "Captain!, you need to create a country first!" << endl;
			}
			break;
		case 6:
			if (allContinent.size() > 0) {
				for (std::pair<std::string, Continent*> element : allContinent) {
					element.second->displayInfo();
				}
			}
			else {
				cout << "" << endl;
				cout << "Captain!, you need to create a continent first!" << endl;
			}
			break;
		case 7: 
			if (allContinent.size() != 0) {
				isConnectedMap();
			}
			else {
				cout << "" << endl;
				cout << "Captain!, you need to create a continent first!" << endl;
			}
			break;


		case 8:
			if (allContinent.size() == 0) {
				cout << "" << endl;
				cout << "You did not create a continent" << endl;
				continue;
			}
			if (allCountry.size() == 0) {
				cout << "" << endl;
				cout << "You need to build at least one country" << endl;
				continue;
			}
			if (isConnectedMap()) {
				startGame();
			}
			exit(0);
			break;
		default:
			cout << "" << endl;
			cout << "Captain!, enter a valid selection!" << endl;
			break;
		}
		}
	}



