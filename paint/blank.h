#ifndef BLANK_H
#define BLANK_H

#include "UI.h"
#include "standard.h"
#include "drawTools.h"

class blank:public UI
{
public:
	LPCSTR name;
	
	blank();
	blank(LPCSTR x);
	void draw(bool hover);
	void(*runCommand)(blank&A);
};
blank::blank()
{
};
blank::blank(LPCSTR x)
{
	name=x;
}
void blank::draw(bool hover)
{
	if(hover)
		drawRect(posX,posY,posX+width,posY+height,2,BGR(30,30,30),BGR(190,255,190));
	else
		drawRect(posX,posY,posX+width,posY+height,2,BGR(30,30,30),BGR(210,210,210));
	setfont(-12,0,"ËÎÌו");
	setbkmode(TRANSPARENT);
	setcolor(BGR(20,20,20));
	rectprintf(posX+5,posY+2,posX+width-5,posX+height-5,name);
}
#endif

