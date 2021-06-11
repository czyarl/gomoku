/*
	A naive AI by s_r_f
*/
#ifndef ENTITY5_CPP
#define ENTITY5_CPP

#include "Entity5.h" 

#include <chrono>
#include <random>
#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
using std::mt19937;

class Entity5_do
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
	//	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();;
	//	mt19937 randn(seed);
		int role;
		int n, m;
		int a[MaxBoardSize+1][MaxBoardSize+1];
		long long val[MaxBoardSize+1][MaxBoardSize+1];
		long long pw[20];
		inline bool in(int x,int y){ return 1 <= x && x <= n && 1 <= y && y <= m; }
		inline bool chk(int x,int y){ return in(x,y) && !a[x][y]; }
		inline int Opp(int r){ return r == 1 ? 2 : 1; }
		void do_endGame(int winner){ }
		void do_prepare(){  pw[0] = 1; for (int i = 1; i <= 19; ++i) pw[i] = pw[i-1] * 50; }
		void do_setPos(pair<int, int> cn, int cm) { }
		int do_resetPos(pair<int, int> cn, int cm) {return 0; }
		bool m0[MaxBoardSize+1][MaxBoardSize+1],m1[MaxBoardSize+1][MaxBoardSize+1];
		bool m2[MaxBoardSize+1][MaxBoardSize+1],m3[MaxBoardSize+1][MaxBoardSize+1];
		inline void work(int dx,int dy){
			int i,j,k,x,y,c[3],cmid; long long addv;
			for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) if (in(i+dx*4,j+dy*4)){
				c[0] = c[1] = c[2] = 0,cmid = 3;
				for (k = 1,x = i,y = j; k <= 5; ++k,x += dx,y += dy){
					++c[a[x][y]]; if (2 <= k && k <= 4) cmid &= a[x][y];
				}
				if (c[1] && c[2]) continue;
				if (!c[1] && !c[2]) addv = 1;
				else if (c[role]) addv = pw[c[role]<<1|1] - pw[(c[role]-1)<<1|1];
				else addv = pw[c[Opp(role)]<<1];
				for (k = 1,x = i,y = j; k <= 5; ++k,x += dx,y += dy) if (!a[x][y]){
					val[x][y] += addv;
					if (c[role] == 4) m0[x][y] = 1;
					else if (c[Opp(role)] == 4) m1[x][y] = 1;
				}
				if (cmid){
					if (c[role] == 3){
						if (chk(i-dx,j-dy)) m2[i][j] = 1;
						if (chk(i+dx*5,j+dy*5)) m2[i+dx*4][j+dy*4] = 1;
					}
					else{
						if (chk(i-dx,j-dy)) m3[i][j] = 1;
						if (chk(i+dx*5,j+dy*5)) m3[i+dx*4][j+dy*4] = 1;
					}
				}
			}
		}
		inline bool checkkill(int x,int y){
			const int dx[] = {1,-1,1,-1,0,0,1,-1},dy[] = {1,-1,0,0,1,-1,-1,1};
			int cnt = 0,tt,i,c[3],len;
			for (tt = 0; tt < 8; ++tt) if (in(x+dx[tt]*4,y+dy[tt]*4)){
				c[1] = c[2] = 0,len = 0;
				for (i = 1; i < 5; ++i) if (a[x+dx[tt]*i][y+dy[tt]*i] != role){ len = i-1; break; }
				if (len == 2 && chk(x-dx[tt],y-dy[tt]) && chk(x+dx[tt]*3,y+dy[tt]*3)) ++cnt;
			}
			return cnt >= 2;
		}
		pair<int,int> do_playChess()
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			mt19937 rand_num(seed);
			int i,j; bool is = 0;
			for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j)
				is |= a[i][j],val[i][j] = rand_num() % (n*m+1),m0[i][j] = m1[i][j] = m2[i][j] = m3[i][j] = 0;
			if (!is) return make_pair((n+1)/2,(m+1)/2);
			work(0,1),work(1,0),work(1,1),work(1,-1);
			for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) if (m0[i][j]) return make_pair(i,j);
			for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) if (m1[i][j]) return make_pair(i,j);
			for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) if (m2[i][j]) return make_pair(i,j);
			for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) if (m3[i][j]) return make_pair(i,j);
			for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) if (!a[i][j] && checkkill(i,j)) return make_pair(i,j);
			int ax = -1,ay = -1;
			for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) if (!a[i][j]){
				if (ax == -1 || val[i][j] > val[ax][ay]) ax = i,ay = j;
			}
			return make_pair(ax,ay);
		}
};

namespace Entity5
{
	Entity5_do P[3];
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


