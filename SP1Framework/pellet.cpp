#include "pellet.h"

SPellet::SPellet(COORD * c, int direction, int damage, double velocity, bool friendly)
{
	this->m_dTime = 0.0;
	this->m_cLocation = *c;
	this->m_siDirection = direction;
	this->m_iDamage = damage;
	this->m_dVelocity = velocity;
	this->m_bFriendly = friendly;
	this->m_bHit = false;
	this->m_dPlayerLifespan = 0.0;
	this->m_dEnemyLifespan = 0.0;
	this->Timer.startTimer();
}
void SPellet::update()
{
	double dt = this->Timer.getElapsedTime();
	this->m_dTime += dt;
	this->m_dPlayerLifespan += dt;
	this->m_dEnemyLifespan += dt;
	if (this->m_bHit) return;
	if (this->m_dTime >= this->m_dVelocity)
	{
		switch (this->m_siDirection)
		{
		case 0:
			this->m_cLocation.X--;
			break;
		case 1:
			this->m_cLocation.X--;
			this->m_cLocation.Y++;
			break;
		case 2:
			this->m_cLocation.Y++;
			break;
		case 3:
			this->m_cLocation.X++;
			this->m_cLocation.Y++;
			break;
		case 4:
			this->m_cLocation.X++;
			break;
		case 5:
			this->m_cLocation.X++;
			this->m_cLocation.Y--;
			break;
		case 6:
			this->m_cLocation.Y--;
			break;
		case 7:
			this->m_cLocation.X--;
			this->m_cLocation.Y--;
			break;
		}
		this->m_dTime -= this->m_dVelocity;
	}
}
COORD SPellet::getRealCoords()
{
	COORD c = this->m_cLocation;
	while (c.X > ROOM_X + 2)
		c.X -= (ROOM_X + 2);
	while (c.Y > ROOM_Y + 2)
		c.Y -= (ROOM_Y + 2);
	std::swap(c.X, c.Y);
	c.X = (c.X << 2) - 1;
	c.Y = (c.Y << 1) - 1;
	return c;
}
