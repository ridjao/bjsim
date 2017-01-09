#include <vector>

#include "Deck.h"

#ifndef SHOE_H
#define SHOE_H

class Shoe
{
public:
	Shoe();
	void shuffle();
	void load(int decks);
	Card deal();
	Card deal(const Card& card);
	void print();
	int count(const std::vector<Card>& cards = std::vector<Card>());

protected:
	std::vector<Card> cards;
};

class CSM: public Shoe
{
public:
	Card deal();
	Card deal(const Card& card);
	void CSM::load(int decks);
	void print();
	int count(const std::vector<Card>& cards = std::vector<Card>());

private:
	std::vector<Card> shute;
	std::vector<Card> discards;
};

#endif /* SHOE_H */