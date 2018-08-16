#pragma once
#ifndef _MENU_H
#define _MENU_H
#include "Framework/console.h"
struct MenuEvent
{
	Console* mainConsole;
	COORD r_curspos;
	bool bStartGame = false;
	bool bOptions = false;
	short sh_cursSel = 0;
	MenuEvent(Console* mainConsole);
};
#endif // !_MENU_H
