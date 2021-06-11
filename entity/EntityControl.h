#ifndef ENTITYCONTROL_H
#define ENTITYCONTROL_H

#include "../basic/BasicDef.h"
#include <string>
using std::string;
namespace EntityControl{
	struct Player
	{
		int type, now_type;
		pair<int, int> (*playChess)(chessBoard&, GameType&, int);
		void (*startGame)(chessBoard&, GameType&, int);
		void (*setPos)(pair<int, int> , int , int );
		int (*resetPos)(pair<int, int> , int , int ); 
		void (*endGame)(int, int);
		void setPlayer(int);
		void getPlayer();
	};

	void en_startGame(int, GameType&, int, int, int = 0);//size; Gametype; PlayerWhite; PlayerBlack
	pair<int,int> en_playChess(int, pair<int, int>, int &);//which player; pos to check(if human player)(if AI, not needed)
	void en_endGame(int cn);
	void en_OutitBoard();
	pair<int, int> en_PreviousStep();
	pair<int, int> en_NextStep();
	string en_GetOpeStr();
	int en_getRoundValue();
	
}

using EntityControl::en_startGame;
using EntityControl::en_playChess;
using EntityControl::en_endGame;
using EntityControl::en_OutitBoard;
using EntityControl::en_PreviousStep;
using EntityControl::en_NextStep;
using EntityControl::en_GetOpeStr;
using EntityControl::en_getRoundValue;

#endif

