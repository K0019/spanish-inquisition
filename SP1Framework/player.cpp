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
	int weaponIndex;

	weaponIndex = rand() % 6 + 1; //Choosing a random number between 1 and 7
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
								//			if (storedIndex == weaponIndex[j]) //If number is already used
								//			{
								//				check = false; //Set check to false
								//				break;
								//			}
								//		}
								//	} while (!check);
								//	weaponIndex[i] = storedIndex;
								//	break;
								//}

	if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[0].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Heaven Cracker
	{
		switch (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponLevel)
		{
		case 1:
			{
				this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage;
				this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
			}
		case 2:
			{
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage + 1);
				this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
			}
		case 3:
			{
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage + 2);
				this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
			}
		case 4:
			{
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage + 3);
				this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
			}
		}
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[1].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Enchanted Sword
	{
		switch (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponLevel)
		{
		case 1: //Enchanted Sword level 1
			{
				this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven;
				this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage;
				this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 2: //Enchanted Sword level 2
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 1);
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage + 1);
				this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 3: //Enchanted Sword level 3
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 2);
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage + 2);
				this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 4: //Enchanted Sword level 4
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 2);
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage + 2);
				this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		}
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[2].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Health Potion
	{
		switch (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponLevel)
		{
		case 1: //Health Potion level 1
			{
				this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven;
				this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 2: //Health Potion level 2
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 2);
				this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 3: //Health Potion level 3
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 4);
				this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 4: //Health Potion level 4
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 6);
				this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		}
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[3].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Clown Fiesta
	{
		this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
		this->m_sPlayerItems.ItemCount++;
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[4].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Magic Potion
	{
		this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon = true;
		this->m_sPlayerItems.ItemCount++;
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[5].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Bonus!
	{
		this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
		this->m_sPlayerItems.ItemCount++;
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[6].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Blue Feather
	{
		this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon = true;
		this->m_sPlayerItems.ItemCount++;
	}
}