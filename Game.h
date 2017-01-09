#include <ctime>
#include <vector>

#include "Player.h"
#include "Shoe.h"

#ifndef GAME_H
#define GAME_H

struct Parameters
{
	Card player_card1;
	Card player_card2;
	Card dealer_card1;
	Card dealer_card2;

	int times;
	int decks;
};

class Game
{
public:
	Game(int players);
	Game::Game(std::vector<Player> players, Parameters* pParams = NULL);
	void run(int times = 1000000);

	void deal(int count = 0);
	void play(); 
	void pay();  

	bool is_show_mode();
	void set_show_mode(bool show_mode);

private:
	std::vector<Player> players;
	Dealer dealer;
	bool show_mode;
	time_t elapsed;
	
	Shoe shoe;
	Parameters* pParams;

	void report(int times);
};

#endif /* GAME_H */
