#ifndef BUTTON_UNDO_H
#define BUTTON_UNDO_H

#include "UI.h"
#include "standard.h"
#include "drawTools.h"
#include "button.h"

button b_undo;

void runCommand_b_undo(button&A)
{
	con_Undo();
	if((con_id_player1!=0)^(con_id_player2!=0))
		con_Undo();
}

#endif

