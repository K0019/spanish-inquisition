#pragma once

#ifndef CONSUMABLEHEAD
#define CONSUMABLEHEAD

#include <string>
#include <vector>

struct SConsumable
{
	std::string m_sName;
	int m_iConsumableIndex;
	int m_iConsumableHealth;
	int m_iConsumableScore;

	SConsumable(std::string name, int index, int health, int score);
};

struct SAllConsumables
{
	std::vector<SConsumable> m_vConsumableList;

	SAllConsumables();
	void addConsumable(SConsumable consumable);
};



#endif // !CONSUMABLEHEAD
