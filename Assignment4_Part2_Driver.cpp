#include "stdafx.h"

#include<iostream>
#include "MapLoader.h"
#include "Bidding.h"
#include "Player.h"
#include "Game.h"
#include "GameObservers.h"
#include "GameEngine.h"

using namespace std;

int main() {

	GameEngine* gameEngine = new GameEngine();

	gameEngine->playGame();

	delete gameEngine;
}