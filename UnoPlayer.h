#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include "OrderedList.h"
#include "Card.h"
using namespace std;

class UnoPlayer
{
public:
	OrderedList<Card, IsLess> hand;
	friend std::ostream& operator<<(std::ostream& os, UnoPlayer &c);
	string getName();
	void setName(string name);
	int isMatch(Card topOfDeck);
private:
	string playerName;
};

