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
	//RNG to choose 1 of the 8 items when an item is picked up.
	int weaponIndex;
	weaponIndex = rand() % 6 + 1; 

	if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[0].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Heaven Cracker
	{
		switch (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponLevel) //Index 1 (Heaven Cracker): Increase player damage by 0/1/2/3
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
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[0].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon == true))
	{
		this->m_iPlayerScore += 50; //If player picks up another Heaven Cracker, +50 score.
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[1].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Enchanted Sword
	{
		switch (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponLevel) //Index 2 (Enchanted Sword): Increase player health by 1/2/3/4, Increase player damage by 2/3/4/5
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
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[1].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon == true))
	{
		this->m_iPlayerScore += 50; //If player picks up another Enchanted Sword, +50 score.
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[2].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Health Potion
	{
		switch (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponLevel) //Index 3 (Health Potion): Increase player health by 2/4/6/8
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
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[2].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon == true))
	{
		this->m_iPlayerScore += 50; //If player picks up another Health Potion, +50 score.
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[3].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Clown Fiesta
	{
		this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
		this->m_sPlayerItems.ItemCount++;
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[3].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon == true))
	{
		this->m_iPlayerScore += 50; //If player picks up another Clown Fiesta, +50 score.
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[4].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Magic Potion
	{
		this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon = true;
		this->m_sPlayerItems.ItemCount++;
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[4].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon == true))
	{
		this->m_iPlayerScore += 50; //If player picks up another Magic Potion, +50 score.
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[5].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Bonus!
	{
		switch (this->m_sPlayerItems.m_vItemsList[5].m_iWeaponLevel) //Index 6 (BONUS!): Multiplies player's score by 1.5/2/2.5/3x
		{
			case 1: //BONUS! Level 1
				{
					this->m_iPlayerScore *= 1.5;
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 2: //BONUS! Level 2
				{
					this->m_iPlayerScore *= 2;
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 3: //BONUS! Level 3
				{
					this->m_iPlayerScore *= 2.5;
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 4: //BONUS! Level 4
				{
					this->m_iPlayerScore *= 3;
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
		}
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[5].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon == true))
	{
		this->m_iPlayerScore *= 2; //If player picks up another BONUS!, multiply score by 2.
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[6].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Blue Feather
	{
		this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon = true;
		this->m_sPlayerItems.ItemCount++;
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[6].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon == true))
	{
		this->m_iPlayerScore += 50; //If player picks up another Blue Feather, +50 score.
	}

}

void SGameChar::minimumScore(int playerScore) //To make sure the minimum score is 0, it should not go to the negatives
{
	m_iPlayerScore = playerScore;
	if (m_iPlayerScore < 0)
	{
		m_iPlayerScore = 0;
	}
}