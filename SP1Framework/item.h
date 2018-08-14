#pragma once

#ifndef ITEMHEAD
#define ITEMHEAD

#include "pellet.h"
#include <random>
#include <ctime>
#include <vector>

struct SItem
{
	std::string m_sName;
	int m_iWeaponIndex;
	int m_iWeaponDamage;
	int m_iWeaponHealthGiven;
	float m_fWeaponAttackSpeed;
	float m_fWeaponVelocity;
	float m_fweaponMovementSpeed;
	bool m_bHasWeapon;

	SItem(std::string name, int index, int damage, int healthGiven, float attackSpeed, float velocity, float moveSpeed, bool HasWeapon);
};

struct SAllItems
{
	std::vector<SItem> m_vItemsList;
	std::vector<bool> m_vItemsObtained;

	SAllItems();
	void addItem(SItem item);
};

#endif