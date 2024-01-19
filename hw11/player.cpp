/*
 * player.cpp
 * CS11 Splendor
 */

#include "player.h"


  /* Player::Player
   * Input: None
   * Description: Constructor for Player class.
   * Output: None.
   */
Player::Player(){
    //Initialize prestigePoints, and loop through discounts
    //and reservedCards to initialize them as well.
    prestigePoints = 0;
    for(int i = 0; i < GEMS - 1; i++){
        discounts[i] = 0;
    }
    for(int i = 0; i < GEMS; i++){
        gems[i] = 0;
    }
    for(int i = 0; i < 3; i++)
    {
        reservedCards[i] = nullptr;
    }
}

  /* Player::~Player
   * Input: None
   * Description: Destructor for Player class (frees memory).
   * Output: None.
   */
Player::~Player(){

}

  /* Player::totalPrestige
   * Input: None
   * Description: Getter for prestigePoints.
   * Output: Int containing total prestige points.
   */
int Player::totalPrestige(){
    return this->prestigePoints;
}

  /* Player::getDiscount
   * Input: Int of discount index.
   * Description: Getter for discounts at provided index.
   * Output: Int containing discounts at provided index.
   */
int Player::getDiscount(int index){
    return this->discounts[index];
}

  /* Player::setDiscount
   * Input: Int of discount index.
   * Description: Increments discounts at a provided index by 1.
   * Output: None.
   */
void Player::setDiscount(int index){
    discounts[index]++;
}

  /* Player::getGemCount
   * Input: Int of gems index.
   * Description: Returns gem count of a provided color index.
   * Output: Int containing total gems of a specific type.
   */
int Player::getGemCount(int index){
    return this->gems[index];
}

  /* Player::getReserve
   * Input: Int of reservedCards index.
   * Description: Returns a card pointer from reservedCards at provided index.
   * Output: Pointer to a card in reservedCards.
   */
Card *Player::getReserve(int index){
    return this->reservedCards[index];
}

  /* Player::addGem
   * Input: Int of gems index.
   * Description: Increments gem of provided color index by 1.
   * Output: None.
   */
void Player::addGem(int gem_index){
    gems[gem_index]++;
}

  /* Player::setReserve
   * Input: A card pointer.
   * Description: Sets a reservedCards member to point to a provided card.
   * Output: None.
   */
void Player::setReserve(Card *c){
    //Make sure the index in reservedCards is empty before adding a card
    if(reservedCards[0] == nullptr){
        reservedCards[0] = c;
    }
    else if(reservedCards[1] == nullptr){
        reservedCards[1] = c;
    }
    else{
        reservedCards[2] = c;
    }
}

  /* Player::deleteReserve
   * Input: Int of reservedCards index.
   * Description: Delete a card in reservedCards and shift the other
   * cards accordingly.
   * Output: None.
   */
void Player::deleteReserve(int index)
{
    //Delete the specified reservedCard.
    delete reservedCards[index];
    reservedCards[index] = nullptr;
    //If the index was 0, shift the other two cards down.
    if(index == 0){
        reservedCards[0] = reservedCards[1];
        reservedCards[1] = reservedCards[2];
        reservedCards[2] = nullptr;
    }
    //If the index was 1, shift the second card down.
    else if(index == 1){
        reservedCards[1] = reservedCards[2];
        reservedCards[2] = nullptr;
    }
}

  /* Player::removeGems
   * Input: Int of gem index, int amount of gems to remove.
   * Description: Removes a specified amount of gems of specified type.
   * Output: None.
   */
void Player::removeGems(int gem_index, int amount)
{
    gems[gem_index] = gems[gem_index] - amount;
}


  /* Player::addPrestige
   * Input: Int number of prestige points.
   * Description: Increment prestigePoints by provided amount.
   * Output: None.
   */
void Player::addPrestige(int prestige)
{
    prestigePoints = prestigePoints + prestige;
}