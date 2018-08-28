#pragma once

/* MADE BY: Winston */

/*Other traps such as snares and turrets are too unhealthy for the game, thus they are not implemented. 
trap.h and trap.cpp remains for easy implementation of traps in the future*/

#ifndef TRAPHEAD
#define TRAPHEAD

#include <string>
#include <vector>

struct STrap //Struct that holds all trap information
{
	std::string m_sName;
	int m_iTrapIndex;
	int m_iTrapHealth;
	int m_iTrapDamage;
	double m_dTrapTime;

	STrap(char name[], int index, int health, int damage, double time);
};

struct SAllTraps //Struct that holds all unqiue traps
{
	std::vector<STrap> m_vTrapList;

	SAllTraps();
	void addTrap(STrap& trap);
};
#endif // !TRAPHEAD
