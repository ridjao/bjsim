#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include "Shoe.h"

Shoe::Shoe()
{
	std::srand (unsigned(std::time(0)));
}

void Shoe::load(int decks)
{
	cards.clear(); // do we really want this here?

	int n = Deck::cards.size();
	for (int i=0; i<decks; i++)
	{
		for (int j=0; j<n; j++)
		{			
			cards.push_back(Deck::cards[j]);			
		}
	}
}

void Shoe::shuffle()
{	
	std::random_shuffle(cards.begin(), cards.end());
}

Card Shoe::deal()
{
	Card card = cards.back();
	cards.pop_back();
	return card;
}

Card Shoe::deal(const Card& card)
{
	if (card.value() != 0)
	{
		std::vector<Card>::reverse_iterator it = std::find(cards.rbegin(), cards.rend(), card);

		if (it == cards.rend())
		{
			throw std::out_of_range("Card not found in shoe");
		}

		Card val = *it;
		cards.erase(it.base()-1);
		return val;
	}
	return deal();
}

void Shoe::print()
{
	int i=0;
	for(std::vector<Card>::iterator card = cards.begin(); card != cards.end(); ++card)
	{
		std::cout<<i++<<":"<<*card<<std::endl;
	}
}

int Shoe::count(const std::vector<Card>& cards)
{
	return 0;
}

Card CSM::deal()
{
	Card out = shute.back();
	shute.pop_back();

	Card in = cards.back();
	cards.pop_back();
	shute.insert(shute.begin(), in);

	discards.push_back(out);

	return out;
}

Card CSM::deal(const Card& card)
{
	if (card.value() != 0)
	{
		std::vector<Card>::reverse_iterator it = std::find(cards.rbegin(), cards.rend(), card);

		if (it == cards.rend())
		{
			throw std::out_of_range("Card not found in shoe");
		}

		Card val = *it;
		cards.erase(it.base()-1);
		return val;
	}
	return deal();
}

void CSM::load(int decks)
{
	unsigned int buffer_size = 20;
	//cards.clear(); // do we really want this here?

	/*std::cout<<std::endl;
	for(std::vector<Card>::iterator card = discards.begin(); card != discards.end(); ++card)
	{
		std::cout<<*card<<" ";
	}
	std::cout<<std::endl;
	std::cout<<"counts [d= "<<count(this->discards)<<", s= "<<count(this->cards)<<", b= "<<count(this->shute)<<"]"<<std::endl;*/

	if(cards.size() == 0)
	{
		int n = Deck::cards.size();
		for (int i=0; i<decks; i++)
		{
			for (int j=0; j<n; j++)
			{		
				cards.push_back(Deck::cards[j]);					
			}
		}

		Shoe::shuffle();
	}
	else
	{
		for(std::vector<Card>::iterator card = discards.begin(); card != discards.end(); ++card)
			cards.push_back(*card);
		discards.clear();
	}

	while (shute.size() <= buffer_size)
	{
		Card card = cards.back();
		cards.pop_back();
		shute.push_back(card);
	}
}

int CSM::count(const std::vector<Card>& cards)
{
	int card_count = 0;

	if (cards.empty())
	{
		for(std::vector<Card>::iterator card = discards.begin(); card != discards.end(); ++card)
		{
			if (card->value() >= 10)
				--card_count;
			else if (card->value() <= 6)
				++card_count;
		}
	}
	else
	{
		for(std::vector<Card>::const_iterator card = cards.begin(); card != cards.end(); ++card)
		{
			if (card->value() >= 10)
				--card_count;
			else if (card->value() <= 6)
				++card_count;
		}
	}

	return card_count;
}

void CSM::print()
{
	Shoe::print();
	std::cout<<std::endl;

	int i=0;
	for(std::vector<Card>::iterator card = shute.begin(); card != shute.end(); ++card)
	{
		std::cout<<i++<<":"<<*card<<std::endl;
	}
}