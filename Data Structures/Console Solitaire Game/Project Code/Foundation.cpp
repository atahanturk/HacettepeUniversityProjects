#include "Foundation.h"

using namespace std;

Foundation::Foundation()
{
    int i;
    for (i = 0; i < 13; i++)
    {
        this->hearts[i] = "";
        this->diamonds[i] = "";
        this->spades[i] = "";
        this->clubs[i] = "";
    }
    this->heartsCount = 0;
    this->diamondsCount = 0;
    this->spadesCount = 0;
    this->clubsCount = 0;
}

// method that returns foundation status string
string Foundation::getFoundationStatus()
{
    string foundationInfo = "";
    if (this->heartsCount == 0)
    {
        foundationInfo += "___ ";
    }
    else
    {
        foundationInfo += this->hearts[this->heartsCount - 1] + " ";
    }

    if (this->diamondsCount == 0)
    {
        foundationInfo += "___ ";
    }
    else
    {
        foundationInfo += this->diamonds[this->diamondsCount - 1] + " ";
    }

    if (this->spadesCount == 0)
    {
        foundationInfo += "___ ";
    }
    else
    {
        foundationInfo += this->spades[this->spadesCount - 1] + " ";
    }

    if (this->clubsCount == 0)
    {
        foundationInfo += "___ ";
    }
    else
    {
        foundationInfo += this->clubs[this->clubsCount - 1] + " ";
    }

    return foundationInfo;
}

// Method that move the right-most card from the waste into foundation
bool Foundation::moveToFoundationFromWaste(Stock *stock)
{
    string topWaste;

    topWaste = stock->getTopWaste(); // getting the right-most card from waste
    if (topWaste.compare("___") == 0)
    {
        return false;
    }
    else if (topWaste.substr(0, 1).compare("H") == 0) // checking which foundation the card belongs to
    {
        // checking if the foundation is empty, if empty then the card from waste must be Ace = 1
        // If foundation is not empty then the card from waste must be 1 higher from the top card of that foundation
        if ((this->heartsCount == 0 && stoi(topWaste.substr(1, 2)) == 1) || (this->heartsCount != 0 && stoi(topWaste.substr(1, 2)) == stoi(this->hearts[this->heartsCount - 1].substr(1, 2)) + 1))
        {
            stock->removeTopWaste();
            this->hearts[this->heartsCount] = topWaste;
            this->heartsCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (topWaste.substr(0, 1).compare("D") == 0)
    {
        if ((this->diamondsCount == 0 && stoi(topWaste.substr(1, 2)) == 1) || (this->diamondsCount != 0 && stoi(topWaste.substr(1, 2)) == stoi(this->diamonds[this->diamondsCount - 1].substr(1, 2)) + 1))
        {
            stock->removeTopWaste();
            this->diamonds[this->diamondsCount] = topWaste;
            this->diamondsCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (topWaste.substr(0, 1).compare("S") == 0)
    {
        if ((this->spadesCount == 0 && stoi(topWaste.substr(1, 2)) == 1) || (this->spadesCount != 0 && stoi(topWaste.substr(1, 2)) == stoi(this->spades[this->spadesCount - 1].substr(1, 2)) + 1))
        {
            stock->removeTopWaste();
            this->spades[this->spadesCount] = topWaste;
            this->spadesCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (topWaste.substr(0, 1).compare("C") == 0)
    {
        if ((this->clubsCount == 0 && stoi(topWaste.substr(1, 2)) == 1) || (this->clubsCount != 0 && stoi(topWaste.substr(1, 2)) == stoi(this->clubs[this->clubsCount - 1].substr(1, 2)) + 1))
        {
            stock->removeTopWaste();
            this->clubs[this->clubsCount] = topWaste;
            this->clubsCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// Method that moves the top open card from the pile into foundation using column
bool Foundation::moveToFoundationFromPile(Pile *pile, int column)
{
    string card = pile->getBottomCardOfColumn(column); // getting the top open card from pile
    if (card.compare("   ") == 0 || card.compare("@@@") == 0)
    {
        return false;
    }
    else if (card.substr(0, 1).compare("H") == 0) // checking which foundation the card belongs to
    {
        // checking if the foundation is empty, if empty then the card from waste must be Ace = 1
        // If foundation is not empty then the card from waste must be 1 higher from the top card of that foundation
        if ((this->heartsCount == 0 && stoi(card.substr(1, 2)) == 1) || (this->heartsCount != 0 && stoi(card.substr(1, 2)) == stoi(this->hearts[this->heartsCount - 1].substr(1, 2)) + 1))
        {
            pile->removeBottomCardOfColumn(column);
            this->hearts[this->heartsCount] = card;
            this->heartsCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (card.substr(0, 1).compare("D") == 0)
    {
        if ((this->diamondsCount == 0 && stoi(card.substr(1, 2)) == 1) || (this->diamondsCount != 0 && stoi(card.substr(1, 2)) == stoi(this->diamonds[this->diamondsCount - 1].substr(1, 2)) + 1))
        {
            pile->removeBottomCardOfColumn(column);
            this->diamonds[this->diamondsCount] = card;
            this->diamondsCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (card.substr(0, 1).compare("S") == 0)
    {
        if ((this->spadesCount == 0 && stoi(card.substr(1, 2)) == 1) || (this->spadesCount != 0 && stoi(card.substr(1, 2)) == stoi(this->spades[this->spadesCount - 1].substr(1, 2)) + 1))
        {
            pile->removeBottomCardOfColumn(column);
            this->spades[this->spadesCount] = card;
            this->spadesCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (card.substr(0, 1).compare("C") == 0)
    {
        if ((this->clubsCount == 0 && stoi(card.substr(1, 2)) == 1) || (this->clubsCount != 0 && stoi(card.substr(1, 2)) == stoi(this->clubs[this->clubsCount - 1].substr(1, 2)) + 1))
        {
            pile->removeBottomCardOfColumn(column);
            this->clubs[this->clubsCount] = card;
            this->clubsCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// Method that moves a card from a foundation into a pile for tactical play
bool Foundation::moveToPileFromFoundation(Pile *pile, int foundationColumn, int pileColumn)
{
    string card = pile->getBottomCardOfColumn(pileColumn); // getting the top open card from pile
    if (card.compare("@@@") == 0)
    {
        return false;
    }
    // Moving a foundation card into an empty pile column
    else if (card.compare("   ") == 0)
    {
        // checking if the foundation is empty, if empty then there is no card to move
        // If foundation is not empty then the card from the top of the foundation is checked if it is suitable for the column
        if (foundationColumn == 0 && this->heartsCount > 0 && stoi(this->hearts[this->heartsCount - 1].substr(1, 2)) == 13)
        {
            this->heartsCount--;
            pile->addCardToBottom(this->hearts[this->heartsCount], pileColumn);
            this->hearts[this->heartsCount] = "";
            return true;
        }
        else if (foundationColumn == 0 && this->diamondsCount > 0 && stoi(this->diamonds[this->diamondsCount - 1].substr(1, 2)) == 13)
        {
            this->diamondsCount--;
            pile->addCardToBottom(this->diamonds[this->diamondsCount], pileColumn);
            this->diamonds[this->diamondsCount] = "";
            return true;
        }
        else if (foundationColumn == 0 && this->spadesCount > 0 && stoi(this->spades[this->spadesCount - 1].substr(1, 2)) == 13)
        {
            this->spadesCount--;
            pile->addCardToBottom(this->spades[this->spadesCount], pileColumn);
            this->spades[this->spadesCount] = "";
            return true;
        }
        else if (foundationColumn == 0 && this->clubsCount > 0 && stoi(this->clubs[this->clubsCount - 1].substr(1, 2)) == 13)
        {
            this->clubsCount--;
            pile->addCardToBottom(this->clubs[this->clubsCount], pileColumn);
            this->clubs[this->clubsCount] = "";
            return true;
        }
        else
        {
            return false;
        }
    }
    // From here on the pile column is not empty
    else if (foundationColumn == 0)
    {
        // checking if the foundation is empty, if empty then there is no card to move
        // If foundation is not empty then the card from the top of the foundation is checked if it is suitable for the column
        if (this->heartsCount > 0 && stoi(this->hearts[this->heartsCount - 1].substr(1, 2)) == stoi(card.substr(1)) - 1)
        {
            this->heartsCount--;
            pile->addCardToBottom(this->hearts[this->heartsCount], pileColumn);
            this->hearts[this->heartsCount] = "";
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (foundationColumn == 1)
    {
        if (this->diamondsCount > 0 && stoi(this->diamonds[this->diamondsCount - 1].substr(1, 2)) == stoi(card.substr(1)) - 1)
        {
            this->diamondsCount--;
            pile->addCardToBottom(this->diamonds[this->diamondsCount], pileColumn);
            this->diamonds[this->diamondsCount] = "";
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (foundationColumn == 2)
    {
        if (this->spadesCount > 0 && stoi(this->spades[this->spadesCount - 1].substr(1, 2)) == stoi(card.substr(1)) - 1)
        {
            this->spadesCount--;
            pile->addCardToBottom(this->spades[this->spadesCount], pileColumn);
            this->spades[this->spadesCount] = "";
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (foundationColumn == 3)
    {
        if (this->clubsCount > 0 && stoi(this->clubs[this->clubsCount - 1].substr(1, 2)) == stoi(card.substr(1)) - 1)
        {
            this->clubsCount--;
            pile->addCardToBottom(this->clubs[this->clubsCount], pileColumn);
            this->clubs[this->clubsCount] = "";
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// Method that checks if the game has been won using the number of cards on the foundation
bool Foundation::hasPlayerWon()
{
    return this->heartsCount == 13 && this->diamondsCount == 13 && this->spadesCount == 13 && this->clubsCount == 13;
}
