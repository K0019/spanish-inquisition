#include "fileio.h"

//Reads from a file, as specified by fileName and will assign the read value to *variable
void load(std::string fileName, std::string *variable)
{
	std::ifstream currentfile;
	currentfile.open(fileName);
	if (currentfile.is_open())
	{
		while (std::getline(currentfile, *variable))
		{
			*variable;
		}
	}
}


//Write to a file, as specified by fileName and will write the *variable to it
void save(std::string fileName, std::string *variable)
{
	std::ofstream currentfile;
	currentfile.open(fileName);
	if (currentfile.is_open())
	{
		currentfile << *variable;
		currentfile.close();
	}
	else
	{
		throw std::invalid_argument("fileName cannot be loaded!");
	}
}