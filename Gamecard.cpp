#pragma once
#include "Cardsfactory.h"
#include <iostream>

using namespace std;

Cards* Cardsfactory::create(string action, string good)
{
	Cards* card = NULL;

	if (good == "Carrot") {
		 card = new Carrot();
	}
	 else if (good == "Anvil") {
		card = new Anvil();
	}
	else if (good == "Forest") {
		card = new Forest();
	}
	else if (good == "Ore") {
		card = new Ore();
	}
	else if (good == "Crystal") {
		card = new Crystal();
	}
	else if (good == "Wild") {
		card = new Wild();
	}
	else {
		return NULL;
	}


	card->applyAction(action);
	card->applyGood();

	return card;
}







