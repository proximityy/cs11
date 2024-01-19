#include "card.h"
#include <iostream>

Card::Card(int suit, int number)
{
    this->suit = suit;
    this->number = number;
}
Card::~Card()
{
    cout << "Argh!" << endl;
}
int Card::getSuit()
{
    return suit;
}
int Card::getNumber()
{
    return number;
}
void Card::setSuit(int suit)
{
    this->suit = suit;
}
void Card::setNumber(int number)
{
    this->number = number;
}