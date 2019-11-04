
#include "stdafx.h"
#include "Cards.h" 
#include<iostream>
#include <time.h>
#include <cstdlib>
#include < algorithm >

Cards::Cards(string newAction, string newGood) {
	good = newGood;
	action = newAction;
}

// deck class that will initiate the 42 cards from the game
Deck::Deck() {

	int random, random2;
	srand(time(NULL));

	Cards* c1 = new Cards("Add 2 Armies or Move 3 Armies", "Forest"); // special case.
	Cards* c2 = new Cards("Destroy 1 Army or Build city", "Forest");
	Cards* c3 = new Cards("Add 3 Armies", "Forest");
	Cards* c4 = new Cards("Move 6 Armies", "Forest");
	Cards* c5 = new Cards("Move 3 Armies via Ship (move over land and/or water)", "Forest");
	Cards* c6 = new Cards("Move 4 Armies via Ship (move over land and/or water)", "Forest");
	Cards* c7 = new Cards("Build City", "Forest");
	Cards* c41 = new Cards("Move 3 Armies", "Forest");


	Cards* c8 = new Cards("Build City", "Carrot");
	Cards* c9 = new Cards("Destroy 1 Army and Add 1 Army", "Carrot");
	Cards* c10 = new Cards("Add 3 Armies", "Carrot");
	Cards* c11 = new Cards("Move 4 Armies", "Carrot");
	Cards* c12 = new Cards("Move 5 Armies", "Carrot");
	Cards* c13 = new Cards("Add 3 Armies (Double Carrot)", "Carrot");
	Cards* c14 = new Cards("Move 3 Armies via Ship (move over land and/or water)", "Carrot");
	Cards* c15 = new Cards("Add 4 Armies or Move 2 Armies", "Carrot"); // special case
	Cards* c16 = new Cards("Move 4 Armies", "Carrot");
	Cards* c18 = new Cards("Build City", "Carrot");

	Cards* c19 = new Cards("Move 4 Armies", "Anvil");
	Cards* c21 = new Cards("Add 3 Armies or Move 4 Armies", "Anvil"); // special case
	Cards* c22 = new Cards("Move 5 Armies", "Anvil");
	Cards* c23 = new Cards("Add 3 Armies", "Anvil");
	Cards* c24 = new Cards("Add 3 Armies", "Anvil");

	Cards* c25 = new Cards("Move 3 Armies via Ship (move over land and/or water)", "Anvil");
	Cards* c20 = new Cards("Build City", "Anvil");
	Cards* c17 = new Cards("Move 4 Armies (Double Anvil) **", "Anvil");
	Cards* c42 = new Cards("Add 3 Armies or Move 3 Armies", "Anvil"); // special case

	Cards* c26 = new Cards("Move 2 Armies", "Ore");
	Cards* c27 = new Cards("Move 3 Armies via Ship (move over land and/or water)", "Ore");
	Cards* c28 = new Cards("Move 2 Armies via Ship (move over land and/or water)", "Ore");
	Cards* c29 = new Cards("Move 2 Armies via Ship (move over land and/or water)", "Ore");
	Cards* c30 = new Cards("Add 3 Armies", "Ore");
	Cards* c31 = new Cards("Add 3 Armies", "Ore");
	Cards* c32 = new Cards("Add 2 Armies", "Ore");

	Cards* c33 = new Cards("Add 2 Armies", "Crystal");
	Cards* c34 = new Cards("Add 2 Armies", "Crystal");
	Cards* c35 = new Cards("Move 2 Armies", "Crystal");
	Cards* c36 = new Cards("Add 1 Army", "Crystal");
	Cards* c37 = new Cards("Add 2 Armies", "Crystal");

	Cards* c38 = new Cards("Move 2 Armies", "Wild");
	Cards* c39 = new Cards("Move 2 Armies", "Wild");
	Cards* c40 = new Cards("Add 2 Armies", "Wild");


	deckOfCard.push_back(c1);
	deckOfCard.push_back(c2);
	deckOfCard.push_back(c3);
	deckOfCard.push_back(c4);
	deckOfCard.push_back(c5);
	deckOfCard.push_back(c6);
	deckOfCard.push_back(c7);
	deckOfCard.push_back(c8);
	deckOfCard.push_back(c9);
	deckOfCard.push_back(c10);
	deckOfCard.push_back(c11);
	deckOfCard.push_back(c12);
	deckOfCard.push_back(c13);
	deckOfCard.push_back(c14);
	deckOfCard.push_back(c15);
	deckOfCard.push_back(c16);
	deckOfCard.push_back(c17);
	deckOfCard.push_back(c18);
	deckOfCard.push_back(c19);
	deckOfCard.push_back(c20);
	deckOfCard.push_back(c21);
	deckOfCard.push_back(c22);
	deckOfCard.push_back(c23);
	deckOfCard.push_back(c24);
	deckOfCard.push_back(c25);
	deckOfCard.push_back(c26);
	deckOfCard.push_back(c27);
	deckOfCard.push_back(c28);
	deckOfCard.push_back(c29);
	deckOfCard.push_back(c30);
	deckOfCard.push_back(c31);
	deckOfCard.push_back(c32);
	deckOfCard.push_back(c33);
	deckOfCard.push_back(c34);
	deckOfCard.push_back(c35);
	deckOfCard.push_back(c36);
	deckOfCard.push_back(c37);
	deckOfCard.push_back(c38);
	deckOfCard.push_back(c39);
	deckOfCard.push_back(c40);
	deckOfCard.push_back(c41);
	deckOfCard.push_back(c42);

	cout << endl;
	cout << " The Deck is created!!" << endl;
	for (int i = 0; i < 42; i++)
	{
		random = rand() % 40 + 1;
		random2 = rand() % 40 + 1;
		Cards* temp = deckOfCard[random];
		Cards* temp2 = deckOfCard[random2];
		deckOfCard[random] = temp2;
		deckOfCard[random2] = temp;

	}
	cout << endl;
	cout << " The Deck is shuffled!!" << endl;




}

//Position starts at 0
// remove a card from the deck 
void Deck::removeCard(int position) {
	hand.erase(hand.begin() + position);
}

// draw a card from the deck vector and put it inside the hand vector
void Deck::draw() {
	// return a card (remove it from the deck) 
	if (deckOfCard.size() != 0) {
		Cards* temp = deckOfCard.front();
		deckOfCard.erase(deckOfCard.begin());
		hand.push_back(temp);
	}
}

// return the hand vector 
vector<Cards*> Deck::getHand() {
	return hand;
}


void Deck::showHand() {
	cout << endl;
	cout << "This is the actual hand of card" << endl;
	
	for(int x = 0; x < hand.size(); x++) {
		switch (x) {
		case 0: 
			cout << "1) " << " COST = 0 " << endl; break;
		case 1: 
			cout << "2) " << " COST = 1 " << endl; break;
		case 2: 
			cout << "3) " << " COST = 1 " << endl; break;
		case 3: 
			cout << "4) " << " COST = 2 " << endl; break;
		case 4: 
			cout << "5) " << " COST = 2 " << endl; break;
		case 5: 
			cout << "6) " << " COST = 3 " << endl; break;
		}

		cout << "		Action : " << hand[x]->action << endl;
		cout << "		Goods : " << hand[x]->good << endl;
		
	}
}

// return a money value for a card in the hand vector given a position
void Hand::exchange(int position) {
	cout << endl;
	cout << endl;
	cout << "BEFORE EXCHANGE" << endl;
	for (auto& x : deck->getHand()) {
			cout <<"- "<< x->action << endl;
	}
	cout << endl;
	playerHand.push_back(deck->getHand().at(position));
	deck->removeCard(position);

	cout << endl;
	cout << endl;
	cout << "AFTER EXCHANGE" << endl;
	for (auto& x : deck->getHand()) {
			cout << "- " << x->action << endl;
	}
	deck->draw();
}

vector<Cards*> Hand::getHand() {
	return deck->getHand();
}
Hand::Hand(Deck* y) {
	vector<Cards*> playerHand;
	deck = y;
}
Hand::Hand() {};

// return the cost of a card 
int Hand::getCostCard(int position) {
	switch (position) {
	case 0: return 0;
	case 1: return 1;
	case 2: return 1;
	case 3: return 2;
	case 4: return 2;
	case 5: return 3;
	default: return 100;
	}
}

