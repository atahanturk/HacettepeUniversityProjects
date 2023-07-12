#include<string>
#include<fstream>
#include "LibrarySystem.h"
using namespace std;

LibrarySystem::LibrarySystem()
{
	userList = new User;
	userList->next = userList->prev = userList;
	movieList = new Movie;
	movieList->next = movieList->prev = movieList;
	movieLength = 0;
	userLength = 0;
}

LibrarySystem:: ~LibrarySystem()
{
	delete userList;
	delete movieList;
	out.close();
}

bool LibrarySystem::setOutputFile(const string file)
{
	out.open(file);
	if (!out.is_open())
		return false;
	return true;
}

void LibrarySystem::closeOutputFile()
{
	out.close();
}

User* LibrarySystem::createUser(const int userID, const string userName)
{
	User* u = new User;
	u->id = userID;
	u->name = userName;
	u->movieList = NULL;
	u->next = u;
	u->prev = u;
	return u;
}

Movie* LibrarySystem::createMovie(const int movieID, const string movieTitle, const int year)
{
	Movie* m = new Movie;
	m->id = movieID;
	m->name = movieTitle;
	m->year = year;
	m->next = m;
	m->prev = m; 
	return m;
}

bool LibrarySystem::checkMovie(const int movieID, Movie* mList)
{
	Movie* itr = mList;
	do
	{
		if (itr->id == movieID)
			return true;
		itr = itr->next;
	} while (itr != mList); // iterate until reaching out head  

	return false; 
}


bool LibrarySystem::checkUser(const int userID)
{
	if (userLength == 0)
		return false; 
	User* itr = userList;
	do
	{
		if (itr->id == userID)
			return true;
		itr = itr->next;
	} while (itr->id != userList->id); // iterate until reaching out head  

	return false;
}

User* LibrarySystem::findUser(const int movieID)
{
	if (userLength == 0)
		return NULL;
	User* itr = userList;
	do
	{
		if (itr->movieList != NULL)
		{
			if (checkMovie(movieID, itr->movieList))
				return itr;
		}

		itr = itr->next;
	} while (itr != userList); // iterate for all users 

	return NULL; 
}

void LibrarySystem::addMovie(const int movieID, const string movieTitle, const int year)
{
	// print out an error if the movie is already in the list 
	if (checkMovie(movieID, movieList))
	{
		out << "Movie " << movieID << " already exists\n";
		return; 
	}

	Movie* m = createMovie(movieID, movieTitle, year);
	if (movieLength != 0) // update if this is not the first node (otherwise it is already self-linked by definition)
	{
		m->next = movieList;
		m->prev = movieList->prev;
		movieList->prev->next = m;
		movieList->prev = m;
	}
	movieList = m;
	movieLength++;
	out << "Movie " << movieID << " has been added\n";
}

void LibrarySystem::deleteMovie(const int movieID)
{
	if (!checkMovie(movieID, movieList))
	{
		User* u = findUser(movieID); // check if movie is checked out by an user.
		if (u == NULL) // if not raise error 
		{
			out << "Movie " << movieID << " does not exist\n";
			return;
		}

		// delete the movie from the user's list 
		Movie* itr = u->movieList;
		while (itr->id != movieID) // find the movie in their list of movies
			itr = itr->next;
		if (itr->next == itr) // if there is only one movie in the list 
			u->movieList = NULL;
		else
		{
			itr->prev->next = itr->next;
			itr->next->prev = itr->prev;
		}
		delete itr;
		out << "Movie " << movieID << " has been checked out\n";
	}

	else
	{
		out << "Movie " << movieID << " has not been checked out\n";
		// delete from the list of not checked out movies 
		Movie* itr = movieList;
		while (itr->id != movieID)
			itr = itr->next;
		if (itr->next == itr) // deleting last movie in the movieList 
		{
			Movie* m = new Movie;
			m->id = -654321; 
			/* for some reason compiling with g++ or VS gives different outputs. This is ugly but if it works it ain't stupid. */
			m->next = m->prev = m;
			movieList = m; 
		}
		else
		{
			itr->prev->next = itr->next;
			itr->next->prev = itr->prev;
			if(movieList == itr)
				movieList = itr->next;
		}
		delete itr;
		movieLength--;
	}

	out << "Movie " << movieID << " has been deleted\n";
}

void LibrarySystem::addUser(const int userID, const string userName)
{
	// print out an error if the movie is already in the list 
	if (checkUser(userID))
	{
		out << "User " << userID << " already exists\n";
		return;
	}

	User* u = createUser(userID, userName); 
	// add user at the beginning of userList 

	if (userLength != 0) // update if this is not the first node (otherwise it is already self-linked by definition
	{
		u->next = userList;
		u->prev = userList->prev;
		userList->prev->next = u;
		userList->prev = u;
	}
	userList = u;
	userLength++;
	out << "User " << userID << " has been added\n";

}
	
void LibrarySystem::deleteUser(const int userID)
{
	if (!checkUser(userID))
	{
		out << "User " << userID << " does not exist\n";
		return;
	}

	User* u = userList;
	while (u->id != userID)
		u = u->next;

	if (u->next == u) // deleting last user in the userList 
	{
		User* u = new User;
		u->next = u->prev = u;
		userList = u;
	}
	else
	{
		u->prev->next = u->next;
		u->next->prev = u->prev;
		userList = u->next;
	}
	delete u;
	userLength--;
	out << "User " << userID << " has been deleted\n";

}

void LibrarySystem::checkoutMovie(const int movieID, const int userID)
{
	if (!checkUser(userID)) //check if user exist
	{
		out << "User " << userID << " does not exist for checkout\n";
		return;
	}
	if (!checkMovie(movieID, movieList))// check if movie is in the list of available movies  
	{
		out << "Movie " << movieID << " does not exist for checkout\n";
		return;
	}

	// give the movie to the user
	User* u = findUser(movieID); // check if movie is taken
	u = userList;
	while (u->id != userID)
		u = u->next;
	Movie* m = movieList;
	//find and delete movie from the list of available movies 
	while (m->id != movieID)
		m = m->next;
	//unlink movie 
	m->prev->next = m->next;
	m->next->prev = m->prev;
	if (m == movieList)
		movieList = m->next;
	movieLength--;
	//add movie to the user's movieList
	if (u->movieList != NULL)
	{
		m->prev = u->movieList->prev;
		m->next = u->movieList;
		u->movieList->prev->next = m;
		u->movieList->prev = m;
	}
	else
		m->prev = m->next=m;

	u->movieList = m;

	out << "Movie " << movieID << " has been checked out by User " << userID << endl;

}

void LibrarySystem::returnMovie(const int movieID)
{	
	// check if it is checked out 
	User* u = findUser(movieID);
	if (u == NULL)
	{
		if (!checkMovie(movieID, movieList))
			// raise an error
		{
			out << "Movie " << movieID << " not exist in the library\n";
			return;
		}

		else
		{
			out << "Movie " << movieID << " has not been checked out\n";
			return; 
		}
			
	}
	// delete movie from user's movie list
	Movie* itr = u->movieList;
	while (itr->id != movieID)
		itr = itr->next;
	itr->next->prev = itr->prev;
	itr->prev->next = itr->next;

	// add movie to list of not checked out movies
	if (movieLength != 0)
	{
		itr->next = movieList;
		itr->prev = movieList->prev;
		movieList->prev->next = itr;
		movieList->prev = itr;
	}
	else
		itr->prev = itr->next = itr; 
	movieList = itr;
	movieLength++;

	out << "Movie " << movieID << " has been returned\n";
}

void LibrarySystem::showAllMovies()
{
	out << "Movie id - Movie name - Year - Status\n";
	Movie* itr = movieList;
	do
	{
		out << itr->id << " " << itr->name << " " << itr->year << " Not checked out\n";
		itr = itr->next;
	} while (itr != movieList);

	User* u = userList;
	do
	{
		itr = u->movieList;
		if (itr == NULL)
		{
		}
		else
		{
			do
			{
				out << itr->id << " " << itr->name << " " << itr->year << " Checked out by User " << u->id << "\n";
				itr = itr->next;
			} while (itr != u->movieList);
		} 
		u = u->next;
	} while (u != userList);
}

void LibrarySystem::showMovie(const int movieID)
{
	User* u = findUser(movieID);
	if (u != NULL) // if movie is checked out
	{
		Movie* m = u->movieList;
		while (m->id != movieID)
			m = m->next;
		out << m->id << " " << m->name << " " << m->year << " Checked out by User " << u->id << "\n";
	}
	else if (checkMovie(movieID, movieList)) // if movie is not checked out but in the list 
	{
		Movie* m = movieList;
		while (m->id != movieID)
			m = m->next;
		out << m->id << " " << m->name << " " << m->year << " Not checked out\n";
	}
	else
		out << "Movie with the id " << movieID << " does not exist\n";

}

void LibrarySystem::showUser(const int userID)
{
	if (!checkUser(userID))
	{
		out << "User " << userID << " does not exist\n";
		return;
	}
	User* u = userList;
	while (u->id != userID)
		u = u->next;
	out << "User id: " << u->id << " User name: " << u->name << endl;
	out << "User " << u->id << " checked out the following movies: \n"; 
	Movie* m = u->movieList;
	if (m != NULL)
	{
		out << "Movie id - Movie name - Year\n";
		do
		{
			out << m->id << " " << m->name << " " << m->year << "\n";
			m = m->next;
		} while (m != u->movieList);
	}
}

void LibrarySystem::print(const string s)
{
	out << s;
}