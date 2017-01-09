#include "Hand.h"

Hand::Hand():soft(false), total(0), bet(0), doubled(false){}

void Hand::add(Card& card)
{
	if (total == -1)
	{
		throw std::domain_error("Cannot add card to busted hand.");
	}

	if ((this->size() == 1) && (this->back().rank() == card.rank()))
	{
		pair = true;	
	}
	else
	{
		pair = false;
	}

	int value = card.value(); 
	this->push_back(card);
	if (value == 11)
		soft = true;

	total+=value;
	
	if (total>21)
	{
		if (soft)
		{
			total-=10;
			soft=false;
		}
		else
		{
			total=-1;
		}
	}
}

Card Hand::sub()
{
	Card card;
	card = this->back();
	this->pop_back();

	total-=card.value();
	if (total == 1)
		total = 11;

	return card;
}

void Hand::set_bet(double bet)
{
	this->bet=bet;
}

double Hand::get_bet()
{
	return bet;
}

int Hand::get_total()
{
	return total;
}

bool Hand::is_soft()
{
	return soft;
}

bool Hand::is_pair()
{
	return pair;
}

void Hand::surrender()
{
	total = -1;
}

bool Hand::is_doubled()
{
	return doubled;
}

void Hand::set_doubled(bool doubled)
{
	this->doubled = doubled;
}