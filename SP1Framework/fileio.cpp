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
	else throw (std::invalid_argument("Cannot write to file."));
}

void g_LoadFromFloor(short FloorNumber, std::vector<std::string> *selectionAvailable)
{
	std::string FloorSelector = "../res/MapData/FloorData/NormalRooms/Floor" + std::to_string(FloorNumber) + ".txt";
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
void g_LoadFromFloorItem(short FloorNumber, std::vector<std::string> * selectionAvailable)
{
	std::string FloorSelector = "../res/MapData/FloorData/ItemRooms/Floor" + std::to_string(FloorNumber) + ".txt";
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
	std::string RoomSelector = "../res/MapData/RoomData/NormalRooms/" + *RoomNumber +".txt";
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
void g_LoadFromItemRoom(std::string *RoomNumber, char(*Level)[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2], COORD gridCoords)
{
	std::string RoomSelector = "../res/MapData/RoomData/ItemRooms/" + *RoomNumber + ".txt";
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
	if (PlayerOptions.is_open())
	{
		int i = 0;
		for (std::string j; std::getline(PlayerOptions, j);)
		{
			OptionsDataArray[i] = std::stoi(j);
			i++;
		}
		PlayerOptions.close();
	}
	else
	{
		std::ofstream PlayerOptions("../res/SaveData/options.txt");
		if (PlayerOptions.is_open())
		{
			PlayerOptions << "0\n";
			PlayerOptions << "1\n";
		}
	}
}

void g_SaveOptions(unsigned short* OptionsDataArray)
{
	std::ofstream PlayerOptions("../res/SaveData/options.txt");
	if (PlayerOptions.is_open())
	{
		if (PlayerOptions.is_open())
		{
			for (int i = 0; i < 2; i++)
			{
				PlayerOptions << OptionsDataArray[i] << '\n';
			}
			PlayerOptions.close();
		}
	}
}