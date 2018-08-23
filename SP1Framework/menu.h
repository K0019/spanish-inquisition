#pragma once
#ifndef _MENU_H
#define _MENU_H
#include "Framework/console.h"
#include "definitions.h"
#include "item.h"
// here we go
struct MenuEvent
{
	Console* mainConsole;					// pointer to the main console (to write to it)
	COORD r_menucurspos;					// the cursor position
	COORD r_optioncurspos;					// the cursor position
	COORD r_shopcurspos;					// the cursor position
	WORD wPlayerColor = 0x0A;				// the color of player (to change in options)
	bool bCredits;							// event processor: if player selected credits
	bool bHasPressedButton;					// event processor: the button has been pressed
	bool bPreventAccident;					// here
	bool bMinimap;							// event processor: if the minimap option is toggled
	bool bPausedGame;
	bool bQuitGame;
	unsigned int uiCreditsRollTime = 0;		// scrapped idea: animation timer for credits
	unsigned int uiActivateDoomButton = 0;	// heehee
	short shPlayerCharColourChoice = 0;
	short shMenuState = 0;
	short shPauseState = 0;
	short sh_cursSel = 0;					// menu selector: stores the menu cursor's selection
	short sh_optionSel = 0;					// menu selector: stores the options cursor's selection
	short sh_shopItemSel = 0;				// menu selector: stores the shop cursor's selection
	unsigned int CreditsOffsetY = 0;		// scrapped idea: how much the credits should go up by
	MenuEvent(Console* mainConsole);		// Construcc

	// RENDER FUNCTIONS

	void MenuRender(unsigned short* OptionsDataArray, std::vector<SItem> * itemList);

	void renderMenuControls();

	void renderTitle();						// renders banner in title screen
	void renderMenu();						// renders menu options
	void renderMenuCursor();				// renders the cursor

	void renderTutorialDetails();			// renders the tutorial keys (i.e. what they do)

	void renderCreditsRollAnimation();		// scrapped idea: see above
	void renderCreditsRollText();			// scrapped idea: converted into just static text

	void renderItemSelected(std::vector<SItem> * itemList);			// shop: selected item name 

	void renderDoomButton();				// heehee
	void renderDoomButtonBrackets();		// heehee's brackets when selected
	void renderColourOption();				// options: char colour option
	void renderMinimapOption();				// options: ugh
	void renderSaveOption();
};
#endif // !_MENU_H
