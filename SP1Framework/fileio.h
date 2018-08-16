#pragma once

/* MADE BY: Yan Quan */

#ifndef _FILEIO_H
#define _FILEIO_H
#include <fstream>
#include <string>
#include "player.h"

void g_LoadFromSave(unsigned int* SaveDataArray);
void g_SaveToSave(unsigned int* SaveDataArray);

struct SaveDataStorage
{
	unsigned int g_iSaveData[9];
	unsigned int g_iWriteData[9];
};
#endif