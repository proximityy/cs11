/*
 * hand.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: Zach Meyers
 * Date: 4/12/2023
 * Purpose: Implement the methods for the Hand class in the Rack-O game.
 *
 */
#include "card.h"
#include "hand.h"
#include <iostream>

using namespace std;

// Constructor: Store the provided card pointers in our hand.
Hand::Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5)
{
    cards[0] = c1;
    cards[1] = c2;
    cards[2] = c3;
    cards[3] = c4;
    cards[4] = c5;
}

// Destructor: Deallocate any cards in our hand
Hand::~Hand()
{
    for (int i = 0; i < HAND_SIZE; i++) {
        delete cards[i];
    }
}

  /* Hand:isWinningHand
   * Input: None.
   * Description: Determine if a Hand object has all cards in ascending order.
   * Output: Boolean (whether or not the deck is in ascending order).
   */
bool Hand::isWinningHand()
{
    //Return whether or not the deck is in ascending order
    return ((cards[0]->getNum() < cards[1]->getNum()) &&
           (cards[1]->getNum() < cards[2]->getNum()) &&
           (cards[2]->getNum() < cards[3]->getNum()) &&
           (cards[3]->getNum() < cards[4]->getNum())); 
}

  /* Hand:replaceCard
   * Input: Pointer to a Card object that the user wants in the new Deck.
   * Description: Prompt the user which Card in the Deck
   * they would like to be replaced with the one they drew.
   * Output: Pointer to a Card that the user would like to discard.
   */
Card *Hand::replaceCard(Card *newCard)
{
    //Create variable to hold user input
    int discard_index = -1;
    //Print out deck
    print();
    cout << endl;
    //Check for valid input
    while(discard_index < 0 || discard_index > 4)
    {
        cout << "Enter the index of the card you'd like to discard: ";
        cin >> discard_index;
    }
    //Create a variable to hold the Card that is to be discarded
    Card *discard_card = cards[discard_index];
    //Set the old Card's index to the new Card, and return the old one
    cards[discard_index] = newCard;
    return discard_card;
}

/*
 * Everything below this comment is purely for "drawing" hands on the screen.
 * Students won't need to read through or modify any of these methods.
 *
 */

void Hand::print()
{
    for (int i = 0; i < HAND_SIZE; i++) {
        if (cards[i] == NULL) {
            cerr << "ERROR: hand does not have " << HAND_SIZE << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        }
    }

    // print Top Edge
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getTopEdge();
    }
    cout << endl;

    // print Blank Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBlankLine();
    }
    cout << endl;

    // print Number Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getNumberLine();
    }
    cout << endl;

    // print Blank Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBlankLine();
    }
    cout << endl;

    // print Bottom Edge
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBottomEdge();
    }
    cout << endl;

    // print index numbers
    for (int i = 0; i < HAND_SIZE; i++) {
        cout << "   ";
        if (i > 0) {
            cout << "    ";
        }
        cout << i;
    }
    cout << endl;
}
