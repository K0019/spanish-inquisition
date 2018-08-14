#include "enemy.h"

Enemy::Enemy(std::string name,  char identifier, WORD color, int HP, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration)
	: m_iMoveDuration(moveDuration), m_sName(name), m_dLengthOfAttack(lengthOfAttack), m_dAttackTimeThreshold(attackTimeThreshold), m_dStunDuration(stunDuration)
{
	this->Timer.startTimer();
	this->m_cIdentifier = identifier;
	this->m_iHP = HP;
	this->m_bFlashAttacking = false;
	this->m_bFlashHit = false;
	this->m_bHit = false;
	this->m_cColor = color;
	this->m_cLocation.X = (GRID_X >> 1) * (ROOM_X + 2) + (ROOM_X >> 1);
	this->m_cLocation.Y = 2 + (GRID_Y >> 1) * (ROOM_Y + 2) + (ROOM_Y >> 1);
	this->m_dAttackTime = 0.0;
	this->m_dDeadTime = 0.0;
	this->m_dFlashAttackingTime = 0.0;
	this->m_dLastMoveTime = this->Timer.accurateTotalTime();
	this->m_dStunTime = 0.0;
}

void Enemy::update(SGameChar * player)
{
	double dt = this->Timer.getElapsedTime();

	if (this->isDead())
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
				this->checkAttackDelayExpire();
			}
			this->m_dStunTime = 0.0;
		}
		else
		{
			checkFlashHitState();
		}
	}
	
	if (!this->isHit() && this->m_dAttackTime <= 0.0)
	{
		if (((this->m_cLocation.X == player->m_cLocation.X + 1 || this->m_cLocation.X == player->m_cLocation.X - 1) && this->m_cLocation.Y == player->m_cLocation.Y) ||
			((this->m_cLocation.Y == player->m_cLocation.Y + 1 || this->m_cLocation.Y == player->m_cLocation.Y - 1) && this->m_cLocation.X == player->m_cLocation.X))
		{
			this->m_dAttackTime = this->m_dLengthOfAttack;
			// TODO: Logic for damage
		}
		else if (this->m_dLastMoveTime + this->m_iMoveDuration < this->Timer.accurateTotalTime())
		{
			if (this->m_cLocation.X - player->m_cLocation.X == 0) // Same row
			{
				if (this->m_cLocation.Y - player->m_cLocation.Y > 0)
				{
					this->m_cLocation.Y--;
				}
				else
				{
					this->m_cLocation.Y++;
				}
			}
			else if (this->m_cLocation.Y - player->m_cLocation.Y == 0) // Same column
			{
				if (this->m_cLocation.X - player->m_cLocation.X > 0)
				{
					this->m_cLocation.X--;
				}
				else
				{
					this->m_cLocation.X++;
				}
			}
			else
			{
				if (abs(this->m_cLocation.X - player->m_cLocation.X) == abs(this->m_cLocation.Y - player->m_cLocation.Y)) // Exactly diagonal
				{
					short dir = rand() / (RAND_MAX / 2);
					if (this->m_cLocation.X - player->m_cLocation.X > 0)
					{
						if (this->m_cLocation.Y - player->m_cLocation.Y > 0)
						{
							switch (dir)
							{
							case 0:
								this->m_cLocation.Y--;
								break;
							case 1:
								this->m_cLocation.X--;
								break;
							}
						}
						else
						{
							switch (dir)
							{
							case 0:
								this->m_cLocation.X--;
								break;
							case 1:
								this->m_cLocation.Y++;
								break;
							}
						}
					}
					else
					{
						if (this->m_cLocation.Y - player->m_cLocation.Y > 0)
						{
							switch (dir)
							{
							case 0:
								this->m_cLocation.X++;
								break;
							case 1:
								this->m_cLocation.Y--;
							}
						}
						else
						{
							switch (dir)
							{
							case 0:
								this->m_cLocation.Y++;
								break;
							case 1:
								this->m_cLocation.X++;
								break;
							}
						}
					}
				}
				else
				{
					if (abs(this->m_cLocation.X - player->m_cLocation.X) > abs(this->m_cLocation.Y - player->m_cLocation.Y))
					{
						if (this->m_cLocation.X - player->m_cLocation.X > 0)
						{
							this->m_cLocation.X--;
						}
						else
						{
							this->m_cLocation.X++;
						}
					}
					else
					{
						if (this->m_cLocation.Y - player->m_cLocation.Y > 0)
						{
							this->m_cLocation.Y--;
						}
						else
						{
							this->m_cLocation.Y++;
						}
					}
				}
			}
			this->m_dLastMoveTime = this->Timer.accurateTotalTime();
		}
	}
}

void Enemy::checkAttackDelayExpire()
{
	if (this->m_dAttackTime <= 0.0)
	{
		this->m_bFlashAttacking = false;
		this->m_dAttackTime = 0.0;
	}
}

bool Enemy::checkFlashHitState()
{
	return this->m_bFlashHit = ((LONGLONG)((this->m_dStunDuration - this->m_dStunTime) / 50) % 2) ? (false) : (true);
}

char Enemy::getIdentifier()
{
	return this->m_cIdentifier;
}
COORD Enemy::getLocation()
{
	return this->m_cLocation;
}
WORD Enemy::getColor()
{
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
bool Enemy::isDead()
{
	return (this->getHP() <= 0) ? (true) : (false);
}

COORD Enemy::getRealLocation()
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