#include "Truck.h"
#include <iostream>

using namespace std;

// Default Constructor
Truck::Truck()
{
    this->number = 0;
}

// Constructor with specific number
Truck::Truck(int number)
{
    this->number = number;
}

// Set truck number
void Truck::setNumber(int number)
{
    this->number = number;
}

// Get truck name
string Truck::getName()
{
    return "T" + to_string(this->number);
}