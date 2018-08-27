#pragma once

/* MADE BY: Woo Josh, Team 4
   Some modifications made by: Kendrick */

#ifndef MUSIC_MAN
#define MUSIC_MAN
#include <vector>
#include <string>
std::wstring s2ws(const std::string& s); /* Made by: Kendrick */
void Mshutdown();
void MusicInit();
struct MLoaded
{
	std::string file = ""; // Can be empty!
	std::string type = ""; // Can be empty!
	std::string alias = ""; // Can be empty!
	int status;
};
bool MusicLoad(std::string file, std::string type, std::string alias, std::string initalvolume, MLoaded* Returnfile);
bool MusicPlay(std::string alias, std::string arguments);
bool MusicStop(std::string alias);
#endif // !MUSIC_MAN
