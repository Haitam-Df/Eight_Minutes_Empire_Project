#pragma once
#include<unordered_map>
#include <string>

using namespace std;
class Phase {
private :
	unordered_map<int, vector<string>> actionsPlayerTook;

public:
	void notify(int playerNb, vector<string>* actionsOfPLayer);

	void display();
	void reset();
};