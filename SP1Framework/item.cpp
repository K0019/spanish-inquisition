#include "item.h"
#include "stat.h"


SItem::SItem(std::string name, int index, int damage, int healthGiven, float attackSpeed, float velocity, float moveSpeed, bool HasWeapon)
{
	this->m_sName = name;
	this->m_iWeaponIndex = index;
	this->m_iWeaponDamage = damage;
	this->m_iWeaponHealthGiven = healthGiven;
	this->m_fWeaponAttackSpeed = attackSpeed;
	this->m_fWeaponVelocity = velocity;
	this->m_fweaponMovementSpeed = moveSpeed;
	this->m_bHasWeapon = HasWeapon;
}


SAllItems::SAllItems() //Constructor to initialise each unique item
{
	this->addItem(SItem("Heaven Cracker", 1, 0, 0, 0, 0, 0, false));
	this->addItem(SItem("Enchanted Sword", 2, 2, 1, 0, 0, 0, false));
	this->addItem(SItem("Health Potion", 3, 0, 2, 0, 0, 0, false));
	this->addItem(SItem("Clown Fiesta", 4, 0, 0, 0, 0, 0, false));
	this->addItem(SItem("Antenna", 5, 0, 0, 0, 0, 0, false));
	this->addItem(SItem("Bonus!", 6, 0, 0, 0, 0, 0, false));
	this->addItem(SItem("Blue Feather", 7, 0, 0, 0, 0, 0.1, false));
}


void SAllItems::addItem(SItem item)
{
	this->m_vItemsList.push_back(item);
	this->m_vItemsObtained.push_back(false);
}