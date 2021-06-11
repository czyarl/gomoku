#ifndef ENTITY8_1_CPP
#define ENTITY8_1_CPP

#include "Entity8.h"
#include<utility>
#include<cstdio>
#include<stdlib.h>
#include<iostream>
using std::pair;
using std::make_pair;
using std::cerr;
using std::endl;
class Entity8_do
{
	public :
		int startGame(const GameType &cn, int cm, const chessBoard &Boa)
		{
			typ = cn; role = cm;
			n = Boa.n; m = Boa.m;
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
		int endGame(int cn)
		{
			do_endGame(cn);
			return 0;
		}
	private :
		typedef long long LL;
		const int EvlRou = 50;
		const double dlt = 1e-1;// for standard evolve speed
		LL get_r(LL cn) {return (1ll*RAND_MAX*RAND_MAX*rand() + 1ll*rand()*RAND_MAX + rand())%cn; }
		LL get_n(LL cn, LL cm) {return cn + get_r(cm-cn+1); }
		GameType typ;
		int role;
		int n, m;
		int a[MaxBoardSize+1][MaxBoardSize+1];
		double f[55][55], mi[55], ans;
		int zhan[55];
		const double evlSpd[10] = {0, 1e-1, 1e-1, 1, 1, 1, 1, 0, 0, 0};
		struct EvlNum {
			double a[20];
			void getit(FILE *F) {for(int i = 0;i<=9;i++) fscanf(F, "%lf", &a[i]); }
			void outit(FILE *F) {for(int i = 0;i<=9;i++) fprintf(F, "%lf\n", a[i]); fprintf(F, "\n"); }
			void addResult(double cn) {a[0] = a[0] + cn; a[8] = a[8] + 1; a[9] = a[9] + 1; }
			void reclear() {a[9] = 0; }
			void clear() {for(int i = 0;i<=9;i++) a[i] = 0; a[1] = -1; a[0] = -1e25; }//not used
			inline friend bool operator <(const EvlNum &cn, const EvlNum &cm) {return cn.a[0]/cn.a[8] > cm.a[0]/cm.a[8]; }
		};
		EvlNum evlNum[10];
		int evlNumLen, evlNumCur, evlRole;
		double curNum[20];
		//Num1, Num2 for f = Num1*Num2^(k-1); Num3 for <=2 ex-weight; Num4 for >=3 ex-weight; Num5 for non-empty random weight; Num6 for empty random weight; Num7 for calcStatus weight
		const int dx[4] = {-1,0,1,1};
		const int dy[4] = {1,1,1,0};
		double calcStatus(int winner)
		{
			double guo = 0;
			for(int i = 1;i<=n;i++) for(int j = 1;j<=n;j++) if(a[i][j] == 0) guo = guo + (winner == role ? curNum[7] : -curNum[7]); 
			if(winner == 3) guo = 0;
			return guo;
		}
		void evlModify(int ori, int tar)
		{
			for(int i = 0;i<=8;i++) 
			{
				double curRate = evlSpd[i]*dlt;
				evlNum[tar].a[i] = evlNum[ori].a[i]*get_n((1-curRate)*1e10, (1+curRate)*1e10)/1e10;
			}
			evlNum[tar].a[8] = 0; evlNum[tar].a[0] = 0;
		}
		void do_endGame(int winner) 
		{
//			cerr<<"in do_endGame"<<endl;
			FILE *F;
			if(role == 1) F = fopen("data\\Entity8_1.evolveData","w");
			else F = fopen("data\\Entity8_2.evolveData","w");
			evlNum[evlNumCur].addResult(calcStatus(winner));
			if(evlNum[evlNumCur].a[9] >= EvlRou) evlNumCur++;
			if(evlNumCur >= evlNumLen) {
				std::sort(evlNum, evlNum + evlNumLen);
				for(int i = 2;i<evlNumLen;i++) evlModify(0, i);
				for(int i = 0;i<evlNumLen;i++) evlNum[i].reclear();
				evlNumCur = 0; 
			}
			fprintf(F, "%d %d %d\n", evlNumLen, evlNumCur, evlRole);
			for(int i = 0;i<evlNumLen;i++) evlNum[i].outit(F);
			fclose(F);
//			cerr<<"re do_endGame"<<endl;
			return; 
		}
		void do_setPos(pair<int, int> cn, int cm) {return; }
		void do_prepare_clear()
		{
			evlNumLen = 5; evlNumCur = 0; evlRole = role;
			evlNum[0].a[1] = 30, evlNum[0].a[2] = 900, evlNum[0].a[3] = 40;
			evlNum[0].a[4] = 90, evlNum[0].a[5] = 799, evlNum[0].a[6] = 10, evlNum[0].a[7] = 1;
			evlNum[0].a[8] = 0, evlNum[0].a[0] = 0; evlNum[0].a[9] = 0;
			for(int i = 1;i<evlNumLen;i++) evlNum[i] = evlNum[0];
		}
		void do_prepare()
		{
			FILE *F;
			if(role == 1) F = fopen("data\\Entity8_1.evolveData","r");
			else F = fopen("data\\Entity8_2.evolveData","r");
			if(F == NULL) do_prepare_clear();
			else {
				int lin = fscanf(F, "%d %d %d", &evlNumLen, &evlNumCur, &evlRole);
				if(lin != 3) do_prepare_clear();
				else for(int i = 0;i<evlNumLen;i++) evlNum[i].getit(F);
			}
			if(role != evlRole) {
				for(int i = 0;i<evlNumLen;i++) evlNum[i].a[0] = evlNum[i].a[8] = evlNum[i].a[9] = 0;
				evlNumCur = 0;
				evlRole = role;
			}
			for(int i = 1;i<=7;i++) curNum[i] = evlNum[evlNumCur].a[i];
			mi[0] = 1; mi[1] = curNum[1];
			for(int i = 2;i<=typ.len;i++) mi[i] = mi[i-1]*curNum[2];
			fclose(F);
			return;
		}
		void swap(int &cn, int &cm) {int cx = cn; cn = cm; cm = cx; }
		void do_geng(int b, int w, int cn)
		{
			if(role == 2) swap(b, w);
			ans = ans + get_n(0,(LL)((b+w)?curNum[5]:curNum[6]));
			if(b && w) return;
			if(b) {ans = ans + mi[b]*cn; return; }
			if(w <= typ.len-3) ans = ans - mi[w]*cn*curNum[3];
			else ans = ans - mi[w]*cn*curNum[4];
		}
		void geng()
		{
			int b = 0, w = 0; 
			int lei = 0, xian = 0;
			for(int i = 1;i<=typ.len;i++)
			{
				if(zhan[i] == colorEmpty) lei = lei+xian*xian, xian = 0;
				if(zhan[i] == colorBlack) xian++, b++;
				if(zhan[i] == colorWhite) xian++, w++;
			}
			lei = lei+xian*xian, xian = 0;
			do_geng(b, w, lei);
		}
		int in_range(int cn, int cl, int cr) {return cl<=cn && cn<=cr; }
		double calc_value()
		{
			ans = 0;
			int bx = typ.len;
			for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) for(int ij = 0;ij<=3;ij++)
			{
				if(!in_range(i+(typ.len-1)*dx[ij], 1, n) || !in_range(j+(typ.len-1)*dy[ij], 1, m)) continue;
				for(int ik = 1;ik<=typ.len;ik++) zhan[ik] = a[i+(ik-1)*dx[ij]][j+(ik-1)*dy[ij]];
				geng();
			}
			return ans;
		}
		pair<int, int> get_max_pos()
		{
			int X=-1,Y=-1;
			double g=-1e20;
			for(int i=1; i<=n; ++i)
				for(int j=1; j<=n; ++j)
					if(a[i][j]==0&&f[i][j]>g)
						g=f[i][j],X=i,Y=j;
			return make_pair(X,Y);
		}
		pair<int, int> do_playChess()
		{
			int lin=0;
			for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) f[i][j]=0, lin += (a[i][j] != 0);
			if(lin==0) return make_pair(n/2+1, n/2+1);
			for(int i = 1; i<=n; i++) for(int j = 1; j<=m; j++) if(a[i][j] == 0)
			{
				a[i][j] = role;
				f[i][j] = calc_value();
				a[i][j] = 0;
			}
			return get_max_pos();
		}
};

namespace Entity8
{
	Entity8_do P[3];
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
}

#endif

