#ifndef ENTITY3_CPP
#define ENTITY3_CPP

#include "Entity3.h" 

using std::pair;
using std::make_pair;
class Entity3_do
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
			printf("in do_endGame\n");
		}
		void do_prepare()
		{
			printf("in do_prepare\n");
		}
		void do_setPos(pair<int, int> cn, int cm)
		{
			return;
		}
		int do_resetPos(pair<int, int> cn, int cm) 
		{
			return 0;
		}
		pair<int, int> do_playChess()
		{
			int bx,by;
			scanf("%d %d",&bx,&by);
			return make_pair(bx,by);
		}
};

namespace Entity3
{
	Entity3_do P[3];
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
	void entity_input(EntityControl::Player &cn)
	{
		cn.startGame = entity_startGame;
		cn.playChess = entity_playChess;
		cn.setPos = entity_setPos;
		cn.endGame = entity_endGame;
	}
	int entity_resetPos(pair<int, int> pos, int cm, int targ) 
	{
		return P[targ].resetPos(pos, cm);
	}
}

#endif
