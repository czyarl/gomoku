#include "dosplay/dosplay.h"
#include <cstdio>
#include <ctime>
#include <stdlib.h>
int main()
{
	int typ; srand(time(NULL));
	printf("Welcome to our Gomoku algorithm testing platform. \n");
	printf("Check readme.md for more detailed information. \n");
	typ = 2;
	if(typ == 2) {
		run_rounds();
	}
	return 0;
}

