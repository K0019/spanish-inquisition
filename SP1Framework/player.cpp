#include "player.h"

SGameChar::SGameChar()
{

}

SGameChar::SGameChar(COORD location, bool active, int playerHealth, int playerDamage, int playerScore)
{
	this->m_iPlayerHealth = playerHealth;
	this->m_iPlayerDamage = playerDamage;
	this->m_iPlayerScore = playerScore;
}

COORD SGameChar::getRealCoords()
{
	COORD c = this->m_cLocation;
	while (c.X > ROOM_X + 2)
		c.X -= (ROOM_X + 2);
	while (c.Y > ROOM_Y + 2)
		c.Y -= (ROOM_Y + 2);
	std::swap(c.X, c.Y);
	c.X = (c.X << 1) - 1;
	return c;
}

void SGameChar::AddItem(bool g_bHasWeapon)
{
	this->hasItem(g_bHasWeapon);
}

void SGameChar::hasItem(bool g_bHasWeapon)
{
	int itemIndex;

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

	if ((itemIndex == this->m_sPlayerItems.m_vItemsList[0].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Heaven Cracker
	{
		this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[0].m_iWeaponHealthGiven;
		this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage;
		this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
	}
	else if ((itemIndex == this->m_sPlayerItems.m_vItemsList[1].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Enchanted Sword
	{
		this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven;
		this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage;
		this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
	}
	else if ((itemIndex == this->m_sPlayerItems.m_vItemsList[2].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Health Potion
	{
		this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven;
		this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[2].m_iWeaponDamage;
		this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
	}
	else if ((itemIndex == this->m_sPlayerItems.m_vItemsList[3].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Clown Fiesta
	{
		this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[3].m_iWeaponHealthGiven;
		this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage;
		this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
	}
	else if ((itemIndex == this->m_sPlayerItems.m_vItemsList[4].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Antenna
	{
		this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[4].m_iWeaponHealthGiven;
		this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[4].m_iWeaponDamage;
		this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon = true;
	}
	else if ((itemIndex == this->m_sPlayerItems.m_vItemsList[5].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Bonus!
	{
		this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[5].m_iWeaponHealthGiven;
		this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[5].m_iWeaponDamage;
		this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
	}
	else if ((itemIndex == this->m_sPlayerItems.m_vItemsList[6].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Blue Feather!
	{
		this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[6].m_iWeaponHealthGiven;
		this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[6].m_iWeaponDamage;
		this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon = true;

	}
	else //Do nothing if this already has all items
	{
	}
}