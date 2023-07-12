#include "Game.h"

using namespace std;

// Constructor
Game::Game(string deckFile, string commandsFile, string outputFile)
{
    this->deckFile = deckFile;
    this->commandsFile = commandsFile;
    this->outputFile = outputFile;
}

// Create deck method that reads deck file and creates a string array of cards
void Game::createDeck()
{
    int i = 51;
    string card;
    ifstream deckfile(this->deckFile);

    while (deckfile >> card && i >= 0)
    {
        this->deck[i] = card;
        i--;
    }
}

// Create new game method that creates stock(waste inside of stock), pile and foundation objects
void Game::createNewGame()
{
    this->foundation = new Foundation();
    this->pile = new Pile(this->deck);
    this->stock = new Stock(this->deck);
}

void Game::startGame()
{
    string command;
    ifstream commands(this->commandsFile); // commands input stream
    ofstream outputs; // output stream
    outputs.open(this->outputFile);

    for (string command; getline(commands, command);)
    {
        if (this->foundation->hasPlayerWon()) { // Checking if the player has won the game
            break;
        }

        // Writing the game status on output file
        outputs << "\n" + this->stock->getStockStatus() + this->foundation->getFoundationStatus() + "\n\n" + this->pile->getPileStatus() + "\n";
        if (command.substr(0, 4).compare("exit") == 0) // checking if the command is exit command
        {
            outputs << "\n****************************************\n\nGame Over!\n";
            break;
        }
        else if (command.length() >= 15 && command.substr(0, 15).compare("open from stock") == 0) // checking if the command is open from stock command
        {
            outputs << command + "\n\n****************************************\n\n";
            this->stock->openFromStock();
        }
        else if (command.substr(0, 4).compare("open") == 0) // checking if the command is open <pile_num> command
        {
            if (this->pile->openCard(stoi(command.substr(5))))
            {
                outputs << command + "\n\n****************************************\n\n";
            }
            else
            {
                outputs << command + "\n\nInvalid Move!\n\n****************************************\n";
            }
        }
        else if (command.length() >= 18 && command.substr(0, 18).compare("move to foundation") == 0) // checking if the command is move to foundation command
        {
            if (command.substr(19, 5).compare("waste") == 0) // checking if the command is move to foundation waste command
            {
                if (this->foundation->moveToFoundationFromWaste(this->stock))
                {
                    outputs << command + "\n\n****************************************\n\n";
                }
                else
                {
                    outputs << command + "\n\nInvalid Move!\n\n****************************************\n";
                }
            }
            else // checking if the command is move to foundation pile <pile_num> command
            {
                if (this->foundation->moveToFoundationFromPile(this->pile, stoi(command.substr(24))))
                {
                    outputs << command + "\n\n****************************************\n\n";
                }
                else
                {
                    outputs << command + "\n\nInvalid Move!\n\n****************************************\n";
                }
            }
        }
        else
        {
            if (command.length() >= 10 && command.substr(0, 10).compare("move waste") == 0) // checking if the command is move waste <destination_pile_num> command
            {
                if (this->pile->moveCardFromWaste(this->stock, stoi(command.substr(11))))
                {
                    outputs << command + "\n\n****************************************\n\n";
                }
                else
                {
                    outputs << command + "\n\nInvalid Move!\n\n****************************************\n";
                }
            }
            else if (command.length() >= 10 && command.substr(0, 10).compare("move pile ") == 0) // checking if the command is move pile <source_pile_num> <source_pile_card_index> <destination_pile_num> command
            {
                int sourceColumn, sourceIndex, destinationColumn;
                string commandIndexes = command.substr(10);

                if (commandIndexes.length() == 7) // checking if the middle number is single or double digit like 0 10 1, only the middle one can be double digits
                {
                    sourceColumn = stoi(commandIndexes.substr(0, 1));
                    sourceIndex = stoi(commandIndexes.substr(2, 2));
                    destinationColumn = stoi(commandIndexes.substr(5));
                }
                else
                {
                    sourceColumn = stoi(commandIndexes.substr(0, 1));
                    sourceIndex = stoi(commandIndexes.substr(2, 1));
                    destinationColumn = stoi(commandIndexes.substr(4));
                }

                if (this->pile->moveCardBetweenColumns(sourceColumn, sourceIndex, destinationColumn))
                {
                    outputs << command + "\n\n****************************************\n\n";
                }
                else
                {
                    outputs << command + "\n\nInvalid Move!\n\n****************************************\n";
                }
            }
            else // checking if the command is move foundation <source_foundation_num> <destination_pile_num> command
            {
                int foundationColumn, pileColumn;
                command = command.substr(16);

                foundationColumn = stoi(command.substr(0, 1));
                pileColumn = stoi(command.substr(2));

                if (this->foundation->moveToPileFromFoundation(this->pile, foundationColumn, pileColumn))
                {
                    outputs << command + "\n\n****************************************\n\n";
                }
                else
                {
                    outputs << command + "\n\nInvalid Move!\n\n****************************************\n";
                }
            }
        }
    }
    if (this->foundation->hasPlayerWon())
    {
        // Writing the game status on output file
        outputs << "\n" + this->stock->getStockStatus() + this->foundation->getFoundationStatus() + "\n\n" + this->pile->getPileStatus() + "\n";
        outputs << "\n****************************************\n\nYou Win!\n\nGame Over!\n";
    }

    outputs.close(); // closing stream
}
