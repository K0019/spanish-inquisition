#include "enemy.h"

// ---------------------------------------
// CLASS DEFINITION: Enemy [ABSTRACT]
// ---------------------------------------

Enemy::Enemy(SLevel * levelPointer, std::string name, std::string identifier, std::string identifier2, COORD location, WORD color, int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration, int scoreGiven, int enemyID)
	: m_iMoveDuration(moveDuration), m_sName(name), m_dLengthOfAttack(lengthOfAttack), m_dAttackTimeThreshold(attackTimeThreshold), m_dStunDuration(stunDuration)
{
	this->levelPointer = levelPointer;
	this->Timer.startTimer();
	this->m_cIdentifier[0] = identifier;
	this->m_cIdentifier[1] = identifier2;
	this->m_iHP = HP;
	this->m_iStrength = damage;
	this->m_bFlashAttacking = false;
	this->m_bFlashHit = false;
	this->m_bHit = false;
	this->m_cColor = color;
	this->m_cLocation.X = location.X;
	this->m_cLocation.Y = location.Y;
	this->m_dAttackTime = 0.0;
	this->m_dDeadTime = 0.0;
	this->m_dFlashAttackingTime = 0.0;
	this->m_dLastMoveTime = this->Timer.accurateTotalTime();
	this->m_dStunTime = 0.0;
	this->m_iScoreGiven = scoreGiven;
	this->m_iEnemyID = enemyID;
}

double Enemy::checkAttackDelayExpire()
{
	double remainderTime = 0.0;
	if (this->m_dAttackTime <= 0.0)
	{
		remainderTime = abs(this->m_dAttackTime);
		this->m_bFlashAttacking = false;
		this->m_dAttackTime = 0.0;
	}
	return remainderTime;
}

void Enemy::updateFlashHitState()
{
	this->m_bFlashHit = ((LONGLONG)((this->m_dStunDuration - this->m_dStunTime) / 50) % 2) ? (false) : (true);
}

std::string * Enemy::getIdentifier()
{
	return this->m_cIdentifier;
}
COORD Enemy::getLocation()
{
	return this->m_cLocation;
}
WORD Enemy::getColor()
{
	if (this->isDead())
	{
		return 0x00;
	}
	if (this->isDying())
	{
		return 0x0C;
	}
	if (this->m_bHit)
	{
		return this->getFlashColorHit();
	}
	if (this->m_dAttackTime != 0.0 && this->m_dAttackTime > this->m_dAttackTimeThreshold)
	{
		return this->getFlashColorAttacking();
	}
	return this->m_cColor;
}
int Enemy::getHP()
{
	return this->m_iHP;
}
bool Enemy::isHit()
{
	return this->m_bHit;
}
bool Enemy::isFlashingHit()
{
	return this->m_bFlashHit;
}
WORD Enemy::getFlashColorHit()
{
	byte color = (byte)((~this->m_cColor) >> 8) << 8;
	return color;
}
bool Enemy::isFlashingAttacking()
{
	return this->m_bFlashAttacking;
}
WORD Enemy::getFlashColorAttacking()
{
	byte color = (byte)(~this->m_cColor);
	return color;
}
bool Enemy::isDying()
{
	return (this->m_iHP <= 0 && this->m_dDeadTime < ENEMY_DYING_LENGTH) ? (true) : (false);
}
bool Enemy::isDead()
{
	return (this->m_iHP <= 0 && this->m_dDeadTime >= ENEMY_DYING_LENGTH) ? (true) : (false);
}

COORD Enemy::getRealLocation()
{
	COORD c = this->m_cLocation;
	while (c.X > ROOM_X + 2)
		c.X -= (ROOM_X + 2);
	while (c.Y > ROOM_Y + 2)
		c.Y -= (ROOM_Y + 2);
	std::swap(c.X, c.Y);
	c.X = (c.X << 2) - 3;
	c.Y = (c.Y << 1) - 1;
	return c;
}

void Enemy::takeDamage(int amount)
{
	this->m_iHP -= amount;
}

void Enemy::scoreGiven(SGameChar * player)
{
	switch (this->m_iEnemyID)
	{
		case 1:
		{
			player->m_iPlayerScore += this->m_iScoreGiven;
			break;
		}
		case 2:
		{
			player->m_iPlayerScore += this->m_iScoreGiven;
			break;
		}
	}
}

bool Enemy::move(int direction)
{
	switch (direction)
	{
	case 0:
		this->m_cLocation.X--;
		if (this->checkOutOfBounds())
		{
			this->m_cLocation.X++;
			return false;
		}
		return true;
	case 1:
		this->m_cLocation.X--;
		this->m_cLocation.Y++;
		if (this->checkOutOfBounds())
		{
			this->m_cLocation.X++;
			this->m_cLocation.Y--;
			return false;
		}
		return true;
	case 2:
		this->m_cLocation.Y++;
		if (this->checkOutOfBounds())
		{
			this->m_cLocation.Y--;
			return false;
		}
		return true;
	case 3:
		this->m_cLocation.X++;
		this->m_cLocation.Y++;
		if (this->checkOutOfBounds())
		{
			this->m_cLocation.X--;
			this->m_cLocation.Y--;
			return false;
		}
		return true;
	case 4:
		this->m_cLocation.X++;
		if (this->checkOutOfBounds())
		{
			this->m_cLocation.X--;
			return false;
		}
		return true;
	case 5:
		this->m_cLocation.X++;
		this->m_cLocation.Y--;
		if (this->checkOutOfBounds())
		{
			this->m_cLocation.X--;
			this->m_cLocation.Y++;
			return false;
		}
		return true;
	case 6:
		this->m_cLocation.Y--;
		if (this->checkOutOfBounds())
		{
			this->m_cLocation.Y++;
			return false;
		}
		return true;
	case 7:
		this->m_cLocation.X--;
		this->m_cLocation.Y--;
		if (this->checkOutOfBounds())
		{
			this->m_cLocation.X++;
			this->m_cLocation.Y++;
			return false;
		}
		return true;
	}
	return false;
}
bool Enemy::checkOutOfBounds()
{
	if (this->levelPointer->getTile(this->m_cLocation) != ' ')
	{
		return true;
	}
	return false;
}

// ---------------------------------------
// CLASS DEFINITION: EnemyMelee
// ---------------------------------------

EnemyMelee::EnemyMelee(SLevel * levelPointer, std::string name, std::string indicator, std::string indicator2, COORD location, WORD color, int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration, int scoreGiven, int enemyID)
	: Enemy(levelPointer, name, indicator, indicator2, location, color, HP, damage, moveDuration, lengthOfAttack, attackTimeThreshold, stunDuration, scoreGiven, enemyID)
{

}

void EnemyMelee::update(SGameChar * player)
{
	double dt = this->Timer.getElapsedTime();

	if (this->isDead())
		return;

	if (this->isDying())
	{
		this->m_dDeadTime += dt;
		return;
	}

	if (this->m_bHit)
	{
		this->m_dStunTime -= dt;
		if (this->m_dStunTime <= 0.0)
		{
			this->m_bHit = false;
			this->m_bFlashHit = false;
			if (this->m_dAttackTime > this->m_dAttackTimeThreshold)
			{
				this->m_dAttackTime = this->m_dLengthOfAttack;
			}
			/*else if (this->m_dAttackTime > 0)
			{
				this->m_dAttackTime += this->m_dStunTime;
				this->m_dLastMoveTime -= this->checkAttackDelayExpire();
			}*/
			this->m_dStunTime = 0.0;
		}
		else
		{
			this->updateFlashHitState();
		}
	}

	if (this->m_dAttackTime > 0.0)
	{
		this->m_dAttackTime -= dt;
		if (!this->m_bAttacked && this->m_dAttackTime <= this->m_dAttackTimeThreshold)
		{
			this->strikeAttack(player);
			this->m_bAttacked = true;
		}
		this->m_dLastMoveTime -= this->checkAttackDelayExpire();
		if (this->m_dAttackTime == 0.0)
		{
			this->m_bAttacked = false;
		}
	}

	if (this->updateMovement(player))
	{
		this->m_dAttackTime = this->m_dLengthOfAttack;
		this->setAttackDirection(player);
		if (this->m_dAttackTimeThreshold == 0.0)
		{
			this->strikeAttack(player);
			this->m_bAttacked = true;
		}
	}
}

void EnemyMelee::setAttackDirection(SGameChar * player)
{
	if (this->m_cLocation.X == player->m_cLocation.X + 1)
	{
		this->attackDirection = 0;
	}
	else if (this->m_cLocation.X == player->m_cLocation.X - 1)
	{
		this->attackDirection = 2;
	}
	else if (this->m_cLocation.Y == player->m_cLocation.Y + 1)
	{
		this->attackDirection = 3;
	}
	else
	{
		this->attackDirection = 1;
	}
}

void EnemyMelee::strikeAttack(SGameChar * player)
{
	switch (this->attackDirection)
	{
	case 0:
		if (this->m_cLocation.X == player->m_cLocation.X + 1 && this->m_cLocation.Y == player->m_cLocation.Y)
			player->m_iPlayerHealth -= this->m_iStrength;
		break;
	case 1:
		if (this->m_cLocation.X == player->m_cLocation.X && this->m_cLocation.Y == player->m_cLocation.Y - 1)
			player->m_iPlayerHealth -= this->m_iStrength;
		break;
	case 2:
		if (this->m_cLocation.X == player->m_cLocation.X - 1 && this->m_cLocation.Y == player->m_cLocation.Y)
			player->m_iPlayerHealth -= this->m_iStrength;
		break;
	case 3:
		if (this->m_cLocation.X == player->m_cLocation.X && this->m_cLocation.Y == player->m_cLocation.Y + 1)
			player->m_iPlayerHealth -= this->m_iStrength;
		break;
	}
	if (player->m_iPlayerScore != 0)
	{
		player->m_iPlayerScore -= 5;
	}
}

bool EnemyMelee::updateMovement(SGameChar * player)
{
	bool notMoved = false;

	if (!this->isHit() && this->m_dAttackTime <= 0.0)
	{
		if (((this->m_cLocation.X == player->m_cLocation.X + 1 || this->m_cLocation.X == player->m_cLocation.X - 1) && this->m_cLocation.Y == player->m_cLocation.Y) ||
			((this->m_cLocation.Y == player->m_cLocation.Y + 1 || this->m_cLocation.Y == player->m_cLocation.Y - 1) && this->m_cLocation.X == player->m_cLocation.X))
		{
			return true;
		}
		else if (this->m_dLastMoveTime + this->m_iMoveDuration < this->Timer.accurateTotalTime())
		{
			if (this->m_cLocation.X - player->m_cLocation.X == 0) // Same row
			{
				if (this->m_cLocation.Y - player->m_cLocation.Y > 0) // To right of player
				{
					while (true)
					{
						if (this->move(6)) break;
						if (this->move(7)) break;
						if (this->move(5)) break;
						if (this->move(4)) break;
						if (this->move(0)) break;
						notMoved = true;
						break;
					}
				}
				else // To left of player
				{
					while (true)
					{
						if (this->move(2)) break;
						if (this->move(3)) break;
						if (this->move(1)) break;
						if (this->move(0)) break;
						if (this->move(4)) break;
						notMoved = true;
						break;
					}
				}
			}
			else if (this->m_cLocation.Y - player->m_cLocation.Y == 0) // Same column
			{
				if (this->m_cLocation.X - player->m_cLocation.X > 0) // If below player
				{
					while (true)
					{
						if (this->move(0)) break;
						if (this->move(7)) break;
						if (this->move(1)) break;
						if (this->move(6)) break;
						if (this->move(2)) break;
						notMoved = true;
						break;
					}
				}
				else // If above player
				{
					while (true)
					{
						if (this->move(4)) break;
						if (this->move(3)) break;
						if (this->move(5)) break;
						if (this->move(2)) break;
						if (this->move(6)) break;
						notMoved = true;
						break;
					}
				}
			}
			else
			{
				if (abs(this->m_cLocation.X - player->m_cLocation.X) == abs(this->m_cLocation.Y - player->m_cLocation.Y)) // Exactly diagonal
				{
					if (abs(this->m_cLocation.X - player->m_cLocation.X) == 1 && abs(this->m_cLocation.Y - player->m_cLocation.Y) == 1) // Within 1 tile of player
					{
						short dir = rand() / (RAND_MAX / 2);
						if (this->m_cLocation.X - player->m_cLocation.X > 0) // Below player
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y > 0) // To right of player
							{
								while (true)
								{
									if (this->move(6)) break;
									if (this->move(0)) break;
									notMoved = true;
									break;
								}
							}
							else // To left of player
							{
								while (true)
								{
									if (this->move(0)) break;
									if (this->move(2)) break;
									notMoved = true;
									break;
								}
							}
						}
						else // Above player
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y > 0) // To right of player
							{
								while (true)
								{
									if (this->move(4)) break;
									if (this->move(6)) break;
									notMoved = true;
									break;
								}
							}
							else // To left of player
							{
								while (true)
								{
									if (this->move(2)) break;
									if (this->move(4)) break;
									notMoved = true;
									break;
								}
							}
						}
					}
					else // Not within 1 tile of player
					{
						if (this->m_cLocation.X - player->m_cLocation.X > 0) // Below player
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y > 0) // To right of player
							{
								while (true)
								{
									if (this->move(7)) break;
									if (this->move(6)) break;
									if (this->move(0)) break;
									notMoved = true;
									break;
								}
							}
							else // To left of player
							{
								while (true)
								{
									if (this->move(1)) break;
									if (this->move(0)) break;
									if (this->move(2)) break;
									notMoved = true;
									break;
								}
							}
						}
						else // Above player
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y > 0) // To right of player
							{
								while (true)
								{
									if (this->move(5)) break;
									if (this->move(4)) break;
									if (this->move(6)) break;
									notMoved = true;
									break;
								}
							}
							else // To left of player
							{
								while (true)
								{
									if (this->move(3)) break;
									if (this->move(2)) break;
									if (this->move(4)) break;
									notMoved = true;
									break;
								}
							}
						}
					}
				}
				else // Some different location
				{
					if (abs(this->m_cLocation.X - player->m_cLocation.X) > abs(this->m_cLocation.Y - player->m_cLocation.Y)) // X difference is greater than Y difference
					{
						if (this->m_cLocation.X - player->m_cLocation.X > 0) // Below player
						{
							while (true)
							{
								if (this->move(0)) break;
								if (this->m_cLocation.Y - player->m_cLocation.Y > 0) // To right of player
								{
									if (this->move(7)) break;
									if (this->move(6)) break;
								}
								else // To left of player
								{
									if (this->move(1)) break;
									if (this->move(2)) break;
								}
								notMoved = true;
								break;
							}
						}
						else // Above player
						{
							while (true)
							{
								if (this->move(4)) break;
								if (this->m_cLocation.Y - player->m_cLocation.Y > 0) // To right of player
								{
									if (this->move(5)) break;
									if (this->move(6)) break;
								}
								else // To left of player
								{
									if (this->move(3)) break;
									if (this->move(2)) break;
								}
								notMoved = true;
								break;
							}
						}
					}
					else // Y difference is greater than X difference
					{
						if (this->m_cLocation.Y - player->m_cLocation.Y > 0) // To right of player
						{
							while (true)
							{
								if (this->move(6)) break;
								if (this->m_cLocation.X - player->m_cLocation.X > 0) // Below player
								{
									if (this->move(7)) break;
									if (this->move(0)) break;
								}
								else // Above player
								{
									if (this->move(5)) break;
									if (this->move(4)) break;
								}
								notMoved = true;
								break;
							}
						}
						else // To left of player
						{
							while (true)
							{
								if (this->move(2)) break;
								if (this->m_cLocation.X - player->m_cLocation.X > 0) // Below player
								{
									if (this->move(1)) break;
									if (this->move(0)) break;
								}
								else
								{
									if (this->move(3)) break;
									if (this->move(4)) break;
								}
								notMoved = true;
								break;
							}
						}
					}
				}
			}
			if (!notMoved) this->m_dLastMoveTime = this->Timer.accurateTotalTime();
		}
	}
	return false;
}

// ---------------------------------------
// CLASS DEFINITION: EnemyRanged
// ---------------------------------------

EnemyRanged::EnemyRanged(SLevel * levelPointer, std::vector<SPellet> * pellet, std::string name, std::string indicator, std::string indicator2, COORD location, WORD color, int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration, bool isMobile, double pelletVelocity, int scoreGiven, int enemyID)
	: Enemy(levelPointer, name, indicator, indicator2, location, color, HP, damage, moveDuration, lengthOfAttack, attackTimeThreshold, stunDuration, scoreGiven, enemyID)
{
	this->m_vPelletList = pellet;
	this->m_bMobile = isMobile;
	this->m_dShootVelocity = pelletVelocity;
}

void EnemyRanged::update(SGameChar * player)
{
	double dt = this->Timer.getElapsedTime();

	if (this->isDead())
		return;

	if (this->isDying())
	{
		this->m_dDeadTime += dt;
		return;
	}

	if (this->m_bHit)
	{
		this->m_dStunTime -= dt;
		if (this->m_dStunTime <= 0.0)
		{
			this->m_bHit = false;
			this->m_bFlashHit = false;
			if (this->m_dAttackTime > this->m_dAttackTimeThreshold)
			{
				this->m_dAttackTime = this->m_dLengthOfAttack;
			}
			else if (this->m_dAttackTime > 0)
			{
				this->m_dAttackTime += this->m_dStunTime;
				this->m_dLastMoveTime -= this->checkAttackDelayExpire();
			}
			this->m_dStunTime = 0.0;
		}
		else
		{
			this->updateFlashHitState();
		}
	}

	if (this->m_dAttackTime > 0.0)
	{
		this->m_dAttackTime -= dt;
		this->m_dLastMoveTime -= this->checkAttackDelayExpire();
	}

	if (this->updateMovement(player))
	{
		this->updateShooting(player);
		this->m_dAttackTime = this->m_dLengthOfAttack;
	}
}

bool EnemyRanged::updateMovement(SGameChar * player)
{
	if (!this->m_bHit && (this->m_bMobile || this->m_dAttackTime <= 0.0))
	{
		if (!this->m_bMobile && this->m_dAttackTime <= 0.0)
		{
			if (((abs(this->m_cLocation.X - player->m_cLocation.X) > 2 && abs(this->m_cLocation.X - player->m_cLocation.X) < 7) ||
				(abs(this->m_cLocation.Y - player->m_cLocation.Y) > 2 && abs(this->m_cLocation.Y - player->m_cLocation.Y) < 7)) &&
				(this->m_cLocation.X == player->m_cLocation.X || this->m_cLocation.Y == player->m_cLocation.Y ||
					(abs(this->m_cLocation.X - player->m_cLocation.X) == abs(this->m_cLocation.Y - player->m_cLocation.Y))))
			{
				return true;
			}
		}
		
		bool notMoved = false;

		if (this->m_dLastMoveTime + this->m_iMoveDuration < this->Timer.accurateTotalTime())
		{
			if (this->m_cLocation.X == player->m_cLocation.X) // If same row
			{
				if (abs(this->m_cLocation.Y - player->m_cLocation.Y) <= 2) // If Y distance 2 or less
				{
					if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
					{
						if (!this->move(6)) notMoved = true;
					}
					else // If right of player
					{
						if (!this->move(2)) notMoved = true;
					}
				}
				else if (abs(this->m_cLocation.Y - player->m_cLocation.Y) >= 7) // If Y distance 7 or more
				{
					if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
					{
						if (!this->move(2)) notMoved = true;
					}
					else // If right of player
					{
						if (!this->move(6)) notMoved = true;
					}
				}
			}
			else if (this->m_cLocation.Y == player->m_cLocation.Y) // If same column
			{
				if (abs(this->m_cLocation.X - player->m_cLocation.X) <= 2) // If X distance 2 or less
				{
					if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
					{
						if (!this->move(0)) notMoved = true;
					}
					else // If below player
					{
						if (!this->move(4)) notMoved = true;
					}
				}
				else if (abs(this->m_cLocation.X - player->m_cLocation.X) >= 7) // If Y distance 7 or more
				{
					if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
					{
						if (!this->move(4)) notMoved = true;
					}
					else // If below player
					{
						if (!this->move(0)) notMoved = true;
					}
				}
			}
			else if (abs(this->m_cLocation.X - player->m_cLocation.X) == abs(this->m_cLocation.Y - player->m_cLocation.Y)) // If diagonal
			{
				if (abs(this->m_cLocation.X - player->m_cLocation.X) <= 2) // If distance 2 or less
				{
					if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
					{
						if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
						{
							while (true)
							{
								if (this->move(7)) break;
								if (this->move(6)) break;
								if (this->move(0)) break;
								notMoved = true;
								break;
							}
						}
						else // If right of player
						{
							while (true)
							{
								if (this->move(1)) break;
								if (this->move(0)) break;
								if (this->move(2)) break;
								notMoved = true;
								break;
							}
						}
					}
					else // If below player
					{
						if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
						{
							while (true)
							{
								if (this->move(5)) break;
								if (this->move(4)) break;
								if (this->move(6)) break;
								notMoved = true;
								break;
							}
						}
						else // If right of player
						{
							while (true)
							{
								if (this->move(3)) break;
								if (this->move(2)) break;
								if (this->move(4)) break;
								notMoved = true;
								break;
							}
						}
					}
				}
				else if (abs(this->m_cLocation.X - player->m_cLocation.X) >= 7) // If distance 7 or more
				{
					if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
					{
						this->m_cLocation.X++;
						if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
						{
							while (true)
							{
								if (this->move(3)) break;
								if (this->move(2)) break;
								if (this->move(4)) break;
								notMoved = true;
								break;
							}
						}
						else // If right of player
						{
							while (true)
							{
								if (this->move(5)) break;
								if (this->move(4)) break;
								if (this->move(6)) break;
								notMoved = true;
								break;
							}
						}
					}
					else // If below player
					{
						if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
						{
							while (true)
							{
								if (this->move(1)) break;
								if (this->move(0)) break;
								if (this->move(2)) break;
								notMoved = true;
								break;
							}
						}
						else // If right of player
						{
							while (true)
							{
								if (this->move(7)) break;
								if (this->move(6)) break;
								if (this->move(0)) break;
								notMoved = true;
								break;
							}
						}
					}
				}
			}
			else { // Any other location
				if (abs(this->m_cLocation.X - player->m_cLocation.X) == 1) // If next to row
				{
					if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
					{
						if (abs(this->m_cLocation.Y - player->m_cLocation.Y) == 2) // If in special location
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								while (true)
								{
									if (this->move(5)) break;
									if (this->move(6)) break;
									if (this->move(7)) break;
									notMoved = true;
									break;
								}
							}
							else // If right of player
							{
								while (true)
								{
									if (this->move(3)) break;
									if (this->move(2)) break;
									if (this->move(1)) break;
									notMoved = true;
									break;
								}
							}
						}
						else if (abs(this->m_cLocation.Y - player->m_cLocation.Y) == 3) // If 3 Y away from player
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								while (true)
								{
									if (this->move(4)) break;
									if (this->move(5)) break;
									notMoved = true;
									break;
								}
							}
							else // If right of player
							{
								while (true)
								{
									if (this->move(4)) break;
									if (this->move(3)) break;
									notMoved = true;
									break;
								}
							}
						}
						else // Any other distance
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								while (true)
								{
									if (this->move(4)) break;
									if (this->move(3)) break;
									if (this->move(5)) break;
									notMoved = true;
									break;
								}
							}
							else // If right of player
							{
								while (true)
								{
									if (this->move(4)) break;
									if (this->move(5)) break;
									if (this->move(3)) break;
									notMoved = true;
									break;
								}
							}
						}
					}
					else // If below player
					{
						if (abs(this->m_cLocation.Y - player->m_cLocation.Y) == 2) // If in special location
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								while (true)
								{
									if (this->move(7)) break;
									if (this->move(6)) break;
									if (this->move(5)) break;
									notMoved = true;
									break;
								}
							}
							else // If right of player
							{
								while (true)
								{
									if (this->move(1)) break;
									if (this->move(2)) break;
									if (this->move(3)) break;
									notMoved = true;
									break;
								}
							}
						}
						else if (abs(this->m_cLocation.Y - player->m_cLocation.Y) == 3) // If 3 Y away from player
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								while (true)
								{
									if (this->move(0)) break;
									if (this->move(7)) break;
									notMoved = true;
									break;
								}
							}
							else // If right of player
							{
								while (true)
								{
									if (this->move(0)) break;
									if (this->move(1)) break;
									notMoved = true;
									break;
								}
							}
						}
						else // Any other location
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								while (true)
								{
									if (this->move(0)) break;
									if (this->move(1)) break;
									if (this->move(7)) break;
									notMoved = true;
									break;
								}
							}
							else // If right of player
							{
								while (true)
								{
									if (this->move(0)) break;
									if (this->move(7)) break;
									if (this->move(1)) break;
									notMoved = true;
									break;
								}
							}
						}
					}
				}
				else if (abs(this->m_cLocation.Y - player->m_cLocation.Y) == 1) // If next to column
				{
					if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
					{
						if (abs(this->m_cLocation.X - player->m_cLocation.X) == 2) // If in special location
						{
							if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
							{
								while (true)
								{
									if (this->move(1)) break;
									if (this->move(0)) break;
									if (this->move(7)) break;
									notMoved = true;
									break;
								}
							}
							else // If below player
							{
								while (true)
								{
									if (this->move(3)) break;
									if (this->move(4)) break;
									if (this->move(5)) break;
									notMoved = true;
									break;
								}
							}
						}
						else if (abs(this->m_cLocation.X - player->m_cLocation.X) == 3) // If 3 X away from player
						{
							if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
							{
								while (true)
								{
									if (this->move(2)) break;
									if (this->move(1)) break;
									notMoved = true;
									break;
								}
							}
							else // If below player
							{
								while (true)
								{
									if (this->move(2)) break;
									if (this->move(3)) break;
									notMoved = true;
									break;
								}
							}
						}
						else // Any other distance
						{
							if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
							{
								while (true)
								{
									if (this->move(2)) break;
									if (this->move(3)) break;
									if (this->move(1)) break;
									notMoved = true;
									break;
								}
							}
							else // If below player
							{
								while (true)
								{
									if (this->move(2)) break;
									if (this->move(1)) break;
									if (this->move(3)) break;
									notMoved = true;
									break;
								}
							}
						}
					}
					else // If right of player
					{
						if (abs(this->m_cLocation.X - player->m_cLocation.X) == 2) // If in special location
						{
							if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
							{
								while (true)
								{
									if (this->move(7)) break;
									if (this->move(0)) break;
									if (this->move(1)) break;
									notMoved = true;
									break;
								}
							}
							else // If below player
							{
								while (true)
								{
									if (this->move(5)) break;
									if (this->move(4)) break;
									if (this->move(3)) break;
									notMoved = true;
									break;
								}
							}
						}
						else if (abs(this->m_cLocation.X - player->m_cLocation.X) == 3) // If 3 X away from player
						{
							if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
							{
								while (true)
								{
									if (this->move(6)) break;
									if (this->move(7)) break;
									notMoved = true;
									break;
								}
							}
							else // If below player
							{
								while (true)
								{
									if (this->move(6)) break;
									if (this->move(5)) break;
									notMoved = true;
									break;
								}
							}
						}
						else // Any other distance
						{
							if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
							{
								while (true)
								{
									if (this->move(6)) break;
									if (this->move(5)) break;
									if (this->move(7)) break;
									notMoved = true;
									break;
								}
							}
							else // If below player
							{
								while (true)
								{
									if (this->move(6)) break;
									if (this->move(7)) break;
									if (this->move(5)) break;
									notMoved = true;
									break;
								}
							}
						}
					}
				}
				else
				{
					if (abs(abs(this->m_cLocation.X - player->m_cLocation.X) - abs(this->m_cLocation.Y - player->m_cLocation.Y)) == 2) // If next to diagonal
					{
						if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								if (abs(this->m_cLocation.X - player->m_cLocation.X) > abs(this->m_cLocation.Y - player->m_cLocation.Y)) // If X difference is more than Y difference
								{
									while (true)
									{
										if (this->move(5)) break;
										if (this->move(2)) break;
										notMoved = true;
										break;
									}
								}
								else // If Y difference is more than X difference
								{
									while (true)
									{
										if (this->move(1)) break;
										if (this->move(4)) break;
										notMoved = true;
										break;
									}
								}
							}
							else // If right of player
							{
								if (abs(this->m_cLocation.X - player->m_cLocation.X) > abs(this->m_cLocation.Y - player->m_cLocation.Y))// If X difference is more than Y difference
								{
									while (true)
									{
										if (this->move(3)) break;
										if (this->move(0)) break;
										notMoved = true;
										break;
									}
								}
								else // If Y difference is more than X difference
								{
									while (true)
									{
										if (this->move(7)) break;
										if (this->move(2)) break;
										notMoved = true;
										break;
									}
								}
							}
						}
						else // If below player
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								if (abs(this->m_cLocation.X - player->m_cLocation.X) > abs(this->m_cLocation.Y - player->m_cLocation.Y)) // If X difference is more than Y difference
								{
									while (true)
									{
										if (this->move(7)) break;
										if (this->move(4)) break;
										notMoved = true;
										break;
									}
								}
								else // If Y difference is more than X difference
								{
									while (true)
									{
										if (this->move(3)) break;
										if (this->move(6)) break;
										notMoved = true;
										break;
									}
								}
							}
							else // If right of player
							{
								if (abs(this->m_cLocation.X - player->m_cLocation.X) > abs(this->m_cLocation.Y - player->m_cLocation.Y)) // If X difference is more than Y difference
								{
									while (true)
									{
										if (this->move(1)) break;
										if (this->move(6)) break;
										notMoved = true;
										break;
									}
								}
								else // If Y difference is more than X difference
								{
									while (true)
									{
										if (this->move(5)) break;
										if (this->move(0)) break;
										notMoved = true;
										break;
									}
								}
							}
						}
					}
					else // Any other location
					{
						if (abs(this->m_cLocation.X - player->m_cLocation.X) > abs(this->m_cLocation.Y - player->m_cLocation.Y)) // If X difference is more than Y difference
						{
							if (this->m_cLocation.Y - player->m_cLocation.Y < 0) // If left of player
							{
								while (true)
								{
									if (abs(this->m_cLocation.X - player->m_cLocation.X) >= 7)
										if (this->move(1)) break;
									if (this->move(2)) break;
									if (abs(this->m_cLocation.X - player->m_cLocation.X) < 7)
										if (this->move(3)) break;
									if (this->move(1)) break;
									notMoved = true;
									break;
								}
							}
							else // If right of player
							{
								while (true)
								{
									if (abs(this->m_cLocation.X - player->m_cLocation.X) >= 7)
										if (this->move(7)) break;
									if (this->move(6)) break;
									if (abs(this->m_cLocation.X - player->m_cLocation.X) < 7)
										if (this->move(5)) break;
									if (this->move(7)) break;
									notMoved = true;
									break;
								}
							}
						}
						else // If Y difference is more than X difference
						{
							if (this->m_cLocation.X - player->m_cLocation.X < 0) // If above player
							{
								while (true)
								{
									if (abs(this->m_cLocation.Y - player->m_cLocation.Y) >= 7)
										if (this->move(3)) break;
									if (this->move(4)) break;
									if (abs(this->m_cLocation.Y - player->m_cLocation.Y) < 7)
										if (this->move(5)) break;
									if (this->move(3)) break;
									notMoved = true;
									break;
								}
							}
							else // If below player
							{
								while (true)
								{
									if (abs(this->m_cLocation.Y - player->m_cLocation.Y) >= 7)
										if (this->move(7)) break;
									if (this->move(0)) break;
									if (abs(this->m_cLocation.Y - player->m_cLocation.Y) < 7)
										if (this->move(1)) break;
									if (this->move(7)) break;
									notMoved = true;
									break;
								}
							}
						}
					}
				}
			}
			if (!notMoved) this->m_dLastMoveTime = this->Timer.accurateTotalTime();
		}

		if (!this->m_bMobile && this->m_dAttackTime <= 0.0 && notMoved)
		{
			return true;
		}

		if (this->m_bMobile && this->m_dAttackTime <= 0.0)
		{
			return true;
		}
	}
	return false;
}

void EnemyRanged::updateShooting(SGameChar * player)
{
	if (this->m_cLocation.X == player->m_cLocation.X)
	{
		if (this->m_cLocation.Y - player->m_cLocation.Y < 0)
		{
			COORD c;
			c.X = this->m_cLocation.X;
			c.Y = this->m_cLocation.Y + 1;
			this->m_vPelletList->push_back(SPellet(&c, 2, this->m_iStrength, this->m_dShootVelocity, false));
		}
		else
		{
			COORD c;
			c.X = this->m_cLocation.X;
			c.Y = this->m_cLocation.Y - 1;
			this->m_vPelletList->push_back(SPellet(&c, 6, this->m_iStrength, this->m_dShootVelocity, false));
		}
	}
	else if (this->m_cLocation.Y == player->m_cLocation.Y)
	{
		if (this->m_cLocation.X - player->m_cLocation.X < 0)
		{
			COORD c;
			c.X = this->m_cLocation.X + 1;
			c.Y = this->m_cLocation.Y;
			this->m_vPelletList->push_back(SPellet(&c, 4, this->m_iStrength, this->m_dShootVelocity, false));
		}
		else
		{
			COORD c;
			c.X = this->m_cLocation.X - 1;
			c.Y = this->m_cLocation.Y;
			this->m_vPelletList->push_back(SPellet(&c, 0, this->m_iStrength, this->m_dShootVelocity, false));
		}
	}
	else
	{
		if (this->m_cLocation.X < player->m_cLocation.X)
		{
			if (this->m_cLocation.Y - player->m_cLocation.Y < 0)
			{
				COORD c;
				c.X = this->m_cLocation.X + 1;
				c.Y = this->m_cLocation.Y + 1;
				this->m_vPelletList->push_back(SPellet(&c, 3, this->m_iStrength, this->m_dShootVelocity, false));
			}
			else
			{
				COORD c;
				c.X = this->m_cLocation.X + 1;
				c.Y = this->m_cLocation.Y - 1;
				this->m_vPelletList->push_back(SPellet(&c, 5, this->m_iStrength, this->m_dShootVelocity, false));
			}
		}
		else
		{
			if (this->m_cLocation.Y - player->m_cLocation.Y < 0)
			{
				COORD c;
				c.X = this->m_cLocation.X - 1;
				c.Y = this->m_cLocation.Y + 1;
				this->m_vPelletList->push_back(SPellet(&c, 1, this->m_iStrength, this->m_dShootVelocity, false));
			}
			else
			{
				COORD c;
				c.X = this->m_cLocation.X - 1;
				c.Y = this->m_cLocation.Y - 1;
				this->m_vPelletList->push_back(SPellet(&c, 7, this->m_iStrength, this->m_dShootVelocity, false));
			}
		}
	}
}