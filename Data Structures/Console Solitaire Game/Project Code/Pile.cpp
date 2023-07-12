#include "Pile.h"

using namespace std;

Pile::Pile(string *deck)
{
    int i, j, deckCursor = 0;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 7; j++)
        {
            this->pile[i][j] = "   ";
            this->pileSeenOnBoard[i][j] = "   ";
        }
    }

    for (i = 0; i < 7; i++)
    {
        for (j = i; j < 7; j++)
        {
            this->pile[i][j] = deck[deckCursor];
            this->pileSeenOnBoard[i][j] = deck[deckCursor];
            deckCursor++;
        }
    }

    for (i = 0; i < 6; i++)
    {
        for (j = i + 1; j < 7; j++)
        {
            this->pileSeenOnBoard[i][j] = "@@@";
        }
    }
}

// method that returns pile status string
string Pile::getPileStatus()
{
    int i, j;
    string pileInfo = "", lineInfo = "";

    for (i = 0; i < 19; i++)
    {
        for (j = 0; j < 7; j++)
        {
            lineInfo += this->pileSeenOnBoard[i][j] + "   ";
        }
        if (lineInfo.compare("                                          ") == 0)
        {
            break;
        }
        pileInfo += lineInfo + "\n";
        lineInfo = "";
    }

    return pileInfo;
}

// method that checks the column and gets to the top card and opens it if the card is a closed one
bool Pile::openCard(int column)
{
    int i;
    string card;
    for (i = 0; i < 19; i++)
    {
        card = this->pileSeenOnBoard[i][column];
        if (card.compare("   ") == 0) // checking if the current card is a blank one if it is then the previous card is checked
        {
            if (i == 0)
            {
                return false;
            }
            card = this->pileSeenOnBoard[i - 1][column];
            i--;
            break;
        }
    }
    if (card.compare("@@@") == 0)
    {
        this->pileSeenOnBoard[i][column] = this->pile[i][column];
        return true;
    }
    else
    {
        return false;
    }
}

// Method that returns the bottom open card string of a column
string Pile::getBottomCardOfColumn(int column)
{
    int i;
    string card;
    for (i = 0; i < 19; i++)
    {
        card = this->pileSeenOnBoard[i][column];
        if (card.compare("   ") == 0)
        {
            if (i == 0)
            {
                return "   ";
            }
            card = this->pileSeenOnBoard[i - 1][column];
            return card;
        }
    }
    return "   ";
}

// Method that removes the bottom open card string of a column
void Pile::removeBottomCardOfColumn(int column)
{
    int i;
    string card;
    for (i = 0; i < 19; i++)
    {
        card = this->pileSeenOnBoard[i][column];
        if (card.compare("   ") == 0)
        {
            this->pileSeenOnBoard[i - 1][column] = "   ";
            this->pile[i - 1][column] = "   ";
            break;
        }
    }
}

// Method that remves a card from waste and add it to the specific column in the pile if it can be moved by rules
bool Pile::moveCardFromWaste(Stock *stock, int column)
{
    int i;
    string card, topWaste;

    topWaste = stock->getTopWaste();
    if (topWaste.compare("___") == 0)
    {
        return false;
    }
    else
    {
        for (i = 0; i < 19; i++)
        {
            card = this->pileSeenOnBoard[i][column];
            if (card.compare("   ") == 0)
            {
                if (i == 0) // checking if the column is empty
                {
                    if (stoi(topWaste.substr(1)) == 13) // if column is empty then the card must be King = 13
                    {
                        this->pileSeenOnBoard[i][column] = topWaste;
                        this->pile[i][column] = topWaste;
                        stock->removeTopWaste();
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    // Checking if the card from waste is 1 below from the bottom of the column
                    card = this->pileSeenOnBoard[i - 1][column];
                    if (stoi(topWaste.substr(1)) == stoi(card.substr(1)) - 1)
                    {
                        this->pileSeenOnBoard[i][column] = topWaste;
                        this->pile[i][column] = topWaste;
                        stock->removeTopWaste();
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

// Method that changes cards places between columns if it is ok by the rules
bool Pile::moveCardBetweenColumns(int sourceColumn, int sourceIndex, int destinationColumn)
{
    int i, j, k;
    string card;

    for (i = 0; i < 19; i++)
    {
        card = this->pileSeenOnBoard[i][sourceColumn];
        if (card.compare("   ") == 0)
        {
            if (i == 0 || (i - 1 - sourceIndex < 0) || (this->pileSeenOnBoard[i - 1 - sourceIndex][sourceColumn].compare("@@@") == 0)) // checking if the source column has an available top open card
            {
                return false;
            }
            i--;
            break;
        }
    }

    for (j = 0; j < 19; j++)
    {
        card = this->pileSeenOnBoard[j][destinationColumn];
        if (card.compare("   ") == 0)
        {
            if (j == 0) // checking if the destination is empty column
            {
                if (stoi(this->pileSeenOnBoard[i - sourceIndex][sourceColumn].substr(1)) == 13) // if empty column then the card must be King = 13
                {
                    for (k = 0; k <= sourceIndex; k++) // Using a loop if player is moving multiple cards in one move
                    {
                        this->pile[k + j][destinationColumn] = this->pile[i - sourceIndex + k][sourceColumn];
                        this->pileSeenOnBoard[k + j][destinationColumn] = this->pileSeenOnBoard[i - sourceIndex + k][sourceColumn];
                        this->pile[i - sourceIndex + k][sourceColumn] = "   ";
                        this->pileSeenOnBoard[i - sourceIndex + k][sourceColumn] = "   ";
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else // not empty column
            {
                card = this->pileSeenOnBoard[j - 1][destinationColumn];
                if  (card.compare("@@@") == 0) // checking if the top card is closed or open
                {
                    return false;
                }
                else if (stoi(card.substr(1)) == stoi(this->pileSeenOnBoard[i - sourceIndex][sourceColumn].substr(1)) + 1) // checking card rule
                {
                    for (k = 0; k <= sourceIndex; k++) // Using a loop if player is moving multiple cards in one move
                    {
                        this->pile[k + j][destinationColumn] = this->pile[i - sourceIndex + k][sourceColumn];
                        this->pileSeenOnBoard[k + j][destinationColumn] = this->pileSeenOnBoard[i - sourceIndex + k][sourceColumn];
                        this->pile[i - sourceIndex + k][sourceColumn] = "   ";
                        this->pileSeenOnBoard[i - sourceIndex + k][sourceColumn] = "   ";
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

// method that adds a new card to the bottom of the column
// checks are done before usage in Foundation class
void Pile::addCardToBottom(string newCard, int column)
{
    int i;
    string card;
    for (i = 0; i < 19; i++)
    {
        card = this->pileSeenOnBoard[i][column];
        if (card.compare("   ") == 0)
        {
            this->pileSeenOnBoard[i][column] = newCard;
            this->pile[i][column] = newCard;
        }
    }
}