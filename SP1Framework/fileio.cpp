#include "fileio.h"

void g_LoadFromSave(unsigned int* SaveDataArray)
{
	std::ifstream SaveFileData("../res/SaveData/saves.SAVE");
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
	std::ofstream SaveFileData("../res/SaveData/saves.SAVE");
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

void g_LoadFromFloor(short FloorNumber, std::vector<std::string> *currRoomIndex)
{
	std::string FloorSelector = "../res/MapData/FloorData/Floor" + std::to_string(FloorNumber) + ".txt";
	std::ifstream FloorFileData(FloorSelector);
	if (FloorFileData.is_open())
	{
		for (std::string j; std::getline(FloorFileData, j);)
		{
			currRoomIndex->push_back(j);
		}
	}
}

void g_LoadFromRoom(std::string *RoomNumber, std::string *Level)
{
	std::string RoomSelector = "../res/MapData/RoomData/" + *RoomNumber +".txt";
	std::ifstream RoomFileData(RoomSelector);
	if (RoomFileData.is_open())
	{
		for (std::string j; std::getline(RoomFileData, j);)
		{
			// KENDRICK DO THINGS
		}
	}
}