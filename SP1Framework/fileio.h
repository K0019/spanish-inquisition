#pragma once

#ifndef _FILEIO_H
#define _FILEIO_H
#include <fstream>
#include <string>
#include "player.h"
// Loads from the player's save in res/SaveData/saves.SAVE
void g_LoadFromSave(unsigned int* SaveDataArray);
// Saves to player's save in res/SaveData/saves.SAVE
void g_SaveToSave(unsigned int* SaveDataArray);

// Loads from Floor data of index in res/MapData/FloorData/***/Floor<index>.txt
void g_LoadFromFloor(short FloorNumber, std::vector<std::string> *selectionAvailable);
void g_LoadFromFloorItem(short FloorNumber, std::vector<std::string> * selectionAvailable);
// Loads from room data of index in red/MapData/RoomData/***/<index>.txt
void g_LoadFromRoom(std::string *RoomNumber, char (*Level)[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2], COORD gridCoords);
void g_LoadFromItemRoom(std::string *RoomNumber, char(*Level)[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2], COORD gridCoords);

void g_LoadOptions(unsigned short* OptionsDataArray);
void g_SaveOptions(unsigned short* OptionsDataArray);
struct DataStorage
{
	unsigned int g_iSaveData[9];
	unsigned short g_shOptionsData[9];
};
#endif