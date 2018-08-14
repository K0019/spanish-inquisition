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
	SGameChar * player;
	this->m_sPlayerItems.hasItem(g_bHasWeapon, player);
}
