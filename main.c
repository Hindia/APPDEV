/*this program is just for testing. it is not part of the project*/

#include "wave.h"	//use double quotes if you are using your own header. for c library headers we use angular brackets
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <sys/wait.h>
#include "screen.h"
#include <stdlib.h> //eliminates warning when -c99 is used
//void printID(char []);	not needed because it has been defined  in header file
//this program will open a wave file, and display WAV header info

int main(int argc, char *argv[]){
	FILE *fp;
	WAVHDR myhdr;
	short int sa[SAMPLE_RATE];
	int answer, ret;
     /*	if(argc != 2){
		printf("Usage: %s wav_file\n", argv[0]);
		return -1;
	}
	fp=fopen(argv[1], "r");
	if(fp == NULL){
		printf("cannot find the file %s\n", argv[1]);
		return -1;
	}*/
	for(;;){	//can also use while(1)
	  ret=system("arecord -r16000 -c1 -d1 -f S16_LE -q data.wav");
	  if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT || WTERMSIG(ret)==SIGQUIT))break;
	clearScreen();
	  fp=fopen("data.wav", "r");		
	  fread(&myhdr, sizeof(myhdr), 1, fp);
		//printID(myhdr.ChunkID);	//not needed because of the display function declared in the header file
		//printf("ChunkID: %c%c%c%c\n", myhdr.ChunkID[0], myhdr.ChunkID[1], myhdr.ChunkID[2], myhdr.ChunkID[3]);
	  displayWAVHDR(myhdr);
          fread(&sa, sizeof(short int), SAMPLE_RATE, fp);
          displayWAVdata(sa);
	  fclose(fp);
	}

	printf("wanna generate a test tone?(1: yes, 0:no)\n");
	scanf("%d", &answer);
	if(answer==1)TestTone(440, 5);
}
