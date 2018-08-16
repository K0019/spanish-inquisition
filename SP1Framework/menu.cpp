#include "menu.h"

MenuEvent::MenuEvent(Console* mainConsole)
{
	this->mainConsole = mainConsole;
}

void MenuEvent::renderTitle()
{
	std::string ASCII[13];
	ASCII[0] = "����������������������������������������������������������������������������������������������������";
	ASCII[1] = "����������������������������������������������������������������������������������������������������";
	ASCII[2] = "����������������������������������������������������������������������������������������������������";
	ASCII[3] = "   �������۲�           �����۲�                     �������۲�                                     ";
	ASCII[4] = "   ۲��۲�۲�          �۲�  �۲�                     �۲�  ۲�                                     ";
	ASCII[5] = "      �۲� ۲�۲���۲� �۲�     ��۲ ���۲��۲����۲� �۲�     ��۲���۲��۲� �۲� �۲���۲����۲�  ";
	ASCII[6] = "      �۲� ۲�۲۲�    �۲�     ۲�۲۲�  ۲�۲ ۲�   �����۲�۲�  ۲�  ۲�۲۲�۲۲�۲۲�۲۲�     ";
	ASCII[7] = "      �۲� ���۲��۲�  �۲� ��۲���۲��۲����۲ ۲�   �۲�     �۲�۲�  ���۲��۲����۲۲�۲��۲�   ";
	ASCII[8] = "      �۲� ۲�۲۲�    �۲�  �۲۲۲ ۲�  ۲�۲ ۲�   �۲�  ۲�  ۲۲�  ۲�۲۲�  ۲�۲۲�۲۲�     ";
	ASCII[9] = "     ���۲�۲�۲���۲   �����۲�۲ ۲���۲۲�۲ ۲�  �������۲��۲� ��۲۲�۲۲�  ۲�۲��۲ ���۲�  ";
	ASCII[10] = "����������������������������������������������������������������������������������������������������";
	ASCII[11] = "����������������������������������������������������������������������������������������������������";
	ASCII[12] = "����������������������������������������������������������������������������������������������������";
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
