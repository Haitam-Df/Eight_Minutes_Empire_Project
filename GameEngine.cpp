#include "stdafx.h"
#include "GameEngine.h" 
#include <limits>

using namespace std;

GameEngine::GameEngine() {
	game = new Game();
}

GameEngine::~GameEngine() {
	delete game;
}

void GameEngine::playGame() {
	cout << endl;
	int playerMode;
	while (true) {
			cout << " Do you want to play Single mode or Tournament ??" << endl;
			cout << " 1) Single Mode" << endl;
			cout << " 2) Tournament Mode" << endl;
			
			cin >> playerMode;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
				
		if (playerMode > 0 && playerMode < 3) {
			break;
		}
		
	}
	cout << endl;
	
	MapLoader* mapLoader = new MapLoader();
	mapLoader->loadMap();

	//Create the Game
	Game* game = new Game();
	game->setMap(mapLoader->getMap());
	game->setPlayerMode(playerMode);

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
	game->computeScoreG();
}