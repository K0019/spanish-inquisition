#pragma once

/* Made by: Winston */

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
	int m_iWeaponCost;
	int m_iWeaponIncrement;
	int m_iWeaponTotalCost;

	SItem(std::string name, int index, int damage, int healthGiven, float attackSpeed, float velocity, float moveSpeed, bool hasWeapon, int weaponLevel, int cost, int increment, int totalCost);
};

struct SAllItems //Struct that holds all items as indiviual items
{
	std::vector<SItem> m_vItemsList;
	std::vector<bool> m_vItemsObtained;
	std::vector<std::string> m_vItemNameList;
	int ItemCount;

	SAllItems();
	void addItem(SItem item);
};

#endif //!ITEMHEAD