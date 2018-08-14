#pragma once

#ifndef ENEMYHEAD
#define ENEMYHEAD
#include "Framework/timer.h"
#include "player.h"
#include <Windows.h>
#include <string>

class Enemy
{
	CStopWatch Timer; // To keep track of time
	double m_dLastMoveTime; // Time since it last moveed
	double m_dStunTime; // Time to delay all updates by, when hit, supersedes m_dAttackTime
	double m_dAttackTime; // Time to delay all updates by, when attacking
	char m_cIdentifier; // Identifier for rendering
	COORD m_cLocation; // Location of enemy on map, tile coordinates
	int m_iHP; // HP of enemy
	bool m_bFlash; // If enemy is already flashing
	bool m_bHit; // If enemy has been hit and m_dStunTime has not expired

	const std::string m_sName; // Name of enemy
	const double m_dLengthOfAttack; // Length of time of attack
	const double m_dAttackTimeThreshold; // Point of time during attack at which attack strikes
	const double m_dStunDuration; // Duration this enemy should be stunned for when hit

public:
	Enemy(std::string& name, char indicator, int HP, double lengthOfAttack, double attackTimeThreshold, double stunDuration); // Constructor

	void update(); // Update everything about enemy
	char getIdentifier(); // Get the char identifier of the enemy
	COORD getLocation(); // Get tile coordinates of where enemy is
	int getHP(); // Get current health of enemy
	bool isHit(); // Get hit status of enemy
	bool isFlashing(); // Get flash status of enemy
	bool isDead(); // Get dead status of enemy
};

class EnemyRanged : public Enemy
{
	short m_siTimesBackedUp;

public:
	void update();
	bool updateShooting();
};

#endif
