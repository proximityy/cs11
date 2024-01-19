/*
 * game.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/9/2022
 * Edited for HW10 by: {YOUR NAME HERE}
 * Date: {DATE YOU STARTED WORKING ON THE HOMEWORK HERE}
 * Purpose: Implement the methods for the Game class in the Rack-O game.
 *
 */
#include "game.h"
#include <iostream>

using namespace std;

// Constructor: initialize the deck, player hands, and the discard pile with new
// objects allocated on the heap
Game::Game(string deckFileName)
{
    deck = new Deck(deckFileName);
    for (int i = 0; i < NUM_PLAYERS; i++) {
        hands[i] = new Hand(deck->draw(), deck->draw(), deck->draw(),
                            deck->draw(), deck->draw());
    }
    discard = new DiscardPile(deck->draw());
}

// Destructor: deallocate all of the objects ''owned'' by the Game object
Game::~Game()
{
    for (int i = 0; i < NUM_PLAYERS; i++) {
        delete hands[i];
    }
    delete discard;
    delete deck;
}

// play
// Input: none
// Description: Play through a game of rack-o!
// Output: None
void Game::play()
{
    int playerNum = 0;

    // Take the first turn
    cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
    takeTurn(playerNum);
    cout << endl;

    // Keep taking turns until either one player wins, or the deck runs out of
    // cards.
    while (!didPlayerWin(playerNum) && !deck->isEmpty()) {
        playerNum = (playerNum + 1) % NUM_PLAYERS;
        cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
        takeTurn(playerNum);
        cout << endl;
    }
    if (didPlayerWin(playerNum)) {
        // A player won!
        cout << "CONGRATULATIONS PLAYER " << playerNum + 1 << "! YOU WIN!!"
             << endl;
    } else {
        // deck is empty
        cout << "The deck is empty. IT'S A TIE!" << endl;
    }
}

  /* Game:takeTurn
   * Input: Int of currently playing player.
   * Description: Allow the specified player to take a turn either
   * drawing a Card or taking one from the discard pile, replacing that Card
   * in their Deck, and printing out their new Deck.
   * Output: None (void).
   */
void Game::takeTurn(int playerNum)
{
    //Check for valid player number
    if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
        cerr << "Invalid player number: " << playerNum << endl;
        exit(EXIT_FAILURE);
    }
    //Print out hand and discard pile
    cout << "Your hand:" << endl;
    hands[playerNum]->print();
    cout << endl << "Discard pile:" << endl;
    discard->print();
    //Prompt user to draw from deck or discard pile, and check for valid input
    cout << endl << "Would you like to" << endl;
    cout << " 1. take the top discard?" << endl;
    cout << " 2. draw from the deck?" << endl;
    int choice = 0;
    while(choice != 1 && choice != 2)
    {
        cout << "Enter the number for your choice: ";
        cin >> choice;}
    //Call helper functions
    if(choice == 1){
        takeDiscard(playerNum);
    }
    else{
        drawFromDeck(playerNum);
    }
    hands[playerNum]->print();
}

  /* Game::takeDiscard
   * Input: Int of currently playing player.
   * Description: Allow user to draw the Card from discard pile and 
   * prompt for a Card in the Deck to be swapped out.
   * Output: None (void).
   */
void Game::takeDiscard(int playerNum)
{
    //Check for valid player number
    if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
        cerr << "Invalid player number: " << playerNum << endl;
        exit(EXIT_FAILURE);
    }
    cout << endl;
    //Get a pointer to the card on top of discard pile
    Card *old_discard_card = discard->takeDiscard();
    //Get a pointer to the card the user wants to be replaced, and replace it
    Card *new_discard_card = hands[playerNum]->replaceCard(old_discard_card);
    //Discard the card the user wants to be replaced
    discard->discard(new_discard_card);
    cout << endl << "Your new hand:" << endl;
}

  /* Game::drawFromDeck
   * Input: Int of currently playing player. 
   * Description: Allow user to draw a Card from top of Deck, and choose
   * whether or not to keep it in their Hand.
   * Output: None (void).
   */
void Game::drawFromDeck(int playerNum)
{
    //Check for valid player number
    if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
        cerr << "Invalid player number: " << playerNum << endl;
        exit(EXIT_FAILURE);
    }
    //Get a pointer to card on top of deck, and print it out
   Card *top_deck_card = deck->draw();
   cout << endl << "You drew:" << endl;
   cout << top_deck_card->toString() << endl;
   char choice = 'a';
   //Check for valid input
   while(choice != 'y' && choice != 'n'){
        cout << "Would you like to keep this card? (y/n) ";
        cin >> choice;
    }
    //If user wants to keep the card
    if(choice == 'y'){
        cout << endl;
        Card *card_to_discard = 
        hands[playerNum]->replaceCard(top_deck_card);
        discard->discard(card_to_discard);
    }
    //If user doesn't want to keep the card
    else{
        cout << endl;
        discard->discard(top_deck_card);
    }
   cout << endl << "Your new hand:" << endl;
}

// didPlayerWin
// Input: The player whose turn it is.
// Description: Check if the player has triggered the win condition
// Output: True if the given player has won; false otherwise.
bool Game::didPlayerWin(int playerNum)
{
    if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
        cerr << "Invalid player number: " << playerNum << endl;
        exit(EXIT_FAILURE);
    }

    return hands[playerNum]->isWinningHand();
}
