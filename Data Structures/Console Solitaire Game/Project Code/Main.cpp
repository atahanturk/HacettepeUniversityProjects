#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char *argv[])
{
    string deckFile, commandsFile, outputFile;

    if (argc < 4) // Checking if there are 3 file paths are present
    {
        cout << "Program needs 3 input files." << endl;
    }

    // Getting paths from args
    deckFile = argv[1];
    commandsFile = argv[2];
    outputFile = argv[3];

    Game game(deckFile, commandsFile, outputFile); // creating game object with file paths
    game.createDeck(); // creating deck from deck file
    game.createNewGame(); // creating new game with creating stock, pile and foundation
    game.startGame(); // starting game that reads commands file and iterates over them

    return 0;
}
