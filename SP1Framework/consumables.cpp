#include "consumables.h"

SConsumable::SConsumable(std::string name, int index, int health, int score)
{
	this->m_sName = name;
	this->m_iConsumableIndex = index;
	this->m_iConsumableScore = score;
}

SAllConsumables::SAllConsumables()
{
	this->addConsumable(SConsumable("Minor Health Potion", 1, 5, 0));
	this->addConsumable(SConsumable("Greater Health Potion", 2, 10, 0));
	this->addConsumable(SConsumable("Small Medal", 3, 0, 20));
	this->addConsumable(SConsumable("Large Medal", 3, 0, 50));
}

void SAllConsumables::addConsumable(SConsumable consumable)
{
	this->m_vConsumableList.push_back(consumable);
}