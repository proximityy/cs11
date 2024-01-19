/*
 * game.cpp
 * CS11 Splendor
 */

#include "game.h"
#include <string>

//constructor
Game::Game(string filename, string play_nobles)
{
    //store gem colors for easy reference in drawing functions
    colors[0] = "white";
    colors[1] = "red";
    colors[2] = "pink";
    colors[3] = "blue";
    colors[4] = "green";
    colors[5] = "gold";

    //include nobles or not
    if (play_nobles == "true") {
        this->play_nobles = true;
    } else {
        this->play_nobles = false;
    }

    //initialize decks
    initializeDecks(filename);
    initializeCardSetup();

    //initialize the board
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
    }

    //initialize gem bank
    gem_bank[0] = 4;
    gem_bank[1] = 4;
    gem_bank[2] = 4;
    gem_bank[3] = 4;
    gem_bank[4] = 4;
    gem_bank[5] = 5;
}

//destructor
Game::~Game(){
    //delete both player's reserve cards
    for(int i = 0; i < 3; i++){
        delete player_1->getReserve(i);
        delete player_2->getReserve(i);
    }
    //delete both players
    delete player_1;
    delete player_2;
    //loop through vendors, transport, mines, and nobles
    //and delete their cards
    for(int i = 0; i < vendors.size(); i++){
        delete vendors.at(i);
    }
    for(int i = 0; i < transport.size(); i++){
        delete transport.at(i);
    }
    for(int i = 0; i < mines.size(); i++){
        delete mines.at(i);
    }
    for(int i = 0; i < nobles.size(); i++){
        delete nobles.at(i);
    }
    //clear memory of cards from the grid
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            delete grid[i][j];
        }
    }
}

//main game loop
void Game::playGame()
{
    bool game_over = false;
    bool player1_turn = true;
    //Variables to handle is a quit is requested
    bool q_requested = false;
    bool *is_q = &q_requested;
    bool player_1_wins = false;

    while (!game_over) {
        //reset the screen
        if(*is_q == true){
            break;
        }
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        drawBoard();
        if(player_1->totalPrestige() >= 15){
            player_1_wins = true;
        }
        checkGems();
 
        if(player1_turn){
            cout << "PLAYER 1, enter your next move: ";
        }
        else{
            cout << "PLAYER 2, enter your next move: ";
        }
        //Call getCommand to capture user command
        string input = getCommand();
        //Handle quit command
        if(input == "q"){
            break;
        }
        //Call handleCommand to handle other commands
        handleCommand(input, player1_turn, is_q);
        //Handle a player win
        if(checkWin(player_1_wins)){
            game_over = true;
        }
        //change turns
        player1_turn = !player1_turn;
    }

}

  /* Game::checkWin
   * Input: Bool of whether player 1 has 15 gems.
   * Description: Check if either player has won the game.
   * Output: Boolean of whether a win has occured.
   */
bool Game::checkWin(bool player_1_wins)
{
    int winner = 0;
    if(player_2->totalPrestige() >= 15){
        //If player 1 already has 15 points
        if(player_1_wins){
            //If player 2 has more points than player 1
            if(player_2->totalPrestige() > player_1->totalPrestige()){
                winner = 2;
            }
            //If player 1 has more points than player 2
            else if(player_2->totalPrestige() < player_1->totalPrestige()){
                winner = 1;
            }
            //If it's a tie
            else{
                winner = 3;
            }
        }
        //If player 1 has less than 15 points
        else{
            winner = 2;
        }
    }
    if(winner > 0){
        //display the win
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        drawBoard();   
        if(winner == 1){
            cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
        }
        else if(winner == 2){
            cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
        }
        else{
            cout << "You losers tied - BORING!!!!" << endl;
        }
        return true;
    }
    return false;
}

  /* Game::checkGems
   * Input: None.
   * Description: Check if either player has more than 10 gems and prompt
   * them to return gems accordingly.
   * Output: None.
   */
void Game::checkGems()
{
    //create variables to hold both players' total gem counts
    int player1_gems = 0;
    int player2_gems = 0;
    string gem;
    int gem_index = -1;
    //loop through both players' gems and capture a total count
    for(int i = 0; i < GEMS; i++){
        player1_gems += player_1->getGemCount(i);
        player2_gems += player_2->getGemCount(i);
    }
    //if player 1 has too many gems
    while(player1_gems > 10){
        //ask user to return a gem
        cout << "PLAYER 1, you have more than 10 gems! ";
        cout << "Name one gem you would like to return: ";
        cin >> gem;
        //if user input is invalid
        while(gem != colors[0] && gem != colors[1] && gem != colors[2] &&
        gem != colors[3] && gem != colors[4] && gem != colors[5]){
            cout << "Invalid color. Name one gem you would like to return: ";
            cin >> gem;
        }
        //find a corresponding index to the provided color
        for(int i = 0; i < GEMS; i++){
            if(colors[i] == gem){
                gem_index = i;
            }
        }
        //if user doesn't have enough of the inputted gems to return
        while(player_1->getGemCount(gem_index) < 1){
            cout << "Invalid color. Name one gem you would like to return: ";
            cin >> gem;
            //find a corresponding index to the provided color
            for(int i = 0; i < GEMS; i++){
                if(colors[i] == gem){
                    gem_index = i;
                }
            }
        }
        //return specified gem to the gem_bank
        player_1->removeGems(gem_index, 1);
        gem_bank[gem_index]++;
        player1_gems--;
        //reprint the game
        clearBoard();
        screen_clear();
        screen_home();
        drawBoard();
    }
    //if player 2 has too many gems
    while(player2_gems > 10){
        //ask user to return a gem
        cout << "PLAYER 2, you have more than 10 gems! ";
        cout << "Name one gem you would like to return: ";
        cin >> gem;
        //if user input is invalid
        while(gem != colors[0] && gem != colors[1] && gem != colors[2] &&
        gem != colors[3] && gem != colors[4] && gem != colors[5]){
            cout << "Invalid color. Name one gem you would like to return: ";
            cin >> gem;
        }
        //find a corresponding index to the provided color
        for(int i = 0; i < GEMS; i++){
            if(colors[i] == gem){
                gem_index = i;
            }
        }
        //if user doesn't have enough of the inputted gems to return
        while(player_2->getGemCount(gem_index) < 1){
            cout << "Invalid color. Name one gem you would like to return: ";
            cin >> gem;
            //find a corresponding index to the provided color
            for(int i = 0; i < GEMS; i++){
                if(colors[i] == gem){
                    gem_index = i;
                }
            }

        }
        //return specified gem to the gem_bank
        player_2->removeGems(gem_index, 1);
        gem_bank[gem_index]++;
        player2_gems--;
        //reprint the game
        clearBoard();
        screen_clear();
        screen_home();
        drawBoard();
    }
}

  /* Game::getCommand
   * Input: None.
   * Description: Prompt user for a command and validates it.
   * Output: String of the player's command.
   */
string Game::getCommand()
{
    //Prompt user to enter a command
    string input;
    cin >> input;
    //Ensure the command is valid
    while(input != "q" && input != "p3" && input != "p2" && input != "r"
    && input != "b" && input != "br"){
        cout << "Invalid move - enter a valid move: ";
        cin >> input;
    }
    //Return the command
    return input;
}

  /* Game::handleCommand
   * Input: String containing the command, bool of whether it's player 1's turn
   * and a pointer to a bool of whether or not the user wants to quit
   * Description: Handle a provided player command by calling corresponding
   * helper functions.
   * Output: None.
   */
void Game::handleCommand(string input, bool player1_turn , bool *is_q)
{
    //If user wants to quit, set the quit boolean to true
    if(input == "q"){
        *is_q = true;
    }
    //p2 command
    else if(input == "p2"){
        //input a gem for p2 command
        string gem;
        cin >> gem;
        //verify that p2 is allowed with the provided gem
        int p2_result = p2_allowed(gem);
        //if p2 is allowed, call the main p2 function
        if(p2_result > -1){
            p2(p2_result, player1_turn);
        }
        //otherwise, prompt for another command
        else{
            input = getCommand();
            handleCommand(input, player1_turn, is_q);
        }
    }
    //p3 command
    else if(input == "p3"){
        //input 3 gems for p3 command
        string gem_1, gem_2, gem_3;
        cin >> gem_1 >> gem_2 >> gem_3;
        //verify that p3 is allowed with provided gems
        int *p3_results = p3_allowed(gem_1, gem_2, gem_3);
        //if p3 is allowed, call main p3 function
        if(p3_results[0] > -1){
            p3(p3_results, player1_turn);
        }
        //othwerwise, prompt for another command
        else{
            input = getCommand();
            handleCommand(input, player1_turn, is_q);
        }
        //clear memory of p3_results
        delete [] p3_results;
    }
    //reserve command
    else if(input == "r"){
        //input a row and column of card to reserve
        string row_type, column_num;
        cin >> row_type >> column_num;
        //verify that r command is allowed with provided card
        Card *r_result = r_allowed(row_type, column_num, player1_turn);
        //if r is allowed, call main reserve function
        if(r_result != nullptr){
            reserve(r_result, player1_turn);
        }
        //otherwise, prompt for another command
        else{
            input = getCommand();
            handleCommand(input, player1_turn, is_q);
        }
    }
    //buy reserve command
    else if(input == "br"){
        //input an index to buy from reserved cards
        string index;
        cin >> index;
        //verify that br command is allowed at provided index
        Card *br_result = br_allowed(index, player1_turn);
        //if br is allowed, call main br function
        if(br_result != nullptr){
            br(br_result, player1_turn);
        }
        //otherwise, prompt for another command
        else{
            input = getCommand();
            handleCommand(input, player1_turn, is_q);
        }
    }
    //buy command
    else if(input == "b"){
        //input a row and column of card to buy
        string row_type, col_num;
        cin >> row_type >> col_num;
        //verify that buy command is allowed with provided card
        Card *b_result = b_allowed(row_type, col_num, player1_turn);
        //if buy is allowed, call main buy function
        if(b_result != nullptr){
            b(b_result, player1_turn);
        }
        //otherwise, prompt for another command
        else{
            input = getCommand();
            handleCommand(input, player1_turn, is_q);
        }
    }
}


//Get the gem color associated with the given index
string Game::indexToColor(int index)
{
    return colors[index];
}

//draw all of the elements onto the game board
void Game::drawBoard()
{
    int vpos = 0;
    int hpos = 1;

    //draw the card decks
    if (!vendors.empty()) {
        drawDeck(vpos, hpos, "Vendors");
    }
    vpos += CARD_HEIGHT + 1;
    if (!transport.empty()) {
        drawDeck(vpos, hpos, "Transport");
    }
    vpos += CARD_HEIGHT + 1;
    if (!mines.empty()) {
        drawDeck(vpos, hpos, "Mines");
    }

    //draw the in play cards
    vpos = 0;
    hpos = CARD_WIDTH + 2;
    for (int i = 0; i < CARD_ROWS; i++) {
        for (int j = 0; j < CARD_COLS; j++) {
            if (grid[i][j] != nullptr) {
                drawCard(vpos, hpos, grid[i][j]);
            }
            hpos += CARD_WIDTH + 1;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = CARD_WIDTH + 2;
    }

    //draw the gems
    int gemOffset = ((CARD_WIDTH + 1) * 5) + 3;
    vpos = 1;
    hpos = gemOffset;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            int index = (i * 2) + j;
            if (gem_bank[index] > 0) {
                board[vpos][hpos + 5] = gem_bank[index] + 48;
                board_color[vpos][hpos + 5] = indexToColor(index);
                drawGem(vpos + 1, hpos, indexToColor(index));
            }
            hpos += CARD_WIDTH;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = gemOffset;
    }

    //draw players
    drawPlayer(vpos + 1, 1, player_1);
    drawPlayer(vpos + 1, ((CARD_WIDTH + 1) * 4), player_2);

    //draw nobles
    if (play_nobles) {
        hpos = ((CARD_WIDTH + 1) * 7) + 2;
        vpos = 2;
        for (int i = 0; i < NUM_NOBLES; i++) {
            if (nobles.at(i) != nullptr) {
                drawNoble(vpos, hpos, nobles.at(i));
            }
            vpos += CARD_HEIGHT + 1;
        }
    }

    //print out the finished board
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board_color[i][j] != "white") {
                screen_fg(board_color[i][j]);
            }
            cout << board[i][j];
            screen_fg("white");
        }
        cout << endl;
    }
    cout << endl;
}

//draws a noble at the specified position of the board
void Game::drawNoble(int vpos, int hpos, Card *c)
{
    string top = "|\\  /*\\  /|";
    string second = "| \\/   \\/ |";
    string blank = "N         N";
    string bottom = "~~~~~~~~~~~";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];

        for (int j = 2; j < 5; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + 5][hpos + i] = bottom[i];
    }

    //draw the prices
    vpos += 2;
    for (int i = 0; i < GEMS - 1; i++) {
        int price = c->getPrice(i);
        if (price > 0) {
            board_color[vpos][hpos + 4] = indexToColor(i);
            board_color[vpos][hpos + 5] = indexToColor(i);
            board_color[vpos][hpos + 6] = indexToColor(i);
            board[vpos][hpos + 4] = '|';
            board[vpos][hpos + 5] = price + 48;
            board[vpos][hpos + 6] = '|';
            vpos++;
        }
    }
}

//draws a player at the specified position of the board
void Game::drawPlayer(int vpos, int hpos, Player *p)
{
    //player string
    string prestige = to_string(p->totalPrestige());
    string player_s;
    if (hpos < 10) {
        player_s = " PLAYER 1: " + prestige + " prestige point(s)";
    } else {
        player_s = " PLAYER 2: " + prestige + " prestige point(s)";
    }
    int length = player_s.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = player_s[i];
    }

    //bonus string
    vpos++;
    string bonus_s = "Discounts: ";
    length = bonus_s.length();
    for (int i = 0; i < GEMS - 1; i++) {
        int bonus = p->getDiscount(i);
        bonus_s += "|" + to_string(bonus) + "| ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
        if (bonus >= 10) {
            length += 1;
        }
    }
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = bonus_s[i];
    }

    //gem string
    vpos++;
    string gems_s = "     Gems: ";
    length = gems_s.length();
    int different_gems = GEMS;
    for (int i = 0; i < different_gems; i++) {
        int gems = p->getGemCount(i);
        gems_s += "(" + to_string(gems) + ") ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
    }
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = gems_s[i];
    }

    //reserve string
    vpos++;
    string reserve_s = " Reserved:";
    length = reserve_s.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = reserve_s[i];
    }

    hpos += reserve_s.length();
    for (int i = 0; i < 3; i++) {
        Card *c = p->getReserve(i);
        if (c == nullptr) {
            drawDeck(vpos, hpos, "");
        } else {
            drawCard(vpos, hpos, c);
        }
        hpos += CARD_WIDTH + 1;
    }
}

//draws a card deck at the specified position of the board
void Game::drawDeck(int vpos, int hpos, string type)
{
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];
        for (int j = 2; j < CARD_HEIGHT; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    int start_pos = hpos + (blank.length() / 2) - (type.length() / 2);
    length = type.length();
    for (int i = 0; i < length; i++) {
        board[vpos + (CARD_HEIGHT / 2)][start_pos + i] = type[i];
    }
}

//draws a gem at the specified position of the board
void Game::drawGem(int vpos, int hpos, string color)
{
    string gem_image[6];
    gem_image[0] = "  _______  ";
    gem_image[1] = ".'_/_|_\\_'.";
    gem_image[2] = "\\`\\  |  /`/";
    gem_image[3] = " `\\  | //' ";
    gem_image[4] = "   `\\|/`   ";
    gem_image[5] = "     `     ";

    for (int i = 0; i < GEMS; i++) {
        int length = gem_image[i].length();
        for (int j = 0; j < length; j++) {
            board[vpos + i][hpos + j] = gem_image[i][j];
            board_color[vpos + i][hpos + j] = color;
        }
    }
}

//draws a card at the specified position of the board
void Game::drawCard(int vpos, int hpos, Card *c)
{
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];

        if (i == 8 || i == 9) {
            board_color[vpos + 1][hpos + i] = c->getGemColor();
        }
        board[vpos + 1][hpos + i] = second[i];

        for (int j = 2; j < CARD_HEIGHT; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    //draw the prestige number and gem
    board[vpos + 2][hpos + 3] = c->getPrestige() + 48;
    board_color[vpos + 2][hpos + 8] = c->getGemColor();
    board_color[vpos + 2][hpos + 9] = c->getGemColor();
    board[vpos + 2][hpos + 8] = '\\';
    board[vpos + 2][hpos + 9] = '/';
    board_color[vpos + 1][hpos + 8] = c->getGemColor();
    board_color[vpos + 1][hpos + 9] = c->getGemColor();
    board[vpos + 1][hpos + 8] = '_';
    board[vpos + 1][hpos + 9] = '_';

    //draw the prices
    vpos += 4;
    for (int i = 0; i < GEMS - 1; i++) {
        int price = c->getPrice(i);
        if (price > 0) {
            board_color[vpos][hpos + 2] = indexToColor(i);
            board_color[vpos][hpos + 3] = indexToColor(i);
            board_color[vpos][hpos + 4] = indexToColor(i);
            board[vpos][hpos + 2] = '(';
            board[vpos][hpos + 3] = price + 48;
            board[vpos][hpos + 4] = ')';
            vpos++;
        }
    }
}

//clear the board display
void Game::clearBoard()
{
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
    }
}

  /* Game::initializeDecks
   * Input: A filename.
   * Description: Opens provided file and calls helper function with
   * its data. 
   * Output: None (void).
   */
void Game::initializeDecks(string filename)
{
    //Create variables to hold file contents
   string trash, discount;
   char typeOfPrestige;
   int prestigeNumber;
   int costs[GEMS-1];
   ifstream infile;
   infile.open(filename);
   //If infile doesn't open, exit
   if(infile.fail()){
    cerr << "ERROR: The file " << filename << " failed to open correctly." << endl;
    exit(EXIT_FAILURE);
    }
    getline(infile, trash); 
    //While the end of file hasn't been reached
    while(!infile.eof()){
        //Read file contents into separate variables
        infile >> typeOfPrestige;
        infile >> prestigeNumber;
        infile >> discount;
        for(int i = 0; i < GEMS - 1; i++){
            infile >> costs[i];
        }
        //Call helper function
        initializeDecksHelper(typeOfPrestige, prestigeNumber, discount, costs);
    }
    infile.close();
}

  /* Game::initializeDecksHelper
   * Input: Variables for the prestige type, number of pretige points,
   discount color, and an array of costs
   * Description: Assigns data from initializeDecks() to different mine,
   transport, vendors, and nobles vectors
   * Output: None (void).
   */
void Game::initializeDecksHelper(char typeOfPrestige, int prestigeNumber, 
string discount, int costs[])
{
    //Create a new card
    Card *c = new Card(discount, prestigeNumber, costs);
    //Push back the vector that the Card corresponds to
    if(typeOfPrestige == 'm'){
        mines.push_back(c);
    }
    else if(typeOfPrestige == 't'){
        transport.push_back(c);
    }
    else if(typeOfPrestige == 'v'){
        vendors.push_back(c);
    }
    else{
        nobles.push_back(c);
    }
}

  /* Game::initializeCardSetup
   * Input: None.
   * Description: Initialized the grid with vendors, transports, and mines.
   * Output: None (void).
   */
void Game::initializeCardSetup()
{
    //Loop through vendors section
    for(int i = 0; i < 4; i++){
        grid[0][i] = vendors.back();
        vendors.pop_back();
    }
    //Loop through transport section
    for(int i = 0; i < 4; i++){
        grid[1][i] = transport.back();
        transport.pop_back();
    }
    //Loop through mines section
    for(int i = 0; i < 4; i++){
        grid[2][i] = mines.back();
        mines.pop_back();
    }
}

  /* Game::p2_allowed
   * Input: String of a gem.
   * Description: Determines if p2 is allowed with a provided gem, returns
   * the gem's index.
   * Output: Int of the index of the gem, or -1 if p2 is not allowed.
   */
int Game::p2_allowed(string gem){
    //Check whether the input is a valid gem
    int index = -1;
    for(int i = 0; i < GEMS-1; i++){
        if(gem == colors[i]){
            index = i;
        }
    }
    //Check if provided gem is not in the list of colors
    if(index == -1){
        cout << "Invalid move (invalid color) - enter a valid move: ";
        return -1; //-1 tells the playGame() loop that the p2 input it invalid
    }
    //Check if provided gem has less than 4 available in gem_bank
    if(gem_bank[index] < 4){
        cout << "Invalid move (unavailable gems) - enter a valid move: ";
        return -1; //-1 tells the playGame() loop that the p2 input it invalid
    }
    //Returns gem's index
    return index;
}

  /* Game::p2
   * Input: Int of gem index, bool of whether it's player 1's turn.
   * Description: Execute the p2 command of putting two of the same gem
   * in player's gem bank.
   * Output: None.
   */
void Game::p2(int gem_index, bool player1_turn){
    //If player 1's turn
    if(player1_turn){
        //Add two of the specified gem
        player_1->addGem(gem_index);
        player_1->addGem(gem_index);
    }
    //If player 2's turn
    else{
        //Add two of the specified gem
        player_2->addGem(gem_index);
        player_2->addGem(gem_index);
    }
    //Subtract two of the specified gem from the gem bank
    gem_bank[gem_index] = gem_bank[gem_index] - 2;
}

  /* Game::p3_allowed
   * Input: 3 gem strings.
   * Description: Determine if p3 is allowed with provided gems.
   * Output: Pointer to int array of indices of the gems, or
   * pointer to array with -1's if p3 is not allowed.
   */
int *Game::p3_allowed(string gem_1, string gem_2, string gem_3){
    //Create array to hold indices, initialize with -1
    int *arr = new int[3];
    for(int i = 0; i < 3; i++){
        arr[i] = -1;
    }
    //Set array to hold indices of provided gems
    for(int i = 0; i < GEMS-1; i++){
        if(gem_1 == colors[i]){
            arr[0] = i;
        }
        if(gem_2 == colors[i]){
            arr[1] = i;
        }
        if(gem_3 == colors[i]){
            arr[2] = i;
        }
    }
    //Loop through arr to check that colors were entered correctly
    for(int i = 0; i < 3; i++){
        //If an inputted gem doesn't match any of the colors
        if(arr[i] == -1){
            cout << "Invalid move (invalid color) - enter a valid move: ";
            arr[0] = -1;
            return arr;
        }
    }
    //Loop through gem_bank to see if inputted gems are unavailable
    for(int i = 0; i < 3; i++){
        //If an inputted gem has 0 gems available in gem_bank
        if(gem_bank[arr[i]] < 1){
            cout << "Invalid move (unavailable gems) - enter a valid move: ";
            arr[0] = -1;
            return arr;
        }
    } 
    //Check for duplicate entries
    if(arr[0] == arr[1] || arr[1] == arr[2] || arr[0] == arr[2]){
        cout << "Invalid move (duplicate color) - enter a valid move: ";
        arr[0] = -1;
        return arr;
    }
    //Otherwise, return array with indices of the inputted gems
    return arr;
}

  /* Game::p3
   * Input: Pointer to array of indices of gems, bool of whether it's
   player 1's turn.
   * Description: Execute p3 command of allowing player to pick 3 gems.
   * Output: None.
   */
void Game::p3(int *p3_results, bool player1_turn)
{
    //If it's player 1's turn
    if(player1_turn){
        //Loop through array of provided gems
        for(int i = 0; i < 3; i++){
            //Subtract gem from gem_bank and add it to player_1
            gem_bank[p3_results[i]]--;
            player_1->addGem(p3_results[i]);
        }
    }
    //If it's player 2's turn
    else{
        //Loop through array of provided gems
        for(int i = 0; i < 3; i++){
            //Subtract gem from gem_bank and add it to player_2
            gem_bank[p3_results[i]]--;
            player_2->addGem(p3_results[i]);
        }
    }
}

  /* Game::r_allowed
   * Input: Strings to represent row and column, and bool of whether or not 
   it's player 1's turn.
   * Description: Determine if reserve is allowed with provided card.
   * Output: Pointer to the requested card, or nullptr if reserve is impossible
   */
Card *Game::r_allowed(string row_type, string col_num, bool player1_turn)
{
    //Check for a valid card type entry
    if(row_type != "v" && row_type != "t" && row_type != "m"){
        cout << "Invalid move (invalid card type) - enter a valid move: ";
        return nullptr;
    }
    //Check for a valid column entry
    if(col_num != "1" && col_num != "2" && col_num != "3" && col_num != "4"){
        cout << "Invalid move (invalid card column) - enter a valid move: ";
        return nullptr;
    }
    //Check to see if player's reserve is already full
    if((player1_turn && player_1->getReserve(0) != nullptr && 
    player_1->getReserve(1) != nullptr && player_1->getReserve(2) != nullptr)
    || (!player1_turn && player_2->getReserve(0) != nullptr && 
    player_2->getReserve(1) != nullptr && player_2->getReserve(2) != nullptr)){
        cout << "Invalid move (reserve is already full) - ";
        cout << "enter a valid move: ";
        return nullptr;
    }
    //Call helper functions to get a row and column int, and return the 
    //corresponding card
    int row_int = getCardType(row_type);
    int col_int =  getColInt(col_num);
    return grid[row_int][col_int];
}

  /* Game::replaceCard
   * Input: Pointer to a card.
   * Description: Removes a provided card from the grid, adds a new one,
   * and return the old one.
   * Output: Pointer to the old card that should be cleared from memory.
   */
Card *Game::replaceCard(Card *c)
{
    //create variables to hold card's row and column
    int r_row, r_col;
    //loop through grid to find card's row and column
    for(int i = 0; i < CARD_ROWS; i++){
        for(int j = 0; j < CARD_COLS; j++){
            if(grid[i][j] == c){
                r_row = i;
                r_col = j;
            }
        }
    }
    //create card pointer to hold the card we want to delete
    Card *to_delete = grid[r_row][r_col];
    //set old grid entry to a nullptr
    grid[r_row][r_col] = nullptr;
    //if row is zero, add a new Card from vendors
    if(r_row == 0){
        grid[r_row][r_col] = vendors.back();
        vendors.pop_back();
    }
    //if row is 1, ad a new Card from transport
    else if(r_row == 1){
        grid[r_row][r_col] = transport.back();
        transport.pop_back();
    }
    //if row is 2, add a new Card from mines
    else{
        grid[r_row][r_col] = mines.back();
        mines.pop_back();
    }
    //return the old card
    return to_delete;
}

  /* Game::reserve
   * Input: Pointer to a card, bool of whether or not it's player 1's turn.
   * Description: Execute reserve command of moving a card from the grid
   * into a player's reserve and adding a gold gem.
   * Output: None.
   */
void Game::reserve(Card *card_to_reserve, bool player1_turn)
{
    //if player 1's turn
    if(player1_turn){
        //Put provided card into player 1's reserve
        player_1->setReserve(card_to_reserve);
        //If a gold gem is available, add it to player 1's bank
        if(gem_bank[5] > 0){
            gem_bank[5]--;
            player_1->addGem(5);
        }
    }
    //if player 2's turn
    else{
        //put provided card into player 2's reserve
        player_2->setReserve(card_to_reserve);
        //if a gold gem is available, add it to player 2's bank
        if(gem_bank[5] > 0){
            gem_bank[5]--;
            player_2->addGem(5);
        }
    }
    //call replaceCard to remove the card from the grid
    replaceCard(card_to_reserve);
}

  /* Game::br_allowed
   * Input: Index of card in reserve, bool of whether it's player 1's turn.
   * Description: Determine if br command is allowed and return a pointer
   * to the requested card.
   * Output: Pointer to card in reserve.
   */
 Card *Game::br_allowed(string index, bool player1_turn)
 {
    //Check that the inputted index is valid
    int index_int;
    if(index != "1" && index != "2" && index != "3"){
        cout << "Invalid move (no card at that index) - enter a valid move: ";
        return nullptr;
    }
    //Convert inputted string to integer
    index_int = stoi(index) - 1;
    //If player 1's turn
    if(player1_turn){
        //Check if there's no card at provided index
        if(player_1->getReserve(index_int) == nullptr){
            cout << "Invalid move (no card at that index) - enter a valid move: ";
            return nullptr;
        }
        //Check if player can afford the requested card
        else if(!enough_gems(player_1->getReserve(index_int), player1_turn)){
            cout << "Invalid move (cannot afford card) - enter a valid move: ";
            return nullptr;
        }
        //Otherwise, return a pointer to the requested card
        else{
            return player_1->getReserve(index_int);
        }
    }
    //If player 2's turn
    if(!player1_turn){
        //Check if there's no card at provided index
        if(player_2->getReserve(index_int) == nullptr){
            cout << "Invalid move (no card at that index) - enter a valid move: ";
            return nullptr;
        }
        //Check if player can afford the requested card
        else if(!enough_gems(player_2->getReserve(index_int), player1_turn)){
            cout << "Invalid move (cannot afford card) - enter a valid move: ";
            return nullptr;
        }
        //Otherwise, return a pointer to the requested card
        else{
            return player_2->getReserve(index_int);
        }
    }
    return nullptr;
 }

  /* Game::goldGemsRequired
   * Input: Pointer to a card, bool of whether it's player 1's turn
   * Description: Determine how many gold gems are required to purchase a 
   * provided card.
   * Output: Int of how many gold gems are required.
   */
int Game::goldGemsRequired(Card *c, bool player1_turn)
{
    //Create variable to hold required gold gems
    int gold_gems = 0;
    //If player 1's turn
    if(player1_turn){
        //Loop through gems
        for(int i = 0; i < GEMS - 1; i++){
            //Check if player 1 doesn't have enough gems and discounts
            //to buy the card without gold gems
            if(player_1->getGemCount(i) < 
            (c->getPrice(i) - player_1->getDiscount(i))){
                //If player 1 doesn't have enough, increment gold_gems 
                //accordingly.
                gold_gems += (c->getPrice(i) - (player_1->getGemCount(i) 
                + player_1->getDiscount(i)));
            }      
        }
    }
    //if player 2's turn
    else{
        //Loop through gems
        for(int i = 0; i < GEMS - 1; i++){
            //Check if player 2 doesn't have enough gems and discounts
            //to buy the card without gold gems
            if(player_2->getGemCount(i) < 
            (c->getPrice(i) - player_2->getDiscount(i))){
                //If player 2 doesn't have enough, increment gold_gems 
                //accordingly.
                gold_gems += (c->getPrice(i) - (player_2->getGemCount(i) 
                + player_2->getDiscount(i)));
            }      
        } 
    }
    //Return total number of gems
    return gold_gems;
}

  /* Game::enough_gems
   * Input: Pointer to a card, bool of whether it's player 1's turn
   * Description: Determine if provided player has enough gems to 
   * purchase a provided card.
   * Output: Bool of whether or not the purchase is possible.
   */
bool Game::enough_gems(Card *c, bool player1_turn)
  {
    //Get total number of gold gems required
    int missing_gems = goldGemsRequired(c, player1_turn);
    //If player 1's turn
    if(player1_turn){
        //If player 1 has enough gold gems to account for the missing
        //ones, return true
        if(player_1->getGemCount(5) >= missing_gems){
            return true;
        }
        //Otherwise, return false
        else{
            return false;
        }
    }
    //If player 2's turn
    else{
        //If player 2 has enough gold gems to account for the missing
        //ones, return true
        if(player_2->getGemCount(5) >= missing_gems){
            return true;
        }
        //Otherwise, return false
        else{
            return false;
        }
    }
  }

  /* Game::makePurchase
   * Input: Pointer to a card, bool of whether it's player 1's turn
   * Description: Transfer gems from a player's gems to the gem bank
   * and give player corresponding discount and prestige points
   * Output: None
   */
void Game::makePurchase(Card *c, bool player1_turn)
  {
    //Create variable to hold the card's discount color
    string discount_color = c->getGemColor();
    int discount_index = -1;
    //Loop through gems to get the index associated with discount color string
    for(int i = 0; i < GEMS - 1; i++){
        if(discount_color == colors[i]){
            discount_index = i;
        }
    }
    //If player 1's turn
    if(player1_turn){
        //loop through gems
        for(int i = 0; i < GEMS - 1; i++){
            //determine how many gold gems are required for a specific color
            int goldGemsNeeded = (c->getPrice(i) - (player_1->getGemCount(i) 
            + player_1->getDiscount(i)));
            //ensure goldGemsNeeded is positive
            if(goldGemsNeeded < 0){
                goldGemsNeeded = 0;
            }
            //determine how many gems should be removed from player's gems
            int gemsToRemove = c->getPrice(i) - 
            ((player_1->getDiscount(i)) + goldGemsNeeded);
            if(gemsToRemove < 0){
                gemsToRemove = 0;
            }
            //remove gems and replace them in the bank
            player_1->removeGems(5, goldGemsNeeded);
            player_1->removeGems(i, gemsToRemove);
            gem_bank[5] = gem_bank[5] + goldGemsNeeded;
            gem_bank[i] = gem_bank[i] + gemsToRemove;
        }
        //add prestige and discount, if available
        player_1->addPrestige(c->getPrestige());
        if(discount_index > -1){
            player_1->setDiscount(discount_index);
        }
        
    }
    //if player 2's turn
    else{
        for(int i = 0; i < GEMS - 1; i++){
            //determine how many gold gems are required for a specific color
            int goldGemsNeeded = (c->getPrice(i) - (player_2->getGemCount(i) 
            + player_2->getDiscount(i)));
            //ensure goldGemsNeeded is positive
            if(goldGemsNeeded < 0){
                goldGemsNeeded = 0;
            }
            //determine how many gems should be removed from player's gems
            int gemsToRemove = c->getPrice(i) - 
            ((player_2->getDiscount(i)) + goldGemsNeeded);
            if(gemsToRemove < 0){
                gemsToRemove = 0;
            }
            //remove gems and replace them in the bank
            player_2->removeGems(5, goldGemsNeeded);
            player_2->removeGems(i, gemsToRemove);
            gem_bank[5] = gem_bank[5] + goldGemsNeeded;
            gem_bank[i] = gem_bank[i] + gemsToRemove;
        }
        //add prestige and discount, if available
        player_2->addPrestige(c->getPrestige());
        if(discount_index > -1){
            player_2->setDiscount(discount_index);
        }
    }
  }

  /* Game::br
   * Input: Pointer to a card, bool of whether it's player 1's turn
   * Description: Execute br command of letting player purchase a card
   * in their reserve pile
   * Output: None
   */
void Game::br(Card *card_br, bool player1_turn)
  {
    //Call makePurchase function
    makePurchase(card_br, player1_turn);
    
    int index_reserve;
    //if player 1's turn
    if(player1_turn){
        //Get the index of the reserved card by looping through reserved cards
        for(int i = 0; i < 3; i++){
            if(card_br == player_1->getReserve(i)){
                index_reserve = i;
            }
        }
        //call deleteReserve function on index of reserved card
        player_1->deleteReserve(index_reserve);
    }
    //if player 2's turn
    else{
        //Get the index of the reserved card by looping through reserved cards
        for(int i = 0; i < 3; i++){
            if(card_br == player_2->getReserve(i)){
                index_reserve = i;
            }
        }
        //call deleteReserve function on index of reserved card
        player_2->deleteReserve(index_reserve);
    }
    }

  /* Game::b_allowed
   * Input: Strings containing a row and column, and bool of whether 
   * it's player 1's turn
   * Description: Determine is buy command can be executed with provided input
   * Output: Card pointer of requested card, or nullptr if not allowed
   */
Card *Game::b_allowed(string row_type, string col_num, bool player1_turn)
{
    //Check for invalid card type
    if(row_type != "v" && row_type != "t" && row_type != "m"){
        cout << "Invalid move (invalid card type) - enter a valid move: ";
        return nullptr;
    }
    //Check for invalid card column
    if(col_num != "1" && col_num != "2" && col_num != "3" && col_num != "4"){
        cout << "Invalid move (invalid card column) - enter a valid move: ";
        return nullptr;
    }
    //Convert row_type and col_num to ints
    int row_int = getCardType(row_type);
    int col_int =  getColInt(col_num);
    //Check if player has enough gems to purchase card
    if(!enough_gems(grid[row_int][col_int], player1_turn)){
        cout << "Invalid move (cannot afford card) - enter a valid move: ";
        return nullptr;
    }
    //If possible, return pointer to the card that the player wants to purchase
    return grid[row_int][col_int];
}

  /* Game::b
   * Input: Pointer to a card, bool of whether it's player 1's turn
   * Description: Execute b command of letting player purchase a card
   * from the main grid
   * Output: None
   */
void Game::b(Card *c, bool player1_turn)
{
    //Call makePurchase on the provided card
    makePurchase(c, player1_turn);
    //Call replaceCard and delete the old (purchased) card from heap
    Card *to_delete = replaceCard(c);
    delete to_delete;
}

  /* Game::getCardType
   * Input: String of card type
   * Description: Convert string card type to a row int
   * Output: Int of the card's row
   */
int Game::getCardType(string row_type)
{
    //Create variable to hold card's row
    int row_int;
    //Check row_type for each of three possible rows it might belong to
    if(row_type == "v"){
        row_int = 0;
    }
    else if(row_type == "t"){
        row_int = 1;
    }
    else{
        row_int = 2;
    }
    //Return card's row
    return row_int;
}

  /* Game::getColInt
   * Input: String of card column
   * Description: Convert string card column to a column int
   * Output: Int of the card's column
   */
int Game::getColInt(string col_type)
{
    return stoi(col_type) - 1;
}





