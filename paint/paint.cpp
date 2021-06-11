#ifndef PAINT_CPP
#define PAINT_CPP

#include "graphics.h"
#include "standard.h"
#include "drawTools.h"
#include "button.h"

#include "../entity/EntityControl.h"
///////////////////////////////////////////////////////
#include "controlHeader.h"

#include "board.h"

#include "button_start.h"
//button b_start("start");

#include "button_show.h"
//button b_start("show");

#include "button_hide.h"
//button b_start("hide");

#include "button_quit.h"
//button b_start("quit");

#include "button_undo.h"
//button b_start("undo");

#include "list_player1.h"
//list l_player1("Player 1");

#include "list_player2.h"
//list l_player2("Player 2");

#include "../entity/AIs/declaration.h"

///////////////////////////////////////////////////////

#include "control.h"

void init()
{
	chessboard.posX=10,chessboard.posY=10;
	chessboard.width=560,chessboard.height=560;
	chessboard.runCommand=runCommand_chessboard;
//////////////////////////////////////////////////////
	b_start.posX=580,b_start.posY=10;
	b_start.width=40,b_start.height=20;
	b_start.name="start";
	b_start.runCommand=runCommand_b_start;
//////////////////////////////////////////////////////
	b_show.posX=580,b_show.posY=40;
	b_show.width=40,b_show.height=20;
	b_show.name="show";
	b_show.runCommand=runCommand_b_show;
//////////////////////////////////////////////////////
	b_hide.posX=630,b_hide.posY=40;
	b_hide.width=40,b_hide.height=20;
	b_hide.name="hide";
	b_hide.runCommand=runCommand_b_hide;
//////////////////////////////////////////////////////
	b_quit.posX=580,b_quit.posY=70;
	b_quit.width=40,b_quit.height=20;
	b_quit.name="quit";
	b_quit.runCommand=runCommand_b_quit;
//////////////////////////////////////////////////////
//	b_undo.posX=580,b_undo.posY=100;
//	b_undo.width=40,b_undo.height=20;
//	b_undo.name="undo";
//	b_undo.runCommand=runCommand_b_undo;
//////////////////////////////////////////////////////
	l_player1.posX=680,l_player1.posY=10;
	l_player1.width=120,l_player1.height=400;
	l_player1.name="Player 1";
	for(int i=0;i<AI_LEN;++i)
	{
		blank B;
		B.name=AI_NAMES[i];
		l_player1.pushBlank(B);
	}
	l_player1.chosen=0;
//////////////////////////////////////////////////////
	l_player2.posX=810,l_player2.posY=10;
	l_player2.width=120,l_player2.height=400;
	l_player2.name="Player 2";
	for(int i=0;i<AI_LEN;++i)
	{
		blank B;
		B.name=AI_NAMES[i];
		l_player2.pushBlank(B);
	}
	l_player2.chosen=0;
//////////////////////////////////////////////////////
}

void updateAll(status x)
{
	if(con_gameStart==1)
	{
		con_gameStart=2;
		chessboard.clear();
		chessboard.draw();
	}
	chessboard.update(x);
	/*
	pii p=chessboard.run();
	if(p.first!=-1)
	{
		chessboard.a[p.first][p.second]=1;
		chessboard.draw();
	}
	*/
//////////////////////////////////////////////////////
	b_start.update(x);
	b_start.run();
//////////////////////////////////////////////////////
	b_show.update(x);
	b_show.run();
//////////////////////////////////////////////////////
	b_hide.update(x);
	b_hide.run();
//////////////////////////////////////////////////////
	b_quit.update(x);
	b_quit.run();
//////////////////////////////////////////////////////
//	b_undo.update(x);
//	b_undo.run();
//////////////////////////////////////////////////////
	l_player1.update(x);
	l_player1.run();
//////////////////////////////////////////////////////
	l_player2.update(x);
	l_player2.run();
	
	--con_start_countdown;
	runGame();
}

void run(int width,int height)
{
    initgraph(width,height,0);
	setcaption("ëFýbû˜");
    init();
    chessboard.a[2][3]=1;
    chessboard.a[3][2]=2;
    chessboard.draw();
    b_start.draw();
    for(;is_run();delay_fps(60))
    {
    	mouse_msg msg;
    	if(mousemsg())
			msg=getmouse();
		
   		status x;
   		x.click_left=msg.is_left();
   		x.click_down=msg.is_down();
   		x.mouseX=msg.x;
   		x.mouseY=msg.y;
   		updateAll(x);
	}
    closegraph();
}
#endif

