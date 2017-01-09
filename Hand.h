#include <vector>

#include "Deck.h"

#ifndef HAND_H
#define HAND_H

class Hand: public std::vector<Card>
{
public:
	Hand();
	void add(Card& card);
	Card sub();
	void set_bet(double bet);
	double get_bet();
	int get_total();
	bool is_soft();
	bool is_pair();
	void surrender();
	bool is_doubled();
	void set_doubled(bool doubled);

private:
	bool pair;
	bool soft;
	int total;
	double bet;
	bool doubled;
};


#endif /* HAND_H */