#ifndef BUTTON_QUIT_H
#define BUTTON_QUIT_H

#include "UI.h"
#include "standard.h"
#include "drawTools.h"
#include "button.h"

button b_quit;

void runCommand_b_quit(button&A)
{
	exit(0);
}

#endif

