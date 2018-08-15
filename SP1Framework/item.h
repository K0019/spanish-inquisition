#pragma once

#ifndef ITEMHEAD
#define ITEMHEAD

#include "pellet.h"
#include <random>
#include <ctime>
#include <vector>

struct SItem //Struct that holds item information
{
	std::string m_sName;
	int m_iWeaponIndex;
	int m_iWeaponDamage;
	int m_iWeaponHealthGiven;
	float m_fWeaponAttackSpeed;
	float m_fWeaponVelocity;
	float m_fweaponMovementSpeed;
	bool m_bHasWeapon;
	int m_iWeaponLevel;

	SItem(std::string name, int index, int damage, int healthGiven, float attackSpeed, float velocity, float moveSpeed, bool hasWeapon, int weaponLevel);
};

struct SAllItems //Struct that holds all items 
{
	std::vector<SItem> m_vItemsList;
	std::vector<bool> m_vItemsObtained;
	int ItemCount;

	SAllItems();
	void addItem(SItem item);
};

#endif