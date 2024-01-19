/*
 * discard_pile.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/9/2022
 * Purpose: Implement the methods for the DiscardPile class in the Rack-O game.
 *
 */
#include "discard_pile.h"
#include <iostream>

using namespace std;

// Constructor: Set the top card of the pile
DiscardPile::DiscardPile(Card *seedCard)
{
    topDiscard = seedCard;
}

// Destructor: deallocate the one card on top of the pile (if the pile isn't
// empty)
DiscardPile::~DiscardPile()
{
    if (topDiscard != NULL) {
        delete topDiscard;
    }
}

// discard
// Input: A pointer to a card
// Description: Replace (and deallocate) the current top card on the discard
//              pile with the provided card.
// Output: None
void DiscardPile::discard(Card *discard)
{
    if (topDiscard != NULL) {
        delete topDiscard;
    }
    topDiscard = discard;
}

// takeDiscard
// Input: None
// Description: Clear out the discard pile.
// Output: The top card that was on the discard pile.
Card *DiscardPile::takeDiscard()
{
    Card *drawCard = topDiscard;
    topDiscard = NULL;
    return drawCard;
}

/*
 * Everything below this comment is purely for "drawing" discard piles on the
 * screen.  Students won't need to read through or modify any of these methods.
 */

void DiscardPile::print()
{
    if (topDiscard == NULL) {
        cout << "(NULL)" << endl;
    } else {
        cout << topDiscard->toString();
    }
}
