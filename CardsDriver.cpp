
#include "stdafx.h"
#include<iostream>
#include "Cards.h"
using namespace std;

/*
int main() {

	// create new deck object 
	// deck object contains both a vector for the deck and a vector for the hand
	Deck* newDeck = new Deck();
	cout << " Cards in the deck : " << endl << endl;
	for (int i = 0; i < newDeck->deckOfCard.size(); i++) {
		cout << newDeck->deckOfCard[i]->action + " " + newDeck->deckOfCard[i]->good << endl;

	}
	cout << endl;
	cout << "the number of cards in the deck are " << newDeck->deckOfCard.size();
	cout << endl;

	// card are drawn from the deck and put into the hand 
	newDeck->draw();
	newDeck->draw();
	newDeck->draw();
	newDeck->draw();
	newDeck->draw();
	newDeck->draw();

	cout << " Cards in the hand  : " << endl << endl;
	for (int i = 0; i < newDeck->hand.size(); i++)
	{
		cout << newDeck->hand[i]->action + " " + newDeck->hand[i]->good << endl;
	}
	cout << endl;
	cout << " Cards in the deck : " << endl << endl;
	for (int i = 0; i < newDeck->deckOfCard.size(); i++) {
		cout << newDeck->deckOfCard[i]->action + " " + newDeck->deckOfCard[i]->good << endl;

	}
	cout << endl;
	cout << "The new number of cards in the deck are " << newDeck->deckOfCard.size();
	cout << endl;


	Hand* x = new Hand(newDeck);
	int temp;
	x->exchange(2);


	while (true) {
		cin >> temp;
		cout << to_string(x->getCostCard(temp)) << endl;
	}

}
*/