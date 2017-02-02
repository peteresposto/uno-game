#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include "Stack.h"
#include "Card.h"
#include "LinkedList.h"
#include "UnoPlayer.h"
#include "Queue.h"
#include "Bag.h"
#include <string>
#define NUMPLAYERS 3
//Keep in mind NUMDENOMINATIONS is a separate figure from the drawTwo cards (so if NUMDENOMINATIONS is 5
//there will actually be 6 different types of cards)
#define NUMDENOMINATIONS 5
#define PLAYERHANDSIZE 5
using namespace std;

class UnoGame
{
public:
	UnoGame();
	Stack<Card> faceUpPile;
	UnoPlayer playerContainer[NUMPLAYERS];
	Queue<Card> deck;
	void createDeck();
	void setPlayerNames();
	void createPlayerHands();
	void drawStartingCard();
	void deckRunsOut();
	void drawTwo(int index, Card &tempCard);
	void play();
	int checkForAWinner();
};