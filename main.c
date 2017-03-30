#include "wave.h"
#include "screen.h"
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h> //eliminates warning when -c99 is used

//this program will open a wave file, and display WAV header info if DEBUG is enabled

int main(int argc, char *argv[]){
	FILE *fp;
	WAVHDR myhdr;
	short int sa[SAMPLE_RATE];
	int answer, ret;
	for(;;){	//starts a never ending loop)
	  	ret=system("arecord -r16000 -c1 -d1 -f S16_LE -q data.wav");
	  	if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT || WTERMSIG(ret)==SIGQUIT))break;
		clearScreen();
	  	fp=fopen("data.wav", "r");
	  	fread(&myhdr, sizeof(myhdr), 1, fp);
	  	displayWAVHDR(myhdr);
          	fread(&sa, sizeof(short int), SAMPLE_RATE, fp);
		displayWAVdata(sa);
		fclose(fp);
	}
	printf("wanna generate a test tone?(1: yes, 0:no)\n");
	scanf("%d", &answer);
	if(answer==1)TestTone(440, 5);
}
