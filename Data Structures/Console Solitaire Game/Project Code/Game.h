#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <fstream>
#include "Foundation.h"
#include "Stock.h"
#include "Pile.h"

using namespace std;

class Game
{
private:
    string deckFile, commandsFile, outputFile, deck[52]; // deck can have maximum 52 cards
    Foundation *foundation;
    Stock *stock;
    Pile *pile;

public:
    Game(string deckFile, string commandsFile, string outputFile);
    void createDeck();
    void createNewGame();
    void startGame();
};

#endif
