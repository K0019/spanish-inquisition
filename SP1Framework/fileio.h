#pragma once

#ifndef _FILEIO_H
#define _FILEIO_H
#include <fstream>
#include <string>

void LoadSave(std::string *SaveFile);
void SaveSave(std::string *SaveFile);

struct SaveStorage {
	std::string SaveVar[7];
}savef;

#endif