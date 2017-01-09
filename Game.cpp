#include <iostream>

#include "Game.h"
#include "Strategy.h"

Game::Game(int players):dealer("Dealer ")
{
	for (int i=0; i<players; i++)
	{
		char id[2]={0};
		id[0]='0'+i+1;
		std::string name = "Player"; 
		name+=id; 
		this->players.push_back(Player(name, &basic));
	}

	show_mode = false;
	pParams = NULL;
}

Game::Game(std::vector<Player> players, Parameters* pParams):dealer("Dealer ")
{
	for (unsigned int i=0; i<players.size(); i++)
	{
		this->players.push_back(players[i]);
	}

	this->pParams = pParams;
	show_mode = false;
}

void Game::deal(int count)
{
	Card player_card1("0X");
	Card player_card2("0X");
	Card dealer_card1("0X");
	int decks = 6;

	if (pParams)
	{
		player_card1 = pParams->player_card1;
		player_card2 = pParams->player_card2;
		dealer_card1 = pParams->dealer_card1;		
		decks = pParams->decks;
	}

	shoe.load(decks);
	shoe.shuffle();
	//if (is_show_mode()) shoe.print();

	double bet = 1.0;
	if (count != 0)
	{
		if (decks == 6)
		{
			if (count >= 5 && count < 10)
				bet = 2.0;
			else if (count >= 10)
				bet = 3.0;
		}
		else
			bet = bet + (count/decks)*bet;
	}

	/* deal fist cards */
	for (std::vector<Player>::iterator player = players.begin(); player != players.end(); ++player)
	{
		player->set_bet(0,bet);
		player->receive(0,shoe.deal(player_card1));
	}
	dealer.receive(0,shoe.deal(dealer_card1));

	/* deal players' second cards & show hands */
	for (std::vector<Player>::iterator player = players.begin(); player != players.end(); ++player)
	{
		player->receive(0,shoe.deal(player_card2));
		if (is_show_mode()) player->show_hand(0);
	}

	if (is_show_mode()) dealer.show_hand(0);
}

void Game::play()
{
	Card dealer_card2("0X");

	if (pParams)
		dealer_card2 = pParams->dealer_card2;

	char action;
	int splits = 0;
	bool all_bjs = true;
	bool all_busts = true;
	bool splitting_aces = false;

	for (std::vector<Player>::iterator player = players.begin(); player != players.end(); ++player)
	{	
		splitting_aces = false;
		splits = 0;
		for (int i=0; i<player->get_number_of_hands(); i++)
		{
			//second card for split hands
			if (i > 0) 
			{			
				player->receive(i, shoe.deal()); 

				if (splitting_aces) break;

				if (is_show_mode()) 
				{
					std::cout<<std::endl;
					player->show_hand(i);
				}
			}

			//blackjack
			if ((player->total(i)) == 21)
			{		
				break;
			} 

			//at least one non-black jack hand
			all_bjs = false;

			if (is_show_mode()) 
			{
				std::cout<<player->get_name()<<" on hand"<<i+1<<": hit/stand? ";
			}

			//std::cin>>action; 
			action = player->get_action(i, dealer.total(0));

			if (is_show_mode())
			{
				std::cout<<action;
				std::cout<<std::endl;
			}

			if (action == 'r')
			{
				player->surrender(i);
			}
			else
			{
				while (action != 's')	
				{
					if (action == 'p' && splits < 2)
					{
						player->split(i);
						++splits;			
					}
					
					if (action == 'd') 
						player->double_bet(i);

					if (action == 'p' && player->total(i) == 11)
					{
						splitting_aces = true;
					}

					player->receive(i, shoe.deal());

					if (action == 'd' || splitting_aces || player->total(i) == -1 || player->total(i) == 21) 
						break;

					if (is_show_mode())
					{
						player->show_hand(i);
						std::cout<<player->get_name()<<" on "<<i+1<<": hit/stand? ";					
					}

					//std::cin >> action;
					action = player->get_action(i, dealer.total(0));

					if (is_show_mode())
					{
						std::cout<<action;
						std::cout<<std::endl;
					}
				}
			}

			if (is_show_mode()) player->show_hand(i);

			//at least one hand was not busted
			if (player->total(i) != -1)
			{
				 all_busts = false;
			}
		}
	}

	//dealers second card
	if (is_show_mode()) std::cout<<std::endl;
	int dealer_total = dealer.total(0);
	if ((!all_busts && !all_bjs) || (all_bjs && (dealer_total==10 || dealer_total==11)))
	{
		while (dealer.total(0) < 17 && dealer.total(0) != -1)
		{
			dealer.receive(0,shoe.deal(dealer_card2));			
			if (is_show_mode()) dealer.show_hand(0);
		}
	}
}

void Game::pay()
{
	bool dealer_bj = dealer.is_blackjack(0);
	int dealer_total = dealer.total(0);

	for (std::vector<Player>::iterator player = players.begin(); player != players.end(); ++player)
	{				
		for (int i=0; i<player->get_number_of_hands(); i++)
		{
			if (is_show_mode()) player->show_hand(i);

			bool player_bj = (player->is_blackjack(i) && (player->get_number_of_hands() == 1));
			if (player->total(i) == -1 || (dealer_bj && !player_bj) ||  dealer_total > player->total(i))
			{
				//dealer.win(0);
				if (dealer_bj && player->is_doubled(i))
					player->set_bet(i, 0.5*player->get_bet(i));

				player->loss(i);
				if (is_show_mode()) std::cout<<"Dealer wins vs "<<player->get_name()<<"'s hand"<<i+1<<"!" << std::endl;
			}
			else if ((player_bj && !dealer_bj) || dealer_total < player->total(i))
			{
				//dealer.loss(0);
				player->win(i, player_bj);
				if (is_show_mode()) std::cout<<player->get_name()<<"'s hand"<<i+1<<" wins!"<<std::endl;
			}
			else
			{
				if (is_show_mode()) std::cout<<player->get_name()<<"'s hand"<<i+1<<" push!"<<std::endl;
			}

			if (is_show_mode()) std::cout<<std::endl;
		}
		player->discard_hands();
	}
	dealer.discard_hands();
}

void Game::report(int times)
{
	for (std::vector<Player>::iterator player = players.begin(); player != players.end(); ++player)
	{
		double earnings = player->get_earnings();
		double ev = (earnings/times)*100;
		std::string name = player->get_name();
		std::cout<<name<<": "<<earnings<<" ("<<player->get_wins()<<"/"<<player->get_pairs()<<"/"<<times<<")"<<" ["<<ev<<"]"<<std::endl;
	}
	std::cout<<std::endl<<"Simulation took "<<double(this->elapsed)/60<<" minutes."<<std::endl;
}

bool Game::is_show_mode()
{
	return show_mode;
}

void Game::set_show_mode(bool show_mode)
{
	this->show_mode = show_mode; 
}

void Game::run(int times)
{
	if (pParams)
		times = pParams->times;

	int i = 0;
	int progress = 0, last_progress = 0;
	int count = 0;
	this->elapsed = std::time(0);
	do
	{
		deal(count);
		play();
		pay();		

		if (is_show_mode())
		{
			char action;
			std::cout<<"Next?";
			std::cin >> action;
		}
		else
		{
			last_progress = progress;
			progress = int((double(i)/times)*1000);					
			if (progress > last_progress && progress%10 == 0)
				std::cout<<".";
		}

		count = shoe.count();
	} while (++i < times);
	this->elapsed = std::time(0) - this->elapsed;

	std::cout<<std::endl;
	report(times);
}
