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
	//RNG to choose 1 of the 7 items when an item is picked up.
	int weaponIndex;
	weaponIndex = rand() % 6 + 1;

	if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[0].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Heaven Cracker
	{
		switch (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponLevel) //Index 1 (Heaven Cracker): Increase player damage by 0/1/2/3
		{
		case 1: //Heaven Cracker Level 1: Increase player damage by 0
			{
				this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage;
				this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
			}
		case 2: //Heaven Cracker Level 2: Increase player damage by 1
			{
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage + 1);
				this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
			}
		case 3: //Heaven Cracker Level 3: Increase player damage by 2
			{
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage + 2);
				this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
			}
		case 4: //Heaven Cracker Level 4: Increase player damage by 3
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
		switch (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponLevel) //Index 2 (Enchanted Sword): Increase player health by 1/2/3/4, increase player damage by 2/3/4/5
		{
		case 1: //Enchanted Sword level 1: Increase player health by 1, increase player damage by 2.
			{
				this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven;
				this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage;
				this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 2: //Enchanted Sword level 2: Increase player health by 2, increase player damage by 3.
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 1);
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage + 1);
				this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 3: //Enchanted Sword level 3: Increase player health by 3, increase player damage by 4.
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 2);
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage + 2);
				this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 4: //Enchanted Sword level 4: Increase player health by 4, increase player damage by 5.
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
		case 1: //Health Potion level 1: Increase player health by 2.
			{
				this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven;
				this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 2: //Health Potion level 2: Increase player health by 4.
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 2);
				this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 3: //Health Potion level 3: Increase player health by 6.
			{
				this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 4);
				this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		case 4: //Health Potion level 4: Increase player health by 8.
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

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[3].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Glass Canon
	{
		switch (this->m_sPlayerItems.m_vItemsList[3].m_iWeaponLevel)
		{
			case 1: //Glass Canon Level 1: Player deals 1 more damage to enemies
				{
					this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage;
					this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 2: //Glass Canon Level 2: Player deals 2 more damage to enemies
				{
					this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage + 1);
					this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 3: //Glass Canon Level 3: Player deals 3 more damage to enemies
				{
					this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage + 2);
					this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 4: //Glass Canon Level 4: Player deals 4 more damage to enemies
				{
					this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage + 3);
					this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
		}
	}
	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[3].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon == true))
	{
		this->m_iPlayerScore += 50; //If player picks up another Glass Canon, +50 score.
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
			case 1: //BONUS! Level 1: Multiplies player's score by 1.5x
				{
					this->m_iPlayerScore = (int)ceil(this->m_iPlayerScore * 1.5);
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 2: //BONUS! Level 2: Multiplies player's score by 2x
				{
					this->m_iPlayerScore <<= 1;
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 3: //BONUS! Level 3: Multiplies player's score by 2.5x
				{
					this->m_iPlayerScore = (int)ceil(this->m_iPlayerDamage * 2.5);
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
					break;
				}
			case 4: //BONUS! Level 4: Multiplies player's score by 3x
				{
					this->m_iPlayerScore = (int)ceil(this->m_iPlayerScore * 3);
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
	if (playerScore < 0)
	{
		if (m_iPlayerScore > (unsigned int) abs(playerScore))
		{
			m_iPlayerScore += playerScore;
		}
		else
		{
			m_iPlayerScore = 0;
		}
	}
	else
	{
		m_iPlayerScore += playerScore;
	}
}