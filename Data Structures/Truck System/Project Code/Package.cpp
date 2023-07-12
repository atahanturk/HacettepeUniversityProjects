#include "Package.h"

using namespace std;

// Default Constructor
Package::Package()
{
    this->number = 0;
}

// Constructor with specific number
Package::Package(int number)
{
    this->number = number;
}

// Set package number
void Package::setNumber(int number)
{
    this->number = number;
}

// Get package name
string Package::getName()
{
    return "P" + to_string(this->number);
}