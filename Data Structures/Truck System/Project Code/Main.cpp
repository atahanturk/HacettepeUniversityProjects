#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Destination.h"

using namespace std;

struct CargoTruck // Double linked-list struck
{
    Package *package; // Package or Truck if first
    CargoTruck *next; // Next cargo
    CargoTruck *prev; // Prev cargo
    bool chosen; // A flag to determine if the package is dropped of on middle city
};

vector<Destination> destinations; // Destinations vector to hold all city information

void createDestinations(string fileName) // Create cities method
{
    string name;
    ifstream destinationFile(fileName); // Input file stream

    while (destinationFile >> name) // Reading city names one by one
    {
        Destination destination = Destination(name); // Creating new city
        destinations.push_back(destination); // Adding city to the city vector
    }
}

void createPackages(string fileName) // Create packages based on cities
{
    int i;
    string name, city;
    ifstream packageFile(fileName);

    while (packageFile >> name >> city) // Reading package names and related city name one by one
    {
        name = name.substr(1); // Removing P from the package number to use as an integer
        for (i = 0; i < destinations.size(); i++) // Looping on all cities to find the correct one
        {
            if (destinations.at(i).getName().compare(city) == 0) // Check if the city is the correct one
            {
                destinations.at(i).addPackage(stoi(name)); // Add package to the city
                break; // Break the loop since we found the city
            }
        }
    }
}

void createTrucks(string fileName) // Create trucks based on cities
{
    int i;
    float f;
    string name, city;
    ifstream truckFile(fileName);

    while (truckFile >> name >> city >> f) // Reading truck names and related city name one by one
    {
        name = name.substr(1); // Removing T from the package number to use as an integer
        for (i = 0; i < destinations.size(); i++) // Looping on all cities to find the correct one
        {
            if (destinations.at(i).getName().compare(city) == 0) // Check if the city is the correct one
            {
                destinations.at(i).addTruck(stoi(name)); // Add truck to the city
                break; // Break the loop since we found the city
            }
        }
    }
}

void processMissions(string fileName)
{
    int i, j, firstLoad, middleLoad;
    string name, firstCity, middleCity, lastCity;
    ifstream missionFile(fileName);

    while (missionFile >> name) // Reading mission info line
    {
        firstCity = name.substr(0, name.find("-")); // Getting the first city name
        name = name.substr(name.find("-") + 1); // Removing first city name from the line
        middleCity = name.substr(0, name.find("-")); // Getting the middle city name
        name = name.substr(name.find("-") + 1); // Removing middle city name from the line
        lastCity = name.substr(0, name.find("-")); // Getting the last city name
        name = name.substr(name.find("-") + 1); // Removing last city name from the line
        firstLoad = stoi(name.substr(0, name.find("-"))); // Getting the first city package count to load
        name = name.substr(name.find("-") + 1); // Removing the count from the line
        middleLoad = stoi(name.substr(0, name.find("-"))); // Getting the middle city package count to load
        name = name.substr(name.find("-") + 1); // Removing the count from the line

        CargoTruck *head, *tail, *cargoTruck; // Creating a head, tail and cargotruck Double linked-lists
        head = new CargoTruck();
        tail = new CargoTruck();
        cargoTruck = new CargoTruck();
        Truck truck; // Truck from the first city
        for (i = 0; i < destinations.size(); i++) // Looping on all cities to find the first one
        {
            if (destinations.at(i).getName().compare(firstCity) == 0)
            {
                destinations.at(i).getTopTruck(truck); // Get the front truck from the city
                break; // Break the loop since we found the city
            }
        }
        cargoTruck->package = &truck; // Make the truck first node of the double linked-list
        cargoTruck->next = NULL; // Setting next and prev NULL since there is not any package yet
        cargoTruck->prev = NULL;

        head = cargoTruck; // Setting head and tail of the double linked-list
        tail = cargoTruck;

        for (i = 0; i < destinations.size(); i++) // Looping on all cities to find the first one
        {
            if (destinations.at(i).getName().compare(firstCity) == 0)
            {
                for (j = 0; j < firstLoad; j++) // Looping required count times to load packages to the truck
                {
                    Package *package; // Package
                    package = new Package();
                    destinations.at(i).getTopPackage(*package); // Getting the top package from the city
                    if (package->getName().compare("P0") == 0) // Checking if the package is present or not
                    {
                        break;
                    }
                    CargoTruck *cargoPackage; // Creating package Cargo
                    cargoPackage = new CargoTruck();
                    cargoPackage->package = package;
                    cargoPackage->prev = tail; // Setting prev to old tail
                    tail->next = cargoPackage; // Setting old tail's next to new package
                    tail = cargoPackage; // Setting new tail
                }
                break; // Break the loop since we found the city
            }
        }

        for (i = 0; i < destinations.size(); i++) // Looping on all cities to find the middle one
        {
            if (destinations.at(i).getName().compare(middleCity) == 0)
            {
                for (j = 0; j < middleLoad; j++) // Looping required count times to load packages to the truck
                {
                    Package *package; // Package
                    package = new Package();
                    destinations.at(i).getTopPackage(*package); // Getting the top package from the city
                    if (package->getName().compare("P0") == 0) // Checking if the package is present or not
                    {
                        break;
                    }
                    CargoTruck *cargoPackage; // Creating package Cargo
                    cargoPackage = new CargoTruck();
                    cargoPackage->package = package;
                    cargoPackage->prev = tail; // Setting prev to old tail
                    tail->next = cargoPackage; // Setting old tail's next to new package
                    tail = cargoPackage; // Setting new tail
                }
                break; // Break the loop since we found the city
            }
        }

        CargoTruck *cursor; // Creating a cursor node to loop through double linked-list
        cursor = new CargoTruck();
        int numberOfPackagesToDrop = count(name.begin(), name.end(), ',') + 1; // Getting the number of packages to drop off. It is equal to the number of "," + 1

        while (numberOfPackagesToDrop != 0) // Loop through drop off
        {
            j = 0;
            int index = stoi(name.substr(0, name.find(","))); // Getting the index of the package to drop off
            cursor = head->next; // Set the cursor to the first package which is index 0// Head is truck

            while (cursor->package != NULL) // Loop until cursor is tail and has no package
            {
                if (j == index) // If correct index then mark the chosen flag of node
                {
                    cursor->chosen = true;
                    for (i = 0; i < destinations.size(); i++)
                    {
                        if (destinations.at(i).getName().compare(middleCity) == 0) // Also found middle city 
                        {
                            destinations.at(i).addPackage(stoi(cursor->package->getName().substr(1))); // Drop off the package to the middle city
                            break;
                        }
                    }
                    break;
                }
                else
                {
                    cursor = cursor->next; // Move cursor to the next node
                    j++; // increase j
                }
            }
            if (numberOfPackagesToDrop == 1)
            {
                break; // If no packages left to drop break
            }
            name = name.substr(name.find(",") + 1); // Remove the dropped off package index
            numberOfPackagesToDrop = count(name.begin(), name.end(), ',') + 1; // Recalculate number of packages to drop off
        }

        cursor = head->next; // Set cursor to the first package
        while (cursor->next != NULL) // Loop until next node is null
        {
            if (cursor->chosen == true) // If flag is true remove node from double linked-list
            {
                cursor->prev->next = cursor->next;
                cursor->next->prev = cursor->prev;
            }
            cursor = cursor->next;
        }
        if (cursor->chosen == true) // Check last node if it has flag remove it too
        {
            cursor->prev->next = NULL;
        }

        // Final city drop off
        cursor = head;
        for (i = 0; i < destinations.size(); i++) // Looping on all cities to find the correct one
        {
            if (destinations.at(i).getName().compare(lastCity) == 0) // Check if the city is the correct one
            {
                while (cursor->next != NULL) // Drop off packages to the last city until truck double linked-list is empty
                {
                    destinations.at(i).addPackage(stoi(cursor->next->package->getName().substr(1)));
                    cursor = cursor->next;
                }
                destinations.at(i).addTruck(stoi(head->package->getName().substr(1))); // Finally add the truck to the final city garage queue
                break; // Break the loop since we found the city
            }
        }
    }
}

void writeOutput(string fileName)
{
    int i;
    ofstream outputs; // output stream
    outputs.open(fileName); // open stream with output file
    for (i = 0; i < destinations.size(); i++) // Looping through cities to print the result
    {
        outputs << destinations.at(i).getName() + "\nPackages:\n"; // Printing city name and Packages: header
        while (true) // Looping through all packages if any in the city
        {
            Package *package;
            package = new Package();
            destinations.at(i).getTopPackage(*package); // Getting the top package info
            if (package->getName().compare("P0") == 0)
            {
                break; // Break the loop if the package name is P0 that means we did not get a package and the stack is empty
            }
            outputs << package->getName() + "\n"; // Printing each package name
        }
        outputs << "Trucks:\n"; // Printing Trucks header
        while (true) // Looping through all trucks if any in the city
        {
            Truck *truck;
            truck = new Truck();
            destinations.at(i).getTopTruck(*truck); // Getting the front truck info
            if (truck->getName().compare("T0") == 0)
            {
                break; // Break the loop if the truck name is T0 that means we did not get a package and the stack is empty
            }
            outputs << truck->getName() + "\n"; // Printing each truck name
        }
        outputs << "-------------\n"; // Printing seperator
    }
    outputs.close(); // Closing output stream
}

int main(int argc, char *argv[])
{
    string destinationFile, packagesFile, trucksFile, missionsFile, resultFile;

    if (argc < 6) // Checking if there are 5 file paths are present
    {
        cout << "Program needs 5 files." << endl;
        return 0;
    }

    // Getting paths from args
    destinationFile = argv[1];
    packagesFile = argv[2];
    trucksFile = argv[3];
    missionsFile = argv[4];
    resultFile = argv[5];

    createDestinations(destinationFile); // Create cities
    createPackages(packagesFile); // Create packages based on cities
    createTrucks(trucksFile); // Create trucks base on cities
    processMissions(missionsFile); // Run the missions creting a double linked-list
    writeOutput(resultFile); // Write the result to the output file

    return 0;
}
