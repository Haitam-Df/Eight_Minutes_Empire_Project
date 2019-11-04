#include "stdafx.h"

#include<iostream>
#include "MapLoader.h"
#include "Bidding.h"
#include "Player.h"
#include "Game.h"
#include "map.h"
#include <sstream> 

using namespace std;

int main() {

	
	
	//Initialize the map
	MapLoader* mapLoader = new MapLoader();
	mapLoader->loadMap();

	//Create the Game
	Game* game = new Game();
	game->setMap(mapLoader->getMap());

	//Create Deck and Shuffle
	game->createDeck();

	game->loadPlayer();

	game->setStartingGameCountry();

	game->if2Players();

	game->playerBid();

	//Main hand
	game->draw6cards(); 
	game->showDeckHand();

	//This function is for testing the Non-Color for 2 players or to see starting point Army
	//game->displayCountry();

//	game->computeScoreG();

	
}
