#ifndef TRUCK_H
#define TRUCK_H

#include <string>
#include "Package.h"

using namespace std;

class Truck : public Package 
{
private:
    int number; // Storing truck number instead of name 

public:
    Truck(); // Default constructor
    Truck(int number); // Constructor with number
    void setNumber(int number); // Number set method 
    string getName(); // Truck name get method that returns string
};

#endif
