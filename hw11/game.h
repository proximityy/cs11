/*
 * game.h
 * CS11 Splendor
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "card.h"
#include "player.h"
#include "vector.h"
using namespace std;

class Game {
public:
    //Constructor and Destructor
    Game(string filename, string play_nobles);
    ~Game();

    //main gameplay
    void playGame();

    //utility functions
    string indexToColor(int index);

private:
    //Vectors to hold vendors, transport, mines, and nobles
    Vector vendors;
    Vector transport;
    Vector mines;
    Vector nobles;

    //Array for gem bank
    int gem_bank[GEMS];

    //Create player objects
    Player *player_1 = new Player();
    Player *player_2 = new Player();

    //Handle commands
    string getCommand();
    void handleCommand(string input, bool player1_turn, bool *is_q);
    bool checkWin(bool player_1_wins);
    void checkGems();
    int p2_allowed(string gem);
    void p2(int gem_index, bool player1_turn);
    int *p3_allowed(string gem_1, string gem_2, string gem_3);
    void p3(int *p3_results, bool player1_turn);
    Card *r_allowed(string row_type, string col_num, bool player1_turn);
    Card *replaceCard(Card *c);
    void reserve(Card *card_to_reserve, bool player1_turn);
    Card *br_allowed(string index, bool player1_turn);
    void br(Card *card_br, bool player1_turn);
    bool enough_gems(Card *c, bool player1_turn);
    int goldGemsRequired(Card *c, bool player1_turn);
    void makePurchase(Card *c, bool player1_turn);
    Card *b_allowed(string row_type, string col_num, bool player1_turn);
    void b(Card *c, bool player1_turn);
    int getColInt(string col_type);
    int getCardType(string row_type);

    //Initialize decks and cards
    void initializeDecks(string filename);
    void initializeDecksHelper(char typeOfPrestige, int prestigeNumber, 
    string discount, int costs[]);
    void initializeCardSetup();

    //drawing functions
    void drawBoard();
    void drawNoble(int vpos, int hpos, Card *c);
    void drawPlayer(int vpos, int hpos, Player *p);
    void drawDeck(int vpos, int hpos, string type);
    void drawCard(int vpos, int hpos, Card *c);
    void drawGem(int vpos, int hpos, string color);
    void clearBoard();

    static const int BOARD_HEIGHT = 41;
    static const int BOARD_WIDTH = 120;
    static const int CARD_WIDTH = 13;
    static const int CARD_HEIGHT = 8;
    static const int CARD_ROWS = 3;
    static const int CARD_COLS = 4;
    static const int NUM_NOBLES = 3;

    //nobles activated true/false
    bool play_nobles;

    //cards in play
    Card *grid[CARD_ROWS][CARD_COLS];

    //display
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    string board_color[BOARD_HEIGHT][BOARD_WIDTH];

    //Gem colors in the game
    string colors[GEMS];
};

#endif
