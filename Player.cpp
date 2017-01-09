#include <exception>
#include <iostream>
#include <vector>
#include <string>

#include "Deck.h"
#include "Hand.h"
#include "Player.h"

Player::Player(std::string name, Strategy *pStrategy)
{
	this->pStrategy = pStrategy;
	this->name = name;
	number_of_hands = 1;
	earnings = 0;
	hands.push_back(Hand());
	wins = 0;

	pairs = 0;
}

void Player::receive(int hand, Card& card)
{
	if (hand >= number_of_hands)
	{
		throw std::invalid_argument("Cannot receive card for an invalid hand");
	}
	hands[hand].add(card);
}

int Player::total(int hand)
{
	if (hand >= number_of_hands)
	{
		throw std::invalid_argument("Cannot total an invalid hand");
	}

	return hands[hand].get_total();
}

void Player::show_hand(int hand)
{
	if (hand >= number_of_hands)
	{
		throw std::invalid_argument("Cannot show an invalid hand");
	}

	std::string cards=get_name()+": ";
	for(std::vector<Card>::iterator card = hands[hand].begin(); card != hands[hand].end(); ++card)
	{
		cards+=(*card + " ");
	}
	std::cout<<"["<<hand<<"/"<<hands[hand].get_bet()<<"/"<<earnings<<"]"<<cards<<"("<<hands[hand].get_total()<<")"<<std::endl;
}

void Player::set_bet(int hand, double bet)
{
	hands[hand].set_bet(bet);
}

double Player::get_bet(int hand)
{
	return hands[hand].get_bet();
}

double Player::compute_bet(int count)
{
	if(pStrategy)
		return pStrategy->compute_bet(count);
	return 1.0;
}

void Player::double_bet(int hand)
{
	if (hands[hand].size() != 2)
	{
		throw std::domain_error("Double not allowed on hand");
	}

	hands[hand].set_bet(2*hands[hand].get_bet());
	hands[hand].set_doubled(true);
}

void Player::split(int hand)
{
	/* to do: if not pair throw exception */
	Card card = hands[hand].sub();		

	Hand new_hand;
	new_hand.add(card);
	new_hand.set_bet(hands[hand].get_bet());

	hands.push_back(new_hand);
	++number_of_hands;
}

void Player::surrender(int hand)
{
	hands[hand].set_bet(0.5*hands[hand].get_bet());
	hands[hand].surrender();
}

void Player::win(int hand, bool bj=false)
{
	double x = 1;
	if (bj) x = 1.5;
	/* check hand */
	earnings += hands[hand].get_bet()*x;
	++wins;
}

void Player::loss(int hand)
{
	/* check hand */
	earnings -= hands[hand].get_bet();
}

std::string Player::get_name()
{
	return name;
}

void Player::discard_hands()
{
	hands.clear();
	number_of_hands = 1;
	hands.push_back(Hand()); //re-visit where best to put this
}

int Player::get_number_of_hands()
{
	return number_of_hands;
}

int Player::get_number_of_cards(int hand)
{
	return hands[hand].size();
}

bool Player::is_blackjack(int hand)
{
	return (hands[hand].get_total()==21 && hands[hand].size()==2);
}

char Player::get_action(int hand, int dealer_total)
{
	int player_total = hands[hand].get_total();
	bool soft = hands[hand].is_soft();
	bool pair = hands[hand].is_pair();
	int cards = hands[hand].size();

	if (pair) ++pairs;

	if (pStrategy)
		return pStrategy->get_action(player_total, dealer_total, soft, pair, cards);

	throw std::domain_error("Cannot get action.");
	return 'x';
}

double Player::get_earnings()
{
	return earnings;
}

bool Player::is_doubled(int hand)
{
	return hands[hand].is_doubled();
}

int Player::get_wins()
{
	return wins;
}

int Player::get_pairs()
{
	return pairs;
}