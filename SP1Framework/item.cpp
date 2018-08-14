#include "item.h"
#include "stat.h"


SItem::SItem(std::string name, int index, int damage, int healthGiven, float attackSpeed, float velocity, bool HasWeapon)
{
	this->m_sName = name;
	this->m_iWeaponIndex = index;
	this->m_iWeaponDamage = damage;
	this->m_iWeaponHealthGiven = healthGiven;
	this->m_iWeaponAttackSpeed = attackSpeed;
	this->m_iWeaponVelocity = velocity;
	this->m_bHasWeapon = HasWeapon;
}


SAllItems::SAllItems() //Constructor to initialise each unique item
{
	this->addItem(SItem("Heaven Cracker", 1, 0, 0, 0, 0, false));
	this->addItem(SItem("Enchanted Sword", 2, 2, 0, 0, 0, false));
	this->addItem(SItem("Health Potion", 3, 0, 2, 0, 0, false));
	this->addItem(SItem("Clown Fiesta", 4, 0, 0, 0, 0, false));
	this->addItem(SItem("Antenna", 5, 0, 0, 0, 0, false));
	this->addItem(SItem("Bonus!", 6, 0, 0, 0, 0, false));

	void HasItem(bool g_bHasItem)
	{
		int weaponIndex;

		if (g_bHasItem = true)
		{
			srand(time(NULL));
			weaponIndex = rand() % 6 + 1;
		}

		if ((weaponIndex == m_vItemsList[0]->m_iWeaponIndex) && (m_vItemsList[0]->m_bHasWeapon == false))
		{
			this->m_iPlayerHealth += m_vItemsList[0].m_iWeaponHealthGiven;
			SGameChar.m_iPlayerDamage += HeavenCracker.m_iWeaponDamage;
			m_vItemsList[0].m_bHasWeapon = true;
		}
		else if ((weaponIndex == m_vItemsList[1]->m_iWeaponIndex) && (m_vItemsList[1]->m_bHasWeapon == false))
		{
			
		}
	}
}

void SAllItems::addItem(SItem item)
{
	this->m_vItemsList.push_back(item);
	this->m_vItemsObtained.push_back(false);
}