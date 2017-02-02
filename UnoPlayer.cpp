#include "UnoPlayer.h"
#include <iostream>
#pragma warning(disable: 4996)
using namespace std;

string UnoPlayer::getName()
{
	return playerName;
}

void UnoPlayer::setName(string name)
{
	playerName = name;
}

//Overload the << operator to write a print function for UnoPlayer
ostream& operator<<(std::ostream& os, UnoPlayer &player)
{
	os << player.getName();
	return os;
}

int UnoPlayer::isMatch(Card topOfDeck)
{
	int tempDenomination = topOfDeck.getDenomination();
	Suit tempSuit = topOfDeck.getSuit();

	//Check to see if the player has a card in their hand with the same number as the card on top of the face up pile
	for (int i = 1; i <= hand.getLength(); i++)
	{
		//If there is a denomination match, return the index of the denomination in the player's hand
		if ((hand.retrieve(i).getDenomination()) == tempDenomination)
		{
			return i;
		}
	}

	//Check to see if the player has a card in their hand with the same suit as the card on top of the face up pile
	for (int i = 1; i <= hand.getLength(); i++)
	{
		//If there is a suit match, return the index of the denomination in the player's hand
		if ((hand.retrieve(i).getSuit()) == tempSuit)
		{
			return i;
		}
	}

	//If there is no denomination or suit match, return -1
		return -1;
}