#ifndef PILE_H
#define PILE_H

#include <string>
#include "Stock.h"

using namespace std;

class Pile
{
private:
    string pile[20][7], pileSeenOnBoard[20][7]; // We have 7 columns and a column can be at most 19 cards => right-most column with 6 closed cards open cards is King and it can extend to 6 + 13 cards. I used 20 for array index bounds on checks

public:
    Pile(string *deck);
    string getPileStatus();
    bool openCard(int column);
    string getBottomCardOfColumn(int column);
    void removeBottomCardOfColumn(int column);
    bool moveCardFromWaste(Stock *stock, int column);
    bool moveCardBetweenColumns(int sourceColumn, int sourceIndex, int destinationColumn);
    void addCardToBottom(string card, int column);
};

#endif
