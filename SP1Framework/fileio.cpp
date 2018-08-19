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
		SaveFileData.close();
	}
	else
	{
		std::ofstream SaveFileData("../res/SaveData/saves.txt");
		if (SaveFileData.is_open())
		{
			for (int i = 0; i < 9; i++)
			{
				SaveFileData << 0 << '\n';
			}
			SaveFileData.close();
		}
		g_LoadFromSave(SaveDataArray);
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

void g_LoadFromFloor(short FloorNumber, std::vector<std::string> *selectionAvailable)
{
	std::string FloorSelector = "../res/MapData/FloorData/Floor" + std::to_string(FloorNumber) + ".txt";
	std::ifstream FloorFileData(FloorSelector);
	if (FloorFileData.is_open())
	{
		// Get the selection
		for (std::string j; std::getline(FloorFileData, j);)
		{
			selectionAvailable->push_back(j);
		}
		FloorFileData.close();
	}
}

void g_LoadFromRoom(std::string *RoomNumber, char (*Level)[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2], COORD gridCoords)
{
	std::string RoomSelector = "../res/MapData/RoomData/" + *RoomNumber +".txt";
	std::ifstream RoomFileData(RoomSelector);
	unsigned int row = 0;
	if (RoomFileData.is_open())
	{
		for (std::string line; std::getline(RoomFileData, line); row++)
		{
			for (unsigned int column = 0; column < line.length(); column++)
			{
				(*Level)[1 + gridCoords.X * (ROOM_X + 2) + row][1 + gridCoords.Y * (ROOM_Y + 2) + column] = line[column];
			}
		}
		RoomFileData.close();
	}
}

void g_LoadOptions(unsigned short* OptionsDataArray)
{
	std::ifstream PlayerOptions("../res/SaveData/options.txt");
}