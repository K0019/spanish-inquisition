#pragma once

/* MADE BY: Kendrick */

#ifndef ENEMYHEAD
#define ENEMYHEAD
#include "Framework/timer.h"
#include "level.h"
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
	std::string m_cIdentifier[2]; // Identifier for rendering
	WORD m_cColor; // Color of enemy for rendering
	COORD m_cLocation; // Location of enemy on map, tile coordinates
	int m_iHP; // HP of enemy
	bool m_bFlashHit; // If enemy is already flashing because it is hit
	bool m_bFlashAttacking; // If enemy is already flashing because it is attacking
	double m_dFlashAttackingTime; // Time to determine whether to change flash or not
	bool m_bHit; // If enemy has been hit and m_dStunTime has not expired
	int m_iStrength; // Damage enemy deals to player
	SLevel * levelPointer; // Access to level
	bool m_bAttacked; // If enemy has attacked this attack cycle
	int m_iScoreGiven; //The amount of score the enemy gives to the player upon being killed
	int m_iEnemyID; //The index of the enemy for reference purposes

	const std::string m_sName; // Name of enemy
	const double m_dLengthOfAttack; // Length of time of attack
	const double m_dAttackTimeThreshold; // Point of time during attack at which attack strikes
	const double m_dStunDuration; // Duration this enemy should be stunned for when hit
	const double m_iMoveDuration; // Duration this enemy should be delayed by before moving again

public:
	Enemy(SLevel * levelPointer, std::string name, std::string indicator, std::string indicator2, COORD location, WORD color,  int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration, int scoreGiven, int enemyID); // Constructor

	virtual void update(SGameChar * player) =0; // Update everything about enemy
	virtual bool updateMovement(SGameChar * player) =0; // Update the movement
	double checkAttackDelayExpire(); // Update attack timings
	void updateFlashHitState(); // Get true or false depending on duration of FlashHitTime and StunDuration
	std::string * getIdentifier(); // Get the char identifier of the enemy
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
	bool move(int direction); // Move, only if location is clear of obstacles
	void scoreGiven(SGameChar * player);

	bool checkOutOfBounds(); // Check if current enemy location is clear of obstacles
	bool checkOutOfBounds(COORD c); // Check if specific location is clear of obstacles

};

class EnemyMelee : public Enemy
{
protected:
	int attackDirection; // Up Right Down Left
public:
	EnemyMelee(SLevel * levelPointer, std::string name, std::string indicator, std::string indicator2, COORD location, WORD color, int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration, int scoreGiven, int enemyID);

	void update(SGameChar * player);
	void setAttackDirection(SGameChar * player); // Target a tile to attack
	void strikeAttack(SGameChar * player); // Hit the player if player is in the tile that enemy was attacking
	bool updateMovement(SGameChar * player); // Updates enemy movement, returns true or false depending on whether the enemy should attack or not
};

class EnemyRanged : public Enemy
{
protected:
	bool m_bMobile; // Ability to shoot while moving
	double m_dShootVelocity; // Speed of pellet
	std::vector<SPellet> * m_vPelletList; // Pointer to the list of pellets, to add pellets of the enemy's
	

public:
	EnemyRanged(SLevel * levelPointer, std::vector<SPellet> * pellets, std::string name, std::string indicator, std::string indicator2, COORD location, WORD color, int HP, int damage, double moveDuration, double lengthOfAttack, double attackTimeThreshold, double stunDuration, bool isMobile, double pelletVelocity, int scoreGiven, int enemyID);

	void update(SGameChar * player);
	bool updateMovement(SGameChar * player); // Updates enemy movement, returns true or false depending on whether the enemy should attack or not
	void updateShooting(SGameChar * player); // Create an enemy pellet
};

#endif
