/*-------------------------------------------
this AI is modified from Entity8 & EntityPCF
---------------------------------------------*/
#ifndef ENTITYCZY_H
#define ENTITYCZY_H

#include "AIHeader.h"

namespace EntityCzy{
	void entity_startGame(chessBoard &Boa, GameType &cn, int cm);
	pair<int, int> entity_playChess(chessBoard &, GameType &, int );
	void entity_setPos(pair<int, int> , int , int );
	void entity_endGame(int , int );
	void entity_input(EntityControl::Player &);
}

#endif

