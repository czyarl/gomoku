#ifndef ENTITYPCF_CPP
#define ENTITYPCF_CPP

#include "EntityPCF.h"
#include <cstring>
#include <iostream>
#include <ctime>

using std::pair;
using std::make_pair;
using std::cout;
using std::cerr;
using std::endl;
namespace PCF
{
	using namespace std;
	typedef long long int ll;
	typedef pair<int,int> pii;
	typedef pair<pair<int,int>,ll> piil;
	const int maxn=15;
	const int BLACK=2;
	const int WHITE=3;
	const int inf=1000000;
	ll P10[5]={10,100,5000,100000,10000000};
	mt19937 rd;
	inline int R(int l,int r)
	{
		return rd()%(r-l+1)+l;
	}
	struct method
	{
		ll black[5],white[5];//ur black
		method()
		{
			memset(black,0,sizeof(black));
			memset(white,0,sizeof(white));
			black[4]=1000000000;
			white[4]=-1000000000;
		}
		inline void addBlack(int pos,ll x)
		{
			black[pos]+=x;
			black[pos]=min(black[pos],P10[pos]);
			black[pos]=max(black[pos],(ll)0);
		}
		inline void addWhite(int pos,ll x)
		{
			white[pos]+=x;
			white[pos]=min(white[pos],(ll)0);
			white[pos]=max(white[pos],-P10[pos]);
		}
	}M0;
	struct info
	{
		ll a[maxn][maxn];
		int b[maxn][maxn];
		info()
		{
			memset(a,0,sizeof(a));
			memset(b,0,sizeof(b));
		}
		inline void out()
		{
			for(int i=0;i<maxn;++i,cout<<endl)
				for(int j=0;j<maxn;++j)
					cout<<a[i][j]<<" ";
		}
		inline ll getSum()
		{
			ll s=0;
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn;++j)
				{
					if(b[i][j]==0)
						s+=a[i][j];
					if(b[i][j]==BLACK)
						s+=min(min(i,maxn-i-1),min(j,maxn-j-1));
				}
			return s;
		}
	};
	struct board
	{
		char a[maxn][maxn];
		board()
		{
			memset(a,0,sizeof(a));
		}
		inline void clear()
		{
			memset(a,0,sizeof(a));
		}
		inline info evaluate(method&M, int cn, int cm)
		{
			info A;
			for(int i = 0;i<=4;i++) M.black[i] = M.black[i]*cn;
			for(int i = 0;i<=4;i++) M.white[i] = M.white[i]*cm;
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn;++j)
					A.b[i][j]=a[i][j];
			if(1){
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn-5;++j)
					if(a[i][j]==0&&a[i][j+1]==BLACK&&a[i][j+4]==BLACK&&a[i][j+5]==0)
					{
						if(a[i][j+2]==BLACK&&a[i][j+3]==0)
							A.a[i][j+3]+=M.black[3];
						if(a[i][j+2]==0&&a[i][j+3]==BLACK)
							A.a[i][j+2]+=M.black[3];
					}
					else if(a[i][j]==0&&a[i][j+1]==WHITE&&a[i][j+4]==WHITE&&a[i][j+5]==0)
					{
						if(a[i][j+2]==WHITE&&a[i][j+3]==0)
							A.a[i][j+3]+=M.white[3];
						if(a[i][j+2]==0&&a[i][j+3]==WHITE)
							A.a[i][j+2]+=M.white[3];
					}
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn-4;++j)
					if(a[i][j]==0&&a[i][j+1]==BLACK&&a[i][j+2]==BLACK&&a[i][j+3]==BLACK&&a[i][j+4]==0)
					{
						A.a[i][j]+=M.black[2]*5;
						A.a[i][j+4]+=M.black[2]*5;
					}
					else if(a[i][j]==0&&a[i][j+1]==WHITE&&a[i][j+2]==WHITE&&a[i][j+3]==WHITE&&a[i][j+4]==0)
					{
						A.a[i][j]+=M.white[2]*5;
						A.a[i][j+4]+=M.white[2]*5;
					}
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn-4;++j)
					if(a[i][j]==BLACK)
					{
						int len=1;
						while(len<5&&a[i][j+len]==BLACK)
							++len;
						for(int k=0;k<=len+1;++k)
							if(0<=j+k-1&&j+k-1<maxn&&a[i][j+k-1]==0)
								A.a[i][j+k-1]+=M.black[len-1];
					}
					else if(a[i][j]==WHITE)
					{
						int len=1;
						while(len<5&&a[i][j+len]==WHITE)
							++len;
						for(int k=0;k<=len+1;++k)
							if(0<=j+k-1&&j+k-1<maxn&&a[i][j+k-1]==0)
								A.a[i][j+k-1]+=M.white[len-1];
					}
			
			
			for(int i=0;i<maxn-5;++i)
				for(int j=0;j<maxn;++j)
					if(a[i][j]==0&&a[i+1][j]==BLACK&&a[i+4][j]==BLACK&&a[i+5][j]==0)
					{
						if(a[i+2][j]==BLACK&&a[i+3][j]==0)
							A.a[i+3][j]+=M.black[3];
						if(a[i+2][j]==0&&a[i+3][j]==BLACK)
							A.a[i+2][j]+=M.black[3];
					}
					else if(a[i][j]==0&&a[i+1][j]==WHITE&&a[i+4][j]==WHITE&&a[i+5][j]==0)
					{
						if(a[i+2][j]==WHITE&&a[i+3][j]==0)
							A.a[i+3][j]+=M.white[3];
						if(a[i+2][j]==0&&a[i+3][j]==WHITE)
							A.a[i+2][j]+=M.white[3];
					}
			for(int i=0;i<maxn-4;++i)
				for(int j=0;j<maxn;++j)
					if(a[i][j]==0&&a[i+1][j]==BLACK&&a[i+2][j]==BLACK&&a[i+3][j]==BLACK&&a[i+4][j]==0)
					{
						A.a[i][j]+=M.black[2]*5;
						A.a[i+4][j]+=M.black[2]*5;
					}
					else if(a[i][j]==0&&a[i+1][j]==WHITE&&a[i+2][j]==WHITE&&a[i+3][j]==WHITE&&a[i+4][j]==0)
					{
						A.a[i][j]+=M.white[2]*5;
						A.a[i+4][j]+=M.white[2]*5;
					}
			for(int i=0;i<maxn-4;++i)
				for(int j=0;j<maxn;++j)
					if(a[i][j]==BLACK)
					{
						int len=1;
						while(len<5&&a[i+len][j]==BLACK)
							++len;
						for(int k=0;k<=len+1;++k)
							if(0<=i+k-1&&i+k-1<maxn&&a[i+k-1][j]==0)
								A.a[i+k-1][j]+=M.black[len-1];
					}
					else if(a[i][j]==WHITE)
					{
						int len=1;
						while(len<5&&a[i+len][j]==WHITE)
							++len;
						for(int k=0;k<=len+1;++k)
							if(0<=i+k-1&&i+k-1<maxn&&a[i+k-1][j]==0)
								A.a[i+k-1][j]+=M.white[len-1];
					}
			
			
			for(int i=0;i<maxn-5;++i)
				for(int j=0;j<maxn-5;++j)
					if(a[i][j]==0&&a[i+1][j+1]==BLACK&&a[i+4][j+4]==BLACK&&a[i+5][j+5]==0)
					{
						if(a[i+2][j+2]==BLACK&&a[i+3][j+3]==0)
							A.a[i+3][j+3]+=M.black[3];
						if(a[i+2][j+2]==0&&a[i+3][j+3]==BLACK)
							A.a[i+2][j+2]+=M.black[3];
					}
					else if(a[i][j]==0&&a[i+1][j+1]==WHITE&&a[i+4][j+4]==WHITE&&a[i+5][j+5]==0)
					{
						if(a[i+2][j+2]==WHITE&&a[i+3][j+3]==0)
							A.a[i+3][j+3]+=M.white[3];
						if(a[i+2][j+2]==0&&a[i+3][j+3]==WHITE)
							A.a[i+2][j+2]+=M.white[3];
					}
			for(int i=0;i<maxn-4;++i)
				for(int j=0;j<maxn-4;++j)
					if(a[i][j]==0&&a[i+1][j+1]==BLACK&&a[i+2][j+2]==BLACK&&a[i+3][j+3]==BLACK&&a[i+4][j+4]==0)
					{
						A.a[i][j]+=M.black[2]*5;
						A.a[i+4][j+4]+=M.black[2]*5;
					}
					else if(a[i][j]==0&&a[i+1][j+1]==WHITE&&a[i+2][j+2]==WHITE&&a[i+3][j+3]==WHITE&&a[i+4][j+4]==0)
					{
						A.a[i][j]+=M.white[2]*5;
						A.a[i+4][j+4]+=M.white[2]*5;
					}
			for(int i=0;i<maxn-4;++i)
				for(int j=0;j<maxn-4;++j)
					if(a[i][j]==BLACK)
					{
						int len=1;
						while(len<5&&a[i+len][j+len]==BLACK)
							++len;
						for(int k=0;k<=len+1;++k)
							if(0<=i+k-1&&i+k-1<maxn&&0<=j+k-1&&j+k-1<maxn&&a[i+k-1][j+k-1]==0)
								A.a[i+k-1][j+k-1]+=M.black[len-1];
					}
					else if(a[i][j]==WHITE)
					{
						int len=1;
						while(len<5&&a[i+len][j+len]==WHITE)
							++len;
						for(int k=0;k<=len+1;++k)
							if(0<=i+k-1&&i+k-1<maxn&&0<=j+k-1&&j+k-1<maxn&&a[i+k-1][j+k-1]==0)
								A.a[i+k-1][j+k-1]+=M.white[len-1];
					}
			
			
			for(int i=0;i<maxn-5;++i)
				for(int j=5;j<maxn;++j)
					if(a[i][j]==0&&a[i+1][j-1]==BLACK&&a[i+4][j-4]==BLACK&&a[i+5][j-5]==0)
					{
						if(a[i+2][j-2]==BLACK&&a[i+3][j-3]==0)
							A.a[i+3][j-3]+=M.black[3];
						if(a[i+2][j-2]==0&&a[i+3][j-3]==BLACK)
							A.a[i+2][j-2]+=M.black[3];
					}
					else if(a[i][j]==0&&a[i+1][j-1]==WHITE&&a[i+4][j-4]==WHITE&&a[i+5][j-5]==0)
					{
						if(a[i+2][j-2]==WHITE&&a[i+3][j-3]==0)
							A.a[i+3][j-3]+=M.white[3];
						if(a[i+2][j-2]==0&&a[i+3][j-3]==WHITE)
							A.a[i+2][j-2]+=M.white[3];
					}
			for(int i=0;i<maxn-4;++i)
				for(int j=4;j<maxn;++j)
					if(a[i][j]==0&&a[i+1][j-1]==BLACK&&a[i+2][j-2]==BLACK&&a[i+3][j-3]==BLACK&&a[i+4][j-4]==0)
					{
						A.a[i][j]+=M.black[2]*5;
						A.a[i+4][j-4]+=M.black[2]*5;
					}
					else if(a[i][j]==0&&a[i+1][j-1]==WHITE&&a[i+2][j-2]==WHITE&&a[i+3][j-3]==WHITE&&a[i+4][j-4]==0)
					{
						A.a[i][j]+=M.white[2]*5;
						A.a[i+4][j-4]+=M.white[2]*5;
					}
			for(int i=0;i<maxn-4;++i)
				for(int j=4;j<maxn;++j)
					if(a[i][j]==BLACK)
					{
						int len=1;
						while(len<5&&a[i+len][j-len]==BLACK)
							++len;
						for(int k=0;k<=len+1;++k)
							if(0<=i+k-1&&i+k-1<maxn&&0<=j-k+1&&j-k+1<maxn&&a[i+k-1][j-k+1]==0)
								A.a[i+k-1][j-k+1]+=M.black[len-1];
					}
					else if(a[i][j]==WHITE)
					{
						int len=1;
						while(len<5&&a[i+len][j-len]==WHITE)
							++len;
						for(int k=0;k<=len+1;++k)
							if(0<=i+k-1&&i+k-1<maxn&&0<=j-k+1&&j-k+1<maxn&&a[i+k-1][j-k+1]==0)
								A.a[i+k-1][j-k+1]+=M.white[len-1];
					}
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn;++j)
					A.a[i][j]+=min(min(i,maxn-i-1),min(j,maxn-j-1));
			}
			for(int i = 0;i<=4;i++) M.black[i] = M.black[i]/cn;
			for(int i = 0;i<=4;i++) M.white[i] = M.white[i]/cm;
			return A;
		}
		inline void reverse()
		{
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn;++j)
					if(a[i][j]==BLACK)
						a[i][j]=WHITE;
					else if(a[i][j]==WHITE)
						a[i][j]=BLACK;
		}
		inline void put(int x,int y,int c)
		{
			a[x][y]=c;
		}
		inline int end()
		{
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn-4;++j)
				{
					int x0=a[i][j];
					int x1=a[i][j+1];
					int x2=a[i][j+2];
					int x3=a[i][j+3];
					int x4=a[i][j+4];
					if(x0!=0&&x0==x1&&x1==x2&&x2==x3&&x3==x4)
						return x0;
				}
			for(int i=0;i<maxn-4;++i)
				for(int j=0;j<maxn;++j)
				{
					int x0=a[i][j];
					int x1=a[i+1][j];
					int x2=a[i+2][j];
					int x3=a[i+3][j];
					int x4=a[i+4][j];
					if(x0!=0&&x0==x1&&x1==x2&&x2==x3&&x3==x4)
						return x0;
				}
			for(int i=0;i<maxn-4;++i)
				for(int j=0;j<maxn-4;++j)
				{
					int x0=a[i][j];
					int x1=a[i+1][j+1];
					int x2=a[i+2][j+2];
					int x3=a[i+3][j+3];
					int x4=a[i+4][j+4];
					if(x0!=0&&x0==x1&&x1==x2&&x2==x3&&x3==x4)
						return x0;
				}
			for(int i=0;i<maxn-4;++i)
				for(int j=4;j<maxn;++j)
				{
					int x0=a[i][j];
					int x1=a[i+1][j-1];
					int x2=a[i+2][j-2];
					int x3=a[i+3][j-3];
					int x4=a[i+4][j-4];
					if(x0!=0&&x0==x1&&x1==x2&&x2==x3&&x3==x4)
						return x0;
				}
			for(int i=0;i<maxn;++i)
				for(int j=0;j<maxn;++j)
					if(a[i][j]==0)
						return 0;
			return -1;
		}
		inline void out()
		{
			for(int i=0;i<maxn;++i,cout<<endl)
				for(int j=0;j<maxn;++j)
					if(a[i][j]==BLACK)
						cout<<"B ";
					else if(a[i][j]==WHITE)
						cout<<"W ";
					else
						cout<<". ";
		}
	};
	const int DEPTH=6;
	const int maxd=8;
	board B;
	bool cmp(const piil&x,const piil&y)
	{
		return x.second>y.second;
	}
	ll dfs(method&M,int d)
	{
		info A;
		if(d>DEPTH)
		{
			A = B.evaluate(M,1,1);
			ll x=A.getSum();
			return x;
		}
		A=B.evaluate(M,1,1);
		if(B.end())
			return A.getSum();
		vector<piil>wait;
		for(int i=0;i<maxn;++i)
			for(int j=0;j<maxn;++j)
				if(B.a[i][j]==0)
					wait.push_back(piil(pii(i,j),((A.a[i][j] < 0) ? -A.a[i][j] : A.a[i][j])));
		sort(wait.begin(),wait.end(),cmp);
		if(d&1)
		{
			ll now=-1E18;
			for(int i=0;i<wait.size()&&i<maxd;++i)
			{
				int x=wait[i].first.first,y=wait[i].first.second;
				B.put(x,y,BLACK);
				
				ll g=dfs(M,d+1);
				now=max(now,g);
				B.put(x,y,0);
			}
			return now;
		}
		else
		{
			ll now=1E18;
			for(int i=0;i<wait.size()&&i<maxd;++i)
			{
				int x=wait[i].first.first,y=wait[i].first.second;
				B.put(x,y,WHITE);
				
				ll g=dfs(M,d+1);
				now=min(now,g);
				B.put(x,y,0);
			}
			return now;
		}
	}
	inline void init()
	{
		rd=mt19937(time(0));
		M0.black[0]=7;//8
		M0.black[1]=28;
		M0.black[2]=4002;//4302
		M0.black[3]=26473;
		M0.black[4]=10000000000;
		M0.white[0]=-8;//7
		M0.white[1]=-55;
		M0.white[2]=-4828;//2828
		M0.white[3]=-5784;
		M0.white[4]=-10000000000;
	}
	inline pii getPos(board B0,method M)
	{
		B=B0;
		info A=B.evaluate(M,1,1);
		vector<piil>wait;
		for(int i=0;i<maxn;++i)
			for(int j=0;j<maxn;++j)
				if(B.a[i][j]==0)
					wait.push_back(piil(pii(i,j),abs(A.a[i][j])));// !!!!!!!
		if(wait.size()==0)
			return pii(-1,-1);
		sort(wait.begin(),wait.end(),cmp);
		
		pii p(0,0);
		ll now=-1E18;
		for(int i=0;i<wait.size()&&i<maxd;++i)
		{
			int x=wait[i].first.first,y=wait[i].first.second;
			B.put(x,y,BLACK);
			ll g=dfs(M,2);
			B.put(x,y,0);
			if(g>now)
				now=g,p=pii(x,y);
		}
		return p;
	}
}
using namespace std;
class EntityPCF_do
{
	typedef pair<int,int> pii;
	public :
		int startGame(const GameType &cn, int cm, const chessBoard &Boa)
		{
			typ=cn;
			role=cm;
			B.clear();
			PCF::init();
			return 0;
		}
		pair<int, int> playChess()
		{
			pii x;
			if(role==1)//  BLACK
			{
				x=PCF::getPos(B,PCF::M0);
				B.put(x.first,x.second,PCF::BLACK);
			}
			else// WHITE
			{
				B.reverse();
				x=PCF::getPos(B,PCF::M0);
				B.reverse();
				B.put(x.first,x.second,PCF::WHITE);
			}
			++x.first,++x.second;//BE CAREFUL
			return x;
		}
		void setPos(pair<int, int> cn, int cm)
		{
			--cn.first,--cn.second;
			if(cm==1)
				B.put(cn.first,cn.second,PCF::BLACK);
			else
				B.put(cn.first,cn.second,PCF::WHITE);
		}
		int resetPos(pair<int, int> cn, int cm)
		{
			--cn.first,--cn.second;
			B.put(cn.first,cn.second,0);
			return 0;
		}
		int endGame(int cn)
		{
			return 0;
		}
	private :
		GameType typ;
		int role;
		int n, m;
		PCF::board B;
};

namespace EntityPCF
{
	EntityPCF_do P[3];
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
	}
}

#endif

