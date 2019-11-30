#include "stdafx.h"
#include "Game.h" 
#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>


using namespace std;

Game::Game() {
	supplyBank = new int(0);
}

Game::~Game() {

	cout << " Currently deleting all instances of the game !" << endl;

	for (int i = 0; i < allPlayers.size(); i++) {
		*allPlayers.at(i)->getCoins() = NULL;
		delete allPlayers.at(i)->getCoins();
		*allPlayers.at(i)->getId() = NULL;
		delete allPlayers.at(i)->getId();
		*allPlayers.at(i)->getUserStrat() = NULL;
		delete allPlayers.at(i)->getUserStrat();
		delete allPlayers.at(i)->getBiddingInstance();
		*allPlayers.at(i)->getHand() = NULL;
		delete allPlayers.at(i)->getHand();
		delete allPlayers.at(i);

	}
	maploader->unloadMap();
	delete deck;
	delete maploader;

	observers.clear();

	actionsOfPLayer = NULL;
	delete actionsOfPLayer;

	viewObserver = NULL;
	delete viewObserver;
	

	cout << " Done!" << endl;
}

int Game::nbOfCoin(int nbOfPlayer) {
	switch(nbOfPlayer){
	case 2: return 14;
	case 3: return 11;
	case 4: return 9;
	case 5: return 8;
	}
}

int Game::nbOfTurn(int nbOfPlayer) {
	if (playerMode == 1) {
		switch (nbOfPlayer) {
		case 2: return 13;
		case 3: return 10;
		case 4: return 8;
		case 5: return 7;
		}
	}
	else {
		cout << endl;
		switch (nbOfPlayer) {
		case 2: 
			cout << " CURRENTLY IN TOURNAMENT MODE: 2 PLAYER IS SET TO 26 TURNS, THEREFORE 13 COMPLETE TURNS!!" << endl;
			return 13;
		case 3: 
			cout << " CURRENTLY IN TOURNAMENT MODE: 3 PLAYER IS SET TO 30 TURNS, THEREFORE 10 COMPLETE TURNS!!" << endl;
			return 10;
		case 4: 
			cout << " CURRENTLY IN TOURNAMENT MODE: 4 PLAYER IS SET TO 28 TURNS, THEREFORE 7 COMPLETE TURNS!!" << endl;
			return 7;
		case 5:
			cout << " CURRENTLY IN TOURNAMENT MODE: 5 PLAYER IS SET TO 30 TURNS, THEREFORE 6 COMPLETE TURNS!!" << endl;
			return 6;
		}
	}
}

void Game::loadPlayer() {
	int nbPlayer = 0;
	int nbCPU = -1;
	srand(time(NULL));
	// GET HOW MANY PLAYER
	while (true) {
		cout << endl;
		cout << endl;
		cout << "How many players are playing (2 to 5)? " << endl;
		cin >> nbPlayer;
		if (nbPlayer > 1 && nbPlayer < 6)
			break;
	}

	while (true) {
		cout << endl;
		cout << endl;
		cout << "How many of the players are CPU (0 to " << nbPlayer << ")?" << endl;
		cin >> nbCPU;
		if (nbCPU > -1 && nbCPU <= nbPlayer)
			break;
	}
	int totalPlayers = nbPlayer;
	nbPlayer = nbPlayer - nbCPU;

	// GET PLAYER AGE

	for (int x = 0; x < nbPlayer; x++) {
		cout << endl;
		cout << endl;
		cout << "How old is the " << (x + 1) << " Player?" << endl;
		int age;
		cin >> age;
		allPlayers.push_back(new Player(age, deck, nbOfCoin(totalPlayers), (x + 1), false, 0));
	}

	int ageCPU;
	for (int x = 0; x < nbCPU; x++) {
		ageCPU = rand() % 12 + 1;
		cout << endl;
		cout << endl;
		cout << "Which strategy are you using for the " << (x + 1) << " CPU" << endl;
		int strat = -1;
		cout << "1) Greedy ( loves to build and destroy)" << endl;
		cout << "2) Moderate ( loves to add to countries he owns)" << endl;
		while (true) {
			cin >> strat;
			if (strat > 0 && strat < 3) {
				break;
			}
		}
		cout << "Player " << (nbPlayer + 1) << " (CPU) age is " << ageCPU << endl;
		allPlayers.push_back(new Player(ageCPU, deck, nbOfCoin(totalPlayers), (nbPlayer + 1), true, strat));
		nbPlayer += 1;
	}



	playerChooseColor(totalPlayers);



}

void Game::playerBid() {
	int positionPlayer = 0;
	int mostBidding = 0;
	int agePlayer = 1000;

	for (int i = 0; i < allPlayers.size(); i++) {
		cout << endl;
		cout << endl;
		cout << "For Player " << (i + 1) << endl;
		// Player Bid
		bool temp = allPlayers[i]->getStatus();
		allPlayers[i]->getBiddingInstance()->runOnce(temp);

		//Those if is not check which Player bid the most
		if (allPlayers[i]->getBiddingInstance()->getBidding() > mostBidding) {
			positionPlayer = i;
			mostBidding = allPlayers[i]->getBiddingInstance()->getBidding();
			agePlayer = allPlayers[i]->getBiddingInstance()->getAge();
		}
		else if ((allPlayers[i]->getBiddingInstance()->getBidding() == mostBidding) && (allPlayers[i]->getBiddingInstance()->getAge() < allPlayers[positionPlayer]->getBiddingInstance()->getAge())) {
			positionPlayer = i;
			mostBidding = allPlayers[i]->getBiddingInstance()->getBidding();
			agePlayer = allPlayers[i]->getBiddingInstance()->getAge();
		}
	}
	cout << endl;
	cout << endl;
	cout << "Player " << (positionPlayer + 1) << " won the bid!!" << endl;

	//reorganize the list to let the winner of the bid starts first
	vector<Player*> reorganizePlayer;
	for (int x = positionPlayer; x < allPlayers.size(); x++) {
		reorganizePlayer.push_back(allPlayers[x]);
	}
	for (int x = 0; x < positionPlayer; x++) {
		reorganizePlayer.push_back(allPlayers[x]);
	}
	for (int x = 0; x < allPlayers.size(); x++) {
		cout << allPlayers[x]->getBiddingInstance()->getAge() << endl;
	}
	cout << endl;
	for (int x = 0; x < reorganizePlayer.size(); x++) {
		cout << reorganizePlayer[x]->getBiddingInstance()->getAge() << endl;
	}
	allPlayers = reorganizePlayer;

	//Need to remove the bid of the first player (The one who won the bid)
	allPlayers[0]->PayCoin(mostBidding);

	//Add the bid to the supply bank
	addSupply(mostBidding);
}

void Game::createDeck() {
	deck = new Deck();
}
void Game::draw6cards() {
	for (int x = 0; x < 6; x++) {
		deck->draw();
	}
}
void Game::showDeckHand() {
	deck->showHand();
}

bool Game::notAlreadyUsed(vector<string> colorUsed, string color) {
	for (int x = 0; x < colorUsed.size(); x++) {
		if (colorUsed[x] == color) {
			return false;
		}
	}
	return true;
}

void Game::setStartingGameCountry() {
	startingGameCountry = map->getRandomCountry();

	cout << endl;
	cout << endl;
	cout << "THE STARTING POINT WAS CHOOSE RANDOMLY AND IT IS : " << startingGameCountry << endl;

	for (int x = 0; x < allPlayers.size(); x++) {
		map->addArmyToCountry(startingGameCountry, allPlayers[x]->getColor(), 3);
		// Add 3 armies to the starting point for each player
		for (int y = 0; y < 3; y++) {
			allPlayers[x]->addArmy(map->getCountryByName(startingGameCountry));
		}
	}
}


// look if the color was choose to play
bool Game::verifyColor(vector<string> colorUsed, string colorChoose, int nbOfPlayer) {
	for (int x = 0; x < allColors.size(); x++) {
		if (allColors[x] == colorChoose ) {
			if (notAlreadyUsed(colorUsed, colorChoose)) {
				if (nbOfPlayer == 2 && colorChoose == "white") {
					return false;
				}
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

void Game::setMap(Map* map) {
	this->map = map;
}

void Game::displayCountry() {
	string countryChoose;
	int x = 0;
	while (x<10) {
		cout << endl;
		cout << endl;
		cout << "which country you want to see the info ?" << endl;
		cin >> countryChoose;
		if (map->isCountryExist(countryChoose)) {
			map->displayCountryInfo(countryChoose);
			cout << endl;
		}
		x++;
	}
}

// if 2 players loop until 10 whites armies are in the board
void Game::if2Players() {
	bool player1CPU = false;
	bool player2CPU = false;
	

	if (*allPlayers.at(0)->getUserStrat()->getStrategy() == 1 || *allPlayers.at(0)->getUserStrat()->getStrategy() == 2) {
		player1CPU = true;
	}
	if (*allPlayers.at(1)->getUserStrat()->getStrategy() == 1 || *allPlayers.at(1)->getUserStrat()->getStrategy() == 2) {
		player2CPU = true;
	}

	if (allPlayers.size() == 2) {
		cout << endl;
		cout << endl;
		map->displayAllCountry();
		cout << endl;
		cout << endl;
		string countryChoose;
		for (int x = 0; x < 5; x++) {
			while (true) {
				//Player1
				cout << endl;
				cout << endl;

				cout << "Player 1 choose a country to place a NON-COLOR Army" << endl;
				if (player1CPU) {
					countryChoose = map->getRandomCountry();
				}else {cin >> countryChoose; }
				if (map->isCountryExist(countryChoose)) {
					map->addArmyToCountry(countryChoose, "white", 1);
					break;
				}
			}
			while (true) {
				//Player2
				cout << endl;
				cout << endl;
				cout << "Player 2 choose a country to place a NON-COLOR Army" << endl;
				if (player2CPU) {
					countryChoose = map->getRandomCountry();
				}
				else { cin >> countryChoose; }
				if (map->isCountryExist(countryChoose)) {
					map->addArmyToCountry(countryChoose, "white", 1);
					break;
				}
			}
		}
	}
}

// Player choose a color to play with
void Game::playerChooseColor(int nbOfPlayer) {
	 vector<string> colorUsed;
	 string colorChoose;
	for (int x = 0; x < allPlayers.size(); x++) {
		while (true) {
			cout << endl;
			cout << endl;
			cout << "Player " << (x + 1) << " choose a color" << endl;
			for (int y = 0; y < allColors.size(); y++) {
				if (!(nbOfPlayer == 2 && allColors[y] == "white") && notAlreadyUsed(colorUsed,allColors[y])) {
					cout << "- " << allColors[y] << endl;
				}
			}
			cin >> colorChoose;

			if (verifyColor(colorUsed,colorChoose, nbOfPlayer)) {
				allPlayers[x]->setColor(colorChoose);
				colorUsed.push_back(colorChoose);
				break;
			}
		}
	}
}

void Game::setPlayerMode(int playerModeInput)
{
	playerMode = playerModeInput;
}


void Game::addSupply(int money) {
	*supplyBank += money;

	cout << endl;
	cout << endl;
	cout <<money<<"coins was added to the Bank!"<< endl;

	cout <<" Total in the bank : "<< *supplyBank <<" coins"<< endl;
}

void Game::playerChooseAction(Player* playerTurn,vector<string>* actions) {
	int action = 0;
	deck->showHand();
	bool missingCoins = true;
	while (true) {
		cout << endl;

		if (!playerTurn->getUserStrat()->getChangeStrat()) {

			if (playerTurn->getStatus() == false && playerTurn->getUserStrat()->changeStrat() == true) {
				if (!playerTurn->getUserStrat()->getChangeStrat())
				playerTurn->setStatus(true);

			}
			else if (playerTurn->getStatus() == true && playerTurn->getUserStrat()->changeStrat() == false) {
				if (!playerTurn->getUserStrat()->getChangeStrat())
				playerTurn->setStatus(false);

			}
		}
		if(*playerTurn->getUserStrat()->getStrategy() == 0){ 
		
		cout << "Which action you want to perform?" << endl;
		action = playerTurn->getUserStrat()->play(deck->getHand());
		
		}
		else {
			if (*playerTurn->getUserStrat()->getStrategy() == 1) {
				
				if (missingCoins) {
					cout << " the CPU will play ( greedy) : ";

					action = playerTurn->getUserStrat()->play(deck->getHand());
					cout << action << endl << endl;
				}
				else {
					cout << " The CPU tried to play a card but is missing coins so it will skip its turn" << endl;
					action = 1;
					playerTurn->getUserStrat()->setAction("ignore");
				}

			}
			if (*playerTurn->getUserStrat()->getStrategy() == 2) {
				
				if (missingCoins) {
					cout << " the CPU will play ( moderate ) : ";
					action = playerTurn->getUserStrat()->play(deck->getHand());
					cout << action << endl << endl;
				}
				else {
				cout << " The CPU tried to play a card but is missing coins so it will skip its turn" << endl;
				action = 1;
				playerTurn->getUserStrat()->setAction("ignore");
			}
			}

		}
		//There is 6 action possible not more or less
		if (action > 0 && action < 7) {
			// Does the player have enough coins
			if (playerTurn->getHand()->getCostCard(action - 1) <= *playerTurn->getCoins()) {

				for (int card = 0; card < deck->getHand().size(); card++) {
					if (card == (action - 1)) {
						// player does the action of the card he chose
						playerTurn->makeAction(deck->getHand()[card]->action , map->getCountryByName(startingGameCountry), allPlayers,actions);
					}
				}
				
				actions->push_back("- Will pay "+ to_string((playerTurn->getHand()->getCostCard(action - 1)))+" coins");
				playerTurn->getHand()->exchange(action - 1);
				playerTurn->PayCoin(playerTurn->getHand()->getCostCard(action - 1));
				addSupply(playerTurn->getHand()->getCostCard(action - 1));
				break;
			}
			else {
				cout << "Not enough coins in your bank" << endl;
				missingCoins = false;
			}
		}
	}
	

}


void Game::startGame() {

	for (int x = 0; x < nbOfTurn(allPlayers.size()); x++) {
		cout << endl;
		cout << endl;
		cout << "Turn : " << (x + 1) << endl;
		for (int y = 0; y < allPlayers.size(); y++) {
			vector<string>* actions = new vector<string>();
			cout << endl;
			cout << "Player " << *(allPlayers.at(y)->getId())<< endl;
			allPlayers[y]->displayInfo();
			playerChooseAction(allPlayers[y], actions);
			setPlayerAction(*(allPlayers.at(y)->getId()), actions);
			for (int x = 0; x < observers.size(); x++) {
				observers[x]->display();
			}
		}
		viewObserver->displayStats();
		for (int x = 0; x < observers.size(); x++) {
			observers[x]->reset();
		}
	}
}
	
void Game::computeScoreG()
{

	int scoredom = 0;
	int playerdom = 0;
	int windom = 0;

	//Compute the score for each player and sets the winner of the game
	for (int i = 0; i < allPlayers.size(); i++)
	{
		int computeScore = allPlayers[i]->computeScoreP(map->getAllContinent());
		viewObserver->notifyPlayerPoints(*allPlayers[i]->getId(), computeScore);
		if (computeScore > scoredom)
		{
			scoredom = computeScore;
			playerdom = (i + 1);
			windom = *allPlayers[i]->getId();
		}
		else 
		{	
			// if score is tied: check if player has more coins than dominant player
			if (computeScore == scoredom && allPlayers[i]->getCoins() > allPlayers[playerdom]->getCoins()) 
			{
				scoredom = computeScore;
				playerdom = (i + 1);
				windom = *allPlayers[i]->getId();
			}
			// if score is tied: check if player has more armies on board than dominant player
			else if (computeScore == scoredom && allPlayers[i]->numArmiesOnBoard > allPlayers[playerdom]->numArmiesOnBoard)
			{
				scoredom = computeScore;
				playerdom = (i + 1);
				windom = *allPlayers[i]->getId();
			}
			// if score is tied: check if player has more country owned than dominant player
			else if (computeScore == scoredom && allPlayers[i]->controlledRegions > allPlayers[playerdom]->controlledRegions)
			{
				scoredom = computeScore;
				playerdom = (i + 1);
				windom = *allPlayers[i]->getId();
			}
		}
	}
	viewObserver->notifyWinner(windom);
	viewObserver->displayWin();

}

void Game::addSubscriber(Phase* observerPhase) {
	observers.push_back(observerPhase);
}

void Game::notify() {
	for (int x = 0; x < observers.size(); x++) {
		observers[x]->notify(playerTurn, actionsOfPLayer);
	}
}
void Game::setPlayerAction(int playerTurn, vector<string>* actions) {
	this->playerTurn = playerTurn;
	actionsOfPLayer = actions;
	notify();

}
void Game::setObserver() {
	viewObserver = map->getObserverView();
	viewObserver->setallContinent(map->getAllContinent());
	viewObserver->setAllPlayers(allPlayers);
	viewObserver->setallCountry(map->getAllCountry());
}