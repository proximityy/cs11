#ifndef	CARD_H
#define	CARD_H

#include <string>
using namespace std;

class Card {
public:
    Card(int suit, int number);
    ~Card();
    int getSuit();
    int getNumber();
    void setSuit(int suit);
    void setNumber(int number);

private:
    int suit;
    int number;
};

#endif