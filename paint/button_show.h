#ifndef BUTTON_SHOW_H
#define BUTTON_SHOW_H

#include "UI.h"
#include "standard.h"
#include "drawTools.h"
#include "button.h"

button b_show;

void runCommand_b_show(button&A)
{
	con_showNum(1);
}

#endif

