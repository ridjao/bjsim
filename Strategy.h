#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy
{
public:
	virtual char get_action(int player_total, int dealer_total, bool soft, bool pair, int cards) = 0;
	virtual double compute_bet(int count);
};

class BasicStrategy: public Strategy
{
	char get_action(int player_total, int dealer_total, bool soft, bool pair, int cards);
};

class InteractiveStrategy: public Strategy
{
	char get_action(int player_total, int dealer_total, bool soft, bool pair, int cards);
};

class ConservativeStrategy: public Strategy
{
	char get_action(int player_total, int dealer_total, bool soft, bool pair, int cards);
};

class AdvancedStrategy: public Strategy
{
	char get_action(int player_total, int dealer_total, bool soft, bool pair, int cards);
};

extern BasicStrategy basic;
extern InteractiveStrategy interactive;
extern ConservativeStrategy conservative;
extern AdvancedStrategy advanced;

#endif /* STRATEGY_H */
