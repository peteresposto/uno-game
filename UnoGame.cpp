#include "UnoGame.h"
#pragma warning(disable: 4996)

UnoGame::UnoGame()
{
	createDeck();
	setPlayerNames();
	createPlayerHands();
	drawStartingCard();
	play();
}

void UnoGame::createDeck()
{
	//First, create cards and put them into a bag
	Bag<Card> bag((NUMDENOMINATIONS+1)*4*2);
	Suit s[] = { RED, BLUE, GREEN, YELLOW };

	//We are creating 2 of every type of card
	for (int a = 1; a < 3; a++)
	{
		//4 suits
		for (int b = 0; b <= 3; b++)
		{
			//NUMDENOMINATIONS denominations + 1 which accounts for drawTwo card (denomination 0)
			for (int c = 0; c <= (NUMDENOMINATIONS); c++)
			{
				bag.add(Card(s[b], c));
			}
		}
	}

	//Next, draw cards from bag and place them into the deck
	for (int i = 1; i <= (2 * (NUMDENOMINATIONS + 1) * 4); i++)
	{

		deck.enqueue(bag.getOne());
	}

}

void UnoGame::setPlayerNames()
{
	//The player container has already been created

	//Set the names of all our uno players
	for (int i = 0; i < NUMPLAYERS; i++)
	{
		playerContainer[i].setName("Player " + to_string(i + 1));
	}
}

void UnoGame::createPlayerHands()
{
	//Outside loop to assign cards to every player
	for (int i = 0; i < NUMPLAYERS; i++)
	{
		//Inner loop to assign cards to fill each player's hand
		for (unsigned int j = 0; j < PLAYERHANDSIZE; j++)
		{
			Card tempCard = deck.dequeue();
			playerContainer[i].hand.insert(tempCard);
		}
	}
}

void UnoGame::drawStartingCard()
{
	//Deque the deck and place that card onto the top of the face up pile stack
	Card tempCard = deck.dequeue();
	faceUpPile.push(tempCard);
}

int UnoGame::checkForAWinner()
{
	//Loop through every player and check to see if their hand is empty
	for (int i = 0; i < NUMPLAYERS; i++)
	{
		if (playerContainer[i].hand.isEmpty() == true)
			return i;
	}
	return -1;
}

void UnoGame::deckRunsOut()
{
	//Check to see if the deck is empty and if it is, execute this function to replenish it
	if (deck.isEmpty() == true)
	{
		cout << "The deck has been repopulated " << endl;
		//Pop the top card off the face up pile
		Card tempCard = faceUpPile.pop();
		Bag<Card> shuffleBag((NUMDENOMINATIONS+1)*4*2);

		//Now, throw the cards into the bag
		while (faceUpPile.isEmpty() == false)
		{
			shuffleBag.add(faceUpPile.pop());
		}

		//Add the the temporary card to the top of the face up pile
		faceUpPile.push(tempCard);

		//Take the cards out of the bag and put them back into the deck
		for (int i = 0; i < shuffleBag.currentSize(); i++)
		{
			deck.enqueue(shuffleBag.getOne());
		}
	}
}

void UnoGame::drawTwo(int i, Card &tempCard)
{
	//Loop through this sequence twice to ensure two cards are drawn and placed into the respective player's hand
	for (int j = 1; j < 3; j++)
	{
		//First, make sure the deck hasn't run out and there are cards available for the player to draw
		deckRunsOut();
		//These two if statements check to see if the player is the last index of the player container
		//and it ensures that the proper player draws cards
		if (i != (NUMPLAYERS - 1))
			playerContainer[i + 1].hand.insert(deck.dequeue());
		if (i == (NUMPLAYERS - 1))
			playerContainer[0].hand.insert(deck.dequeue());
	}
	
	//Once again cout the proper player index
	if (i != (NUMPLAYERS - 1))
		cout << playerContainer[i + 1] << " is drawing two cards and will skip their turn! " << endl;
	if (i == (NUMPLAYERS - 1))
		cout << playerContainer[0] << " is drawing two cards and will skip their turn! " << endl;

	faceUpPile.push(tempCard);
	deckRunsOut();
}

void UnoGame::play()
{
	cout << "Welcome to UNO!" << endl;
	int isGameWon = -1;

	//Loop through the UNO game while there isn't already a winner
	while (isGameWon == -1)
	{
		for (int i = 0; i < NUMPLAYERS; i++)
		{
			//Start by checking if the player has a match in their hand
			int cardIndex = playerContainer[i].isMatch(faceUpPile.peek());
			int correctPlayerIndex = 1;
			cout << endl;

			cout << "The card at the top of the pile is: " << faceUpPile.peek() << endl;

			//If they do have a match, have them remove the card from their hand and place it at the top of the pile
			if (cardIndex != -1)
			{
				Card tempCard = playerContainer[i].hand.remove(cardIndex);

				//If the card is a drawTwo, call the drawTwo function
				if (tempCard.getDenomination() == 0)
				{
					cout << playerContainer[i] << " played " << tempCard << endl;
					drawTwo(i, tempCard);
					i++;
					correctPlayerIndex = 0;
				}

				//If the card is not a draw two, place the card onto the top of the face up pile stack
				if (tempCard.getDenomination() != 0)
				{
					cout << playerContainer[i] << " played " << tempCard << endl;
					faceUpPile.push(tempCard);
				}
			}

			//If they do not have a match,
			if (cardIndex == -1)
			{
				cout << playerContainer[i] << " did not have a match and is drawing a card " << endl;
				//Have them draw a card from the deck and insert it into their hand
				Card tempCard = deck.dequeue();
				cout << "They drew " << tempCard << endl;
				playerContainer[i].hand.insert(tempCard);

				//Then, check to see if this freshly drawn card is a match
				cardIndex = playerContainer[i].isMatch(faceUpPile.peek());

				//If it is, have them remove it from their hand and place it on the face up pile
				if (cardIndex != -1)
				{
					cout << "The card they drew can be played! " << endl;
					Card tempCard = playerContainer[i].hand.remove(cardIndex);
					cout << playerContainer[i] << " played " << tempCard << endl;
					faceUpPile.push(tempCard);
				}
			}

			//Display the hand size of the player who's turn it currently is
			if (correctPlayerIndex == 1)
				cout << playerContainer[i] << " has a hand size of " << playerContainer[i].hand.getLength() << endl;
			if (correctPlayerIndex == 0)
				cout << playerContainer[i - 1] << " has a hand size of " << playerContainer[i - 1].hand.getLength() << endl;

			//Finally, check to see if the deck has run out, and if it has, replenish it
			deckRunsOut();
			isGameWon = checkForAWinner();
			if (checkForAWinner() != -1)
				break;
		}
		cout << endl;
	}

	int winnerIndex = checkForAWinner();
	cout << playerContainer[winnerIndex] << " screams UNO and wins the game!";
}
