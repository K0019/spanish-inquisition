#pragma once

#ifndef ENEMYHEAD
#define ENEMYHEAD
#include "Framework/timer.h"
#include "player.h"
#include <Windows.h>
#include <string>
#include <bitset>

class Enemy
{
	CStopWatch Timer; // To keep track of time
	double m_dLastMoveTime; // Time when it last moved, in accurateTime
	double m_dStunTime; // Time to delay all updates by, when hit, supersedes m_dAttackTime
	double m_dAttackTime; // Time to delay all updates by, when attacking
	double m_dDeadTime; // Time to track when to delete this enemy when dead
	char m_cIdentifier; // Identifier for rendering
	WORD m_cColor; // Color of enemy for rendering
	COORD m_cLocation; // Location of enemy on map, tile coordinates
	int m_iHP; // HP of enemy
	bool m_bFlashHit; // If enemy is already flashing because it is hit
	bool m_bFlashAttacking; // If enemy is already flashing because it is attacking
	double m_dFlashAttackingTime; // Time to determine whether to change flash or not
	bool m_bHit; // If enemy has been hit and m_dStunTime has not expired

	const std::string m_sName; // Name of enemy
	const double m_dLengthOfAttack; // Length of time of attack
	const double m_dAttackTimeThreshold; // Point of time during attack at which attack strikes
	const double m_dStunDuration; // Duration this enemy should be stunned for when hit
	const double m_iMoveDuration; // Duration this enemy should be delayed by before moving again

public:
	Enemy(std::string name, char indicator, WORD color, int HP, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration); // Constructor

	void update(SGameChar * player); // Update everything about enemy
	void checkAttackDelayExpire(); // Update attack timings
	bool checkFlashHitState(); // Get true or false depending on duration of FlashHitTime and StunDuration
	char getIdentifier(); // Get the char identifier of the enemy
	COORD getLocation(); // Get tile coordinates of where enemy is
	WORD getColor(); // Get normal color of enemy
	int getHP(); // Get current health of enemy
	bool isHit(); // Get hit status of enemy
	bool isFlashingHit(); // Get flash status of enemy if hit
	WORD getFlashColorHit(); // Get flash color of enemy if hit
	bool isFlashingAttacking(); // Get flash status of enemy if attacking
	WORD getFlashColorAttacking(); // Get flash color of enemy if attacking
	bool isDead(); // Get dead status of enemy
	COORD getRealLocation(); // Get console coordinates of where enemy is
};

class EnemyRanged : public Enemy
{
	short m_siTimesBackedUp;

public:
	void update();
	bool updateShooting();
};

#endif
