#include "paint/paint.h"
#include "dosplay/dosplay.h"
#include <cstdio>
#include <ctime>
#include <stdlib.h>
int main()
{
	int typ; srand(time(NULL));
	printf("Welcome to our Gomoku algorithm testing platform. \n");
	printf("Check readme.md for more detailed information. \n");
	printf("Please enter mode (1 for UI; 2 for dos) : "); scanf("%d",&typ);
	if(typ == 1) {
		int width=1000,height=600;
		run(width,height);
	}
	else if(typ == 2) {
		run_rounds();
	}
	else {
		printf("csl txdy! he found this bug but I do not wanna fix it. \n");
	}
	return 0;
}

