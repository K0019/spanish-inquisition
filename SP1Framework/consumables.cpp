#include "consumables.h"

SConsumable::SConsumable(char name[], int index, int health, int score)
{
	this->m_sName = name;
	this->m_iConsumableHealth = health;
	this->m_iConsumableIndex = index;
	this->m_iConsumableScore = score;
}

SAllConsumables::SAllConsumables() //Constructor to initialise each unique consumable and their stats.
{
	this->addConsumable(SConsumable("Minor Health Pack", 1, 5, 0));
	this->addConsumable(SConsumable("Greater Health Pack", 2, 10, 0));
	//this->addConsumable(SConsumable("Minor health pack", 1, 5, 0));
	//this->addconsumable(SConsumable("greater health pack", 2, 10, 0));
	this->addConsumable(SConsumable("Small Medal", 3, 0, 20));
	this->addConsumable(SConsumable("Large Medal", 3, 0, 50));
}

void SAllConsumables::addConsumable(SConsumable& consumable)
{
	this->m_vConsumableList.push_back(consumable);
}