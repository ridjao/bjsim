#include <vector>

#include "Deck.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"
#include "Shoe.h"

Parameters Defaults;

int test_splitting_aces();
int test_11_vs_10();
int test_15_vs_10();
int test_game_sim();
int test_game_interactive();
int test_game_sim_2_players();
int test_game_CSM_6_players();

int main()
{
	//test_11_vs_10();
	//test_game_sim();
	//test_game_interactive();
	//test_15_vs_10();
	//test_game_sim_2_players();
	//test_splitting_aces();

	test_game_CSM_6_players();

	return 0;
}

int test_11_vs_10()
{
	std::vector<Player> players;
	Parameters params;

	params.player_card1 = Card("5C");
	params.player_card2 = Card("6C");
	params.dealer_card1 = Card("KH");
	params.dealer_card2 = Card("0X");
	params.times = 10000;
	params.decks = 6;

	players.push_back(Player("Player1", &basic));
	players.push_back(Player("Player2", &conservative));

	Game test(players,&params);
	test.set_show_mode(false);
	test.run();

	return 0;
}

int test_15_vs_10()
{
	std::vector<Player> players;
	Parameters params;

	params.player_card1 = Card("5C");
	params.player_card2 = Card("TC");
	params.dealer_card1 = Card("KH");
	params.dealer_card2 = Card("0X");
	params.times = 10000;
	params.decks = 6;

	players.push_back(Player("Player1", &basic));
	players.push_back(Player("Player2", &conservative));

	Game test(players,&params);
	test.set_show_mode(false);
	test.run();

	return 0;
}

int test_splitting_aces()
{
	std::vector<Player> players;
	Parameters params;

	params.player_card1 = Card("AC");
	params.player_card2 = Card("AS");
	params.dealer_card1 = Card("0X");
	params.dealer_card2 = Card("0X");
	params.times = 5;
	params.decks = 6;

	players.push_back(Player("Player1", &interactive));

	Game test(players,&params);
	test.set_show_mode(true);
	test.run();

	return 0;
}

int test_game_sim()
{
	std::vector<Player> players;
	Parameters params;

	params.player_card1 = Card("0X");
	params.player_card2 = Card("0X");
	params.dealer_card1 = Card("0X");
	params.dealer_card2 = Card("0X");
	params.times = 10000000;
	params.decks = 6;

	players.push_back(Player("Player", &basic));

	Game test(players,&params);
	test.set_show_mode(true);
	test.run();

	return 0;
}

int test_game_sim_2_players()
{
	std::vector<Player> players;
	Parameters params;

	params.player_card1 = Card("0X");
	params.player_card2 = Card("0X");
	params.dealer_card1 = Card("0X");
	params.dealer_card2 = Card("0X");
	params.times = 100000000;
	params.decks = 6;

	players.push_back(Player("Player1", &basic));
	//players.push_back(Player("Player2", &basic));
	players.push_back(Player("Player2", &conservative));

	Game test(players,&params);
	test.set_show_mode(false);
	test.run();

	return 0;
}

int test_game_interactive()
{
	std::vector<Player> players;
	Parameters params;

	params.player_card1 = Card("0X");
	params.player_card2 = Card("0X");
	params.dealer_card1 = Card("0X");
	params.dealer_card2 = Card("0X");
	params.times = 10000;
	params.decks = 1;

	players.push_back(Player("Player1", &basic));
	//players.push_back(Player("Player2", &basic));

	Game test(players,&params);
	test.set_show_mode(true);
	test.run();

	return 0;
}

int test_game_CSM_6_players()
{
	std::vector<Player> players;
	Parameters params;

	params.player_card1 = Card("0X");
	params.player_card2 = Card("0X");
	params.dealer_card1 = Card("0X");
	params.dealer_card2 = Card("0X");
	params.times = 10000000;
	params.decks = 6;

	players.push_back(Player("Player1", &basic));
	//players.push_back(Player("Player2", &basic));
	//players.push_back(Player("Player3", &basic));
	//players.push_back(Player("Player4", &basic));
	//players.push_back(Player("Player5", &basic));
	//players.push_back(Player("Player6", &basic));
	//players.push_back(Player("Player2", &basic));

	Game test(players,&params);
	test.set_show_mode(false);
	test.run();

	return 0;
}

