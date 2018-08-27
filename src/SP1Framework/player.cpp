#include "player.h"

SGameChar::SGameChar() //Default constructor for the struct containing player information
{
	this->m_iPlayerScore = 0;
}

SGameChar::SGameChar(COORD location, bool active, int playerHealth, int playerDamage, int playerScore, std::string lastItem) //Constructor to initialise specific player information
{
	this->m_iPlayerHealth = playerHealth;
	this->m_iPlayerDamage = playerDamage;
	this->m_iPlayerScore = playerScore;
	this->m_sLastItem = lastItem;
}

COORD SGameChar::getRealCoords()
{
	COORD c = this->m_cLocation;
	while (c.X > ROOM_X + 2)
		c.X -= (ROOM_X + 2);
	while (c.Y > ROOM_Y + 2)
		c.Y -= (ROOM_Y + 2);
	std::swap(c.X, c.Y);
	c.X = (c.X << 2) - 2;
	c.Y = (c.Y << 1) - 1;
	return c;
}

void SGameChar::addItem(bool g_bHasWeapon) //Passing in the condition check for items picked up
{
	this->hasItem(g_bHasWeapon);
}

void SGameChar::addConsumable(bool g_bHasConsumable, int index) //Passing in condition check for consumables picked up and which consumable
{
	this->hasConsumable(g_bHasConsumable, index);
}

void SGameChar::hasItem(bool g_bHasWeapon) //Function to determine what item the player gets
{
	int weaponIndex = 0;
	//RNG to choose 1 of the 7 items when an item is picked up.
	//Loop to ensure the player only gets 1 of each item
	do
	{
		if ((this->m_sPlayerItems.ItemCount >= 7) && (g_bHasWeapon == true))
		{
			this->m_iPlayerScore += 50;
			break;
		}
		weaponIndex = rand() % 7;
	} while (this->m_sPlayerItems.m_vItemsList[weaponIndex].m_bHasWeapon); //If the player already has that item, go through the loop again


	if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[0].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Heaven Cracker
	{
		switch (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponLevel) //Index 1 (Heaven Cracker): Increase player damage by 0/2/3/4
		{
		case 0: //Heaven Cracker Level 1: Increase player damage by 0.
		{
			this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage;
			this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 1: //Heaven Cracker Level 2: Increase player damage by 2.
		{
			this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage + 2);
			this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 2: //Heaven Cracker Level 3: Increase player damage by 3.
		{
			this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage + 3);
			this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 3: //Heaven Cracker Level 4: Increase player damage by 4.
		{
			this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[0].m_iWeaponDamage + 4);
			this->m_sPlayerItems.m_vItemsList[0].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		}
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[1].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Enchanted Sword
	{
		switch (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponLevel) //Index 2 (Enchanted Sword): Increase player health by 3/4/5/6, increase player damage by 2/3/4/5
		{
		case 0: //Enchanted Sword level 1: Increase player health by 3, increase player damage by 2.
		{
			this->m_iMaxHealth += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven;
			this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven;
			this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage;
			this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 1: //Enchanted Sword level 2: Increase player health by 4, increase player damage by 3.
		{
			this->m_iMaxHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 1);
			this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 1);
			this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage + 1);
			this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 2: //Enchanted Sword level 3: Increase player health by 5, increase player damage by 4.
		{
			this->m_iMaxHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 2);
			this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 2);
			this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponDamage + 2);
			this->m_sPlayerItems.m_vItemsList[1].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 3: //Enchanted Sword level 4: Increase player health by 6, increase player damage by 5.
		{
			this->m_iMaxHealth += (this->m_sPlayerItems.m_vItemsList[1].m_iWeaponHealthGiven + 2);
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
		switch (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponLevel) //Index 3 (Health Potion): Increase player health by 5/7/9/11
		{
		case 0: //Health Potion level 1: Increase player health by 5.
		{
			this->m_iMaxHealth += this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven;
			this->m_iPlayerHealth += this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven;
			this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 1: //Health Potion level 2: Increase player health by 7.
		{
			this->m_iMaxHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 2);
			this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 2);
			this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 2: //Health Potion level 3: Increase player health by 9.
		{
			this->m_iMaxHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 4);
			this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 4);
			this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		case 3: //Health Potion level 4: Increase player health by 11.
		{
			this->m_iMaxHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 6);
			this->m_iPlayerHealth += (this->m_sPlayerItems.m_vItemsList[2].m_iWeaponHealthGiven + 6);
			this->m_sPlayerItems.m_vItemsList[2].m_bHasWeapon = true;
			this->m_sPlayerItems.ItemCount++;
			break;
		}
		}
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[3].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Glass Canon
	{
		switch (this->m_sPlayerItems.m_vItemsList[3].m_iWeaponLevel) //Index 4 (Glass Canon): Increase player's damage by 4/5/6/7.
		{
			case 0: //Glass Canon Level 1: Player deals 4 more damage to enemies
			{
				this->m_iPlayerDamage += this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage;
				this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
			case 1: //Glass Canon Level 2: Player deals 5 more damage to enemies
			{
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage + 1);
				this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
			case 2: //Glass Canon Level 3: Player deals 6 more damage to enemies
			{
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage + 2);
				this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
			case 3: //Glass Canon Level 4: Player deals 7 more damage to enemies
			{
				this->m_iPlayerDamage += (this->m_sPlayerItems.m_vItemsList[3].m_iWeaponDamage + 3);
				this->m_sPlayerItems.m_vItemsList[3].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		}
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[4].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Magic Potion
	{
		switch (this->m_sPlayerItems.m_vItemsList[5].m_iWeaponLevel) //Index 4 (Magic Potion): Increase pellet velocity by 20%/30%/40%/50%
		{
			case 0: //Magic Potion Level 1: Pellet velocity increased by 20%
			{
				this->m_dVelocity *= (this->m_sPlayerItems.m_vItemsList[4].m_fWeaponVelocity - 0.20);
				this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
			case 1: //Magic Potion Level 1: Pellet velocity increased by 30%
			{
				this->m_dVelocity *= (this->m_sPlayerItems.m_vItemsList[4].m_fWeaponVelocity - 0.30);
				this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
			case 2: //Magic Potion Level 1: Pellet velocity increased by 40%
			{
				this->m_dVelocity *= (this->m_sPlayerItems.m_vItemsList[4].m_fWeaponVelocity - 0.40);
				this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
			case 3: //Magic Potion Level 1: Pellet velocity increased by 50%
			{
				this->m_dVelocity *= (this->m_sPlayerItems.m_vItemsList[4].m_fWeaponVelocity - 0.50);
				this->m_sPlayerItems.m_vItemsList[4].m_bHasWeapon = true;
				this->m_sPlayerItems.ItemCount++;
				break;
			}
		}
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[5].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Bonus!
	{
		switch (this->m_sPlayerItems.m_vItemsList[5].m_iWeaponLevel) //Index 6 (BONUS!): Multiplies player's score by 1.5/2/2.5/3x
		{
			case 0: //BONUS! Level 1: Multiplies player's score by 1.5x
				{
					if (this->m_iPlayerScore == 0) //Score multiplier is useless when score is still 0, so add 10/20/30/40 score to player depending on item level
					{
						this->m_iPlayerScore += 10;
					}
					else
					{
						this->m_iPlayerScore = (int)ceil(this->m_iPlayerScore * 1.5);
						this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
						this->m_sPlayerItems.ItemCount++;
					}
						break;
				}
			case 1: //BONUS! Level 2: Multiplies player's score by 2x
				{
					if (this->m_iPlayerScore == 0) //Add 20 score if score is 0
					{
						this->m_iPlayerScore += 20;
					}
					else
					{
						this->m_iPlayerScore <<= 1;
						this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
						this->m_sPlayerItems.ItemCount++;
					}
						break;
				}
			case 2: //BONUS! Level 3: Multiplies player's score by 2.5x
			{
				if (this->m_iPlayerScore == 0) //Add 30 score if score is 0
				{
					this->m_iPlayerScore += 30;
				}
				else
				{
					this->m_iPlayerScore = (int)ceil(this->m_iPlayerDamage * 2.5);
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
				}
					break;
			}
			case 3: //BONUS! Level 4: Multiplies player's score by 3x
			{
				if (this->m_iPlayerScore == 0) //Add 40 score if score is 0
				{
					this->m_iPlayerScore += 40;
				}
				else
				{
					this->m_iPlayerScore = (int)ceil(this->m_iPlayerScore * 3);
					this->m_sPlayerItems.m_vItemsList[5].m_bHasWeapon = true;
					this->m_sPlayerItems.ItemCount++;
				}
					break;
			}
		}
	}

	else if ((weaponIndex == this->m_sPlayerItems.m_vItemsList[6].m_iWeaponIndex) && (this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon == false)) //Checking if randomized weaponIndex gives the Blue Feather
	{
		this->m_sPlayerItems.m_vItemsList[6].m_bHasWeapon = true;
		this->m_sPlayerItems.ItemCount++;
	}


	this->m_sLastItem = this->m_sPlayerItems.m_vItemsList[weaponIndex].m_sName;
	this->m_sPlayerItems.m_vItemNameList.push_back(m_sLastItem);
}

void SGameChar::minimumScore(int playerScore) //To make sure the minimum score is 0, it should not go to the negatives
{
	if (this->m_iPlayerScore > (unsigned int) abs(playerScore))
	{
		this->m_iPlayerScore += playerScore;
	}
	else
	{
		this->m_iPlayerScore = 0;
	}
}

void SGameChar::hasConsumable(bool g_bHasConsumable, int index)
{
	if (g_bHasConsumable == true)
	{
		switch (index)
		{
		case 1: //Index 1: Minor Health Potion, restores 5 health (potion will not restore any higher than maximum hp)
		{
			this->m_iPlayerHealth += this->m_sConsumables.m_vConsumableList[0].m_iConsumableHealth;
			if (this->m_iPlayerHealth > this->m_iMaxHealth) //Prevents the player's health from going above player's max health
			{
				this->m_iPlayerHealth = this->m_iMaxHealth;
			}
			break;
		}
		case 2: //Index 1: Greater Health Potion, restores 10 health (potion will not restore any higher than maximum hp)
		{
			this->m_iPlayerHealth += this->m_sConsumables.m_vConsumableList[1].m_iConsumableHealth;
			if (this->m_iPlayerHealth > this->m_iMaxHealth) //Prevents the player's health from going above player's max health
			{
				this->m_iPlayerHealth = this->m_iMaxHealth;
			}
			break;
		}
		case 3: //Index 1: Small Medal, adds 20 score to the player
		{
			this->m_iPlayerScore += this->m_sConsumables.m_vConsumableList[2].m_iConsumableScore;
			break;
		}
		case 4: //Index 1: Large Medal, adds 50 score to the player
		{
			this->m_iPlayerScore += this->m_sConsumables.m_vConsumableList[3].m_iConsumableScore;
			break;
		}
		}
	}
}