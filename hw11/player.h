/*
 * player.h
 * CS11 Splendor
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
using namespace std;


class Player {
public:
    //constructor and destructor
    Player();
    ~Player();
    //Methods
    int totalPrestige();
    int getDiscount(int index);
    void setDiscount(int index);
    int getGemCount(int index);
    void setReserve(Card *c);
    Card *getReserve(int index);
    void deleteReserve(int index);
    void addGem(int gem_index);
    void removeGems(int gem_index, int amount);
    void addPrestige(int prestige);

private:
    int prestigePoints;
    int discounts[GEMS-1];
    int gems[GEMS];
    Card *reservedCards[3];
};

#endif