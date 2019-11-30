#include "Cards.h"
class abstractGameObserver
{
public:
	virtual void notify(int playerNb, vector<string>* actionsOfPLayer) =0;

	virtual void display()=0;
	virtual void reset()=0;
};

class abstractview{
public:
	virtual void notify(string country, string playerColor)=0;
	virtual void notifyPlayerPoints(int player, int point)=0;
	virtual void notifyWinner(int player)=0;
};