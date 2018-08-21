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

// title banner
void MenuEvent::renderTitle()
{
	//main event
	std::string ASCII[13];
	ASCII[0] = "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	ASCII[1] = "                                                                                                    ";
	ASCII[2] = "   ÛÛÛÛÛÛÛÛ²°           ÛÛÛÛÛÛ²°                     ÛÛÛÛÛÛÛÛ²°                                     ";
	ASCII[3] = "   Û²°ÛÛ²°Û²°          ÛÛ²°  ÛÛ²°                     ÛÛ²°  Û²°                                     ";
	ASCII[4] = "      ÛÛ²° Û²°Û²ÛÛÛÛ²° ÛÛ²°     ÛÛÛ² ÛÛÛÛ²°ÛÛ²°ÛÛÛÛ²° ÛÛ²°     ÛÛÛ²°ÛÛÛ²°ÛÛ²° ÛÛ²° ÛÛ²°ÛÛÛ²°ÛÛÛÛ²°  ";
	ASCII[5] = "      ÛÛ²° Û²°Û²Û²°    ÛÛ²°     Û²°Û²Û²°  Û²°Û² Û²°   ÛÛÛÛÛÛ²°Û²°  Û²°  Û²°Û²Û²°Û²Û²°Û²Û²°Û²Û²°     ";
	ASCII[6] = "      ÛÛ²° ÛÛÛÛ²ÛÛÛ²°  ÛÛ²° ÛÛÛ²ÛÛÛÛ²ÛÛÛ²°ÛÛÛÛ² Û²°   ÛÛ²°     ÛÛ²°Û²°  ÛÛÛÛ²ÛÛÛ²°ÛÛÛÛ²Û²°Û²ÛÛÛ²°   ";
	ASCII[7] = "      ÛÛ²° Û²°Û²Û²°    ÛÛ²°  ÛÛ²Û²Û² Û²°  Û²°Û² Û²°   ÛÛ²°  Û²°  Û²Û²°  Û²°Û²Û²°  Û²°Û²Û²°Û²Û²°     ";
	ASCII[8] = "     ÛÛÛÛ²°Û²°Û²ÛÛÛÛ²   ÛÛÛÛÛÛ²°Û² Û²ÛÛÛÛ²Û²°Û² Û²°  ÛÛÛÛÛÛÛÛ²ÛÛÛ²° ÛÛÛ²Û²°Û²Û²°  Û²°Û²ÛÛÛ² ÛÛÛÛ²°  ";
	ASCII[9] = "                                                                                                    ";
	ASCII[10] = "²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²";
	ASCII[11] = "±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";
	ASCII[12] = "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
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
					ASCII[i] += "°";
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
					ASCII[i] = "²" + ASCII[i];
					break;
				case 11:
					ASCII[i] = "±" + ASCII[i];
					break;
				case 12:
					ASCII[i] = "°" + ASCII[i];
					break;
				}
			}
			else if (j > paddingleft && j < this->mainConsole->getConsoleSize().X)
			{
				switch (i)
				{
				case 0:
					ASCII[i] += "°";
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
					ASCII[i] += "²";
					break;
				case 11:
					ASCII[i] += "±";
					break;
				case 12:
					ASCII[i] += "°";
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
	c.Y = this->mainConsole->getConsoleSize().Y / 10 * 8 - 1;
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
	this->mainConsole->writeToBuffer(c, "@", 0x0A);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - You", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "b", 0x01);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Bandit", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "(Melee Enemies)", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "M", 0x01);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Mage", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, " - Ranged Enemy", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "#&_ ", 0x01);
	c.X += 4;
	this->mainConsole->writeToBuffer(c, " - Staircase", 0x0f);
	c.X -= 4;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "##&_ ", 0x01);
}

// ye... scrapped :/
void MenuEvent::renderCreditsRollAnimation()
{
	//COORD c = this->mainConsole->getConsoleSize();

	//if (uiCreditsRollTime > 1000)
	//{
	//	(c.X >>= 1) -= 9;
	//	c.Y >>= 1;
	//	this->mainConsole->writeToBuffer(c, "Press [Enter] to go back", 0x0f);
	//}
	//if (!(uiCreditsRollTime % 10))
	//{
	//	CreditsOffsetY += 1;
	//}
	//if (uiCreditsRollTime == 4294967294)
	//{
	//	uiCreditsRollTime = 0;
	//}
	//uiCreditsRollTime++;
}

// static text of credits
void MenuEvent::renderCreditsRollText()
{
	COORD c = this->mainConsole->getConsoleSize();
	c.X /= 10;
	c.Y = (c.Y >> 1) >> 1;
	this->mainConsole->writeToBuffer(c, "Credits", 0x0f);
	c.Y += 2;
	this->mainConsole->writeToBuffer(c, "Kendrick Sim", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "Lim Yan Quan", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "Winston Ngoui", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "Pi Jo Chu", 0x0f);
}

//UNDONE
void MenuEvent::renderItemSelected(std::vector<SItem> * itemList)
{
	std::string nameOfItem = (*itemList)[sh_shopItemSel].m_sName;
	COORD c;
	c.X = c.Y = 1;
	switch (sh_shopItemSel)
	{
		case 0:
		{
			this->mainConsole->writeToBuffer(c, nameOfItem, 0x0f);
			int currentTier = (*itemList)[sh_shopItemSel].m_iWeaponLevel;
			c.Y += 2;
			this->mainConsole->writeToBuffer(c, "Pellets pass through invisible rocks.");
			c.Y++;
			this->mainConsole->writeToBuffer(c, "Pellet lifespan doubled.");
			c.Y++;
			switch (currentTier)
			{
				case 1:
				{
					this->mainConsole->writeToBuffer(c, "Increases damage by 2.");
					break;
				}
				case 2:
				{
					this->mainConsole->writeToBuffer(c, "Increases damage by 3.");
					break;
				}
				case 3:
				{
					this->mainConsole->writeToBuffer(c, "Increases damage by 4.");
					break;
				}
				default:
					break;
			}
			break;
		}
		case 1:
		{
			this->mainConsole->writeToBuffer(c, nameOfItem, 0x0f);
			int currentTier = (*itemList)[sh_shopItemSel].m_iWeaponLevel;
			switch (currentTier)
			{
				case 0:
				{
					c.Y += 2;
					this->mainConsole->writeToBuffer(c, "Damage increased by 2.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Health increased by 3.");
					break;
				}
				case 1:
				{
					c.Y += 2;
					this->mainConsole->writeToBuffer(c, "Damage increased by 3.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Health increased by 4.");
					break;
				}
				case 2:
				{
					c.Y += 2;
					this->mainConsole->writeToBuffer(c, "Damage increased by 4.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Health increased by 5.");
					break;
				}
				case 3:
				{
					c.Y += 2;
					this->mainConsole->writeToBuffer(c, "Damage increased by 5.");
					c.Y++;
					this->mainConsole->writeToBuffer(c, "Health increased by 6.");
					break;
				}
				default:
					break;
			}
			break;
		}
		case 2:
		{
			this->mainConsole->writeToBuffer(c, nameOfItem, 0x0f);
			int currentTier = (*itemList)[sh_shopItemSel].m_iWeaponLevel;
			switch (currentTier)
			{
				case 0:
				{
					c.Y += 2;
					this->mainConsole->writeToBuffer(c, "Increases the HP stat of the player by 5 hp.");
					break;
				}
				case 1:
				{
					c.Y += 2;
					this->mainConsole->writeToBuffer(c, "Increases the HP stat of the player by 7 hp.");
					break;
				}
				case 2:
				{
					c.Y += 2;
					this->mainConsole->writeToBuffer(c, "Increases the HP stat of the player by 9 hp.");
					break;
				}
				case 3:
				{
					c.Y += 2;
					this->mainConsole->writeToBuffer(c, "Increases the HP stat of the player by 11 hp.");
					break;
				}
				default:
					break;
			}
			break;
		}
		case 3:
		{
			this->mainConsole->writeToBuffer(c, nameOfItem, 0x0f);
			int currentTier = (*itemList)[sh_shopItemSel].m_iWeaponLevel;
			switch (currentTier)
			{
			case 0:
			{
				c.Y += 2;
				this->mainConsole->writeToBuffer(c, "All enemies deal 2 more damage.");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Player deals 4 more damage.");
				break;
			}
			case 1:
			{
				c.Y += 2;
				this->mainConsole->writeToBuffer(c, "All enemies deal 3 more damage.");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Player deals 5 more damage.");
				break;
			}
			case 2:
			{
				c.Y += 2;
				this->mainConsole->writeToBuffer(c, "All enemies deal 4 more damage.");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Player deals 6 more damage.");
				break;
			}
			case 3:
			{
				c.Y += 2;
				this->mainConsole->writeToBuffer(c, "All enemies deal 5 more damage.");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Player deals 7 more damage.");
				break;
			}
			default:
				break;
			}
			break;
		}
		case 4:
		{
			this->mainConsole->writeToBuffer(c, nameOfItem, 0x0f);
			int currentTier = (*itemList)[sh_shopItemSel].m_iWeaponLevel;
			switch (currentTier)
			{
			case 0:
			{
				c.Y += 2;
				this->mainConsole->writeToBuffer(c, "Attack speed increased by 20%");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Pellet velocity increased by 20%.");
				break;
			}
			case 1:
			{
				c.Y += 2;
				this->mainConsole->writeToBuffer(c, "Attack speed increased by 30%");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Pellet velocity increased by 30%.");
				break;
			}
			case 2:
			{
				c.Y += 2;
				this->mainConsole->writeToBuffer(c, "Attack speed increased by 40%");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Pellet velocity increased by 40%.");
				break;
			}
			case 3:
			{
				c.Y += 2;
				this->mainConsole->writeToBuffer(c, "Attack speed increased by 50%");
				c.Y++;
				this->mainConsole->writeToBuffer(c, "Pellet velocity increased by 50%.");
				break;
			}
			default:
				break;
			}
			break;
		}
		case 5:
		{
			this->mainConsole->writeToBuffer(c, nameOfItem, 0x0f);
			int currentTier = (*itemList)[sh_shopItemSel].m_iWeaponLevel;
			c.Y += 2;
			this->mainConsole->writeToBuffer(c, "Increases player's score by "); 
			c.X += 28;
			switch (currentTier)
			{
			case 0:
			{
				this->mainConsole->writeToBuffer(c, "1.5x");
				break;
			}
			case 1:
			{
				this->mainConsole->writeToBuffer(c, "2x.");
				break;
			}
			case 2:
			{
				this->mainConsole->writeToBuffer(c, "2.5x.");
				break;
			}
			case 3:
			{
				this->mainConsole->writeToBuffer(c, "3x.");
				break;
			}
			default:
				break;
			}
			break;
		}
		case 6:
		{
			this->mainConsole->writeToBuffer(c, nameOfItem, 0x0f);
			int currentTier = (*itemList)[sh_shopItemSel].m_iWeaponLevel;
			c.Y += 2;
			this->mainConsole->writeToBuffer(c, "Increases player's movement speed by ");
			c.X += 37;
			switch (currentTier)
			{
			case 0:
			{
				this->mainConsole->writeToBuffer(c, "20%.");
				break;
			}
			case 1:
			{
				this->mainConsole->writeToBuffer(c, "30%.");
				break;
			}
			case 2:
			{
				this->mainConsole->writeToBuffer(c, "40%.");
				break;
			}
			case 3:
			{
				this->mainConsole->writeToBuffer(c, "50%.");
				break;
			}
			default:
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
	Button[0] = " ÛÛÛÛÛÛÛÛ ";
	Button[1] = "ÛÛÛÛÛÛÛÛÛÛ";
	Button[2] = "ÛÛÛÛÛÛÛÛÛÛ";
	Button[3] = "ÛÛÛÛÛÛÛÛÛÛ";
	Button[4] = " ÛÛÛÛÛÛÛÛ ";
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
	LeftBracket[0] = "ÛÛÛÛ";
	LeftBracket[1] = "ÛÛ";
	LeftBracket[2] = "ÛÛ";
	LeftBracket[3] = "ÛÛ";
	LeftBracket[4] = "ÛÛ";
	LeftBracket[5] = "ÛÛ";
	LeftBracket[6] = "ÛÛÛÛ";
	RightBracket[0] = "ÛÛÛÛ";
	RightBracket[1] = "  ÛÛ";
	RightBracket[2] = "  ÛÛ";
	RightBracket[3] = "  ÛÛ";
	RightBracket[4] = "  ÛÛ";
	RightBracket[5] = "  ÛÛ";
	RightBracket[6] = "ÛÛÛÛ";
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
