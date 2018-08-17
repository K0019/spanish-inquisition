#pragma once
#ifndef _MENU_H
#define _MENU_H
#include "Framework/console.h"
#include "definitions.h"
struct MenuEvent
{
	Console* mainConsole;
	COORD r_curspos;
	WORD wPlayerColor = 0x0A;
	bool bStartGame = false;
	bool bOptions = false;
	bool bShop = false;
	bool bHowToPlay = false;
	bool bMenu = false;
	bool bCredits = false;
	bool bHasPressedButton = false;
	unsigned int uiCreditsRollTime = 0;
	unsigned int uiActivateDoomButton = 0;
	short sh_cursSel = 0;
	short sh_optionSel = 0;
	short sh_shopItemSel = 0;
	unsigned int CreditsOffsetY = 0;
	MenuEvent(Console* mainConsole);

	void renderTitle();
	void renderMenu();
	void renderCursor();

	void renderTutorialDetails();

	void renderCreditsRollAnimation();
	void renderCreditsRollText();

	void renderItemTitleSelected();
	void renderItemPriceSelected();
	void renderItemDescSelected();
	void renderItemCurrTSelected();
	void renderItemNextTSelected();

	void renderDoomButton();
	void renderGoomButtonBrackets();
	void renderColourOption();
	void renderOtherOptions();
};
#endif // !_MENU_H
