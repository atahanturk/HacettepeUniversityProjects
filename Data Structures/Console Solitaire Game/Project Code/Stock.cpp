#include "Stock.h"

using namespace std;

Stock::Stock(string *deck)
{
    int i;
    for (i = 0; i < 24; i++)
    {
        this->stock[i] = deck[i + 28];
        this->waste[i] = "___";
    }
    for (i = 0; i < 3; i++)
    {
        this->currentWaste[i] = "___";
    }
    this->stockCount = 24;
    this->wasteCount = 0;
    this->currentStockIndex = 0;
    this->currentWasteCount = 0;
}

// method that returns stock status string
string Stock::getStockStatus()
{
    string stockInfo, wasteInfo;
    if (this->stockCount == 0)
    {
        stockInfo = "___ ";
    }
    else
    {
        stockInfo = "@@@ ";
    }

    wasteInfo = this->currentWaste[0] + " " + this->currentWaste[1] + " " + this->currentWaste[2] + "         ";

    return stockInfo + wasteInfo;
}

// Method that checks the stock count and updating stock and waste data accordingly
void Stock::openFromStock()
{
    if (this->stockCount >= 3)
    {
        this->currentWasteCount = 3;
        this->currentWaste[0] = this->stock[this->currentStockIndex];
        this->currentWaste[1] = this->stock[this->currentStockIndex + 1];
        this->currentWaste[2] = this->stock[this->currentStockIndex + 2];
        this->waste[this->wasteCount] = this->stock[this->currentStockIndex];
        this->waste[this->wasteCount + 1] = this->stock[this->currentStockIndex + 1];
        this->waste[this->wasteCount + 2] = this->stock[this->currentStockIndex + 2];
        this->currentStockIndex += 3;
        this->wasteCount += 3;
        this->stockCount -= 3;
    }
    else if (this->stockCount == 2)
    {
        this->currentWasteCount = 2;
        this->currentWaste[0] = this->stock[this->currentStockIndex];
        this->currentWaste[1] = this->stock[this->currentStockIndex + 1];
        this->currentWaste[2] = "___";
        this->waste[this->wasteCount] = this->stock[this->currentStockIndex];
        this->waste[this->wasteCount + 1] = this->stock[this->currentStockIndex + 1];
        this->currentStockIndex += 2;
        this->wasteCount += 2;
        this->stockCount -= 2;
    }
    else if (this->stockCount == 1)
    {
        this->currentWasteCount = 1;
        this->currentWaste[0] = this->stock[this->currentStockIndex];
        this->currentWaste[1] = "___";
        this->currentWaste[2] = "___";
        this->waste[this->wasteCount] = this->stock[this->currentStockIndex];
        this->currentStockIndex += 1;
        this->wasteCount += 1;
        this->stockCount -= 1;
    }
    else if (this->stockCount == 0)
    {
        this->currentWasteCount = 0;
        this->currentWaste[0] = "___";
        this->currentWaste[1] = "___";
        this->currentWaste[2] = "___";
        this->currentStockIndex = 0;
        for (int i = 0; i < this->wasteCount; i++)
        {
            this->stock[i] = this->waste[i];
            this->waste[i] = "___";
        }
        this->stockCount = this->wasteCount;
        this->wasteCount = 0;
    }
}

// Method that returns the card info that is on the right-most available card on the waste
string Stock::getTopWaste()
{
    if (this->currentWasteCount == 1)
    {
        return this->currentWaste[0];
    }
    else if (this->currentWasteCount == 2)
    {
        return this->currentWaste[1];
    }
    else if (this->currentWasteCount == 3)
    {
        return this->currentWaste[2];
    }
    else
    {
        return "___";
    }
}

// Method that removes the right-most card from waste replacing it with ___
void Stock::removeTopWaste()
{
    this->currentWasteCount--;
    this->wasteCount--;
    if (this->currentWasteCount == 0)
    {
        if (this->wasteCount == 0)
        {
            this->currentWaste[0] = "___";
        }
        else
        {
            this->currentWaste[0] = this->waste[this->wasteCount - 1];
        }
    }
    else if (this->currentWasteCount == 1)
    {
        this->currentWaste[1] = "___";
    }
    else if (this->currentWasteCount == 2)
    {
        this->currentWaste[2] = "___";
    }
}
