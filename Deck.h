#include <vector>

#ifndef DECK_H
#define DECK_H
class Card: public std::string
{
public:
	Card();
	Card(std::string name);
	int value() const;
	char rank() const;
};

class Deck
{
public:
	static std::vector<Card> cards;
	static void initialize();

private:
	static void print();
};

#endif /* DECK_H */