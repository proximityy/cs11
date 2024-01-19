/*
 * card.cpp
 * CS11 Splendor
 */

#include "card.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

  /* Card::Card
   * Input: A color string, an int for the card's prestige, a pointer
   to an int array of gem prices.
   * Description: Constructor for Card class.
   * Output: None.
   */
Card::Card(string color, int prestigeValue, int *prices){
    //Assigns color, prestige, and price values to class variables
    this->color = color;
    this->prestigeValue = prestigeValue;
    //Loop through prices to initialize all values
    for(int i = 0; i < GEMS - 1; i++)
    {
        this->prices[i] = prices[i];
    }
}

  /* Card::~Card
   * Input: None.
   * Description: Destructor for Card class (frees memory).
   * Output: None.
   */
Card::~Card(){
    
}

  /* Card::getPrestige
   * Input: None.
   * Description: Returns prestigeValue variable.
   * Output: Int of the card's prestige.
   */
int Card::getPrestige(){
    return prestigeValue;
}

  /* Card::getGemColor
   * Input: None.
   * Description: Returns card's color variable.
   * Output: String of the card's color.
   */
string Card::getGemColor(){
    return color;
}

  /* Card::getPrice
   * Input: Int index of the price to return.
   * Description: Returns a member of the prices array.
   * Output: Int of a card's price at specified index.
   */
int Card::getPrice(int index){
    return prices[index];
}

