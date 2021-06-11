#ifndef BOARD_H
#define BOARD_H

#include "UI.h"
#include "standard.h"
#include "drawTools.h"

const int bias=30;
const int boardSize=500;
const int blockLen=40;
const int webSize=15;

class board:public UI
{
public:
	int n;
	int a[21][21];
	int tot;
	int num[21][21];
	bool showNum;
	
	board();
	board(int x);
	bool put(int x,int y,int z,int clear=0);
	void draw();
	pii (*runCommand)(board&A);
	pii run();
	void clear();
	bool outOfRange(int x,int y);
	bool win();
	pii getPos(int x,int y);
};
board::board()
{
	tot=n=0;
	showNum=1;
	memset(a,0,sizeof(a));
}
board::board(int x)
{
	n=x;
	tot=0;
	showNum=1;
	memset(a,0,sizeof(a));
}
bool board::put(int x,int y,int z,int clear)
{
	if(clear==0&&a[x][y]!=0)
		return 0;
	a[x][y]=z;
	if(clear==0)
		num[x][y]=++tot;
	return 1;
}
void board::draw()
{
	drawRect(posX,posY,posX+width,posY+height,10,BGR(27,105,185),BGR(70,160,233));
	int del=boardSize/(n-1);
	int radius=boardSize/n/2;
	int maxx=posX+bias+(n-1)*del;
	for(int i=1;i<=n;++i)
		drawLine(posX+bias,posY+bias+(i-1)*del,maxx,posY+bias+(i-1)*del,2,0);
	for(int i=1;i<=n;++i)
		drawLine(posX+bias+(i-1)*del,posY+bias,posX+bias+(i-1)*del,maxx,2,0);
		
	drawCircle(posX+bias+(n/2)*del,posY+bias+(n/2)*del,5,1,0,0);
		
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			if(a[i][j]==1)
			{
				drawCircle(posX+bias+(i-1)*del,posY+bias+(j-1)*del,radius,1,BGR(10,10,10),BGR(20,20,20));
				if(showNum)
					if(num[i][j]==tot)
						textOutMid(posX+bias+(i-1)*del,posY+bias+(j-1)*del,num[i][j],BGR(0,0,255));
					else
						textOutMid(posX+bias+(i-1)*del,posY+bias+(j-1)*del,num[i][j],BGR(255,255,255));
			}
			else if(a[i][j]==2)
			{
				drawCircle(posX+bias+(i-1)*del,posY+bias+(j-1)*del,radius,1,BGR(230,230,230),BGR(250,250,250));
				if(showNum)
					if(num[i][j]==tot)
						textOutMid(posX+bias+(i-1)*del,posY+bias+(j-1)*del,num[i][j],BGR(0,0,255));
					else
						textOutMid(posX+bias+(i-1)*del,posY+bias+(j-1)*del,num[i][j],BGR(0,0,0));
			}
		}
	bool g=win();
}
pii board::run()
{
	return runCommand(*this);
}
void board::clear()
{
	tot=0;
	memset(a,0,sizeof(a));
}
bool board::outOfRange(int x,int y)
{
	return !(1<=x&&x<=n&&1<=y&&y<=n&&a[x][y]==0);
}
bool board::win()
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n-4;++j)
			if(a[i][j]!=0&&a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2]&&a[i][j]==a[i][j+3]&&a[i][j]==a[i][j+4])
			{
				drawLine(getPos(i,j),getPos(i,j+4),5,BGR(0,0,255));
				return true;
			}
	for(int i=1;i<=n-4;++i)
		for(int j=1;j<=n;++j)
			if(a[i][j]!=0&&a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j]&&a[i][j]==a[i+3][j]&&a[i][j]==a[i+4][j])
			{
				drawLine(getPos(i,j),getPos(i+4,j),5,BGR(0,0,255));
				return true;
			}
	for(int i=1;i<=n-4;++i)
		for(int j=1;j<=n-4;++j)
			if(a[i][j]!=0&&a[i][j]==a[i+1][j+1]&&a[i][j]==a[i+2][j+2]&&a[i][j]==a[i+3][j+3]&&a[i][j]==a[i+4][j+4])
			{
				drawLine(getPos(i,j),getPos(i+4,j+4),5,BGR(0,0,255));
				return true;
			}
	for(int i=5;i<=n;++i)
		for(int j=1;j<=n-4;++j)
			if(a[i][j]!=0&&a[i][j]==a[i-1][j+1]&&a[i][j]==a[i-2][j+2]&&a[i][j]==a[i-3][j+3]&&a[i][j]==a[i-4][j+4])
			{
				drawLine(getPos(i,j),getPos(i-4,j+4),5,BGR(0,0,255));
				return true;
			}
	return false;
}
pii board::getPos(int x,int y)
{
	int del=boardSize/(n-1);
	return pii(posX+bias+(x-1)*del,posY+bias+(y-1)*del);
}
//////////////////////////////////////////////////////////////////////////////
pii runCommand_chessboard(board&A)
{
	if(A.onClick())
	{
		int x=A.now.mouseX,y=A.now.mouseY;
		int del=boardSize/(A.n-1);
		int posX=round((ld)(x-bias-A.posX)/del)+1;
		int posY=round((ld)(y-bias-A.posY)/del)+1;
		if(A.outOfRange(posX,posY))
			return pii(-1,-1);
		return pii(posX,posY);
	}
	return pii(-1,-1);
}

board chessboard(webSize);

#endif

