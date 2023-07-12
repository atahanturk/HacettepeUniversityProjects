#pragma once
#include <iostream>
#include<fstream>
using namespace std;

struct Movie
{
	string name;
	int id;
	int year;

	Movie* prev;
	Movie* next;
};


struct User
{
	string name;
	int id;
	Movie* movieList; // head of the movie list, chceked out by that specific user 

	User* prev;
	User* next;
};

class LibrarySystem
{
public: 
	LibrarySystem();
	~LibrarySystem();

	void addMovie(const int movieID, const string movieTitle, const int year);
	void deleteMovie(const int movieID);

	void addUser(const int userID, const string userName);
	void deleteUser(const int userID);

	void checkoutMovie(const int movieID, const int userID);
	void returnMovie(const int movieID);

	void showAllMovies();
	void showMovie(const int movieID);
	void showUser(const int userID);

	bool setOutputFile(const string file); // initialize output file 
	void closeOutputFile(); 
	void print(const string s); //write a given string into the output file 

private:
	User* userList; // head of the user list
	Movie* movieList; // head of the movie list for movies that are not checked out yet
	User* createUser(const int userID, const string userName);
	Movie* createMovie(const int movieID, const string movieTitle, const int year);
	bool checkMovie(const int movieID, Movie* mList); // true if the movie is in mList;
	bool checkUser(const int userID); // true if the user is already in userList
	User* findUser(const int movieID); // returns to the user's pointer who checked out that movie 
	ofstream out;
	int movieLength;
	int userLength;
};

