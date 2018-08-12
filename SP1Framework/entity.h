#pragma once

#ifndef ENTITYHEAD
#define ENTITYHEAD

#include "pellet.h"
#include "definitions.h"
#include <vector>

struct SAllEntities
{
	std::vector<SPellet> m_vPellets;

	void updatePellets();
	void checkHitPellets();
};

#endif // !ENTITYHEAD
