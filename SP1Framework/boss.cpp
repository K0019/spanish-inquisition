#include "boss.h"

Boss1::Boss1(SGameChar * player, std::vector<SPellet> * pelletContainer, std::string identifier[4], WORD colorMelee, WORD colorRanged, int hp, double whenSwitchToMelee, double switchToMeleeDuration, double whenSwitchToRanged, double switchToRangedDuration, double ranged1AttackDuration, double ranged1AttackThreshold, double ranged2AttackDuration, double ranged2AttackThreshold, double meleeAttackThreshold, double deceleration, double moveDelay)
	: m_dSwitchTimeWhenMelee(whenSwitchToRanged), m_dSwitchTimeWhenRanged(whenSwitchToMelee), m_dSwitchDurationToMelee(switchToMeleeDuration), m_dSwitchDurationToRanged(switchToRangedDuration), m_dRanged1AttackDuration(ranged1AttackDuration), m_dRanged1AttackThreshold(ranged1AttackThreshold), m_dRanged2AttackDuration(ranged2AttackDuration), m_dRanged2AttackThreshold(ranged2AttackThreshold), m_dMeleeAttackThreshold(meleeAttackThreshold), m_dDecelerationPerSec(deceleration), m_dMoveDelay(moveDelay)
{
	this->Timer.startTimer();
	this->m_sPlayer = player;
	this->m_pvPelletContainer = pelletContainer;
	this->m_sIdentifier[0] = identifier[0];
	this->m_sIdentifier[1] = identifier[1];
	this->m_sIdentifier[2] = identifier[2];
	this->m_sIdentifier[3] = identifier[3];
	this->m_wColorMelee = colorMelee;
	this->m_wColorRanged = colorRanged;
	this->m_dLocationX = (ROOM_X >> 1);
	this->m_dLocationY = (ROOM_Y >> 1);
	this->m_dLocationCoord = { ROOM_X >> 1, ROOM_Y >> 1 };

	this->m_dLastAttackInitiateTime = 0.0;
	this->m_dLastAttackTime = 0.0;
	this->m_dLastMoveTime = 0.0;
	this->m_dLastSwitchTime = 0.0;
	this->m_dNextAttackTime = 0.0;
	this->m_iHP = hp;
}

void Boss1::update()
{
	double dt = this->Timer.getElapsedTime();
	this->m_dCurrentAccurateTime = this->Timer.accurateTotalTime();

	if (this->isDying())
		return;
	this->checkHit(); // Check for hit with pellet

	// If currently switching
	if (this->m_bEnemyState[3])
	{
		if (this->m_dCurrentAccurateTime < this->m_dLastSwitchTime) // If enemy hasn't finished switching
		{
			return;
		}
		else // If enemy has finished switching
		{
			dt -= this->m_dCurrentAccurateTime - this->m_dLastSwitchTime;
			if (this->m_bEnemyState[0])
			{
				this->m_dLocationCoord.X = (SHORT)round(this->m_dLocationX);
				this->m_dLocationCoord.Y = (SHORT)round(this->m_dLocationY);
			}
			else
			{
				this->m_dLocationX = (double)this->m_dLocationCoord.X;
				this->m_dLocationY = (double)this->m_dLocationCoord.Y;
			}
			this->m_dLastAttackInitiateTime = this->m_dLastAttackTime = this->m_dLastMoveTime = this->m_dCurrentAccurateTime;
			this->m_dNextAttackTime = this->m_dCurrentAccurateTime + ((double)(rand() / ((RAND_MAX + 75) / 1000))) / 1000.0;
			this->m_bEnemyState.flip(0);
			this->m_bEnemyState.flip(3);
			if (dt < 0.0) return;
		}
	}

	// If currently attacking
	else if (this->m_bEnemyState[1])
	{
		if (this->m_bEnemyState[0]) // If melee
		{
			double newVelocity = this->m_dVelocity + this->m_dDecelerationPerSec * dt;
			double distanceMoved = this->m_dVelocity * dt + 0.5 * this->m_dDecelerationPerSec * pow(dt, 2);
			if (newVelocity < 0.0)
			{
				double negativeTime = dt - (-this->m_dVelocity / this->m_dDecelerationPerSec);
				distanceMoved += 0.5 * (-this->m_dDecelerationPerSec) * pow(negativeTime, 2);
				this->m_dVelocity = 0.0;
				this->m_bEnemyState.flip(1);
				this->m_dNextAttackTime = this->m_dCurrentAccurateTime + this->m_dMeleeAttackThreshold;
			}
			else
			{
				this->m_dVelocity = newVelocity;
			}
			this->m_dLocationX += distanceMoved * m_dDirX;
			this->m_dLocationY += distanceMoved * m_dDirY;

			while (true)
			{
				if (this->m_dLocationX - 1 < 0 || this->m_dLocationX + 0.75 >= ROOM_X ||
					this->m_dLocationY - 1 < 0 || this->m_dLocationY + 0.75 >= ROOM_Y)
				{
					if (this->m_dLocationX - 1 < 0)
					{
						this->m_dLocationX -= 2 * (this->m_dLocationX - 1);
						this->m_dDirX *= -1;
					}
					else if (this->m_dLocationX + 1 >= ROOM_X)
					{
						this->m_dLocationX -= 2 * (this->m_dLocationX + 1 - ROOM_X);
						this->m_dDirX *= -1;
					}
					if (this->m_dLocationY - 1 < 0)
					{
						this->m_dLocationY -= 2 * (this->m_dLocationY - 1);
						this->m_dDirY *= -1;
					}
					else if (this->m_dLocationY + 1 >= ROOM_Y)
					{
						this->m_dLocationY -= 2 * (this->m_dLocationY + 1 - ROOM_Y);
						this->m_dDirY *= -1;
					}
					this->checkCollisionWithPlayer();
					continue;
				}
				int code = this->checkCollisionWithPlayer();
				if (code == 0)
					break;
				if (this->m_dCurrentAccurateTime >= this->m_dPlayerHitCooldown)
				{
					this->m_sPlayer->m_iPlayerHealth -= 3;
					this->m_dPlayerHitCooldown = this->m_dCurrentAccurateTime + 0.4;
				}
				switch (code)
				{
				case 1:
				case 2:
					this->m_dDirX *= -1;
					break;
				case 3:
				case 4:
					this->m_dDirY *= -1;
					break;
				case 5:
				case 6:
				case 7:
				case 8:
					this->m_dDirX *= -1;
					this->m_dDirY *= -1;
					break;
				}
				/*switch (code)
				{
				case 1:
					this->m_dLocationX += 2 * (this->getPlayerLocationX() - this->m_dLocationX);
					break;
				case 2:
					this->m_dLocationX -= 2 * (this->m_dLocationX - this->getPlayerLocationX());
					break;
				case 3:
					this->m_dLocationY += 2 * (this->getPlayerLocationY() - this->m_dLocationY);
					break;
				case 4:
					this->m_dLocationY += 2 * (this->m_dLocationY - this->getPlayerLocationY());
					break;
				case 5:
					this->m_dLocationX += 2 * (this->getPlayerLocationX() - this->m_dLocationX);
					this->m_dLocationY += 2 * (this->getPlayerLocationY() - this->m_dLocationY);
					break;
				case 6:
					this->m_dLocationX += 2 * (this->getPlayerLocationX() - this->m_dLocationX);
					this->m_dLocationY -= 2 * (this->m_dLocationY - this->getPlayerLocationY());
					break;
				case 7:
					this->m_dLocationX -= 2 * (this->m_dLocationX - this->getPlayerLocationX());
					this->m_dLocationY += 2 * (this->getPlayerLocationY() - this->m_dLocationY);
					break;
				case 8:
					this->m_dLocationX -= 2 * (this->m_dLocationX - this->getPlayerLocationX());
					this->m_dLocationY -= 2 * (this->m_dLocationY - this->getPlayerLocationY());
					break;
				}*/
			}
		}
		else // If ranged
		{
			if (!this->m_bEnemyState[4] && this->m_dCurrentAccurateTime >= this->m_dLastAttackInitiateTime + ((this->m_bEnemyState[2]) ? (this->m_dRanged1AttackThreshold) : (this->m_dRanged2AttackThreshold)))
			{
				if (this->m_bEnemyState[2])
					this->rangedAttack1();
				else
					this->rangedAttack2();
				this->m_bEnemyState.flip(4);
				return;
			}
			else if (this->m_dCurrentAccurateTime < this->m_dLastAttackTime) // If attack hasn't expired
			{
				return;
			}
			else // If enemy has finished attacking
			{
				dt -= this->m_dCurrentAccurateTime - this->m_dLastAttackTime;
				this->m_bEnemyState.flip(1);
				this->m_bEnemyState.flip(4);
				if (dt < 0.0) return;
			}
		}

		this->checkHit(); // Check hit for pellet
	}

	// Check if enemy should switch modes
	if (this->m_bEnemyState[0]) // Melee
	{
		if (!this->m_bEnemyState[1] && this->m_dCurrentAccurateTime - this->m_dLastSwitchTime >= this->m_dSwitchTimeWhenMelee)
		{
			this->switchMode();
			return;
		}
	}
	else // Ranged
	{
		if (!this->m_bEnemyState[1] && this->m_dCurrentAccurateTime - this->m_dLastSwitchTime >= this->m_dSwitchTimeWhenRanged)
		{
			this->switchMode();
			return;
		}
	}

	// Determine what the boss should do
	if (this->m_bEnemyState[0]) // If melee
	{
		if (!this->m_bEnemyState[1] && this->m_dCurrentAccurateTime >= this->m_dNextAttackTime)
		{
			double hypotenuse = sqrt(pow(this->getPlayerLocationX() - this->m_dLocationX, 2) + pow(this->getPlayerLocationY() - this->m_dLocationY, 2));
			this->m_dDirX = (this->getPlayerLocationX() - this->m_dLocationX) / hypotenuse;
			this->m_dDirY = (this->getPlayerLocationY() - this->m_dLocationY) / hypotenuse;
			this->m_dVelocity = 16.0;

			this->m_bEnemyState.flip(1);
		}
	}
	else // If ranged
	{
		//if (this->m_dCurrentAccurateTime >= this->m_dLastMoveTime)
		//{
		//	if (rand() / (RAND_MAX / 100) < 35) // Attack chance
		//	{

		//	}
		//	else // Move chance
		//	{

		//	}
		//}

		if (this->m_dCurrentAccurateTime >= this->m_dNextAttackTime) // If boss should attack
		{
			if (rand() / (RAND_MAX / 2))
				this->m_bEnemyState.flip(2);
			this->m_dLastAttackInitiateTime = this->m_dCurrentAccurateTime;
			this->m_dNextAttackTime = this->m_dCurrentAccurateTime + ((this->m_bEnemyState[2]) ? (this->m_dRanged1AttackDuration) : (this->m_dRanged2AttackDuration)) + (((double)(rand() / ((RAND_MAX + 75) / 1000))) / 1000.0);
			this->m_dLastMoveTime = this->m_dLastAttackTime = this->m_dCurrentAccurateTime + ((this->m_bEnemyState[2]) ? (this->m_dRanged1AttackDuration) : (this->m_dRanged2AttackDuration));
			this->m_bEnemyState.flip(1);
		}
		else if (!this->m_bEnemyState[1] && this->m_dCurrentAccurateTime - this->m_dLastMoveTime >= this->m_dMoveDelay) // If boss should move
		{
			this->updateMovement();
			this->m_dLastMoveTime += this->m_dMoveDelay;
		}
	}
}

void Boss1::switchMode()
{
	if (this->m_bEnemyState[0]) // If currently melee
	{
		m_dLastSwitchTime = this->m_dCurrentAccurateTime + this->m_dSwitchDurationToRanged;
	}
	else // If currently ranged
	{
		m_dLastSwitchTime = this->m_dCurrentAccurateTime + this->m_dSwitchDurationToMelee;
	}
	this->m_bEnemyState.flip(3); // Indicate that enemy is switching
}

COORD Boss1::getRealLocation()
{
	if (this->m_bEnemyState[0]) // If currently melee
	{
		return { (SHORT)(this->m_dLocationY * 4.0 + 1.0), (SHORT)(this->m_dLocationX * 2.0 + 1.0) };
	}
	else // If currently ranged
	{
		COORD c = this->m_dLocationCoord;
		std::swap(c.X, c.Y);
		c.X = (c.X << 2) + 1;
		c.Y = (c.Y << 1) + 1;
		return c;
	}
}
SHORT Boss1::getPlayerLocationX()
{
	SHORT x = this->m_sPlayer->m_cLocation.X;
	while (x > ROOM_X + 2)
		x -= (ROOM_X + 2);
	return x - 2;
}
SHORT Boss1::getPlayerLocationY()
{
	SHORT y = this->m_sPlayer->m_cLocation.Y;
	while (y > ROOM_Y + 2)
		y -= (ROOM_Y + 2);
	return y - 2;
}
COORD Boss1::getLocation(COORD c)
{
	while (c.X > ROOM_X + 2)
		c.X -= (ROOM_X + 2);
	while (c.Y > ROOM_Y + 2)
		c.Y -= (ROOM_Y + 2);
	c.X -= 2;
	c.Y -= 2;
	return c;
}
std::string * Boss1::getIdentifier()
{
	return this->m_sIdentifier;
}
WORD Boss1::getColor()
{
	if (this->isDying())
	{
		if ((unsigned int)(this->Timer.accurateTotalTime() * 1000) % 250 < 100) // If it should be flashing
		{
			return 0xf0;
		}
		else
		{
			return 0x0f;
		}
	}
	else if (this->m_bEnemyState[3]) // If switching
	{
		if ((unsigned int)(this->Timer.accurateTotalTime() * 1000) % 200 < 50) // If it should be flashing
		{
			WORD currentTextColor = ((this->m_bEnemyState[0]) ? (this->m_wColorMelee) : (this->m_wColorRanged) << 4) >> 4;
			return 0x20 + currentTextColor;
		}
		else
		{
			return (this->m_bEnemyState[0]) ? (this->m_wColorMelee) : (this->m_wColorRanged);
		}
	}
	else if (this->m_bEnemyState[1]) // If attacking
	{
		if (this->m_bEnemyState[0]) // If melee
		{
			return 0xbc;
		}
		else // If ranged
		{
			if (this->m_bEnemyState[2]) // If type of attack is in-line
			{
				if (this->m_dCurrentAccurateTime - this->m_dLastAttackInitiateTime < this->m_dRanged1AttackThreshold) // If about to strike
				{
					return 0xde;
				}
				else // If already striked
				{
					return 0x0e;
				}
			}
			else // If type of attack is diagonal
			{
				if (this->m_dCurrentAccurateTime - this->m_dLastAttackInitiateTime < this->m_dRanged2AttackThreshold) // If about to strike
				{
					return 0xbe;
				}
				else // If already striked
				{
					return 0x0e;
				}
			}
		}
	}
	// Anything else
	return (this->m_bEnemyState[0]) ? (this->m_wColorMelee) : (this->m_wColorRanged);
}

bool Boss1::move(Boss::Direction dir)
{
	switch (dir)
	{
	case Boss::UP:
		if (((this->m_dLocationCoord.X - 2 == this->getPlayerLocationX() || this->m_dLocationCoord.X - 1 == this->getPlayerLocationX()) &&
			(this->m_dLocationCoord.Y == this->getPlayerLocationY() || this->m_dLocationCoord.Y - 1 == this->getPlayerLocationY()))
			|| (this->m_dLocationCoord.X - 2 < 0))
		{
			return false;
		}
		this->m_dLocationCoord.X--;
		return true;
	case Boss::UP_RIGHT:
		if (((this->m_dLocationCoord.X - 2 == this->getPlayerLocationX() || this->m_dLocationCoord.X - 1 == this->getPlayerLocationX()) &&
			(this->m_dLocationCoord.Y + 1 == this->getPlayerLocationY() || this->m_dLocationCoord.Y == this->getPlayerLocationY())) ||
			(this->m_dLocationCoord.X - 2 < 0 || this->m_dLocationCoord.Y + 1 >= ROOM_Y))
		{
			return false;
		}
		this->m_dLocationCoord.X--;
		this->m_dLocationCoord.Y++;
		return true;
	case Boss::RIGHT:
		if (((this->m_dLocationCoord.X - 1 == this->getPlayerLocationX() || this->m_dLocationCoord.X == this->getPlayerLocationX()) &&
			(this->m_dLocationCoord.Y + 1 == this->getPlayerLocationY() || this->m_dLocationCoord.Y == this->getPlayerLocationY()))
			|| (this->m_dLocationCoord.Y + 1 >= ROOM_Y))
		{
			return false;
		}
		this->m_dLocationCoord.Y++;
		return true;
	case Boss::DOWN_RIGHT:
		if (((this->m_dLocationCoord.X == this->getPlayerLocationX() || this->m_dLocationCoord.X + 1 == this->getPlayerLocationX()) &&
			(this->m_dLocationCoord.Y + 1 == this->getPlayerLocationY() || this->m_dLocationCoord.Y == this->getPlayerLocationY())) ||
			(this->m_dLocationCoord.X + 1 >= ROOM_X || this->m_dLocationCoord.Y + 1 >= ROOM_Y))
		{
			return false;
		}
		this->m_dLocationCoord.X++;
		this->m_dLocationCoord.Y++;
		return true;
	case Boss::DOWN:
		if (((this->m_dLocationCoord.X == this->getPlayerLocationX() || this->m_dLocationCoord.X + 1 == this->getPlayerLocationX()) &&
			(this->m_dLocationCoord.Y == this->getPlayerLocationY() || this->m_dLocationCoord.Y - 1 == this->getPlayerLocationY())) ||
			(this->m_dLocationCoord.X + 1 >= ROOM_X))
		{
			return false;
		}
		this->m_dLocationCoord.X++;
		return true;
	case Boss::DOWN_LEFT:
		if (((this->m_dLocationCoord.X == this->getPlayerLocationX() || this->m_dLocationCoord.X + 1 == this->getPlayerLocationX()) &&
			(this->m_dLocationCoord.Y - 1 == this->getPlayerLocationY() || this->m_dLocationCoord.Y - 2 == this->getPlayerLocationY())) ||
			(this->m_dLocationCoord.X + 1 >= ROOM_X || this->m_dLocationCoord.Y - 2 < 0))
		{
			return false;
		}
		this->m_dLocationCoord.X++;
		this->m_dLocationCoord.Y--;
		return true;
	case Boss::LEFT:
		if (((this->m_dLocationCoord.X - 1 == this->getPlayerLocationX() || this->m_dLocationCoord.X == this->getPlayerLocationX()) &&
			(this->m_dLocationCoord.Y - 1 == this->getPlayerLocationY() || this->m_dLocationCoord.Y - 2 == this->getPlayerLocationY())) ||
			(this->m_dLocationCoord.Y - 2 < 0))
		{
			return false;
		}
		this->m_dLocationCoord.Y--;
		return true;
	case Boss::UP_LEFT:
		if (((this->m_dLocationCoord.X - 2 == this->getPlayerLocationX() || this->m_dLocationCoord.X - 1 == this->getPlayerLocationX()) &&
			(this->m_dLocationCoord.Y - 1 == this->getPlayerLocationY() || this->m_dLocationCoord.Y - 2 == this->getPlayerLocationY())) ||
			(this->m_dLocationCoord.X - 2 < 0 || this->m_dLocationCoord.Y - 2 < 0))
		{
			return false;
		}
		this->m_dLocationCoord.X--;
		this->m_dLocationCoord.Y--;
		return true;
	}
}

void Boss1::updateMovement()
{
	std::vector<Boss::Direction> directions = { Boss::UP, Boss::UP_RIGHT, Boss::RIGHT, Boss::DOWN_RIGHT, Boss::DOWN, Boss::DOWN_LEFT, Boss::LEFT, Boss::UP_LEFT };
	std::random_shuffle(directions.begin(), directions.end());

	for (auto& dir : directions)
	{
		if (this->move(dir)) return;
	}
}

void Boss1::rangedAttack1()
{
	COORD pelletsLocation[8] = { 
		{ this->m_dLocationCoord.X - 1, this->m_dLocationCoord.Y + 1 }, // Upper rightmost
		{ this->m_dLocationCoord.X, this->m_dLocationCoord.Y + 1 }, // Lower rightmost
		{ this->m_dLocationCoord.X + 1, this->m_dLocationCoord.Y }, // Below right
		{ this->m_dLocationCoord.X + 1, this->m_dLocationCoord.Y - 1 }, // Below left
		{ this->m_dLocationCoord.X, this->m_dLocationCoord.Y - 2 }, // Lower leftmost
		{ this->m_dLocationCoord.X - 1, this->m_dLocationCoord.Y - 2 }, // Upper leftmost
		{ this->m_dLocationCoord.X - 2, this->m_dLocationCoord.Y - 1 }, // Above left
		{ this->m_dLocationCoord.X - 2, this->m_dLocationCoord.Y } }; // Above right
	for (int pellet = 0; pellet < 8; pellet++) // Pellet location fix
	{
		pelletsLocation[pellet].X += (this->m_sPlayer->m_cLocation.X - 1) / (ROOM_X + 2) * (ROOM_X + 2) + 2;
		pelletsLocation[pellet].Y += (this->m_sPlayer->m_cLocation.Y - 1) / (ROOM_Y + 2) * (ROOM_Y + 2) + 2;
	}

	Boss::Direction dir = Boss::RIGHT;
	for (int index = 0; index < 8; index++)
	{
		switch (index)
		{
		case 2:
			dir = Boss::DOWN;
			break;
		case 4:
			dir = Boss::LEFT;
			break;
		case 6:
			dir = Boss::UP;
			break;
		}
		this->m_pvPelletContainer->push_back(SPellet(&pelletsLocation[index], dir, 4, 0.18, false));
	}
}

void Boss1::rangedAttack2()
{
	COORD pelletsLocation[4] = {
		{ this->m_dLocationCoord.X + 1, this->m_dLocationCoord.Y + 1 }, // Bottom right
		{ this->m_dLocationCoord.X + 1, this->m_dLocationCoord.Y - 2 }, // Bottom left
		{ this->m_dLocationCoord.X - 2, this->m_dLocationCoord.Y - 2 }, // Above left
		{ this->m_dLocationCoord.X - 2, this->m_dLocationCoord.Y + 1 } }; // Above right
	for (int pellet = 0; pellet < 4; pellet++) // Pellet location fix
	{
		pelletsLocation[pellet].X += (this->m_sPlayer->m_cLocation.X - 1) / (ROOM_X + 2) * (ROOM_X + 2) + 2;
		pelletsLocation[pellet].Y += (this->m_sPlayer->m_cLocation.Y - 1) / (ROOM_Y + 2) * (ROOM_Y + 2) + 2;
	}

	Boss::Direction dir = Boss::DOWN_RIGHT;
	for (int index = 0; index < 4; index++)
	{
		switch (index)
		{
		case 1:
			dir = Boss::DOWN_LEFT;
			break;
		case 2:
			dir = Boss::UP_LEFT;
			break;
		case 3:
			dir = Boss::UP_RIGHT;
			break;
		}
		this->m_pvPelletContainer->push_back(SPellet(&pelletsLocation[index], dir, 5, 0.18, false));
	}
}

int Boss1::checkCollisionWithPlayer()
{
	int collisionCode = 0;
	if ((this->m_dLocationX - 1.0 <= this->getPlayerLocationX() + 1 && this->m_dLocationX + 1.0 >= this->getPlayerLocationX()) &&
		(this->m_dLocationY - 1.0 <= this->getPlayerLocationY() + 1 && this->m_dLocationY + 1.0 >= this->getPlayerLocationY()) &&
		!(this->m_abSidesHit[0] && this->m_abSidesHit[1] && this->m_abSidesHit[2] && this->m_abSidesHit[3]))
	{
		for (int code = 1; code <= 4; code++)
		{
			if (!this->m_abSidesHit[code - 1])
				collisionCode = code;
		}
		switch (m_abSidesHit[0])
		{
		case false:
			if (m_abSidesHit[2] == false) // Top left
				collisionCode = 5;
			else if (m_abSidesHit[3] == false) // Top right
				collisionCode = 6;
		}
		switch (m_abSidesHit[1])
		{
		case false:
			if (m_abSidesHit[2] == false) // Bottom left
				collisionCode = 7;
			else if (m_abSidesHit[3] == false) // Bottom right
				collisionCode = 8;
		}
	}

	if (this->m_dLocationX - 1.0 <= this->getPlayerLocationX() + 1) // Top side
		this->m_abSidesHit[0] = true;
	else
		this->m_abSidesHit[0] = false;
	if (this->m_dLocationX + 1.0 >= this->getPlayerLocationX()) // Bottom side
		this->m_abSidesHit[1] = true;
	else
		this->m_abSidesHit[1] = false;
	if (this->m_dLocationY - 1.0 <= this->getPlayerLocationY() + 1) // Left side
		this->m_abSidesHit[2] = true;
	else
		this->m_abSidesHit[2] = false;
	if (this->m_dLocationY + 1.0 >= this->getPlayerLocationY()) // Right side
		this->m_abSidesHit[3] = true;
	else
		this->m_abSidesHit[3] = false;

	return collisionCode;
}

void Boss1::checkHit()
{
	for (auto& pellet : (*this->m_pvPelletContainer))
	{
		if (pellet.m_bHit) continue;
		COORD c = this->getLocation(pellet.m_cLocation);

		if ((this->m_dLocationX - 1.0 < c.X + 1 && this->m_dLocationX + 1.0 > c.X) &&
			(this->m_dLocationY - 1.0 < c.Y + 1 && this->m_dLocationY + 1.0 > c.Y))
		{
			pellet.m_bHit = true;
			pellet.m_bHitReason = pellet::P_ENEMY;
			this->m_iHP -= pellet.m_iDamage;
		}
	}
	if (this->isDying())
		this->m_dDeadTime = this->m_dCurrentAccurateTime;
}

bool Boss1::isDying()
{
	if (this->m_iHP <= 0)
	{
		return true;
	}
	return false;
}

bool Boss1::isDead()
{
	if (this->isDying() && this->m_dDeadTime + 5.0 < this->m_dCurrentAccurateTime)
	{
		return true;
	}
	return false;
}

bool Boss1::isOverlapping(COORD c)
{
	c = this->getLocation(c);

	if ((this->m_dLocationX - 1.0 < c.X + 1 && this->m_dLocationX + 1.0 > c.X) &&
		(this->m_dLocationY - 1.0 < c.Y + 1 && this->m_dLocationY + 1.0 > c.Y))
	{
		return true;
	}

	return false;
}