#ifndef ENTITY3_H
#define ENTITY3_H

#include "AIHeader.h" 

namespace Entity3{
	void entity_startGame(chessBoard &Boa, GameType &cn, int cm);
	pair<int, int> entity_playChess(chessBoard &, GameType &, int );
	void entity_setPos(pair<int, int> , int , int );
	void entity_endGame(int , int );
	void entity_input(EntityControl::Player &);
	int entity_resetPos(pair<int, int> , int , int );
}

#endif

