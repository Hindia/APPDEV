//headers included
#include "screen.h"
#include <stdio.h>

void setFGcolor(int fg){	//function for setting the foreground color
	printf("\033[%d;1m",fg);
	fflush(stdout);
}

void resetColors(void){	//function for reseting the color
	printf("\033[0m");
	fflush(stdout);
}

void gotoXY(int row, int col){	//function to  move the cursor on screen
	printf("\033[%d;%dH", row, col);
	fflush(stdout);
}

void clearScreen(void){	//function to clear the screen
	printf("\033[2J");
	fflush(stdout);
}

void displayBar(double rms, int col){	//function to display bar used for the bargraph
	int i;
	for(i=0; i<rms/3; i++){
		gotoXY(40-i,col);
#ifndef UNICODE	//if UNICODE is not defined we use stars to draw the graph
		printf("*");
#else
		printf("%s", BAR);
#endif
	}
	fflush(stdout);
}
