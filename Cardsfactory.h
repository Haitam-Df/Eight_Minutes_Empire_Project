#pragma once
#include "Cards.h"

using namespace std;


class Cardsfactory {

public:
	static Cards* create(string action, string good);
	Cardsfactory() {};
private:

};

class Carrot : public Cards {
public:
	 void applyAction(string newAction) { action = newAction; };
	 void applyGood() { good = "Carrot"; };

};

class Anvil : public Cards {
public:
	 void applyAction(string newAction) { action = newAction; };
	 void applyGood() { good = "Anvil"; };

};

class Forest : public Cards {
public:
	 void applyAction(string newAction) { action = newAction; };
	 void applyGood() { good = "Forest"; };
};

class Ore : public Cards {
public:
	 void applyAction(string newAction) { action = newAction; };
	 void applyGood() { good = "Ore"; };
};

class Crystal : public Cards {
public:
	 void applyAction(string newAction) { action = newAction; };
	 void applyGood() { good = "Crystal"; };
};
class Wild : public Cards {
public:
	void applyAction(string newAction) { action = newAction; };
	void applyGood() { good = "Wild"; };
};