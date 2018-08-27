#include "trap.h"

STrap::STrap(char name[], int index, int health, int damage, double time) //Constructor to initialise trap information
{
	this->m_sName = name;
	this->m_iTrapIndex = index;
	this->m_iTrapHealth = health;
	this->m_iTrapDamage = damage;
	this->m_dTrapTime = time;
}

SAllTraps::SAllTraps() //Constructor to initialise each unique trap and their stats.
{
	this->addTrap(STrap("Spike", 1, 0, 4, 0));
}

void SAllTraps::addTrap(STrap& trap)
{
	this->m_vTrapList.push_back(trap);
}