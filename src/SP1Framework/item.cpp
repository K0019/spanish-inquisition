#include "item.h"

//Constructor to initialise all item information
SItem::SItem(std::string name, int index, int damage, int healthGiven, float attackSpeed, float velocity, float moveSpeed, bool hasWeapon, int weaponLevel, int cost, int increment, int totalCost)
{
	this->m_sName = name;
	this->m_iWeaponIndex = index;
	this->m_iWeaponDamage = damage;
	this->m_iWeaponHealthGiven = healthGiven;
	this->m_fWeaponAttackSpeed = attackSpeed;
	this->m_fWeaponVelocity = velocity;
	this->m_fweaponMovementSpeed = moveSpeed;
	this->m_bHasWeapon = hasWeapon;
	this->m_iWeaponLevel = weaponLevel;
	this->m_iWeaponCost = cost;
	this->m_iWeaponIncrement = increment;
	this->m_iWeaponTotalCost = totalCost;
}


SAllItems::SAllItems() //Constructor to initialise each unique item and their stats.
{
	this->addItem(SItem("Heaven Cracker", 0, 0, 0, 0.0, 0.0, 0.0, false, 0, 400, 150, 400));
	this->addItem(SItem("Enchanted Sword", 1, 2, 3, 0.0, 0.0, 0.0, false, 0, 600, 150, 600));
	this->addItem(SItem("Health Potion", 2, 0, 5, 0.0, 0.0, 0.0, false, 0, 400, 200, 400));
	this->addItem(SItem("Glass Canon", 3, 4, 0, 0.0, 0.0, 0.0, false, 0, 500, 150, 500));
	this->addItem(SItem("Magic Potion", 4, 0, 0, (float)1.0, (float)1.0, 0.0, false, 0, 500, 150, 400));
	this->addItem(SItem("Bonus!", 5, 0, 0, 0.0, 0.0, 0.0, false, 0, 300, 200, 400));
	this->addItem(SItem("Blue Feather", 6, 0, 0, 0.0, 0.0, (float)1.0, false, 0, 500, 150, 500));
}


void SAllItems::addItem(SItem item)
{
	this->m_vItemsList.push_back(item);
	this->m_vItemsObtained.push_back(false);
	this->ItemCount;
}