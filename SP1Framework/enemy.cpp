#include "enemy.h"

Enemy::Enemy(std::string& name,  char identifier, int HP, double lengthOfAttack, double attackTimeThreshold, double stunDuration)
	: m_sName(name), m_dLengthOfAttack(lengthOfAttack), m_dAttackTimeThreshold(attackTimeThreshold), m_dStunDuration(stunDuration)
{
	this->m_cIdentifier = identifier;
	this->m_iHP = HP;
}

void Enemy::update()
{
	double dt = this->Timer.getElapsedTime();

	if (this->isHit)
	{
		this->m_dStunTime -= dt;
		if (this->m_dStunTime <= 0.0)
		{
			this->isHit = false;
			this->isFlashing = false;
			if (this->m_dAttackTime > this->m_dAttackTimeThreshold)
			{
				this->m_dAttackTime = this->m_dLengthOfAttack;
			}
			else if (this->m_dAttackTime > 0)
			{
				this->m_dAttackTime += this->m_dStunTime;
			}
			else
			{
				this->m_dLastMoveTime -= this->m_dStunTime;
			}
			this->m_dStunTime = 0.0;
		}
		else
		{
			this->isFlashing = !this->isFlashing;
		}
	}
	else if ()
	{

	}
}

char Enemy::getIdentifier()
{
	return this->m_cIdentifier;
}
COORD Enemy::getLocation()
{
	return this->m_cLocation;
}
int Enemy::getHP()
{
	return this->m_iHP;
}
bool Enemy::isHit()
{
	return this->m_bHit;
}
bool Enemy::isFlashing()
{
	return this->m_bFlash;
}
bool Enemy::isDead()
{
	return (this->getHP <= 0) ? (true) : (false);
}