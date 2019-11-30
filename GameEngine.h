#pragma once
#include "Game.h"
#include "GameEngine.h"

class GameEngine {
private:
	Game* game;

public:
	GameEngine();
	~GameEngine();
	void playGame();

};