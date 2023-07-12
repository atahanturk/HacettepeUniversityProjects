#ifndef STOCK_H
#define STOCK_H

#include <string>

using namespace std;

class Stock
{
private:
    int stockCount, wasteCount, currentStockIndex, currentWasteCount;
    string stock[24], waste[24], currentWaste[3]; // Since 28 cards are on the pile already 24 elements are enough for stock array

public:
    Stock(string *deck);
    string getStockStatus();
    void openFromStock();
    string getTopWaste();
    void removeTopWaste();
};

#endif
