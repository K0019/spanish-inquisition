#include "entity.h"

void SAllEntities::updatePellets()
{
	for (auto& pellet : this->m_vPellets)
	{
		pellet.update();
	}
	this->checkHitPellets();
}
void SAllEntities::checkHitPellets()
{
	for (std::vector<SPellet>::iterator pellet = this->m_vPellets.begin(); pellet != this->m_vPellets.end(); )
	{
		if ((*pellet).m_bHit)
		{
			if ((*pellet).m_dTime >= 0.15)
			{
				pellet = this->m_vPellets.erase(pellet);
				continue;
			}
			pellet++;
			continue;
		}

		// Check collision with wall
		if ((*pellet).m_cLocation.X % (ROOM_X + 1) == 0 || (*pellet).m_cLocation.Y % (ROOM_Y + 1) == 0)
		{
			(*pellet).m_bHit = true;
			(*pellet).m_dTime = 0;
			continue;
		}

		// Check hit with other pellets
		/*if (pellet == this->m_vPellets.end()) break;
		for (std::vector<SPellet>::iterator otherPellet = pellet + 1; otherPellet != this->m_vPellets.end(); otherPellet++)
		{
		if ((*otherPellet).m_cLocation.X == (*pellet).m_cLocation.X && (*otherPellet).m_cLocation.Y == (*pellet).m_cLocation.Y)
		{
		(*otherPellet).m_bHit = (*pellet).m_bHit = true;
		(*otherPellet).m_dTime = (*pellet).m_dTime = 0;
		break;
		}
		}*/

		pellet++;
	}
}
