/*
 * card.h
 * CS11 Splendor
 */

#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;
static const int GEMS = 6;

class Card{
public:
    //Constructor and destructor
    Card(string color, int prestigeValue, int *prices);
    ~Card(); 
    //Methods
    int getPrestige();
    string getGemColor();
    int getPrice(int index);

private:
    string color;
    int prices[GEMS-1];
    int prestigeValue;
};




#endif