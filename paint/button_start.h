#ifndef BUTTON_START_H
#define BUTTON_START_H

#include "UI.h"
#include "standard.h"
#include "drawTools.h"
#include "button.h"

button b_start;

void runCommand_b_start(button&A)
{
	con_NewGame();
}

#endif

