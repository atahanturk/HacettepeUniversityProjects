#ifndef FOUNDATION_H
#define FOUNDATION_H

#include <string>
#include "Stock.h"
#include "Pile.h"

using namespace std;

class Foundation
{
private:
    int heartsCount, diamondsCount, clubsCount, spadesCount;
    string hearts[13], diamonds[13], clubs[13], spades[13]; // every type has 13 cards

public:
    Foundation();
    string getFoundationStatus();
    bool moveToFoundationFromWaste(Stock *stock);
    bool moveToFoundationFromPile(Pile *pile, int column);
    bool moveToPileFromFoundation(Pile *pile, int foundationColumn, int pileColumn);
    bool hasPlayerWon();
};

#endif
