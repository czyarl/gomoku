#ifndef LIST_H
#define LIST_H

#include "UI.h"
#include "standard.h"
#include "blank.h"
#include "drawTools.h"

class list:public UI
{
public:
	LPCSTR name;
	ui wordHeight;
	vector<blank>blanks;
	int chosen;
	
	list();
	list(LPCSTR x);
	list(LPCSTR x,ui h);
	void draw();
	void(*runCommand)(list&A);
	void run();
	void pushBlank(const blank&A);
	int what();
};
list::list()
{
	chosen=-1;
	wordHeight=22;
};
list::list(LPCSTR x)
{
	chosen=-1;
	name=x;
	wordHeight=22;
}
list::list(LPCSTR x,ui h)
{
	chosen=-1;
	name=x;
	wordHeight=h;
}
void list::draw()
{
	drawRect(posX,posY,posX+width,posY+height,2,BGR(30,30,30),BGR(210,210,210));
	drawRect(posX,posY,posX+width,posY+wordHeight,2,BGR(30,30,30),BGR(240,240,240));
	setfont(-12,0,"ËÎÌו");
	setbkmode(TRANSPARENT);
	setcolor(BGR(20,20,20));
	rectprintf(posX+5,posY+2,posX+width-5,posY+wordHeight-5,name);
	
	for(int i=0;i<blanks.size();++i)
	{
		blanks[i].posX=posX;
		blanks[i].posY=posY+wordHeight*2+(i-1)*20;
		blanks[i].width=width;
		blanks[i].height=20;
		if(blanks[i].onClick())
			chosen=i;
		blanks[i].draw(chosen==i);
	}
}
void list::run()
{
	for(int i=0;i<blanks.size();++i)
		blanks[i].update(now);
	draw();
}
void list::pushBlank(const blank&A)
{
	blanks.push_back(A);
}
int list::what()
{
	return chosen;
}
#endif

