#include "stdafx.h"
#include<iostream>
#include "MapLoader.h"
#include "Bidding.h"
#include "Player.h"
#include "Game.h"

using namespace std;

int main() {

	//Initialize the map
	MapLoader* mapLoader = new MapLoader();
	mapLoader->loadMap();

	//Create the Game
	Game* game = new Game();
	game->setMap(mapLoader->getMap());
	game->loadPlayer();
	game->setObserver();
	
}
