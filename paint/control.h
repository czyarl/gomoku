#ifndef CONTROL_H
#define CONTROL_H

#include "standard.h"
#include "../entity/EntityControl.h"
#include "controlHeader.h"
#include "board.h"
#include "button_start.h"
#include "list_player1.h"
#include "list_player2.h"

void con_NewGame()
{
	if(con_start_countdown>0)
		return;
	con_gameStart=1;
	con_id_player1=l_player1.what();
	con_id_player2=l_player2.what();
	con_nowPlayer=1;
	cout<<con_id_player1<<" "<<con_id_player2<<endl;
	con_start_countdown=20;
	
	GameType G;
	G.typ=1;
	G.len=5;
	en_startGame(webSize,G,con_id_player1,con_id_player2);
}
void runGame()
{
	--con_gameClick;
	if(con_gameStart!=2||con_gameClick>0)
		return;
	if(con_nowPlayer==1)
	{
		int ok=0;
		if(con_id_player1==0)
		{
			pii x=chessboard.run();
			if(x.first==-1)
				return;
			con_gameClick=10; 
			x=en_playChess(1,x,ok);
			if(x.first!=-1)
			{
				con_nowPlayer=2;
				chessboard.put(x.first,x.second,1);
				chessboard.draw();
			}
		}
		else
		{
			pii x=en_playChess(1,pii(-1,-1),ok);
			if(x.first!=-1)
			{
				con_nowPlayer=2;
				chessboard.put(x.first,x.second,1);
				chessboard.draw();
			}
		}
		if(ok)
		{
			chessboard.win();
			cout<<"Black wins !"<<endl;
			con_gameStart=0;
			return;
		}
	}
	else
	{
		int ok=0;
		if(con_id_player2==0)
		{
			pii x=chessboard.run();
			if(x.first==-1)
				return;
			con_gameClick=10;
			x=en_playChess(2,x,ok);
			if(x.first!=-1)
			{
				con_nowPlayer=1;
				chessboard.put(x.first,x.second,2);
				chessboard.draw();
			}
		}
		else
		{
			pii x=en_playChess(2,pii(-1,-1),ok);
			if(x.first!=-1)
			{
				con_nowPlayer=1;
				chessboard.put(x.first,x.second,2);
				chessboard.draw();
			}
		}
		if(ok)
		{
			chessboard.win();
			cout<<"White wins !"<<endl;
			con_gameStart=0;
			return;
		}
	}
}
void con_showNum(bool x)
{
	chessboard.showNum=x;
	chessboard.draw();
}
void con_Undo()
{
	if(con_gameStart!=2)
		return;
	pii x=en_PreviousStep();
	cout<<x.first<<" "<<x.second<<endl;
	if(x.first==-1)
		return;
	chessboard.put(x.first,x.second,0,1);
	chessboard.tot-=1;
	chessboard.draw();
	if(con_nowPlayer==1)
		con_nowPlayer=0;
	else
		con_nowPlayer=1;
}
#endif

