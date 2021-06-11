#ifndef ENTITY6_H
#define ENTITY6_H

#include "AIHeader.h"

namespace Entity6{
	void entity_startGame(chessBoard &Boa, GameType &cn, int cm);
	pair<int, int> entity_playChess(chessBoard &, GameType &, int );
	void entity_setPos(pair<int, int> , int , int );
	void entity_endGame(int , int );
	void entity_input(EntityControl::Player &);
	int entity_resetPos(pair<int, int> , int , int );
}

#endif

