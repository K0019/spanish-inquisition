#pragma once
#ifndef _MENU_H
#define _MENU_H
#include "Framework/console.h"
#include "definitions.h"
// here we go
struct MenuEvent
{
	Console* mainConsole;					// pointer to the main console (to write to it)
	COORD r_curspos;						// the cursor position
	WORD wPlayerColor = 0x0A;				// the color of player (to change in options)
	bool bCredits;							// event processor: if player selected credits
	bool bHasPaused;
	bool bHasPressedButton;					// event processor: the button has been pressed
	bool bHowToPlay;						// event processor: if player selected tutorial
	bool bMenu;								// event processor: if player backed into menu
	bool bMinimap;							// event processor: if the minimap option is toggled
	bool bOptions;							// event processor: if player selected options
	bool bPausedGame;
	bool bQuitGame;
	bool bShop;								// event processor: if player selected shop
	bool bStartGame;						// event processor: if player selected start game
	unsigned int uiCreditsRollTime = 0;		// scrapped idea: animation timer for credits
	unsigned int uiActivateDoomButton = 0;	// heehee
	short sh_cursSel = 0;					// menu selector: stores the menu cursor's selection
	short sh_optionSel = 0;					// menu selector: stores the options cursor's selection
	short sh_shopItemSel = 0;				// menu selector: stores the shop cursor's selection
	unsigned int CreditsOffsetY = 0;		// scrapped idea: how much the credits should go up by
	MenuEvent(Console* mainConsole);		// Construcc

	void renderTitle();						// renders banner in title screen
	void renderMenu();						// renders menu options
	void renderCursor();					// renders the cursor

	void renderTutorialDetails();			// renders the tutorial keys (i.e. what they do)

	void renderCreditsRollAnimation();		// scrapped idea: see above
	void renderCreditsRollText();			// scrapped idea: converted into just static text

	void renderItemTitleSelected();			// shop: selected item name 
	void renderItemPriceSelected();			// shop: selected item's price 
	void renderItemDescSelected();			// shop: selected item desc
	void renderItemCurrTSelected();			// shop: selected item's current tier
	void renderItemNextTSelected();			// shop: selected item's next tier

	void renderDoomButton();				// heehee
	void renderDoomButtonBrackets();		// heehee's brackets when selected
	void renderColourOption();				// options: char colour option
	void renderOtherOptions();				// options: ugh
};
#endif // !_MENU_H
