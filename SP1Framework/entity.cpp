#include "entity.h"

void SAllEntities::updatePellets()
{
	for (auto& pellet : this->m_vPellets)
	{
		pellet.update();
	}
}

void SAllEntities::clearPellets()
{
	this->m_vPellets.clear();
}

void SAllEntities::clearEnemies()
{
	this->m_vEnemy.clear();
}

void SAllEntities::updateEnemies()
{
	for (auto& enemy : this->m_vEnemy)
	{
		enemy->update(&this->g_sChar);
	}
}