#include "menu.h"

MenuEvent::MenuEvent(Console* mainConsole)
{
	this->mainConsole = mainConsole;
}

void MenuEvent::renderTitle()
{
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
	this->mainConsole->writeToBuffer(c, ">PLAY<", 0x0c);
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
