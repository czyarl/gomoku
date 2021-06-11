#ifndef ENTITYCZY_1_CPP
#define ENTITYCZY_1_CPP

#include "EntityCzy.h"
#include<utility>
#include<cstdio>
#include<stdlib.h>
#include<iostream>
using std::pair;
using std::make_pair;
using std::cerr;
using std::endl;
using std::max;
using std::min;
class EntityCzy_do
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
		double mi[55], ans;
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
		static const int maxDepth = 8;
//		const int maxPoints[maxDepth+1] = {0,7,6,5,4,4,3,3,3,2};
		const int maxPoints[maxDepth+1] = {0,6,4,4,4,3,2,2,2};
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
			FILE *F;
			if(role == 1) F = fopen("data\\EntityCzy_1.evolveData","w");
			else F = fopen("data\\EntityCzy_2.evolveData","w");
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
			if(role == 1) F = fopen("data\\EntityCzy_1.evolveData","r");
			else F = fopen("data\\EntityCzy_2.evolveData","r");
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
		void Max(int &cn, int cm) {cn = cn < cm ? cm : cn; }
		void Min(int &cn, int cm) {cn = cn < cm ? cn : cm; }
		int in_range(int cn, int cl, int cr) {return cl<=cn && cn<=cr; }
		struct Val{
			double val;
			int dep;
			Val() {val = dep = 0; }
			Val(double cn, int cm) {val = cn; dep = cm; }
			inline friend bool operator <(Val cn, Val cm) {return cn.dep == cm.dep ? cn.val < cm.val : cn.dep < cm.dep; }
		};
		typedef pair<Val, pair<int, int> > P_vp;
		P_vp mkP_vp(double cn, int cm, int cx, int cy) {return make_pair(Val(cn, cm), make_pair(cx, cy)); }
		
			pair<int, int> zhan[55];
			double f[55][55];
			int Eva_lose;
			double Eva_do_geng(int b, int w, int cn, int cm)
			{
				if(role == 2) swap(b, w);
				double ans = 0;
				ans = ans + get_n(-(LL)((b+w)?curNum[5]:curNum[6]),(LL)((b+w)?curNum[5]:curNum[6]));
				if(b && w) return ans;
				if(b) {
					if(b <= typ.len-3) ans = ans + mi[b]*cn*curNum[3]/10;
					else if(b <= typ.len-1) ans = ans + mi[b]*cn*curNum[4]/10;
					else ans = ans + mi[b]*cn*curNum[4]*10;
				}
				else {
					if(w <= typ.len-3) ans = ans - mi[w]*cn*curNum[3];
					else if(w <= typ.len-1) ans = ans - mi[w]*cn*curNum[4];
					else ans = ans - mi[w]*cn*curNum[4]*1000;
				}
				int ge = b+w;
				if(cm == 2 && cn == 5) ans = ans/10.0;
				if(cm == 1 && ge == 3) ans = ans*10;
				if(ge == 4) ans = ans*100;
				if(ge == 5) Eva_lose = 1;
				return ans;
			}
			void Eva_geng(int cn)//1 for dfs; 2 for eva
			{
				int b = 0, w = 0; 
				int lei = 0, xian = 0, lian = 0, malian = 0;
				for(int i = 1;i<=typ.len;i++)
				{
					int curColor = a[zhan[i].first][zhan[i].second];
					if(curColor == colorEmpty) lei = lei+xian*xian, xian = 0, lian++, malian = std::max(malian, lian);
					if(curColor == colorBlack) xian++, b++, lian = 0;
					if(curColor == colorWhite) xian++, w++, lian = 0;
				}
				lei = lei+xian*xian, xian = 0;
				double ans = Eva_do_geng(b, w, lei, malian);
				if(cn == 1 && ans < 0) ans = -ans; 
				for(int i = 1;i<=typ.len;i++) f[zhan[i].first][zhan[i].second] += ans;
			}
			void Eva_erase_empty()
			{
				int bxl = n+1, bxr = 0, byl = m+1, byr = 0;
				for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) if(a[i][j] != colorEmpty)
				{
					Min(bxl, i); Max(bxr, i);
					Min(byl, j); Max(byr, j);
				}
				bxl = max(bxl-3, 1); bxr = min(bxr+3, n);
				byl = max(byl-3, 1); byr = min(byr+3, m);
				for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) 
					if((i < bxl || i > bxr) && (j < byl || j > byr)) a[i][j] = 0;
			}
			void Eva_calc_value(int cn)
			{
				int bx = typ.len;
				for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) f[i][j] = 0;
				Eva_lose = 0;
				for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) for(int ij = 0;ij<=3;ij++)
				{
					if(!in_range(i+(typ.len-1)*dx[ij], 1, n) || !in_range(j+(typ.len-1)*dy[ij], 1, m)) continue;
					for(int ik = 1;ik<=typ.len;ik++) zhan[ik] = make_pair(i+(ik-1)*dx[ij], j+(ik-1)*dy[ij]);
					Eva_geng(cn);
				}
				Eva_erase_empty();
			}
			void Eva_get_pos(vector<P_vp > &V)
			{
				for(int i = 1;i<=n;i++) for(int j = 1;j<=n;j++)
					if(a[i][j] == colorEmpty) V.push_back(mkP_vp(f[i][j], maxDepth+1, i, j));
			}
			double Eva_get_sum()
			{
				double ans = 0;
				for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) if(a[i][j] == colorEmpty) ans = ans + f[i][j];
				return ans;
			}
		vector<P_vp> V_pos;
		vector<pair<int, int> > pos[maxDepth+1];
		P_vp combat_dfs(int cn)
		{
			if(cn > maxDepth) {
				Eva_calc_value(2);
				P_vp guo = mkP_vp(Eva_get_sum(), cn, -1, -1);
//				printf("re combat_dfs : cn = %d (%.6lf, %d, %d)\n",cn,guo.first,guo.second.first,guo.second.second);
				return guo;
			}
//			printf("in combat_dfs : cn = %d\n",cn);
			Eva_calc_value(1);
			if(Eva_lose) return mkP_vp((cn&1) ? -1e25 : 1e25, cn, 1, 1);
//			for(int i = 1;i<=n;i++) {for(int j = 1;j<=m;j++) printf("%.0lf ",f[i][j]); puts(""); }
			V_pos.clear();
			Eva_get_pos(V_pos);
			sort(V_pos.begin(), V_pos.end());
			int len = 0;
			pos[cn].clear();
			for(int i = V_pos.size()-1;i>=0 && len <= maxPoints[cn];i--) pos[cn].push_back(V_pos[i].second), len++;
//			for(auto i : pos[cn]) printf("  %d %d\n",i.first,i.second);
			V_pos.clear();
			
			int colA = colorBlack, colB = colorWhite;
			if(role == 2) swap(colA, colB);
			P_vp guo;
			if(cn & 1) {
				guo = mkP_vp(-1e30, -1, 1, 1);
				for(auto i : pos[cn])
				{
					a[i.first][i.second] = colA;
					P_vp guo2 = combat_dfs(cn+1);
					a[i.first][i.second] = colorEmpty;
					int lin = 0;
					if(guo2.first.val >= 1e24) {
						if(guo.first.val < 1e24) lin = 1;
						else if(guo2.first.dep < guo.first.dep) lin = 1;
					}
					else if(guo2.first.val <= -1e24) {
						if(guo.first.val > -1e24) lin = 0;
						else if(guo2.first.dep > guo.first.dep) lin = 1;
					}
					else if(guo2.first.val > guo.first.val) lin = 1;
					if(lin) guo = mkP_vp(guo2.first.val, guo2.first.dep, i.first, i.second);
				}
			}
			else {
				guo = mkP_vp(1e30, -1, 1, 1);
				for(auto i : pos[cn])
				{
					a[i.first][i.second] = colB;
					P_vp guo2 = combat_dfs(cn+1);
					a[i.first][i.second] = colorEmpty;
					int lin = 0;
					if(guo2.first.val >= 1e24) {
						if(guo.first.val < 1e24) lin = 0;
						else if(guo2.first.dep > guo.first.dep) lin = 1;
					}
					else if(guo2.first.val <= -1e24) {
						if(guo.first.val > -1e24) lin = 1;
						else if(guo2.first.dep < guo.first.dep) lin = 1;
					}
					else if(guo2.first.val < guo.first.val) lin = 1;
					if(lin) guo = mkP_vp(guo2.first.val, guo2.first.dep, i.first, i.second);
				}
			}
//			printf("re combat_dfs : cn = %d (%.6lf, %d, %d)\n",cn,guo.first,guo.second.first,guo.second.second);
			return guo;
		}
		pair<int, int> do_playChess()
		{
			printf("in do_playChess\n");
			int lin = 0;
			for(int i = 1; i<=n; i++) for(int j=1; j<=n; j++) lin += (a[i][j] != 0);
			if(lin == 0) return make_pair(n/2+1, n/2+1);
			return combat_dfs(1).second;
		}
};

namespace EntityCzy
{
	EntityCzy_do P[3];
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

