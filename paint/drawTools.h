#ifndef DRAWTOOLS_H
#define DRAWTOOLS_H

#include "standard.h"
#include "graphics.h"

void drawRect(int x1,int y1,int x2,int y2,int lineWidth,color_t boarder,color_t fill);
void drawLine(int x1,int y1,int x2,int y2,int lineWidth,color_t color);
void drawLine(pii x,pii y,int lineWidth,color_t color);
void drawCircle(int x,int y,int r,int lineWidth,color_t boarder,color_t color);
void textOutMid(int x,int y,LPCSTR str);
void textOutMid(int x,int y,int str,color_t c);
LPCSTR numToStr(int x);

void drawRect(int x1,int y1,int x2,int y2,int lineWidth,color_t boarder,color_t fill)
{
	setlinewidth(lineWidth);
	setcolor(boarder);
	setfillcolor(fill);
	int pt[8]={x1,y1,x2,y1,x2,y2,x1,y2};
	fillpoly(4,pt);
}
void drawLine(int x1,int y1,int x2,int y2,int lineWidth,color_t color)
{
	setlinewidth(lineWidth);
	setcolor(color);
	line(x1,y1,x2,y2);
}
void drawLine(pii x,pii y,int lineWidth,color_t color)
{
	drawLine(x.first,x.second,y.first,y.second,lineWidth,color);
}
void drawCircle(int x,int y,int r,int lineWidth,color_t boarder,color_t color)
{
	setlinewidth(lineWidth);
	setcolor(boarder);
	setfillcolor(color);
	fillellipse(x,y,r,r);
}
void textOutMid(int x,int y,LPCSTR str)
{
	setfont(-12,0,"ËÎÌו");
	setbkmode(TRANSPARENT);
	setcolor(BGR(0,0,255));
	int g=sizeof(str);
	rectprintf(x,y,x+g*15,y+20,str);
}
int GTOM[55];
char GTNUM[10][2]={{'0'},{'1'},{'2'},{'3'},{'4'},{'5'},{'6'},{'7'},{'8'},{'9'}};
void textOutMid(int x,int y,int str,color_t c=BGR(0,0,255))
{
	setfont(-12,0,"ËÎÌו");
	setbkmode(TRANSPARENT);
	setcolor(c);
	int g=0;
	do{GTOM[++g]=str%10;str/=10;}while(str);
	int bias=(ld)g*3;
	for(int i=0;i<g;++i)
		rectprintf(x+i*6-bias,y-6,x+(i+1)*6-bias,y+8,GTNUM[GTOM[g-i]]);
}
LPCSTR numToStr(int x)
{
	int g=0;
	int G[55];
	do{G[++g]=x%10;x/=10;}while(x);
	char*s=new char[g+1];
	for(int i=0;i<g;++i)
		s[i]=G[g-i]+'0';
	s[g]=0;
	return s;
}
#endif

