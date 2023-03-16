#include "CardSet.h"
#include <iostream>

CardSet::CardSet()
{
	cardSet_size = 0;
}

bool CardSet::add(unsigned long cardNumber)
// Add a card number to the CardSet.  Return true if and only if the
// card number was actually added.
{
	if (cardSet.size() > DEFAULT_MAX_ITEMS)
	{
		return false;
	}

	else
	{
		if (cardSet.insert(cardNumber) == true)
		{
			cardSet_size++;
			return true;

		}

		return false;
	}
}

int CardSet::size() const  // Return the number of card numbers in the CardSet.
{
	return cardSet.size();
}

void CardSet::print() const
// Write to cout every card numbe	r in the CardSet exactly once, one
// per line.  Write no other text.
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		unsigned long card;
		if (cardSet.get(i, card) == true)
		{
			cout << card << '\n';
		}
	}
}