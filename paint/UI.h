#ifndef UI_H
#define UI_H

#include "standard.h"

///////////////////////////////////////////////////////////status
struct status//状态 
{
	bool click_left;
	bool click_right;
	bool click_down;
	int mouseX,mouseY;
	keyboard key_down;
	keyboard key_up;
	
	status();
	~status(); 
};
status::status()
{
	click_left=click_right=click_down=0;
	mouseX=mouseY=0;
}
status::~status()
{
}

///////////////////////////////////////////////////////////UI
int TOTUID;
class UI
{
public:
	ui posX,posY;//规定：所有UI的左上角为(posX,posY)，分别是从左到右和从上到下 
	ui height,width;//行像素数和列像素数 
	status last,now;
	int UID;
	
	UI();
	~UI();
	UI(ui px,ui py,ui h,ui w);
	void update(status A);
	bool onClick();
	bool onClickUp();
};

UI::UI()
{
	UID=++TOTUID;
}
UI::~UI()
{
}
UI::UI(ui px,ui py,ui h,ui w)
{
	UID=++TOTUID;
	posX=px,posY=py;
	height=h,width=w;
}
void UI::update(status A)
{
	last=now;
	now=A;
}
bool UI::onClick()
{
	return now.click_left&&posX<=now.mouseX&&posY<=now.mouseY&&now.mouseX<=posX+width&&now.mouseY<=posY+height;
}
bool UI::onClickUp()
{
	return last.click_down==1&&posX<=last.mouseX&&posY<=last.mouseY&&last.mouseX<=posX+width&&last.mouseY<=posY+height&&
		   now.click_down==0&&posX<=now.mouseX&&posY<=now.mouseY&&now.mouseX<=posX+width&&now.mouseY<=posY+height;
}
#endif

