#pragma once

#ifndef TRAPHEAD
#define TRAPHEAD

#include <string>
#include <vector>

struct STrap
{
	std::string m_sName;
	int m_iTrapIndex;
	int m_iTrapHealth;
	int m_iTrapDamage;
	double m_dTrapTime;

	STrap(char name[], int index, int health, int damage, double time);
};

struct SAllTraps
{
	std::vector<STrap> m_vTrapList;

	SAllTraps();
	void addTrap(STrap& trap);
};
#endif // !TRAPHEAD
