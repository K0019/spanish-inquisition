#pragma once

#ifndef ENEMYHEAD
#define ENEMYHEAD
#include "Framework/timer.h"
#include "player.h"
#include <Windows.h>
#include <string>
#include <bitset>
#include <vector>

class Enemy
{
protected:
	CStopWatch Timer; // To keep track of time
	double m_dLastMoveTime; // Time when it last moved, in accurateTime
	double m_dStunTime; // Time to delay all updates by, when hit, supersedes m_dAttackTime
	double m_dAttackTime; // Time to delay all updates by, when attacking
	double m_dDeadTime; // Time to track when to delete this enemy when dead
	std::string m_cIdentifier; // Identifier for rendering
	WORD m_cColor; // Color of enemy for rendering
	COORD m_cLocation; // Location of enemy on map, tile coordinates
	int m_iHP; // HP of enemy
	bool m_bFlashHit; // If enemy is already flashing because it is hit
	bool m_bFlashAttacking; // If enemy is already flashing because it is attacking
	double m_dFlashAttackingTime; // Time to determine whether to change flash or not
	bool m_bHit; // If enemy has been hit and m_dStunTime has not expired
	int m_iStrength; // Damage enemy deals to player

	const std::string m_sName; // Name of enemy
	const double m_dLengthOfAttack; // Length of time of attack
	const double m_dAttackTimeThreshold; // Point of time during attack at which attack strikes
	const double m_dStunDuration; // Duration this enemy should be stunned for when hit
	const double m_iMoveDuration; // Duration this enemy should be delayed by before moving again

public:
	Enemy(std::string name, std::string indicator, COORD location, WORD color,  int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration); // Constructor

	virtual void update(SGameChar * player) =0; // Update everything about enemy
	virtual bool updateMovement(SGameChar * player) =0;
	double checkAttackDelayExpire(); // Update attack timings
	void updateFlashHitState(); // Get true or false depending on duration of FlashHitTime and StunDuration
	std::string getIdentifier(); // Get the char identifier of the enemy
	COORD getLocation(); // Get tile coordinates of where enemy is
	WORD getColor(); // Get normal color of enemy
	int getHP(); // Get current health of enemy
	bool isHit(); // Get hit status of enemy
	bool isFlashingHit(); // Get flash status of enemy if hit
	WORD getFlashColorHit(); // Get flash color of enemy if hit
	bool isFlashingAttacking(); // Get flash status of enemy if attacking
	WORD getFlashColorAttacking(); // Get flash color of enemy if attacking
	bool isDying(); // Get dying status of enemy
	bool isDead(); // Get dead status of enemy
	COORD getRealLocation(); // Get console coordinates of where enemy is
	void takeDamage(int amount); // Deal damage to this enemy
};

class EnemyMelee : public Enemy
{
public:
	EnemyMelee(std::string name, std::string indicator, COORD location, WORD color, int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration);

	void update(SGameChar * player);
	bool updateMovement(SGameChar * player); // Updates enemy movement, returns true or false depending on whether the enemy should attack or not
};

class EnemyRanged : public Enemy
{
protected:
	bool m_bMobile; // Ability to shoot while moving
	double m_dShootVelocity; // Speed of pellet
	std::vector<SPellet> * m_vPelletList; // Pointer to the list of pellets, to add pellets of the enemy's

public:
	EnemyRanged(std::vector<SPellet> * pellets, std::string name, std::string indicator, COORD location, WORD color, int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration, bool isMobile, double pelletVelocity);

	void update(SGameChar * player);
	bool updateMovement(SGameChar * player);
	void updateShooting(SGameChar * player);
};

#endif
