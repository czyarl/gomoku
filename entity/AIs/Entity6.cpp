#ifndef ENTITY6_CPP
#define ENTITY6_CPP

#include "Entity6.h" 

using std::pair;
using std::make_pair;
using std::min;

class Entity6_do
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
			do_setPos(cn, cm);
		}
		int resetPos(pair<int, int> cn, int cm)
		{
			do_setPos(cn, 0);
			return 0;
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
		int w[MaxBoardSize+1][MaxBoardSize+1]; 
		long long wt;
		void do_endGame(int winner){}
		void do_prepare(){
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
					w[i][j] = 50+min(i, n-i+1) + min(j, m-j+1);
		}
		bool inboard(int x, int y) {
			return x > 0 && y > 0 && x <= n && y <= m;
		}
		long long getval(int x, int y, int dir) {
			int u, v;
			if (dir == 0) u = 1, v = 0;
			if (dir == 1) u = 0, v = 1;
			if (dir == 2) u = v = 1;
			if (dir == 3) u = 1, v = -1;
			int cnt[3] = {0,0,0};
			long long val = 1;
			if (!inboard(x, y) || !inboard(x+4*u, y+4*v)) return 0;
			for (int i = 0; i <= 4; i++) {
				int x0 = x+i*u, y0 = y+i*v;
				if(a[x0][y0]) val *= w[x0][y0];
				++cnt[a[x0][y0]];
			}
			if (cnt[0] <= 1) val *= 20;
			if (cnt[role] && !cnt[3-role]) return val;
			if (!cnt[role] && cnt[3-role]) return -val;
			return 0;
		}
		void do_setPos(pair<int, int> cn, int cm) {
			int u = cn.first, v = cn.second;
			for (int i = 0; i <= 4; i++) {
				wt -= getval(u-i, v, 0);
				wt -= getval(u, v-i, 1);
				wt -= getval(u-i, v-i, 2);
				wt -= getval(u-i, v+i, 3);
			}
			a[u][v] = cm;
			for (int i = 0; i <= 4; i++) {
				wt += getval(u-i, v, 0);
				wt += getval(u, v-i, 1);
				wt += getval(u-i, v-i, 2);
				wt += getval(u-i, v+i, 3);
			}
		}
		bool valid(int x, int y) {
			return !a[x][y];
		}
		pair<int, int> do_playChess()
		{
			pair<int, int> res;
			long long maxval = -0x3f3f3f3f3f3f3f3f;
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
					if (valid(i, j)) {
						do_setPos(make_pair(i, j), role);
						long long tmp = 0x3f3f3f3f3f3f3f3f;
						for (int k = 1; k <= n && tmp > maxval; k++)
							for (int l = 1; l <= m && tmp > maxval; l++)
								if (valid(k, l)) {
									do_setPos(make_pair(k, l), 3-role);
									tmp = min(tmp, wt);
									do_setPos(make_pair(k, l), 0);
								}
						if (tmp > maxval) maxval = tmp, res = make_pair(i, j);
						do_setPos(make_pair(i, j), 0);
					}
			return res;
		}
};

namespace Entity6
{
	Entity6_do P[3];
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

