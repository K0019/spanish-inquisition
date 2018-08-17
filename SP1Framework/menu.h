#pragma once
#ifndef _MENU_H
#define _MENU_H
#include "Framework/console.h"
#include "definitions.h"
struct MenuEvent
{
	Console* mainConsole;
	COORD r_curspos;
	bool bStartGame = false;
	bool bOptions = false;
	bool bShop = false;
	bool bHowToPlay = false;
	bool bMenu = false;
	bool bCredits = false;
	short sh_cursSel = 0;
	MenuEvent(Console* mainConsole);

	void renderTitle();
	void renderMenu();
	void renderCursor();
	
	void renderTutorialDetails();
};
#endif // !_MENU_H
