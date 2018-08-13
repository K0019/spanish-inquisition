#pragma once

#ifndef ENTITYHEAD
#define ENTITYHEAD

#include "pellet.h"
#include "definitions.h"
#include <vector>

struct SAllEntities
{
	std::vector<SPellet> m_vPellets; // Hold all pellet entitites

	void updatePellets(); // Update location of all pellets
	void checkHitPellets(); // Check if any pellet should be erased or marked for erasal
};

#endif // !ENTITYHEAD
