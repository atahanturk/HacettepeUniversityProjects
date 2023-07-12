#include<fstream>
#include<string>
#include<sstream>
#include "LibrarySystem.h"
using namespace std;

bool isInt(string str) // return true if the input is numeric / false if the input is string
{
	for (unsigned int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Usage: filename_to_commands filename_to_output. Exiting!";
		return -1;
	}

	string inputFile = argv[1];
	string outFile = argv[2]; 

/*int main()
{
	string inputFile = "commands3.txt";
	string outFile = "output.txt";
	*/
	fstream inF;
	inF.open(inputFile.c_str());
	if (!inF.is_open())
	{
		cout << "Could not open command file. Exiting!";
		return -1;
	}

	
	// initialize
	LibrarySystem myLib;
	if (!myLib.setOutputFile(outFile))
	{
		cout << "Could not open output file. Exiting.";
		return -1;
	}

	string word, line, function, name, prev_func = "", title;
	int id, id2;
	myLib.print("===Movie Library System===\n");
	// read commands 
	while (getline(inF, line)) 
	{
		word = function = name = "";
		istringstream input(line);
		input >> function;
		if (function != prev_func)
		{
			title = "\n===" + function + "() method test===\n";
			myLib.print(title);
		}
		
		if (function == "addUser")
		{
			input >> id >> name;
			while (input >> word)
				name = name + " " + word;
			myLib.addUser(id, name);
		}

		else if (function == "addMovie")
		{
			input >> id >> name;
			while (input >> word && !isInt(word))
				name = name + " " + word;

			myLib.addMovie(id, name, stoi(word)); // just an ugly trick. last word is actually the year of the movie. 
		}

		else if (function == "showAllMovie")
		{
			myLib.showAllMovies();
		}

		else if (function == "checkoutMovie")
		{
			input >> id >> id2; 
			myLib.checkoutMovie(id, id2);
		}

		else if (function == "showMovie")
		{
			input >> id;
			myLib.showMovie(id);
		}

		else if (function == "showUser")
		{
			input >> id;
			myLib.showUser(id);
		}

		else if (function == "deleteMovie")
		{
			input >> id;
			myLib.deleteMovie(id);
		}
		
		else if (function == "returnMovie")
		{
			input >> id;
			myLib.returnMovie(id);
		}

		else if (function == "deleteUser")
		{
			input >> id;
			myLib.deleteUser(id);
		}
		prev_func = function;
	}

	myLib.closeOutputFile();
	return 0;
}