#include "menu.h"

MenuEvent::MenuEvent(Console* mainConsole)
{
	this->mainConsole = mainConsole;
}

void MenuEvent::renderTitle()
{
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
	ASCII[10] = "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	ASCII[11] = "±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";
	ASCII[12] = "²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²";
	COORD c = this->mainConsole->getConsoleSize();
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
					ASCII[i] = "°" + ASCII[i];
					break;
				case 11:
					ASCII[i] = "±" + ASCII[i];
					break;
				case 12:
					ASCII[i] = "²" + ASCII[i];
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
					ASCII[i] += "°";
					break;
				case 11:
					ASCII[i] += "±";
					break;
				case 12:
					ASCII[i] += "²";
					break;
				}
			}
			c.Y = 2 + i;
			if (!(i < 10))
				this->mainConsole->writeToBuffer(c, ASCII[i][j], 0x80);
			else
				this->mainConsole->writeToBuffer(c, ASCII[i][j], 0x64);
			c.X++;
		}
	}
}

void MenuEvent::renderMenu()
{
	COORD c;
	c.X = this->mainConsole->getConsoleSize().X / 5 + 2;
	c.Y = this->mainConsole->getConsoleSize().Y / 10 * 8;
	this->mainConsole->writeToBuffer(c, "PLAY", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "HOW TO PLAY", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "SHOP", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "OPTIONS", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "CREDITS", 0x0f);
}

void MenuEvent::renderCursor()
{
	COORD c = r_curspos;
	this->mainConsole->writeToBuffer(c, ">", 0x0f);
	if (DEBUG)
	{
		c.X -= 2;
		this->mainConsole->writeToBuffer(c, std::to_string(r_curspos.Y), 0x0f);
		c.X -= 2;
		this->mainConsole->writeToBuffer(c, std::to_string(sh_cursSel), 0x0f);
	}
}

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
	this->mainConsole->writeToBuffer(c, "@@", 0x0A);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - You", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "tt", 0x01);
	c.X += 2;
	this->mainConsole->writeToBuffer(c, " - Enemy", 0x0f);
	c.X -= 2;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "#&_ ", 0x01);
	c.X += 4;
	this->mainConsole->writeToBuffer(c, " - Staircase", 0x0f);
	c.X -= 4;
	c.Y++;
	this->mainConsole->writeToBuffer(c, "##&_ ", 0x01);
}

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

void MenuEvent::renderCreditsRollText()
{
	COORD c = this->mainConsole->getConsoleSize();
	c.X /= 10;
	c.Y = (c.Y >> 1) * 0.5;
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

void MenuEvent::renderItemTitleSelected()
{

}

void MenuEvent::renderItemPriceSelected()
{

}

void MenuEvent::renderItemDescSelected()
{

}

void MenuEvent::renderItemCurrTSelected()
{

}

void MenuEvent::renderItemNextTSelected()
{

}

void MenuEvent::renderDoomButton()
{
	std::string Button[5];
	Button[0] = " ÛÛÛÛÛÛÛÛ ";
	Button[1] = "ÛÛÛÛÛÛÛÛÛÛ";
	Button[2] = "ÛÛÛÛÛÛÛÛÛÛ";
	Button[3] = "ÛÛÛÛÛÛÛÛÛÛ";
	Button[4] = " ÛÛÛÛÛÛÛÛ ";
	COORD c = this->mainConsole->getConsoleSize();
	c.X /= 10;
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

void MenuEvent::renderGoomButtonBrackets()
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
	(c.X /= 10) -= 6;
	(c.Y /= 4) -= 1;
	for (int i = 0; i < 7; i++)
	{
		this->mainConsole->writeToBuffer(c, LeftBracket[i], 0x08);
	}
}