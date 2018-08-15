#include "fileio.h"

void g_LoadFromSave(unsigned int* SaveDataArray)
{
	std::ifstream SaveFileData("../res/SaveData/saves.txt");
	if (SaveFileData.is_open())
	{
		int i = 0;
		for (std::string j; std::getline(SaveFileData, j);)
		{
			SaveDataArray[i] = std::stoi(j);
			i++;
		}
	}
}

void g_SaveToSave(unsigned int* SaveDataArray)
{
	std::ofstream SaveFileData("../res/SaveData/saves.txt");
	if (SaveFileData.is_open())
	{
		for (int i = 0; i < 9 ; i++)
		{
			SaveFileData << SaveDataArray[i] << '\n';
		}
		SaveFileData.close();
	}
	else throw (std::invalid_argument("cannot write to file."));
}