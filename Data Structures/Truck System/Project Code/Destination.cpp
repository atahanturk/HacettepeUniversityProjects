#include "Destination.h"

using namespace std;

// Constructor with name
Destination::Destination(string name)
{
    this->name = name;
}

// Get city name method
string Destination::getName()
{
    return this->name;
}

// Add package to city package stack method
void Destination::addPackage(int packageNumber)
{
    Package package(packageNumber); // Creating a package with number
    this->packages.push(package); // Pushing into the stack
}

// Add truck to city garage queue method
void Destination::addTruck(int truckNumber)
{
    Truck truck(truckNumber); // Creating a truck with number
    this->trucks.enqueue(truck); // Enqueueing to the queue
}

// Get truck method that puts the first truck into reference and remove it
void Destination::getTopTruck(Truck &truck)
{
    this->trucks.getFront(truck); // Get the front of the queue
    this->trucks.dequeue(); // Remove the front
}

// Get package method that puts the top package into reference and remove it
void Destination::getTopPackage(Package &package)
{
    this->packages.getTop(package); // Get the top of the stack
    this->packages.pop(); // Remove the top
}
