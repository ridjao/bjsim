#include <string>
#include <iostream>

#include "Deck.h"

Card::Card(){}
Card::Card(std::string name):std::string(name){}

char Card::rank() const
{
	return this->c_str()[0];
}

int Card::value() const
{
	char rank = this->c_str()[0];
	int value;

	if (rank == 'T' || rank == 'J' || rank == 'Q' || rank == 'K')
	{
		value = 10;
	}
	else if (rank == 'A')
	{
		value = 11;
	}
	else
	{
		value = rank - '0';
	}

	return value;
}


void Deck::initialize()
{
	std::string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
	std::string suits[] = {"C", "S", "H", "D"};

	for (int i=0; i<sizeof(suits)/sizeof(suits[0]); i++)
	{
		for(int j=0; j<sizeof(ranks)/sizeof(ranks[0]); j++)
		{	
			std::string card = ranks[j]+suits[i];
			Deck::cards.push_back(card);
		}
	}
}

void Deck::print()
{
	for(std::vector<Card>::iterator it = Deck::cards.begin(); it != Deck::cards.end(); ++it)
	{
		std::cout<<*it<<std::endl;
	}
}

std::vector<Card> Deck::cards;

// magic or hackery?
static bool initialize()
{
	Deck::initialize();
	return true;
}

static bool is_initialized = initialize();