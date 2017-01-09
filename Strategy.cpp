#include <exception>
#include <iostream>
#include "Strategy.h"

BasicStrategy basic;
InteractiveStrategy interactive;
ConservativeStrategy conservative;
AdvancedStrategy advanced;

double Strategy::compute_bet(int count)
{
	return 1.0;
}

char BasicStrategy::get_action(int player_total, int dealer_total, bool soft, bool pair, int cards)
{
	if (pair)
	{
		//AA
		if (player_total == 12)
		{
			if (dealer_total != 11)
				return 'p';
			return 'h';
		}

		//TT, JJ, QQ, KK
		if (player_total == 20)
		{
			return 's';
		}

		//99
		if (player_total == 18)
		{
			if (dealer_total == 7 || dealer_total == 10 || dealer_total == 11)
				return 's';
			return 'p';
		}
		
		//88
		if (player_total == 16)
		{
			if (dealer_total == 11) //No surrender vs A
				return 'h';

			if (dealer_total >= 9)
				return 'r';
			return 'p';
		}			

		//77
		if (player_total == 14 && dealer_total == 10)
			return 'r';

		//77, 33, 22
		if (player_total == 14 || player_total == 6 || player_total == 4) 
		{
			if (dealer_total >= 8)
				return 'h';
			return 'p';
		}

		//66
		if (player_total == 12)
		{
			if (dealer_total >= 7)
				return 'h';
			return 'p';
		}

		//55
		if (player_total == 10)
		{
			if (player_total > dealer_total) 
				return 'd';
			return 'h';
		}

		//44
		if (player_total == 8) 
		{
			if (dealer_total == 5 || dealer_total == 6)
				return 'p';
			return 'h';
		}	
	}
	else if (!soft)
	{
		if (dealer_total >= 7) /* 7 to A */
		{
			if (player_total >= 17)
				return 's';

			if ((player_total == 11 || player_total == 10) && player_total > dealer_total)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			if (player_total == 16 && dealer_total == 10 && cards == 2)
				return 'r';

			if (player_total == 16 && dealer_total == 10 && cards > 2)
				return 's';

			if (player_total >= 14 && player_total <= 16 && (dealer_total == 10 || dealer_total == 9) && cards == 2)
				return 'r';

			if (player_total < 17)
				return 'h';
		}
		else /* 2 to 6 */
		{
			if (player_total >= 13)
				return 's';
			
			if (player_total == 12 && dealer_total >= 4)
				return 's';

			if (player_total == 12 && (dealer_total == 2 || dealer_total == 3))
				return 'h';

			if (player_total == 11 || player_total == 10)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			if (player_total == 9 && dealer_total != 2)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			if (player_total == 9 && dealer_total == 2)
				return 'h';

			if (player_total < 9)
				return 'h';
		}
	}
	else /*soft*/
	{
		if (player_total >= 19) /* A8 or higher */
			return 's';

		if (dealer_total >= 7) /* 7 to A */
		{
			if (player_total == 18 && dealer_total >= 9)
				return 'h';

			if (player_total == 18 && dealer_total < 9)
				return 's';

			if (player_total < 18)
				return 'h';
		}
		else 
		{
			if (dealer_total >= 5) /* 5 and 6 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 4 && player_total >= 15) /* A4, A5 or higher vs 4 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 4 && player_total < 15)
				return 'h';

			if (dealer_total == 3 && player_total >= 17) /* A6, A7 or higher vs 3 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 3 && player_total < 17)
				return 'h';

			if (dealer_total == 2)
				return 'h';
		}
	}

	return 'x';
}

char InteractiveStrategy::get_action(int player_total, int dealer_total, bool soft, bool pair, int cards)
{
	char action;
	std::cin>>action;
	return action;
}

char ConservativeStrategy::get_action(int player_total, int dealer_total, bool soft, bool pair, int cards)
{
	if (pair)
	{
		//AA
		if (player_total == 12)
		{
			if (dealer_total != 11)
				return 'p';
			return 'h';
		}

		//TT, JJ, QQ, KK
		if (player_total == 20)
		{
			return 's';
		}

		// 0. Don't split 9s
		//99
		if (player_total == 18)
		{
			if (dealer_total == 7 || dealer_total == 10 || dealer_total == 11)
				return 's';
			return 's';
		}
		
		//88
		if (player_total == 16)
		{
			if (dealer_total == 11) //No surrender vs A
				return 'h';

			if (dealer_total >= 9)
				return 'r';
			return 'p';
		}			

		//77
		if (player_total == 14 && dealer_total == 10)
			return 'r';

		//77, 33, 22
		if (player_total == 14 || player_total == 6 || player_total == 4) 
		{
			if (dealer_total >= 8)
				return 'h';
			return 'p';
		}

		//66
		if (player_total == 12)
		{
			if (dealer_total >= 7)
				return 'h';
			return 'p';
		}

		//55
		if (player_total == 10)
		{
			if (player_total > dealer_total) 
				return 'd';
			return 'h';
		}

		//44
		if (player_total == 8) 
		{
			if (dealer_total == 5 || dealer_total == 6)
				return 'p';
			return 'h';
		}	
	}
	else if (!soft)
	{
		if (dealer_total >= 7) /* 7 to A */
		{
			if (player_total >= 17)
				return 's';

			// 1. just hit on 11 vs 10
			if (player_total == 11 && dealer_total == 10)
				return 'h';

			if ((player_total == 11 || player_total == 10) && player_total > dealer_total)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			// 2. stay at 16 vs 10
			if (player_total == 16 && dealer_total == 10 && cards == 2)
				return 'r';

			if (player_total == 16 && dealer_total == 10 && cards > 2)
				return 's';

			// 2. stay at 15 vs 10
			if (player_total == 15 && dealer_total == 10)
				return 's';

			if (player_total >= 14 && player_total <= 16 && (dealer_total == 10 || dealer_total == 9) && cards == 2)
				return 'r';

			if (player_total < 17)
				return 'h';
		}
		else /* 2 to 6 */
		{
			if (player_total >= 13)
				return 's';
			
			if (player_total == 12 && dealer_total >= 4)
				return 's';

			// 3. stay on 2 vs 12 & 13
			if (player_total == 12 && (dealer_total == 2 || dealer_total == 3))
				return 's';

			if (player_total == 11 || player_total == 10)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			if (player_total == 9 && dealer_total != 2)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			if (player_total == 9 && dealer_total == 2)
				return 'h';

			if (player_total < 9)
				return 'h';
		}
	}
	else /*soft*/
	{
		// 4. staty on soft 18
		if (player_total >= 18) /* A8 or higher */
			return 's';

		if (dealer_total >= 7) /* 7 to A */
		{
			if (player_total == 18 && dealer_total >= 9)
				return 'h';

			if (player_total == 18 && dealer_total < 9)
				return 's';

			if (player_total < 18)
				return 'h';
		}
		else 
		{
			if (dealer_total >= 5) /* 5 and 6 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 4 && player_total >= 15) /* A4, A5 or higher vs 4 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 4 && player_total < 15)
				return 'h';

			if (dealer_total == 3 && player_total >= 17) /* A6, A7 or higher vs 3 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 3 && player_total < 17)
				return 'h';

			if (dealer_total == 2)
				return 'h';
		}
	}

	return 'x';
}

char AdvancedStrategy::get_action(int player_total, int dealer_total, bool soft, bool pair, int cards)
{
	if (pair)
	{
		//AA
		if (player_total == 12)
		{
			if (dealer_total != 11)
				return 'p';
			return 'h';
		}

		//TT, JJ, QQ, KK
		if (player_total == 20)
		{
			return 's';
		}

		//99
		if (player_total == 18)
		{
			if (dealer_total == 7 || dealer_total == 10 || dealer_total == 11)
				return 's';
			return 'p';
		}
		
		//88
		if (player_total == 16)
		{
			if (dealer_total == 11) //No surrender vs A
				return 'h';

			if (dealer_total >= 9)
				return 'r';
			return 'p';
		}			

		//77
		if (player_total == 14 && dealer_total == 10)
			return 'r';

		//77, 33, 22
		if (player_total == 14 || player_total == 6 || player_total == 4) 
		{
			if (dealer_total >= 8)
				return 'h';
			return 'p';
		}

		//66
		if (player_total == 12)
		{
			if (dealer_total >= 7)
				return 'h';
			return 'p';
		}

		//55
		if (player_total == 10)
		{
			if (player_total > dealer_total) 
				return 'd';
			return 'h';
		}

		//44
		if (player_total == 8) 
		{
			if (dealer_total == 5 || dealer_total == 6)
				return 'p';
			return 'h';
		}	
	}
	else if (!soft)
	{
		if (dealer_total >= 7) /* 7 to A */
		{
			if (player_total >= 17)
				return 's';

			if ((player_total == 11 || player_total == 10) && player_total > dealer_total)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			if (player_total == 16 && dealer_total == 10 && cards == 2)
				return 'r';

			if (player_total == 16 && dealer_total == 10 && cards > 2)
				return 's';

			if (player_total >= 14 && player_total <= 16 && (dealer_total == 10 || dealer_total == 9) && cards == 2)
				return 'r';

			if (player_total < 17)
				return 'h';
		}
		else /* 2 to 6 */
		{
			if (player_total >= 13)
				return 's';
			
			if (player_total == 12 && dealer_total >= 4)
				return 's';

			if (player_total == 12 && (dealer_total == 2 || dealer_total == 3))
				return 'h';

			if (player_total == 11 || player_total == 10)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			if (player_total == 9 && dealer_total != 2)
			{
				if (cards == 2)
					return 'd';

				return 'h';
			}

			if (player_total == 9 && dealer_total == 2)
				return 'h';

			if (player_total < 9)
				return 'h';
		}
	}
	else /*soft*/
	{
		if (player_total >= 19) /* A8 or higher */
			return 's';

		if (dealer_total >= 7) /* 7 to A */
		{
			if (player_total == 18 && dealer_total >= 9)
				return 'h';

			if (player_total == 18 && dealer_total < 9)
				return 's';

			if (player_total < 18)
				return 'h';
		}
		else 
		{
			if (dealer_total >= 5) /* 5 and 6 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 4 && player_total >= 15) /* A4, A5 or higher vs 4 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 4 && player_total < 15)
				return 'h';

			if (dealer_total == 3 && player_total >= 17) /* A6, A7 or higher vs 3 */
			{
				if (cards == 2)
					return 'd';

				if (player_total == 18)
					return 's';

				return 'h';
			}

			if (dealer_total == 3 && player_total < 17)
				return 'h';

			if (dealer_total == 2)
				return 'h';
		}
	}

	return 'x';
}
