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