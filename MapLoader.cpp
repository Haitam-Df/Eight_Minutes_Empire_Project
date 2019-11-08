#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include<string>
#include <fstream>

#include "MapLoader.h"


using namespace std;

//MapLoader implementation

bool MapLoader::noRightLabel(vector<string> lineToArray,string labelname) {
	return (lineToArray.size() == 0 || lineToArray.size() > 1 || lineToArray[0] != "[" + labelname + "]");
}
void MapLoader::getQuestion() {
	return map->askBuildMapQuestion();
}
void MapLoader::setMap(Map* newMap) {
	this->map = newMap;
}
void MapLoader::showMap() {
	this->map->showMap();
}

Map* MapLoader::getMap() {
	return this->map;
}



//The map file needs to follow specifics rules to be accepted
/*
Rule 1: You need to have [Map] as the first line document

Rule 2: You need to have an empty line as the second line!

Rule 3: You need to have [Continents] as the third line document

Rule 4: After Rule 3 ,You need to have 1 element in the line and needs to be new continent and at the end , empty line

Rule 5: You need to have [Countries] in this line

Rule 6: After Rule 5 ,You need to have 1 element in the line and needs to be new country and at the end , empty line

Rule 7: You need to have [Informations] in this line

Rule 8: After Rule 7 ,You need to have at least 3 elements in this row [country,continent,edgeCountry1,..]
*/
bool MapLoader::isValidMap(ifstream& file) {

	string line;
	int section = 1;
	while (getline(file, line))
	{
		vector<string> lineToArray = stringToArray(line, ',');
		switch (section) {
		case 1: {
			if (noRightLabel(lineToArray,"Map")) {
				cout << "" << endl;
				cout << "Error : You need to have [Map] as the first line document" << endl;
				return 0;
			}
			else {
				section++;
			}
			break;
		}
		case 2: {
			if (lineToArray.size() == 0) {
				section++;
			}
			else {
				cout << "" << endl;
				cout << "Error : You need to have empty line as the second line!" << endl;
				return 0;
			}
			break;
		}
		case 3: {
			if (noRightLabel(lineToArray, "Continents")) {
				cout << "" << endl;
				cout << "Error : You need to have [Continents] as the third line document" << endl;
				return 0;
			}
			else {
				section++;
			}
			break;

		}
		case 4: {
			if (lineToArray.size() == 1 && map->createContinent(lineToArray[0])) {
				break;
			}
			else {
				if (lineToArray.size() == 0) {
					section++;
				}
				else
				{
					cout << "" << endl;
					cout << "Error : You need to have 1 element in the line and needs to be new continent" << endl;
					return 0;
				}
			}
			break;
		}
		case 5: {
			if (noRightLabel(lineToArray, "Countries")) {
				cout << "" << endl;
				cout << "Error : You need to have [Countries] in this line" << endl;
				return 0;
			}
			else {
				section++;
			}
			break;
		}
		case 6: {
			if (lineToArray.size() == 1 && map->createCountry(lineToArray[0])) {
				break;
			}
			else {
				if (lineToArray.size() == 0) {
					section++;
				}
				else
				{
					cout << "" << endl;
					cout << "Error : You need to have 1 element in the line and needs to be new country" << endl;
					return 0;
				}
			}
			break;
		}
		case 7: {
			if (noRightLabel(lineToArray, "Informations")) {
				cout << "" << endl;
				cout << "Error : You need to have [Informations] in this line" << endl;
				return 0;
			}
			else {
				section++;
			}
			break;

		}
		case 8: {
			if (lineToArray.size() == 0) {
				break;
			}
			else {
				if (lineToArray.size() == 1 || lineToArray.size() == 2) {
					cout << "" << endl;
					cout << "Error : You need to have at least 3 elements in this row [country,continent,edgeCountry1,..]" << endl;
					return 0;
				}
				else {
					if(map->isCountryExist(lineToArray[0])){
						if (map->connectToContinent(lineToArray[1], lineToArray[0])) {
							for (std::size_t i = 2; i < lineToArray.size(); ++i) {
								if (lineToArray[0] == lineToArray[i]) {
									cout << "" << endl;
									cout << "Error : Cannot connect a country to itself"  << endl;
									return 0;
								}
								if (!(map->isCountryExist(lineToArray[i]) && map->connectToCountry(lineToArray[0], lineToArray[i]))) {
									cout << "" << endl;
									cout << "Error : you need to have 2 existing country and that are not already connected" << endl;
									return 0;
								}
							}
								
						}
						else {
							cout << "" << endl;
							cout << " Error : A country can only have 1 continent and this continent must exist " << endl;
							return 0;
						}
					}
					else {
						cout << "" << endl;
						cout << "Error : This country already exist" << endl;
						return 0;
					}
				}
			}
			break;
		}
		}
		
	}
	
	return map->isConnectedMap();
}
//This function is the way in C++ to change a string to array.
//This function is not provide in the c++ , therefore we needed to write it by following the Docs of Microsoft.
vector<string> MapLoader:: stringToArray(string row, char delimiter)
{
	string stringToArray{ "" };
	vector<string> arrayOfString;

	for (auto n : row)
	{
		if (n != delimiter)
			stringToArray += n;
		else
			if (n == delimiter && stringToArray != "") {
				arrayOfString.push_back(stringToArray);
				stringToArray = "";
			}
	}
	if (stringToArray != "")
		arrayOfString.push_back(stringToArray);

	return arrayOfString;
}

int MapLoader::loadMap() {
	while (true) {
		cout << endl;
		cout << "Enter a valid map file!" << endl;

		string filename;

		cin >> filename;
		ifstream file(filename);

		if (!file.fail()) {
			Map* map = Map::getInstance();
			setMap(map);
			if (isValidMap(file)) {
				return 1;
			}
			else {
				delete map;
				map = NULL;
				cout << endl;
				cout << "This is NOT a valid map!" << endl;
			}
		}
		
	}
}