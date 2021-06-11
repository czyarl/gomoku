#ifndef BUTTON_H
#define BUTTON_H

#include "UI.h"
#include "standard.h"
#include "drawTools.h"

class button:public UI
{
public:
	LPCSTR name;
	
	button();
	button(LPCSTR x);
	void draw();
	void(*runCommand)(button&A);
	void run();
};
button::button()
{
};
button::button(LPCSTR x)
{
	name=x;
}
void button::draw()
{
	if(onClick())
		drawRect(posX,posY,posX+width,posY+height,2,BGR(30,30,30),BGR(120,120,120));
	else
		drawRect(posX,posY,posX+width,posY+height,2,BGR(30,30,30),BGR(240,240,240));
	if(onClickUp())
		runCommand(*this);
	setfont(-12,0,"ËÎÌו");
	setbkmode(TRANSPARENT);
	setcolor(BGR(20,20,20));
	rectprintf(posX+5,posY+2,posX+width-5,posY+height-5,name);
}
void button::run()
{
	draw();
}
#endif

