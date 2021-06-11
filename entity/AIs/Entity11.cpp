#include<bits/stdc++.h>
#ifndef ENTITY11_CPP
#define ENTITY11_CPP

#include "AIHeader.h"
using namespace std;
namespace Entity11_out{

using clk=chrono::steady_clock;
int LEN,mx_dep=9,nod_cnt,time_lim=10000;
decltype(clk::now()) stime;
bool time_out;
const int limits[]={15,7,5,5,4,4,4,4,3,3,3,3,3,3};
struct game{
	int a[21][21],tag,s[21][21][4][2],mxx,mnx,mxy,mny;
	void clear(){
		memset(s,0,sizeof(s));
		memset(a,0,sizeof(a));tag=0;
		mnx=mny=LEN/2,mxx=mxy=LEN/2;
	}
	game(){
		clear();
	}
	void print(){
		cerr<<"********************************************\n";
		cerr<<"  ";
		for(int i=1;i<=LEN;i++) cerr<<' '<<i%10;cerr<<'\n';
		for(int i=1;i<=LEN;i++){
			cerr<<i%10<<' ';
			for(int j=1;j<=LEN;j++)
				cerr<<' '<<".#@"[a[i][j]];
			cerr<<'\n';
		}
	}
	void set_impl(int x,int y,int tag){
		assert(a[x][y]==0);
		a[x][y]=tag+1;
		mxx=max(mxx,x);mnx=min(mnx,x);
		mxy=max(mxy,y);mny=min(mny,y);
		int tx=x,ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][0][tag]++;
			tx--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][1][tag]++;
			ty--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][2][tag]++;
			tx--;ty--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty>LEN) break;
			s[tx][ty][3][tag]++;
			tx--;ty++;
		}
	}
	void set(int x,int y){set_impl(x,y,tag);tag^=1;}
	void reset(int x,int y){
		//not back up mn mx
		assert(a[x][y]==(tag^1)+1);
		a[x][y]=0;tag^=1;	
		int tx=x,ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][0][tag]--;
			tx--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][1][tag]--;
			ty--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][2][tag]--;
			tx--;ty--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty>LEN) break;
			s[tx][ty][3][tag]--;
			tx--;ty++;
		}
	}
	int finish(){
		for(int i=1;i<=LEN;i++)
			for(int j=1;j<=LEN;j++)
				for(int k=0;k<4;k++){
					if(s[i][j][k][1]==5) return 2;
					if(s[i][j][k][0]==5) return 1;
				}
		return 0;
	}
};
class my_AI{
	int Debug,h[21][21];
	double p[21][21];
	public:
	double calc(game&G){
		++nod_cnt;
		double mP[6]={0,10,20000,50000,-10100,1e100};
		double oP[6]={0,-100,-29990,-2e6,-1e40,-1e100};
		double ans=0;
		int mC=0,oC=0,dx=0,dy=-1,tag=1;
		memset(h,0,sizeof(h));
		for(int i=1;i<=LEN;i++){
			for(int j=1;j<=LEN-4;j++){
				if(G.s[i][j][tag][0]&&G.s[i][j][tag][1]) continue;
				int mS=G.s[i][j][tag][G.tag^1],oS=G.s[i][j][tag][G.tag];
				if(mS) ans+=mP[mS];
				else ans+=oP[oS];
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&mS>=4&&G.s[i+dx][j+dy][tag][G.tag^1]>=4&&!G.s[i+dx][j+dy][tag][G.tag]) ans+=1e30;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&oS>=4&&G.s[i+dx][j+dy][tag][G.tag]>=4&&!G.s[i+dx][j+dy][tag][G.tag^1]) ans-=1e50;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&mS>=3&&G.s[i+dx][j+dy][tag][G.tag^1]>=3&&!G.s[i+dx][j+dy][tag][G.tag]&&!h[i+dx][j+dy]) mC++,h[i][j]=1;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&oS>=3&&G.s[i+dx][j+dy][tag][G.tag]>=3&&!G.s[i+dx][j+dy][tag][G.tag^1]&&!h[i+dx][j+dy]) oC++,h[i][j]=1;
			}
		}
		memset(h,0,sizeof(h));
		dx=-1;dy=0;tag=0;
		for(int i=1;i<=LEN-4;i++){
			for(int j=1;j<=LEN;j++){
				if(G.s[i][j][tag][0]&&G.s[i][j][tag][1]) continue;
				int mS=G.s[i][j][tag][G.tag^1],oS=G.s[i][j][tag][G.tag];
				if(mS) ans+=mP[mS];
				else ans+=oP[oS];
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&mS>=4&&G.s[i+dx][j+dy][tag][G.tag^1]>=4&&!G.s[i+dx][j+dy][tag][G.tag]) ans+=1e30;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&oS>=4&&G.s[i+dx][j+dy][tag][G.tag]>=4&&!G.s[i+dx][j+dy][tag][G.tag^1]) ans-=1e50;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&mS>=3&&G.s[i+dx][j+dy][tag][G.tag^1]>=3&&!G.s[i+dx][j+dy][tag][G.tag]&&!h[i+dx][j+dy]) mC++,h[i][j]=1;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&oS>=3&&G.s[i+dx][j+dy][tag][G.tag]>=3&&!G.s[i+dx][j+dy][tag][G.tag^1]&&!h[i+dx][j+dy]) oC++,h[i][j]=1;
			}
		}
		memset(h,0,sizeof(h));
		dx=-1;dy=-1;tag=2;
		for(int i=1;i<=LEN-4;i++){
			for(int j=1;j<=LEN-4;j++){
				if(G.s[i][j][tag][0]&&G.s[i][j][tag][1]) continue;
				int mS=G.s[i][j][tag][G.tag^1],oS=G.s[i][j][tag][G.tag];
				if(mS) ans+=mP[mS];
				else ans+=oP[oS];
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&mS>=4&&G.s[i+dx][j+dy][tag][G.tag^1]>=4&&!G.s[i+dx][j+dy][tag][G.tag]) ans+=1e30;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&oS>=4&&G.s[i+dx][j+dy][tag][G.tag]>=4&&!G.s[i+dx][j+dy][tag][G.tag^1]) ans-=1e50;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&mS>=3&&G.s[i+dx][j+dy][tag][G.tag^1]>=3&&!G.s[i+dx][j+dy][tag][G.tag]&&!h[i+dx][j+dy]) mC++,h[i][j]=1;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&oS>=3&&G.s[i+dx][j+dy][tag][G.tag]>=3&&!G.s[i+dx][j+dy][tag][G.tag^1]&&!h[i+dx][j+dy]) oC++,h[i][j]=1;
			}
		}
		memset(h,0,sizeof(h));
		dx=-1;dy=1;tag=3;
		for(int i=1;i<=LEN-4;i++){
			for(int j=5;j<=LEN;j++){
				if(G.s[i][j][tag][0]&&G.s[i][j][tag][1]) continue;
				int mS=G.s[i][j][tag][G.tag^1],oS=G.s[i][j][tag][G.tag];
				if(mS) ans+=mP[mS];
				else ans+=oP[oS];
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&mS>=4&&G.s[i+dx][j+dy][tag][G.tag^1]>=4&&!G.s[i+dx][j+dy][tag][G.tag]) ans+=1e30;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&oS>=4&&G.s[i+dx][j+dy][tag][G.tag]>=4&&!G.s[i+dx][j+dy][tag][G.tag^1]) ans-=1e50;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&mS>=3&&G.s[i+dx][j+dy][tag][G.tag^1]>=3&&!G.s[i+dx][j+dy][tag][G.tag]&&!h[i+dx][j+dy]) mC++,h[i][j]=1;
				if(i+dx>0&&j+dy>0&&j+dy<=LEN&&oS>=3&&G.s[i+dx][j+dy][tag][G.tag]>=3&&!G.s[i+dx][j+dy][tag][G.tag^1]&&!h[i+dx][j+dy]) oC++,h[i][j]=1;
			}
		}
		if(Debug) cerr<<oC<<' '<<mC<<'\n';
		if(oC>0) ans-=1e13;
		if(oC>1) ans-=1e25;
		if(mC>0) ans+=2e7;
		if(mC>1) ans+=1e10;
		return ans+1.0*rand()/RAND_MAX;
	}
	my_AI(){Debug=0;}
	vector<pair<int,int> > get_nxts(game G){
		memset(p,0,sizeof(p));
		vector<pair<int,int> > V;
		int lx=max(1,G.mnx-2),rx=min(G.mxx+2,LEN);
		int ly=max(1,G.mny-2),ry=min(G.mxy+2,LEN);
		for(int i=lx;i<=rx;i++)
			for(int j=ly;j<=ry;j++){
				if(G.a[i][j]) continue;
				G.set(i,j);
				p[i][j]=calc(G);
				V.emplace_back(i,j);
				G.reset(i,j);
			}
		sort(V.begin(),V.end(),[&](pair<int,int> a,pair<int,int> b){
			return p[a.first][a.second]>p[b.first][b.second];
		});
		return V;
	}
	double debug(int x,int y,game G){
		G.set(x,y);
		Debug=1;
		double ans=calc(G);
		Debug=0;
		return ans;
	}
};

class Entity11_do
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
		my_AI p;
		game G;
double search(game G,int x,int y,int dep,double A,double B){
	if(clk::now()-stime>time_lim*1ms){time_out=true;return 0;}
	G.set(x,y);
	if(dep==mx_dep) return p.calc(G);
	if(dep&1){
		if(G.finish()) return 1e100;
		auto v=p.get_nxts(G);
		int cnt=0;
		double mn=1e200;
		for(auto&pr:v){
			if(++cnt>limits[dep]) break;
			mn=min(mn,search(G,pr.first,pr.second,dep+1,A,B));
			if(time_out)return 0;
			B=min(B,mn);
			if(B<=A) break;
		}
		return mn;
	}
	else{
		if(G.finish()) return -1e100;
		auto v=p.get_nxts(G);
		int cnt=0;
		double mx=-1e200;
		for(auto&pr:v){
			if(++cnt>limits[dep]) break;
			mx=max(mx,search(G,pr.first,pr.second,dep+1,A,B));
			if(time_out)return 0;
			A=max(A,mx);
			if(B<=A) break;
		}
		return mx;
	}
}
pair<int,int> Search_for_next(game G,double*ret=NULL){
	stime=clk::now();time_out=false;nod_cnt=0;
	auto v=p.get_nxts(G);
	if(v.empty()){
		if(ret)*ret=0;
		return {LEN+1>>1,LEN+1>>1};
	}
	if(v.size()>limits[0])v.resize(limits[0]);
	pair<int,int> onxt;double oval=-1e200;
	static double ev[21][21];
	for(mx_dep=5;mx_dep<14;mx_dep+=2){
		double A=-1e200,B=1e200;
		pair<int,int> nxt;double val=-1e200;
		for(auto&pr:v){
			double vl=search(G,pr.first,pr.second,1,A,B);
			ev[pr.first][pr.second]=vl;
			if(time_out){
				if(ret)*ret=oval;
				return onxt;
			}
//			printf("%d %d %.1lf\n",pr.first,pr.second,vl);
			if(vl>val) val=vl,nxt=pr;
			A=max(A,vl);
		}
//		if(abs(val)>1e50){if(ret)*ret=val;return nxt;}
		onxt=nxt,oval=val;
		sort(v.begin(),v.end(),[&](pair<int,int> a,pair<int,int> b){
			return ev[a.first][a.second]>ev[b.first][b.second];
		});
		v.resize(ceil(v.size()*0.7));
		cerr<<mx_dep<<endl;
	}
	return onxt;
}
		void do_endGame(int winner){}
		void do_prepare(){
			LEN = n;
			G.clear();
		}
		void do_setPos(pair<int, int> cn, int cm)
		{
			G.set(cn.first,cn.second);
		}
		int do_resetPos(pair<int, int> cn, int cm) 
		{
			G.reset(cn.first, cn.second);
			return 0;
		}
		pair<int, int> do_playChess()
		{
			int nx,ny;double vl;tie(nx,ny)=Search_for_next(G,&vl);
			return make_pair(nx,ny);
		}
};
}
		
namespace Entity11
{
	Entity11_out::Entity11_do P[3];
	void entity_startGame(chessBoard &Boa, GameType &cn, int cm)
	{
		srand(time(NULL));
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

