#ifndef CONTROL_HEADER_H
#define CONTROL_HEADER_H

#include "standard.h"

int con_gameStart=0;
int con_id_player1=-1;
int con_id_player2=-1;
int con_start_countdown=0;
int con_nowPlayer=0;
int con_gameClick=0;

void con_NewGame();
void con_runGame();
void con_showNum(bool x);
void con_Undo();

#endif

