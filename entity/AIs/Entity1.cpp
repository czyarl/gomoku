#ifndef ENTITY1_CPP
#define ENTITY1_CPP

#include "Entity1.h"

using std::pair;
using std::make_pair;

class Entity1_do
{
	public :
		int startGame(const GameType &cn, int cm, const chessBoard &Boa)
		{
			typ = cn;
			role = cm;
			n = Boa.n;
			m = Boa.m;
			for(int i = 1; i<=n; i++) for(int j = 1; j<=m; j++) a[i][j] = Boa.a[i][j];
			do_prepare();
			return 0;
		}
		pair<int, int> playChess()
		{
			return do_playChess();
		}
		void setPos(pair<int, int> cn, int cm)
		{
			a[cn.first][cn.second] = cm;
			do_setPos(cn, cm);
		}
		int resetPos(pair<int, int> cn, int cm)
		{
			a[cn.first][cn.second] = 0;
			return do_resetPos(cn, cm);
		}
		int endGame(int cn)
		{
			do_endGame(cn);
			return 0;
		}
	private :
		GameType typ;
		int role;
		int n, m;
		int a[MaxBoardSize+1][MaxBoardSize+1];
		void do_endGame(int winner)
		{
//			printf("in do_endGame\n");
		}
		void do_prepare()
		{
//			printf("in do_prepare\n");
		}
		void do_setPos(pair<int, int> cn, int cm)
		{
//			printf("in do_setPos\n");
		}
		int do_resetPos(pair<int, int> cn, int cm) 
		{
			return 0;
		}
		pair<int, int> do_playChess()
		{
			int lef = 0;
			for(int i = 1; i<=n; i++) for(int j = 1; j<=m; j++) lef = lef+(a[i][j]==colorEmpty);
			lef = rand()%lef+1;
			for(int i = 1; i<=n; i++) for(int j = 1; j<=m; j++) if(a[i][j] == colorEmpty)
					{
						lef--;
						if(!lef) return make_pair(i,j);
					}
			return make_pair(-1,-1);
		}
};

namespace Entity1
{
	Entity1_do P[3];
	void entity_startGame(chessBoard &Boa, GameType &cn, int cm)
	{
		P[cm].startGame(cn, cm, Boa);
	}
	pair<int, int> entity_playChess(chessBoard &B, GameType &G, int cm)
	{
		return P[cm].playChess();
	}
	void entity_setPos(pair<int, int> pos, int cm, int targ)
	{
		P[targ].setPos(pos, cm);
	}
	void entity_endGame(int cn, int cm)
	{
		P[cm].endGame(cn);
	}
	int entity_resetPos(pair<int, int> pos, int cm, int targ) 
	{
		return P[targ].resetPos(pos, cm);
	}
	void entity_input(EntityControl::Player &cn)
	{
		cn.startGame = entity_startGame;
		cn.playChess = entity_playChess;
		cn.setPos = entity_setPos;
		cn.endGame = entity_endGame;
		cn.resetPos = entity_resetPos;
	}
}

#endif

