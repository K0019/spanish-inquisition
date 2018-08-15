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
	for (std::vector<std::unique_ptr<Enemy>>::iterator enemy = this->m_vEnemy.begin(); enemy != this->m_vEnemy.end(); )
	{
		(*enemy)->update(&this->g_sChar);
		
		if ((*enemy)->isDead())
		{
			enemy = this->m_vEnemy.erase(enemy);
			continue;
		}
		enemy++;
	}
}