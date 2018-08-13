#pragma once

#ifndef ITEMHEAD
#define ITEMHEAD

#include "pellet.h"
#include "game.h"

struct SAllItems
{
	int m_iWeaponDamage;
	int m_iWeaponHealthGiven;
	float m_iWeaponAttackSpeed;
	float m_iWeaponVelocity;

	SAllItems(int damage, int healthGiven, float attackSpeed, float velocity);
};

struct SAllItems HeavenCracker(0, 0, 0, 0);
struct SAllItems EnchantedSword(2, 0, 0, 0);
struct SAllItems HealthPotion(0, 2, 0, 0);
struct SAllItems ClownFiesta(0, 0, 0, 0);
struct SAllItems Antenna(0, 0, 0, 0);
struct SAllItems Bonus(0, 0, 0, 0);


#endif