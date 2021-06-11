#ifndef ENTITYCONTROL_CPP
#define ENTITYCONTROL_CPP

#include<iostream>
#include "../basic/BasicDef.h"
#include "Entity.h"
#include "AIs/initAIs.h"
#include <string>

namespace EntityControl
{
	using std::to_string;
	using std::string;

	const int MaxEntityType = 100;
	const int MaxEntityNum = 2;
	const int MaxRound = 100;
	const int MaxUndoLength = 1000;

	const int PlayerHuman = 0;
	chessBoard B;
	GameType G;
	Player P[3];//.type == 0 for Human
	int CurRound = 0;

	struct Info_type{
		string Info_s;
		void clear() {Info_s.clear(); }
		void add(char c, pair<int, int> cn, int cm)
		{
			Info_s += c;
			Info_s += ' '; Info_s += to_string(cn.first);
			Info_s += ' '; Info_s += to_string(cn.second);
			Info_s += ' '; Info_s += to_string(cm);
		}
	} Info[MaxRound+1];

	struct Undo_Unit {
		pair<int, int> pos;
		int role;
		void mk(pair<int, int> cn, int cm) {pos = cn; role = cm; }
	};
	struct Undo_type {
		Undo_Unit stack[MaxUndoLength];
		int slen;
		int cur_top;
		void clear()
		{
			slen = 0; 
			cur_top = 0;
		}
		void push(pair<int, int> cn, int cm) 
		{
			slen = cur_top;
			Info[CurRound].add('s', cn, cm);
			stack[++slen].mk(cn, cm);
			Info[CurRound].add('s', cn, cm);
			cur_top = slen;
		}
		pair<int, int> pop()
		{
			if(!cur_top) return make_pair(-1, -1);
			Info[CurRound].add('u', stack[cur_top].pos, stack[cur_top].role);
			cur_top--;
			int x=stack[cur_top+1].pos.first;
			int y=stack[cur_top+1].pos.second;
			B.a[x][y]=0;
			if(P[1].type!=PlayerHuman)
				P[1].resetPos(stack[cur_top+1].pos,0,1);
			if(P[2].type!=PlayerHuman)
				P[2].resetPos(stack[cur_top+1].pos,0,2);
			return stack[cur_top+1].pos;
		}
		pair<int, int> unpop()
		{
			if(cur_top == slen) return make_pair(-1, -1);
			cur_top++;
			Info[CurRound].add('r', stack[cur_top].pos, stack[cur_top].role);
			return stack[cur_top].pos;
		}
	} Undo[MaxRound];

	void Player::setPlayer(int cn)
	{
		now_type = type = cn;
		initAIs(*this,cn);
	}

	void Player::getPlayer()
	{
		while(1)
		{
			scanf("%d", &type);
			if(1<=type && type<=MaxEntityType) break;
			printf("Invalid Entity, Please try another : ");
		}
		setPlayer(type);
	}

	pair<int,int> en_playChess_do(int role, pair<int, int> ans, int &status); 

	void en_startGame(int size, GameType &cG, int PlayerBlack, int PlayerWhite, int ifGambit)
	{
		CurRound = (CurRound+1)%MaxRound;
		B.clear(size, size);
		G = cG;
		P[1].setPlayer(PlayerBlack);
		P[2].setPlayer(PlayerWhite);
		if(PlayerBlack!=PlayerHuman)
			P[1].startGame(B, G, 1);
		if(PlayerWhite!=PlayerHuman)
			P[2].startGame(B, G, 2);
		Info[CurRound].clear();
		Undo[CurRound].clear();
		
		static vector<pair<int, pair<int, int> > > V;
		if(ifGambit) {
			B.setGambit(ifGambit, V);
			int lin;
			for(auto i : V) en_playChess_do(i.first, i.second, lin);
		}
	}

	pair<int,int> en_playChess_do(int role, pair<int, int> ans, int &status)
	{
		if(!B.setPos(ans,role))
			ans = make_pair(-1,-1);
		else
		{
			if(P[1].type!=PlayerHuman)
				P[1].setPos(ans, role, 1);
			if(P[2].type!=PlayerHuman)
				P[2].setPos(ans, role, 2);
		}
		status = B.checkWin(G);
		if(ans.first != -1) Undo[CurRound].push(ans, role);
		return ans;
	}

	pair<int,int> en_playChess(int role, pair<int, int> ans, int &status)
	{
//		printf("in en_playChess : role = %d\n",role);
		if(P[role].now_type != P[role].type)
			P[role].setPlayer(P[role].type), P[role].startGame(B, G, role);
		if(P[role].type != PlayerHuman)
			ans = P[role].playChess(B, G, role);
		return en_playChess_do(role, ans, status);
	}

	void en_endGame(int cn)
	{
		P[1].endGame(cn, 1);
		P[2].endGame(cn, 2);
		return;
	}
	int en_getRoundValue()
	{
		return B.getValue();
	}
	void en_OutitBoard()
	{
		B.std_outit();
	}
	pair<int, int> en_PreviousStep()
	{
		return Undo[CurRound].pop();
	}
	pair<int, int> en_NextStep()
	{
		return Undo[CurRound].unpop();
	}
	string en_GetOpeStr()
	{
		return Info[CurRound].Info_s;
	}

}


#endif
