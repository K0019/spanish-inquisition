#include "menu.h"

//creates a pointer to the main game console
MenuEvent::MenuEvent(Console* mainConsole)
{
	this->mainConsole = mainConsole;
	this->bCredits = false;
	this->bQuitGame = false;
	this->bHasPressedButton = false;
	this->bPausedGame = false;
	this->bMinimap = true;
}

void MenuEvent::MenuRender(unsigned short* OptionsDataArray, std::vector<SItem> * itemList)
{
	if (shMenuState > 0)
	{
		tipIndex = rand() % 6;
	}
	renderMenuControls();
	switch (shMenuState)
	{
	case 0:
		renderMenu();
		renderTitle();
		renderMenuCursor();
		break;
	case 1:
		renderTutorialDetails();
		break;
	case 2:
		renderItemSelected(itemList);
		renderShopBorder();
		break;
	case 3:
		renderDoomButton();
		renderDoomButtonBrackets();
		renderColourOption();
		renderMinimapOption();
		renderSaveOption();
		break;
	case 4:
		renderCreditsRollText();
		break;
	}
}

void MenuEvent::renderMenuControls()
{
	COORD c = this->mainConsole->getConsoleSize();
	c.Y -= 2;
	switch (shMenuState)
	{
	case 0:
		c.X = (c.X >> 1) + 16;
		this->mainConsole->writeToBuffer(c, "[UP] & [DOWN] - Choose | [ENTER] - Select");
		break;
	case 1:
		c.X = (c.X >> 1) - 20;
		this->mainConsole->writeToBuffer(c, "[ESCAPE] - Back");
		break;
	case 2:
		c.X = (c.X >> 1) - 20;
		this->mainConsole->writeToBuffer(c, "[LEFT] & [RIGHT] - Choose | [ENTER] - Buy|[ESCAPE] - Back");
		break;
	case 3:
		c.X = (c.X >> 1) - 40;
		this->mainConsole->writeToBuffer(c, "[UP] & [DOWN] - Choose | [ENTER] - Select | [LEFT] & [RIGHT] - Switch | [ESCAPE] - Back");
		break;
	case 4:
		c.X = (c.X >> 1) - 20;
		this->mainConsole->writeToBuffer(c, "[ESCAPE] - Back");
		break;
	}
}

// title banner
void MenuEvent::renderTitle()
{
	//main event
	std::string ASCII[13];
	ASCII[0] = "����������������������������������������������������������������������������������������������������";
	ASCII[1] = "                                                                                                    ";
	ASCII[2] = "   �������۲�           �����۲�                     �������۲�                                     ";
	ASCII[3] = "   ۲��۲�۲�          �۲�  �۲�                     �۲�  ۲�                                     ";
	ASCII[4] = "      �۲� ۲�۲���۲� �۲�     ��۲ ���۲��۲����۲� �۲�     ��۲���۲��۲� �۲� �۲���۲����۲�  ";
	ASCII[5] = "      �۲� ۲�۲۲�    �۲�     ۲�۲۲�  ۲�۲ ۲�   �����۲�۲�  ۲�  ۲�۲۲�۲۲�۲۲�۲۲�     ";
	ASCII[6] = "      �۲� ���۲��۲�  �۲� ��۲���۲��۲����۲ ۲�   �۲�     �۲�۲�  ���۲��۲����۲۲�۲��۲�   ";
	ASCII[7] = "      �۲� ۲�۲۲�    �۲�  �۲۲۲ ۲�  ۲�۲ ۲�   �۲�  ۲�  ۲۲�  ۲�۲۲�  ۲�۲۲�۲۲�     ";
	ASCII[8] = "     ���۲�۲�۲���۲   �����۲�۲ ۲���۲۲�۲ ۲�  �������۲��۲� ��۲۲�۲۲�  ۲�۲��۲ ���۲�  ";
	ASCII[9] = "                                                                                                    ";
	ASCII[10] = "����������������������������������������������������������������������������������������������������";
	ASCII[11] = "����������������������������������������������������������������������������������������������������";
	ASCII[12] = "����������������������������������������������������������������������������������������������������";
	COORD c = this->mainConsole->getConsoleSize();
	// This part here is meant to make the banner flexible (i.e. can fill any width higher than its own
	for (int i = 0; i < 13; i++)
	{
		c.X = 0;
		int paddingleft = ((this->mainConsole->getConsoleSize().X) - 100 )/ 2;
		for (int j = 0; j < (this->mainConsole->getConsoleSize().X); j++)
		{
			if (j < paddingleft)
			{
				switch (i)
				{
				case 0:
					ASCII[i] += "�";
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
					ASCII[i] = " " + ASCII[i];
					break;
				case 10:
					ASCII[i] = "�" + ASCII[i];
					break;
				case 11:
					ASCII[i] = "�" + ASCII[i];
					break;
				case 12:
					ASCII[i] = "�" + ASCII[i];
					break;
				}
			}
			else if (j > paddingleft && j < this->mainConsole->getConsoleSize().X)
			{
				switch (i)
				{
				case 0:
					ASCII[i] += "�";
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
					ASCII[i] += " ";
					break;
				case 10:
					ASCII[i] += "�";
					break;
				case 11:
					ASCII[i] += "�";
					break;
				case 12:
					ASCII[i] += "�";
					break;
				}
			}
			c.Y = 2 + i;
			if (!(i < 10))
				this->mainConsole->writeToBuffer(c, ASCII[i][j], 0x06);
			else
				this->mainConsole->writeToBuffer(c, ASCII[i][j], 0x64);
			c.X++;
		}
	}
}

// as annotated: menu options
void MenuEvent::renderMenu()
{
	COORD c;
	c.X = this->mainConsole->getConsoleSize().X / 5 + 2;
	c.Y = this->mainConsole->getConsoleSize().Y / 10 * 8 - 6;
	this->mainConsole->writeToBuffer(c, "   PLAY    ", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "HOW TO PLAY", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "   SHOP    ", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "  OPTIONS  ", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "  CREDITS  ", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "   QUIT    ", 0x0f);

	c.X = this->mainConsole->getConsoleSize().X / 3 + 15;
	c.Y = this->mainConsole->getConsoleSize().Y / 10 * 8 - 4;

	switch (tipIndex)
	{
	case 0: 
	{
		this->mainConsole->writeToBuffer(c, "~Empty rooms may not be as empty as they seem~", 0x0f);
		break;
	}
	case 1: 
	{
		this->mainConsole->writeToBuffer(c, "~Ranged enemies aren't trained in the strafing department~", 0x0f);
		break;
	}
	case 2:
	{
		this->mainConsole->writeToBuffer(c, "~Kiting and Melee makes for a good pairing~", 0x0f);
		break;
	}
	case 3:
	{
		this->mainConsole->writeToBuffer(c, "~Two walls on a diagonal, a bullet in between~", 0x0f);
		break;
	}
	case 4:
	{
		this->mainConsole->writeToBuffer(c, "~Symmetry is key~", 0x0f);
		break;
	}
	case 5:
	{
		this->mainConsole->writeToBuffer(c, "~Don't forget to spend your score! 90% is lost upon game start~", 0x0f);
		break;
	}
	}
}

// the cursor in the main menu
void MenuEvent::renderMenuCursor()
{
	COORD c = r_menucurspos;
	this->mainConsole->writeToBuffer(c, "[", 0x0f);
	c.X += 14;
	this->mainConsole->writeToBuffer(c, "]", 0x0f);
	c.X -= 14;
	if (DEBUG)
	{
		c.X -= 2;
		this->mainConsole->writeToBuffer(c, std::to_string(r_menucurspos.Y), 0x0f);
		c.X -= 2;
		this->mainConsole->writeToBuffer(c, std::to_string(sh_cursSel), 0x0f);
	}
}

// i really dont like the tutorial screen but it is what it is
void MenuEvent::renderTutorialDetails()
{
	COORD c = this->mainConsole->getConsoleSize();
	// LEFT SIDE
	c.X /= 10;
	c.Y /= 10;
	this->mainConsole->writeToBuffer(c, "How to play", 0x0f);
	c.Y += 2;
	this->mainConsole->writeToBuffer(c, "Controls", 0x0f);
	c.Y += 2;
	this->mainConsole->writeToBuffer(c, "[W]", 0x8f);
	c.X += 3;
	this->mainConsole->writeToBuffer(c, " - Move up", 0x0f);
	c.X -= 3;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "[A]", 0x8f);
	c.X += 3;
	this->mainConsole->writeToBuffer(c, " - Move right", 0x0f);
	c.X -= 3;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "[S]", 0x8f);
	c.X += 3;
	this->mainConsole->writeToBuffer(c, " - Move down", 0x0f);
	c.X -= 3;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "[D]", 0x8f);
	c.X += 3;
	this->mainConsole->writeToBuffer(c, " - Move right", 0x0f);
	c.X -= 3;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "[Up]", 0x8f);
	c.X += 4;
	this->mainConsole->writeToBuffer(c, " - Shoot up", 0x0f);
	c.X -= 4;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "[Down]", 0x8f);
	c.X += 6;
	this->mainConsole->writeToBuffer(c, " - Shoot down", 0x0f);
	c.X -= 6;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "[Left]", 0x8f);
	c.X += 6;
	this->mainConsole->writeToBuffer(c, " - Shoot left", 0x0f);
	c.X -= 6;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "[Right]", 0x8f);
	c.X += 7;
	this->mainConsole->writeToBuffer(c, " - Shoot right", 0x0f);
	c.X -= 7;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "[Space]", 0x8f);
	c.X += 7;
	this->mainConsole->writeToBuffer(c, " - Interact", 0x0f);
	c.X -= 7;
	c.Y++;
	// RIGHT SIDE
	c.X = this->mainConsole->getConsoleSize().X / 10 * 5;
	c.Y = this->mainConsole->getConsoleSize().Y / 10 + 2;
	this->mainConsole->writeToBuffer(c, "In-game", 0x0f);
	c.Y += 2;
	this->mainConsole->writeToBuffer(c, "@", wPlayerColor);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - You", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "oo", 0x0A);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Minor Health Pack", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "OO", 0x02);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Greater Health Pack", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "ss", 0x0A);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Small Medal", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "SS", 0x02);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Large Medal", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "  ", 0x60);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Item", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "^^", 0x04);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Spike Trap", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "##&_ ", 0x09);
	c.X += 4;
	this->mainConsole->writeToBuffer(c, " - Exit", 0x0f);
	c.X -= 4;
	c.Y -= 7;
	c.X += 25;
	this->mainConsole->writeToBuffer(c, "(Enemies)", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "B", 0x0E);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Bandit", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "M", 0x0E);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Mage", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "K", 0x0E);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Knight", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "E", 0x0E);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Enhanced Sorcerer", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "G", 0x0E);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Guardian", 0x0f);
	c.X -= 2;
	c.X -= 25;

}

// ye... scrapped :/
void MenuEvent::renderCreditsRollAnimation()
{
	/*COORD c = this->mainConsole->getConsoleSize();
	if (uiCreditsRollTime > 1000)
	{
		(c.X >>= 1) -= 9;
		c.Y >>= 1;
		this->mainConsole->writeToBuffer(c, "Press [Enter] to go back", 0x0f);
	}
	if (!(uiCreditsRollTime % 10))
	{
		CreditsOffsetY += 1;
	}
	if (uiCreditsRollTime == 4294967294)
	{
		uiCreditsRollTime = 0;
	}
	uiCreditsRollTime++;*/
}

// static text of credits
void MenuEvent::renderCreditsRollText()
{
	COORD c = this->mainConsole->getConsoleSize();
	c.X = (c.X >> 1) - 4;
	c.Y = (c.Y >> 1) >> 1;
	this->mainConsole->writeToBuffer(c, "Credits", 0x0f);
	c = this->mainConsole->getConsoleSize();
	c.X = (c.X >> 1) - 8;
	c.Y = ((c.Y >> 1) >> 1) + 2;
	this->mainConsole->writeToBuffer(c, " Kendrick Sim  ", 0x5f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, " Lim Yan Quan  ", 0x2f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "   Pi Jo Chu   ", 0x6f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, " Winston Ngoui ", 0x1f);
	c.X -= 10;
	c.Y += 2;
	this->mainConsole->writeToBuffer(c, "Developed in Visual Studio 2015/2017", 0x0f);
	c.X -= 6;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "Music by: Breakbeat Heartbeat: Leaving Home Album", 0x0f);

}

void MenuEvent::renderShopBorder()
{
	for (int i = 0; i < this->mainConsole->getConsoleSize().Y - 5; i++)
	{
		this->mainConsole->writeToBuffer(0, i, "||", 0x08);
	}
	for (int i = 0; i < this->mainConsole->getConsoleSize().Y - 5; i++)
	{
		this->mainConsole->writeToBuffer((this->mainConsole->getConsoleSize().X >> 1) - 2, i, "||", 0x08);
	}
	for (int i = 0; i < this->mainConsole->getConsoleSize().Y - 5; i++)
	{
		this->mainConsole->writeToBuffer(this->mainConsole->getConsoleSize().X - 2, i, "||", 0x08);
	}
	for (int i = 0; i < this->mainConsole->getConsoleSize().X; i++)
	{
		this->mainConsole->writeToBuffer(i, 3, "=", 0x08);
	}
	for (int i = 0; i < this->mainConsole->getConsoleSize().X; i++)
	{
		this->mainConsole->writeToBuffer(i, 5, "=", 0x08);
	}
}

// SHOP MENU
void MenuEvent::renderItemSelected(std::vector<SItem> * itemList)
{
	std::string nameOfItem = (*itemList)[sh_shopItemSel].m_sName;
	COORD c;
	c.Y = 4;
	c.X = 2;

	std::ostringstream currTierText;
	currTierText << "Current Tier (Tier " << (*itemList)[sh_shopItemSel].m_iWeaponLevel + 1 << ")";
	this->mainConsole->writeToBuffer(c, currTierText.str());
	c.X = this->mainConsole->getConsoleSize().X >> 1;

	std::ostringstream nextTierText;
	nextTierText << "Next Tier " << (((*itemList)[sh_shopItemSel].m_iWeaponLevel) > 3 ? "N/A" : "(Tier ") << (*itemList)[sh_shopItemSel].m_iWeaponLevel + 2 << ")";
	this->mainConsole->writeToBuffer(c, nextTierText.str());
	c.X = this->mainConsole->getConsoleSize().X - (SHORT)strlen("Cost: ") - (SHORT)std::to_string((*itemList)[sh_shopItemSel].m_iWeaponCost).length() - 5;
	c.Y = this->mainConsole->getConsoleSize().Y - 4;

	std::ostringstream cost;
	cost.str("");
	cost << "Cost: " << (*itemList)[sh_shopItemSel].m_iWeaponTotalCost;
	this->mainConsole->writeToBuffer(c, cost.str());
	c.X = c.Y = 2;
	this->mainConsole->writeToBuffer(c, nameOfItem, 0x1f);
	int currentTier = (*itemList)[sh_shopItemSel].m_iWeaponLevel;
	switch (sh_shopItemSel)
	{
		case 0:
		{
			switch (currentTier)
			{
				case 0:
				{
					c.Y += 4;
					this->mainConsole->writeToBuffer(c, "Pellets pass through invisible rocks.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Pellet lifespan doubled.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
				}
				case 1:
				{
					c.Y += 4;
					if (currentTier == 0) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Pellets pass through invisible rocks.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Pellet lifespan doubled.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Increases damage by 2.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 0) break;
				}
				case 2:
				{
					c.Y += 4;
					if (currentTier == 1) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Pellets pass through invisible rocks.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Pellet lifespan doubled.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Increases damage by 3.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 1) break;
				}
				case 3:
				{
					c.Y += 4;
					if (currentTier == 2) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Pellets pass through invisible rocks.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Pellet lifespan doubled.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Increases damage by 4.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 2) break;
				}
				default:
					c.Y = 6;
					this->mainConsole->writeToBuffer(c, "No valid higher tier");
					break;
			}
			break;
		}
		case 1:
		{
			switch (currentTier)
			{
				case 0:
				{
					c.Y += 4;
					this->mainConsole->writeToBuffer(c, "Damage increased by 2.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Health increased by 3.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;

				}
				case 1:
				{
					c.Y += 4;
					if (currentTier == 0) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Damage increased by 3.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Health increased by 4.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 0) break;
				}
				case 2:
				{
					c.Y += 4;
					if (currentTier == 1) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Damage increased by 4.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Health increased by 5.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 1) break;
				}
				case 3:
				{
					c.Y += 4;
					if (currentTier == 2) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Damage increased by 5.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Health increased by 6.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 2) break;
				}
				default:
					c.Y = 6;
					this->mainConsole->writeToBuffer(c, "No valid higher tier");
					break;
			}
			break;
		}
		case 2:
		{
			switch (currentTier)
			{
				case 0:
				{
					c.Y += 4;
					this->mainConsole->writeToBuffer(c, "Increases the HP stat of the player by 5 hp.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
				}
				case 1:
				{
					c.Y += 4;
					if (currentTier == 0) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Increases the HP stat of the player by 7 hp.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 0) break;
				}
				case 2:
				{
					c.Y += 4;
					if (currentTier == 1) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Increases the HP stat of the player by 9 hp.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 1) break;
				}
				case 3:
				{
					c.Y += 4;
					if (currentTier == 2) c.Y = 6;
					this->mainConsole->writeToBuffer(c, "Increases the HP stat of the player by 11 hp.");
					c.X = this->mainConsole->getConsoleSize().X >> 1;
					if (currentTier == 2) break;
				}
				default:
					c.Y = 6;
					this->mainConsole->writeToBuffer(c, "No valid higher tier");
					break;
			}
			break;
		}
		case 3:
		{
			switch (currentTier)
			{
			case 0:
			{
				c.Y += 4;
				this->mainConsole->writeToBuffer(c, "All enemies deal 2 more damage.");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Player deals 4 more damage.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
			}
			case 1:
			{
				c.Y += 4;
				if (currentTier == 0) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "All enemies deal 2 more damage.");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Player deals 5 more damage.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 0) break;
			}
			case 2:
			{
				c.Y += 4;
				if (currentTier == 1) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "All enemies deal 3 more damage.");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Player deals 6 more damage.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 1) break;
			}
			case 3:
			{
				c.Y += 4;
				if (currentTier == 2) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "All enemies deal 3 more damage.");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Player deals 7 more damage.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 2) break;
			}
			default:
				c.Y = 6;
				this->mainConsole->writeToBuffer(c, "No valid higher tier");
				break;
			}
			break;
		}
		case 4:
		{
			switch (currentTier)
			{
			case 0:
			{
				c.Y += 4;
				this->mainConsole->writeToBuffer(c, "Attack speed increased by 20%");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Pellet velocity increased by 20%.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
			}
			case 1:
			{
				c.Y += 4;
				if (currentTier == 0) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Attack speed increased by 30%");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Pellet velocity increased by 30%.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 0) break;
			}
			case 2:
			{
				c.Y += 4;
				if (currentTier == 1) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Attack speed increased by 40%");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Pellet velocity increased by 40%.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 1) break;
			}
			case 3:
			{
				c.Y += 4;
				if (currentTier == 2) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Attack speed increased by 50%");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Pellet velocity increased by 50%.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 2) break;
			}
			default:
				c.Y = 6;
				this->mainConsole->writeToBuffer(c, "No valid higher tier");
				break;
			}
			break;
		}
		case 5:
		{
			switch (currentTier)
			{
			case 0:
			{
				c.Y += 4;
				this->mainConsole->writeToBuffer(c, "Increases player's score by 1.5x");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
			}
			case 1:
			{
				c.Y += 4;
				if (currentTier == 0) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Increases player's score by 2x.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 0) break;
			}
			case 2:
			{
				c.Y += 4;
				if (currentTier == 1) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Increases player's score by 2.5x.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 1) break;
			}
			case 3:
			{
				c.Y += 4;
				if (currentTier == 2) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Increases player's score by 3x.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 2) break;
			}
			default:
				c.Y = 6;
				this->mainConsole->writeToBuffer(c, "No valid higher tier");
				break;
			}
			break;
		}
		case 6:
		{
			switch (currentTier)
			{
			case 0:
			{
				c.Y += 4;
				this->mainConsole->writeToBuffer(c, "Increases player's movement speed by 20%.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
			}
			case 1:
			{
				c.Y += 4;
				if (currentTier == 0) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Increases player's movement speed by 30%.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 0) break;
			}
			case 2:
			{
				c.Y += 4;
				if (currentTier == 1) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Increases player's movement speed by 40%.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 1) break;
			}
			case 3:
			{
				c.Y += 4;
				if (currentTier == 2) c.Y = 6;
				this->mainConsole->writeToBuffer(c, "Increases player's movement speed by 50%.");
				c.X = this->mainConsole->getConsoleSize().X >> 1;
				if (currentTier == 2) break;
			}
			default:
				this->mainConsole->writeToBuffer(c, "No valid higher tier");
				break;
			}
			break;
		}
		default:
		{
			this->mainConsole->writeToBuffer(c, "Invalid Item");
		}
	}
	
}

// heehee
void MenuEvent::renderDoomButton()
{
	std::string Button[5];
	Button[0] = " �������� ";
	Button[1] = "����������";
	Button[2] = "����������";
	Button[3] = "����������";
	Button[4] = " �������� ";
	COORD c = this->mainConsole->getConsoleSize();
	c.X = (c.X >> 1) - 8;
	c.Y /= 4;
	for (int i = 0; i < 5; i++)
	{
		this->mainConsole->writeToBuffer(c, Button[i], 0x0c);
		c.Y++;
	}
	c.X++;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "Prestige", 0x0f);
}

// heehee's brackets
void MenuEvent::renderDoomButtonBrackets()
{
	std::string LeftBracket[7];
	std::string RightBracket[7];
	LeftBracket[0] = "����";
	LeftBracket[1] = "��";
	LeftBracket[2] = "��";
	LeftBracket[3] = "��";
	LeftBracket[4] = "��";
	LeftBracket[5] = "��";
	LeftBracket[6] = "����";
	RightBracket[0] = "����";
	RightBracket[1] = "  ��";
	RightBracket[2] = "  ��";
	RightBracket[3] = "  ��";
	RightBracket[4] = "  ��";
	RightBracket[5] = "  ��";
	RightBracket[6] = "����";
	COORD c = this->mainConsole->getConsoleSize();
	c.X = (c.X >> 1) - 12;
	(c.Y /= 4) -= 1;
	if (sh_optionSel == 0)
	{
		for (int i = 0; i < 7; i++)
		{
			this->mainConsole->writeToBuffer(c, LeftBracket[i], 0x08);
			c.Y++;
		}
		c = this->mainConsole->getConsoleSize();
		c.X = (c.X >> 1) + 2;
		(c.Y /= 4) -= 1;
		for (int i = 0; i < 7; i++)
		{
			this->mainConsole->writeToBuffer(c, RightBracket[i], 0x08);
			c.Y++;
		}
	}
}

void MenuEvent::renderColourOption()
{
	COORD c = this->mainConsole->getConsoleSize();
	c.X = (c.X >> 1) - 10;
	c.Y = (c.Y >> 1) + 3;
	this->mainConsole->writeToBuffer(c, "Char Colour: ");
	c.X += 12;
	this->mainConsole->writeToBuffer(c, (sh_optionSel == 1 ? "<" : ""));
	c.X += 2;
	this->mainConsole->writeToBuffer(c, "@", wPlayerColor);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, (sh_optionSel == 1 ? ">" : ""));
}

void MenuEvent::renderMinimapOption()
{
	COORD c = this->mainConsole->getConsoleSize();
	c.X = (c.X >> 1) - 10;
	c.Y = (c.Y >> 1) + 4;
	this->mainConsole->writeToBuffer(c, "Minimap: ");
	c.X += 12;
	this->mainConsole->writeToBuffer(c, (sh_optionSel == 2 ? "<" : ""));
	c.X++;
	this->mainConsole->writeToBuffer(c, (bMinimap ? "Yes" : "No"), (bMinimap ? 0x0a : 0x0c));
	c.X += 3;
	this->mainConsole->writeToBuffer(c, (sh_optionSel == 2 ? ">" : ""));
}

void MenuEvent::renderSaveOption()
{
	COORD c = this->mainConsole->getConsoleSize();
	c.X = (c.X >> 1) - 7;
	c.Y -= 5;
	this->mainConsole->writeToBuffer(c, (sh_optionSel == 3 ? ">" : ""));
	c.X++;
	this->mainConsole->writeToBuffer(c, " SAVE ");
	c.X += 6;
	this->mainConsole->writeToBuffer(c, (sh_optionSel == 3 ? "<" : ""));
}