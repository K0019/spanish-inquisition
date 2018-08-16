#include "menu.h"

MenuEvent::MenuEvent(Console* mainConsole)
{
	this->mainConsole = mainConsole;
}

void MenuEvent::renderTitle()
{
	std::string ASCII[13];
	ASCII[0] = "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	ASCII[1] = "±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";
	ASCII[2] = "²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²";
	ASCII[3] = "   ÛÛÛÛÛÛÛÛ²°           ÛÛÛÛÛÛ²°                     ÛÛÛÛÛÛÛÛ²°                                     ";
	ASCII[4] = "   Û²°ÛÛ²°Û²°          ÛÛ²°  ÛÛ²°                     ÛÛ²°  Û²°                                     ";
	ASCII[5] = "      ÛÛ²° Û²°Û²ÛÛÛÛ²° ÛÛ²°     ÛÛÛ² ÛÛÛÛ²°ÛÛ²°ÛÛÛÛ²° ÛÛ²°     ÛÛÛ²°ÛÛÛ²°ÛÛ²° ÛÛ²° ÛÛ²°ÛÛÛ²°ÛÛÛÛ²°  ";
	ASCII[6] = "      ÛÛ²° Û²°Û²Û²°    ÛÛ²°     Û²°Û²Û²°  Û²°Û² Û²°   ÛÛÛÛÛÛ²°Û²°  Û²°  Û²°Û²Û²°Û²Û²°Û²Û²°Û²Û²°     ";
	ASCII[7] = "      ÛÛ²° ÛÛÛÛ²ÛÛÛ²°  ÛÛ²° ÛÛÛ²ÛÛÛÛ²ÛÛÛ²°ÛÛÛÛ² Û²°   ÛÛ²°     ÛÛ²°Û²°  ÛÛÛÛ²ÛÛÛ²°ÛÛÛÛ²Û²°Û²ÛÛÛ²°   ";
	ASCII[8] = "      ÛÛ²° Û²°Û²Û²°    ÛÛ²°  ÛÛ²Û²Û² Û²°  Û²°Û² Û²°   ÛÛ²°  Û²°  Û²Û²°  Û²°Û²Û²°  Û²°Û²Û²°Û²Û²°     ";
	ASCII[9] = "     ÛÛÛÛ²°Û²°Û²ÛÛÛÛ²   ÛÛÛÛÛÛ²°Û² Û²ÛÛÛÛ²Û²°Û² Û²°  ÛÛÛÛÛÛÛÛ²ÛÛÛ²° ÛÛÛ²Û²°Û²Û²°  Û²°Û²ÛÛÛ² ÛÛÛÛ²°  ";
	ASCII[10] = "²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²";
	ASCII[11] = "±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";
	ASCII[12] = "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	COORD c = this->mainConsole->getConsoleSize();
	c.X = 0;
	for (int i = 0; i < 13; i++)
	{
		c.Y = 2 + i;
		if (!(i > 2 && i < 10))
			this->mainConsole->writeToBuffer(c, ASCII[i], 0x06);
		else
			this->mainConsole->writeToBuffer(c, ASCII[i], 0x64);
	}
}

void MenuEvent::renderMenu()
{
	COORD c;
	c.X = this->mainConsole->getConsoleSize().X / 5 + 2;
	c.Y = this->mainConsole->getConsoleSize().Y / 10 * 8;
	this->mainConsole->writeToBuffer(c, ">PLAY<", 0x0c);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "HOW TO PLAY", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "SHOP", 0x0f);
	c.Y++;
	this->mainConsole->writeToBuffer(c, "OPTIONS", 0x0f);
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