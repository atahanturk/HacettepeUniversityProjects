#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>
#include "Stack.h"
#include "Queue.h"
#include "Package.h"
#include "Truck.h"

using namespace std;

class Destination
{
private:
    string name; // City name
    Stack<Package> packages; // Packages in that city as Stack
    Queue<Truck> trucks; // Trucks in that city as Queue

public:
    Destination(string name); // Constructor with name
    string getName(); // Get city name method
    void addPackage(int packageNumber); // Add package to city package stack method
    void addTruck(int truckNumber); // Add truck to city garage queue method
    void getTopTruck(Truck &truck); // Get truck method that puts the first truck into reference and remove it
    void getTopPackage(Package &package); // Get package method that puts the top package into reference and remove it
};

#endif
