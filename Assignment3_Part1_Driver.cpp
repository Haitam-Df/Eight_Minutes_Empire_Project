#include "stdafx.h"

#include<iostream>
#include "MapLoader.h"
#include "Bidding.h"
#include "Player.h"
#include "Game.h"

using namespace std;
/*
int main() {

	//Initialize the map
	MapLoader* mapLoader = new MapLoader();
	mapLoader->loadMap();

	//Create the Game
	Game* game = new Game();
	game->setMap(mapLoader->getMap());

	Phase* phase = new Phase();

	game->addSubscriber(phase);

	//Create Deck and Shuffle
	game->createDeck();

	game->loadPlayer();
	game->setObserver();
	game->setStartingGameCountry();

	game->if2Players();

	game->playerBid();

	//Main hand
	game->draw6cards();
	game->showDeckHand();

	game->startGame();
	game->displayCountry();
	game->computeScoreG();
}*/
