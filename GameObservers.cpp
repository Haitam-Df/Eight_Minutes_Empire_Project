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