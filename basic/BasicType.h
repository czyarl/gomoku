#ifndef BASICTYPE_H
#define BASICTYPE_H

#include<utility>
#include<cstdio>
#include<cstdlib>
#include<vector>
using std::pair;
using std::make_pair;
using std::vector;
const int MaxBoardSize = 100;
const int colorBlack = 1;
const int colorWhite = 2;
const int colorEmpty = 0;
struct GameType {
	int typ;
	int len;
	void setClassic(int c_len)
	{
		typ = 1;
		len = c_len;
	}
	void getClassic()
	{
		printf("the number of pieces : ");
		scanf("%d",&len);
	}
	void getit()
	{
		while(1)
		{
			scanf("%d",&typ);
			if(typ == 1)
			{
				getClassic();
				break;
			}
			printf("no such gamemode. please try sth else. \n");
		}
	}
};

class chessBoard {
	public :
		int a[MaxBoardSize+1][MaxBoardSize+1];
		int n, m;
		int getValue()
		{
			int ans = 0;
			for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) ans += (a[i][j] != colorEmpty);
			return ans;
		}
		pair<int, pair<int, int> > setGambit_do(int cn, int cxl, int cxr, int cyl, int cyr)
		{
			while(1)
			{
				int cx = std::rand()%(cxr-cxl+1)+cxl, cy = rand()%(cyr-cyl+1)+cyl;
				if(a[cx][cy] != colorEmpty) continue;
				a[cx][cy] = cn; 
				return make_pair(cn, make_pair(cx, cy));
			}
		}
		void setGambit(int cn, vector<pair<int, pair<int, int> > > &V)
		{
			if(cn == 0) return;
			int bx = (n+1)/2, by = (m+1)/2;
			V.clear();
			for(int i = 1;i<=2;i++) 
			{
				V.push_back(setGambit_do(colorBlack, bx-1, bx+1, by-1, by+1));
				V.push_back(setGambit_do(colorWhite, bx-1, bx+1, by-1, by+1));
			}
			std_outit();
			clear(n, m);
		}
		void std_outit()
		{
			printf("   ");
			for(int i = 1; i<=m; i++) printf("%3d",i);
			puts("");
			for(int i = 1; i<=n; i++)
			{
				printf("%3d",i);
				for(int j = 1; j<=m; j++) printf("  %c",a[i][j] == colorEmpty ? '-' : a[i][j]+'0');
				puts("");
			}
		}
		void clear(int height, int width)
		{
			n = height;
			m = width;
			for(int i = 1; i<=n; i++) for(int j = 1; j<=m; j++) a[i][j] = colorEmpty;
		}
		int setPos(pair<int, int> cn, int cm)
		{
//			printf("in setPos : (%d,%d) %d n = %d m = %d %d\n",cn.first,cn.second,cm,n,m,a[cn.first][cn.second]);
			if(1>cn.first || cn.first>n || 1>cn.second || cn.second>m) return 0;
			if(a[cn.first][cn.second] != colorEmpty) return 0;
			a[cn.first][cn.second] = cm;
//			printf("%d\n",a[cn.first][cn.second]);
			return 1;
		}
		int resetPos(pair<int, int> cn)
		{
//			printf("in setPos : (%d,%d) %d n = %d m = %d %d\n",cn.first,cn.second,cm,n,m,a[cn.first][cn.second]);
			if(1>cn.first || cn.first>n || 1>cn.second || cn.second>m) return 0;
			if(a[cn.first][cn.second] == colorEmpty) return 0;
			a[cn.first][cn.second] = colorEmpty;
//			printf("%d\n",a[cn.first][cn.second]);
			return 1;
		}
		int full() {for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) if(a[i][j] == colorEmpty) return 0; return 1; }
		int checkWin(GameType G)
		{
//			printf("in checkWin : %d %d\n",G.typ,G.len);
			if(G.typ != 1) return 0;
			int cn = G.len;
			for(int i = 1; i<=n; i++) for(int j = 1; j<=m; j++) if(a[i][j] != colorEmpty)
			{
				if(j+(cn-1) <= m)
				{
					int lin = 1;
					for(int k = 1; k<=cn-1; k++) if(a[i][j+k] != a[i][j]) lin = 0;
					if(lin) return a[i][j];
				}
				if(i+(cn-1) <= n)
				{
					int lin = 1;
					for(int k = 1; k<=(cn-1); k++) if(a[i+k][j] != a[i][j]) lin = 0;
					if(lin) return a[i][j];
				}
				if(i+(cn-1) <= n && j+(cn-1) <= m)
				{
					int lin = 1;
					for(int k = 1; k<=(cn-1); k++) if(a[i+k][j+k] != a[i][j]) lin = 0;
					if(lin) return a[i][j];
				}
				if(i-(cn-1) >= 1 && j+(cn-1) <= m)
				{
					int lin = 1;
					for(int k = 1; k<=(cn-1); k++) if(a[i-k][j+k] != a[i][j]) lin = 0;
					if(lin) return a[i][j];
				}
			}
			if(full()) return 3;
			return 0;
		}
};

#endif

