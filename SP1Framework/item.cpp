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

void SAllItems::hasItem(bool g_bHasWeapon, SGameChar * player)
{
	int itemIndex;

	srand(time(NULL)); //Seed RNG before using
	itemIndex = rand() % 6 + 1; //Choosing a random number between 1 and 7
	//for (int i = 0; i < 6; i++)
	//{
	//	bool check;
	//	int storedIndex;
	//	do
	//	{
	//		storedIndex = rand() % 6 + 1;
	//		check = true; //Check if number is already used to prevent repeats
	//		for (int j = 0; j < i; j++)
	//		{
	//			if (storedIndex == itemIndex[j]) //If number is already used
	//			{
	//				check = false; //Set check to false
	//				break;
	//			}
	//		}
	//	} while (!check);
	//	itemIndex[i] = storedIndex;
	//	break;
	//}

	if ((itemIndex == this->m_vItemsList[0].m_iWeaponIndex) && (m_vItemsList[0].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Heaven Cracker
	{
		player->m_iPlayerHealth += m_vItemsList[0].m_iWeaponHealthGiven;
		player->m_iPlayerDamage += m_vItemsList[0].m_iWeaponDamage;
		m_vItemsList[0].m_bHasWeapon = true;
	}
	else if ((itemIndex == m_vItemsList[1].m_iWeaponIndex) && (m_vItemsList[1].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Enchanted Sword
	{
		player->m_iPlayerHealth += m_vItemsList[1].m_iWeaponHealthGiven;
		player->m_iPlayerDamage += m_vItemsList[1].m_iWeaponDamage;
		m_vItemsList[1].m_bHasWeapon = true;
	}
	else if ((itemIndex == m_vItemsList[2].m_iWeaponIndex) && (m_vItemsList[2].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Health Potion
	{
		player->m_iPlayerHealth += m_vItemsList[2].m_iWeaponHealthGiven;
		player->m_iPlayerDamage += m_vItemsList[2].m_iWeaponDamage;
		m_vItemsList[2].m_bHasWeapon = true;
	}
	else if ((itemIndex == m_vItemsList[3].m_iWeaponIndex) && (m_vItemsList[3].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Clown Fiesta
	{
		player->m_iPlayerHealth += m_vItemsList[3].m_iWeaponHealthGiven;
		player->m_iPlayerDamage += m_vItemsList[3].m_iWeaponDamage;
		m_vItemsList[3].m_bHasWeapon = true;
	}
	else if ((itemIndex == m_vItemsList[4].m_iWeaponIndex) && (m_vItemsList[4].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Antenna
	{
		player->m_iPlayerHealth += m_vItemsList[4].m_iWeaponHealthGiven;
		player->m_iPlayerDamage += m_vItemsList[4].m_iWeaponDamage;
		m_vItemsList[4].m_bHasWeapon = true;
	}
	else if ((itemIndex == m_vItemsList[5].m_iWeaponIndex) && (m_vItemsList[5].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Bonus!
	{
		player->m_iPlayerHealth += m_vItemsList[5].m_iWeaponHealthGiven;
		player->m_iPlayerDamage += m_vItemsList[5].m_iWeaponDamage;
		m_vItemsList[5].m_bHasWeapon = true;
	}
	else if ((itemIndex == m_vItemsList[6].m_iWeaponIndex) && (m_vItemsList[6].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Blue Feather!
	{
		player->m_iPlayerHealth += m_vItemsList[6].m_iWeaponHealthGiven;
		player->m_iPlayerDamage += m_vItemsList[6].m_iWeaponDamage;
		m_vItemsList[6].m_bHasWeapon = true;

	}
	else //Do nothing if player already has all items
	{
	}
}

void SAllItems::addItem(SItem item)
{
	this->m_vItemsList.push_back(item);
	this->m_vItemsObtained.push_back(false);
}