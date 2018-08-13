#pragma once

#ifndef _FILEIO_H
#define _FILEIO_H
#include <fstream>
#include <string>

void load(std::string fileName, std::string *variable);
void save(std::string fileName, std::string *variable);

#endif