#include "Cards.h"

class abstractPlayerStrategy
{
public:
	virtual int play(vector<Cards*> gameDeck)=0;
};

