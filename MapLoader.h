#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include<queue>
#include "map.h"

using namespace std;

class MapLoader {
public :
	bool isValidMap(ifstream& file);
	vector<string> stringToArray(string s, char c);
	bool noRightLabel(vector<string> lineToArray,string labelname);
	void getQuestion();
	void setMap(Map* map);
	Map* getMap();
	void showMap();//
	int loadMap();
private:
	Map * map;
};