#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include<queue>
#include "Player.h"
#include <cstdlib>

using namespace std;

class Country;
class Player;



class Continent {

public:
	Continent(string name);
	~Continent();
	void addSubCountry(string name, Country* country);
	bool isSubCountryExist(string name);
	unordered_map<string, Country*> getSubCountry();
	string getName();
	void displayInfo();
	bool isConnectedContinent();
	bool recursiveCheckTree(unordered_map<string, int> arrOfEdgeCountry, queue<Country*> queueOfCountry);
	int computeScoreC(string colorP);


private:
	unordered_map<string, Country*> subCountry;
	string continentName;
};

class Country {
public:
	Country(string name);
	~Country();
	void addEdgeCountry(string name, Country* country);
	void setContinentName(string name);
	void setOwner(string player);
	bool isEdgeCountryExist(string name);
	string getCountryName();
	string getContinentName();
	int getEdgeCountrySize();
	unordered_map<string, Country*> getEdgeCountry();
	void displayInfo();
	void addArmies(string color, int nbOfArmies);
	void addCities(string color, int nbOfCities);
	void DestroyArmies(string color);
	void setOwnedColor();
	int computeScoreR(string playerColor);
	string getOwnerColor();
	bool hasOwner();

private:
	unordered_map<string, Country*> edgeCountry;
	string countryName;
	string continentName;
	string ownerColor;
	unordered_map<string, int*> armies;
	unordered_map<string, int*> cities;
};

class Map {

public:
	bool createContinent(string continentName);
	bool createCountry(string countryName);
	bool isContinentExist(string name);
	bool isCountryExist(string name);
	Continent* getContinent(string name);
	Country* getCountry(string name);
	static Map* getInstance();
	static void releaseInstance();


	void askBuildMapQuestion();
	void startGame();
	bool connectToContinent(string continentName, string countryName);
	bool connectToCountry(string countryFrom, string CountryTo);
	bool displayContinentInfo(string continentName);
	bool displayCountryInfo(string countryName);
	bool isConnectedMap();
	bool recursiveCheckTree(unordered_map<string, int> arrOfCountry, queue<Country*> queueOfCountry);
	void deleteMap();
	void showMap();
	void displayAllCountry();
	void addArmyToCountry(string countryName, string color, int nbOfArmy);
	void addCityToCountry(string countryName, string color, int nbOfCity);
	string getRandomCountry();
	Country* getCountryByName(string countryName);
	unordered_map<string, Continent*> getAllContinent();



private:
	Map();
	~Map();
	unordered_map<string, Country*> allCountry;
	unordered_map<string, Continent*> allContinent;
	static Map* m_instance;
};
