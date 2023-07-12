#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

using namespace std;

class Package
{
private:
    int number; // Storing package number instead of name 

public:
    Package(); // Default constructor
    Package(int number); // Constructor with number
    void setNumber(int number); // Number set method 
    virtual string getName(); // Package name get method that returns string
};

#endif
