#pragma once

/* MADE BY: Winston */

#ifndef CONSUMABLEHEAD
#define CONSUMABLEHEAD

#include <string>
#include <vector>

struct SConsumable //Struct that holds all consumable information
{
	std::string m_sName;
	int m_iConsumableIndex;
	int m_iConsumableHealth;
	int m_iConsumableScore;

	SConsumable(char name[], int index, int health, int score);
};

struct SAllConsumables //Struct that holds all consumables as individual consumables
{
	std::vector<SConsumable> m_vConsumableList;

	SAllConsumables();
	void addConsumable(SConsumable& consumable);
};



#endif // !CONSUMABLEHEAD
