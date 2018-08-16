#pragma once

/* MADE BY: Yan Quan */

#ifndef _FILEIO_H
#define _FILEIO_H
#include <fstream>
#include <string>
#include "player.h"

void g_LoadFromSave(unsigned int* SaveDataArray);
void g_SaveToSave(unsigned int* SaveDataArray);
void g_LoadFromFloor(short FloorNumber, std::vector<std::string> *selectionAvailable);
void g_LoadFromRoom(std::string *RoomNumber, char (*Level)[(ROOM_X + 2) * GRID_X + 2][(ROOM_Y + 2) * GRID_Y + 2], COORD gridCoords);

struct SaveDataStorage
{
	unsigned int g_iSaveData[9];
	unsigned int g_iWriteData[9];
};
#endif