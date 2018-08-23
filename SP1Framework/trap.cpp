#include "trap.h"

STrap::STrap(char name[], int index, int health, int damage, double time)
{
	this->m_sName = name;
	this->m_iTrapIndex = index;
	this->m_iTrapHealth = health;
	this->m_iTrapDamage = damage;
	this->m_dTrapTime = time;
}

SAllTraps::SAllTraps()
{
	this->addTrap(STrap("Spike", 1, 0, 4, 0));
	this->addTrap(STrap("Snare", 2, 0, 0, 2));
	this->addTrap(STrap("Turret", 3, 10, 2, 0));
}

void SAllTraps::addTrap(STrap& trap)
{
	this->m_vTrapList.push_back(trap);
}