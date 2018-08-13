#include "item.h"

SAllItems::SAllItems(int damage, int healthGiven, float attackSpeed, float velocity)
{
	this->m_iWeaponDamage = damage;
	this->m_iWeaponHealthGiven = healthGiven;
	this->m_iWeaponAttackSpeed = attackSpeed;
	this->m_iWeaponVelocity = velocity;
}

