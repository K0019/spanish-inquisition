#pragma once

#ifndef BOSSHEAD
#define BOSSHEAD
#include "Framework/timer.h"
#include "definitions.h"
#include "pellet.h"
#include "player.h"
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>

namespace Boss
{
	enum Direction
	{
		UP,
		UP_RIGHT,
		RIGHT,
		DOWN_RIGHT,
		DOWN,
		DOWN_LEFT,
		LEFT,
		UP_LEFT
	};
}

class Boss1
{
protected:
	CStopWatch Timer; // When to update
	double m_dCurrentAccurateTime;
	double m_dLastMoveTime; // Time when boss last moved, in accurateTime
	double m_dLastSwitchTime; // Time when boss last switched modes, in accurateTime
	double m_dLastAttackTime, m_dLastAttackInitiateTime; // Time when boss last attacked, in accurateTime
	double m_dNextAttackTime; // Time when boss should attack next, in accurateTime (ranged)
	double m_dDeadTime; // Time when boss reached 0 health
	std::string m_sIdentifier[4]; // String identifier for rendering boss
	WORD m_wColorMelee, m_wColorRanged; // Color of boss to render
	double m_dLocationX, m_dLocationY; // Location of boss in melee
	COORD m_dLocationCoord; // Location of boss in ranged
	double m_dDirX, m_dDirY; // Vector for direction
	double m_dVelocity; // Current velocity of boss (melee)
	bool m_abSidesHit[4]; // Memory for which sides of the boss was last hit by the player
	double m_dPlayerHitCooldown; // Invincibility for player, to avoid unfair additional damage due to bouncing
	std::bitset<5> m_bEnemyState; // Melee/Ranged, Is Attacking?, Attacking In-Line/Diagonal (for ranged attacks), Is Switching State? (Melee/Ranged)
	SGameChar * m_sPlayer; // Pointer to player location
	std::vector<SPellet> * m_pvPelletContainer; // Access to add pellets
	int m_iHP; // Health of boss

	const double m_dMoveDelay; // How long to wait between moves (ranged)
	const double m_dSwitchTimeWhenMelee, m_dSwitchTimeWhenRanged; // When to switch to other phase
	const double m_dSwitchDurationToMelee, m_dSwitchDurationToRanged; // How long does it take to switch to other phase
	const double m_dRanged1AttackDuration, m_dRanged2AttackDuration; // How long does the boss have to spend during the attack
	const double m_dMeleeAttackThreshold, m_dRanged1AttackThreshold, m_dRanged2AttackThreshold; // When during the attack will the boss strike
	const double m_dDecelerationPerSec; // How quickly to decrease velocity of boss melee attack
public:
	Boss1(SGameChar * player, std::vector<SPellet> * pelletContainer, std::string identifier[4], WORD colorMelee, WORD colorRanged, int hp, 
		double whenSwitchToMelee, double switchToMeleeDuration, double whenSwitchToRanged, double switchToRangedDuration, double ranged1AttackDuration,
		double ranged1AttackThreshold, double ranged2AttackDuration, double ranged2AttackThreshold, double meleeAttackThreshold, double deceleration,
		double moveDelay);

	void update(); // Boss update function
	void updateMovement(); // Update movement function
	void switchMode(); // Switch mode from melee to ranged and vice versa
	void rangedAttack1(); // Execute in-line ranged attack
	void rangedAttack2(); // Execute diagonal ranged attack
	void checkHit(); // Check if a pellet has hit the boss
	bool move(Boss::Direction dir); // Try to move in given direction
	COORD getRealLocation(); // Get coordinates to print out to console
	SHORT getPlayerLocationX(); // Get coordinates of player locationX relative to boss
	SHORT getPlayerLocationY(); // Get coordinates of player locationY relative to boss
	COORD getLocation(COORD c); // Get coordinates of c relative to boss
	int checkCollisionWithPlayer(); // Checks collision with player
	std::string * getIdentifier(); // Get pointer to the string identifier array
	WORD getColor(); // Get current color of boss
	bool isDying(); // Check if boss is dying
	bool isDead(); // Check if boss is dead
	bool isOverlapping(COORD c); // Check if a specified coordinate is overlapping with the boss
};

#endif // !BOSSHEAD
