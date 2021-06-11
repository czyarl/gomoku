#ifndef DOSPLAY_CPP
#define DOSPLAY_CPP

#include "../entity/Entity.h"
#include "../basic/BasicDef.h"
#include <ctime>

namespace dosplay_func{
	void getNewChar(char c) 
	{
		while(getchar() != c); 
		if(c != '\n') getNewChar('\n');
	}
	void getNum(FILE *Fin, FILE *Fout, int &targ, int cl, int cr)
	{
		while(1)
		{
			int num = fscanf(Fin, "%d", &targ);
			if(num != 1) {
				fprintf(Fout, "bad setting!\n");
				exit(0);
			}
			if(cl <= targ && targ <= cr) break;
			fprintf(Fout, "the value should be a integer in [%d, %d], try again : ", cl, cr);
		}
	}
	void getNum(int &targ, int cl, int cr)
	{
		getNum(stdin, stdout, targ, cl, cr);
	}
}

namespace dos_Record{
	using namespace dosplay_func;
	int ifRecord;
	string fileName;
	FILE *Fout;
	void prepare_Info_record()
	{
		printf("Wanna record and output the results ? (1 yes/0 no)"); getNum(ifRecord, 0, 1); 
	}
	int maxRounds() {return INT_MAX; }
	void tellNewRound(int winner, int val) 
	{
		Fout = fopen("records.txt","at+");
		fprintf(Fout, "%d %d\n", winner, val);
		fclose(Fout);
	}
	void endRecord()
	{
		
	}
}

namespace dosplay{
	using namespace dosplay_func;
	using EntityControl::Player;
	using dos_Record::prepare_Info_record;
	using dos_Record::maxRounds;
	using dos_Record::tellNewRound;
	using dos_Record::endRecord;
	int T;
	Player P1, P2;
	GameType G;
	int setMode;
	FILE *Fset;
	int ifGambit;
	int ifPause_step, ifPause_round; 
	int ifOutput_round, ifOutput_step_pos, ifOutput_step_boa;
	int winTimes[10];

	pair<int, int> ans;
	int whichwin, len, n;
	void prepare_preworkSetup()
	{
		srand(time(NULL));
		winTimes[1] = 0; winTimes[2] = 0;
	}

	void prepare_Info_mode()
	{
		while(1)
		{
			printf("Which setting mode do you wanna use? (1 for default / 0 for manual) "); getNum(setMode, 0, 1); 
			if(setMode == 1) break;
			if(setMode == 0) break;
			if(setMode == 2) {//have not been completed
				Fset = fopen("chess.setting","r");
				if(Fset == NULL) {
					int ifGen;
					printf("Oops! the file does not exit. Do you want to generate and use it? (1 for yes/0 for no)"); getNum(setMode, 0, 1); 
				}
				else break;
			}
			printf("Invalid mode, please try another. \n"); 
		}
	}

	void prepare_Info_chess()
	{
		if(setMode == 1) n = 15;
		else printf("Please enter the size of the square chessboard : "), getNum(n, 1, 1000); 
		if(setMode == 1) G.setClassic(5);
		else printf("Please enter the rule of the game(1 for Classic)(We only have this one currently. ): "), G.getit();
		if(setMode == 1) ifGambit = 0;
		else printf("Wanna get a random gambit ? (1 yes/0 no) : "), getNum(ifGambit, 0, 1);
	}

	void prepare_Info_player()
	{
		printf("Please enter Player 1 (please check readme.md to find the number of each AI) : "); P1.getPlayer();
		printf("Please enter Player 2 (please check readme.md to find the number of each AI) : "); P2.getPlayer();
	}

	void prepare_Info_con()
	{
		dos_Record::prepare_Info_record();
		printf("How many rounds do you want to play ? "); getNum(T, 0, maxRounds()); 
		printf("Attention : you are not suggested to use the pause and output function. \n");
		printf("  Do you want to pause after each step ? (1 for yes/0 for no)"); getNum(ifPause_step, 0, 1); 
		printf("  Do you want to pause after each round ? (1 for yes/0 for no)"); getNum(ifPause_round, 0, 1);
		printf("  Do you want to output positon after each step ? (1 for yes/0 for no)"); getNum(ifOutput_step_pos, 0, 1);
		printf("  Do you want to output board after each step ? (1 for yes/0 for no)"); getNum(ifOutput_step_boa, 0, 1);
		printf("  Do you want to output result after each round ? (1 for yes/0 for no)"); getNum(ifOutput_round, 0, 1);
	}

	void prepare_Round()
	{
		en_startGame(n, G, P1.type, P2.type, ifGambit); whichwin = 0;
	}

	void prepare_Info()
	{
		prepare_Info_mode();
		prepare_Info_chess();
		prepare_Info_player();
		prepare_Info_con();
	}

	int pro_playChess(int PlayerNum)
	{
		ans = en_playChess(PlayerNum, make_pair(-1,-1), whichwin);
		if(ifOutput_step_pos) printf("  Player %d : (%d, %d)\n",PlayerNum,ans.first,ans.second);
		if(ifOutput_step_boa) en_OutitBoard();
		return ans != make_pair(-1,-1);
	}

	void pro_Pause(int ifPause)
	{
		if(ifPause) {
			printf("Please Enter to generate the next");
			getNewChar('\n');
		}
	}

	void endGame(int cn, int cm)
	{
		tellNewRound(cn, cm);
		en_endGame(cn);
		winTimes[cn]++;
		if(ifOutput_round) printf("Player %d win !\n",cn), en_OutitBoard();
		pro_Pause(ifPause_round);	
	}

	void playRound()
	{
		prepare_Round();
		while(1)
		{
			int resBlack = pro_playChess(1);
			if(whichwin) {endGame(whichwin, en_getRoundValue()); break; }
			pro_Pause(ifPause_step);
			int resWhite = pro_playChess(2);
			if(resBlack == 0 && resWhite == 0) whichwin = 3;
			if(whichwin) {endGame(whichwin, en_getRoundValue()); break; }
			pro_Pause(ifPause_step);
		}
	}

	void run_rounds()
	{
		prepare_preworkSetup();
		prepare_Info();
		printf("Press 'c' to start\n"); getNewChar('c'); 
		for(int i = 1;i<=T;i++) playRound();
		endRecord();
		printf("Player 1(black) win : %d\n",winTimes[1]);
		printf("Player 2(white) win : %d\n",winTimes[2]);
		printf("Press 'c' to exit\n"); getNewChar('c'); 
	}
};

#endif
