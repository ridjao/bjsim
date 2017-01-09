#include <string>

#include "Deck.h"
#include "Hand.h"
#include "Strategy.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(std::string name="", Strategy* pStrategy = NULL);
	void receive(int hand, Card& card);
	int total(int hand);
	void show_hand(int hand);
	void set_bet(int hand, double bet);
	double get_bet(int hand);
	double compute_bet(int count);
	void double_bet(int hand);
	void split(int hand);
	void surrender(int hand);
	void win(int hand, bool bj);
	void loss(int hand);
	std::string get_name();
	void discard_hands();
	int get_number_of_hands();
	int get_number_of_cards(int hand);
	bool is_blackjack(int hand);
	char get_action(int hand, int dealer_total);
	double get_earnings();
	bool is_doubled(int hand);
	int get_wins();

	int get_pairs();
private:
	std::vector<Hand> hands;
	int number_of_hands;
	std::string name;
	double earnings;
	Strategy* pStrategy;
	int wins;

	int pairs;
};

class Dealer: public Player
{
public:
	Dealer(){};
	Dealer(std::string name):Player(name){};
};

#endif /* PLAYER_H */