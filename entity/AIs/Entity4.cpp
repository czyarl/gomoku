#ifndef ENTITY4_CPP
#define ENTITY4_CPP

#include "Entity4.h" 

using std::pair;
using std::make_pair;
class Entity4_do
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
//			return;
		}
		int do_resetPos(pair<int, int> cn, int cm) 
		{
			return 0;
		}
		typedef pair<int,int>pii;
		typedef long long int ll;
		inline int R(int l,int r)
		{
			return ((rand()*rand()+rand())%(r-l+1)+(r-l+1))%(r-l+1)+l;
		}
		ll f[55][55],P50[55];
		bool flag=1;
		ll ans, Maxnum;
		void swap(int &cn, int &cm)
		{
			int cx = cn;
			cn = cm;
			cm = cx;
		}
		void geng(int b, int w)
		{
			if(role == 2) swap(b, w);
			ans+=R(0,(b+w)?Maxnum:100);
			if(b && w) return;
			if(b) {ans += P50[b]; return; }
			if(w <= typ.len-3) ans -= P50[w]*100;
			else ans -= P50[w]*200;
		}
		ll calc_value()
		{
			ans = 0;
			Maxnum = 2499;
			int bx = typ.len;
			for(int i=1; i<=n; ++i) for(int j=1; j<=n-bx+1; ++j)
				{
					int b=0,w=0;
					for(int k=0; k<bx; ++k)
					{
						if(a[i][j+k]==1) ++b;
						else if(a[i][j+k]==2) ++w;
					}
					geng(b, w);
				}
			for(int i=1; i<=n-bx+1; ++i) for(int j=1; j<=n; ++j)
				{
					int b=0,w=0;
					for(int k=0; k<bx; ++k)
					{
						if(a[i+k][j]==1) ++b;
						else if(a[i+k][j]==2) ++w;
					}
					geng(b, w);
				}
			for(int i=1; i<=n-bx+1; ++i) for(int j=1; j<=n-bx+1; ++j)
				{
					int b=0,w=0;
					for(int k=0; k<bx; ++k)
					{
						if(a[i+k][j+k]==1) ++b;
						else if(a[i+k][j+k]==2) ++w;
					}
					geng(b, w);
				}
			for(int i=bx; i<=n; ++i) for(int j=1; j<=n-bx+1; ++j)
				{
					int b=0,w=0;
					for(int k=0; k<bx; ++k)
					{
						if(a[i-k][j+k]==1) ++b;
						else if(a[i-k][j+k]==2) ++w;
					}
					geng(b, w);
				}
			return ans;
		}
		const int dv[8] = {1,2,1,2,2,1,2,1};
		const int dx[8] = {-1,-1,-1,0,0,1,1,1};
		const int dy[8] = {-1,0,1,-1,1,-1,0,1};
		pii do_playChess()
		{
//		printf("in real AI\n");
			int flag=0;
			for(int i=1; i<=n; ++i)
				for(int j=1; j<=n; ++j)
				{
					f[i][j]=0;
					if(a[i][j]!=0)
						flag=1;
				}
			if(flag==0)
				return pii(n/2+1,n/2+1);
			P50[1]=50; P50[0] = 1;
			for(int i=2; i<=typ.len; ++i)
				P50[i]=P50[i-1]*50*50;
			for(int i = 1; i<=n; i++) for(int j = 1; j<=m; j++) if(a[i][j] == 0)
			{
				a[i][j] = role;
				f[i][j] = calc_value();
				a[i][j] = 0;
			}
			int X=-1,Y=-1;
			ll g=-LONG_LONG_MAX;
			for(int i=1; i<=n; ++i)
				for(int j=1; j<=n; ++j)
					if(a[i][j]==0&&f[i][j]>g)
						g=f[i][j],X=i,Y=j;
			return pii(X,Y);
		}
};

namespace Entity4
{
	Entity4_do P[3];
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

