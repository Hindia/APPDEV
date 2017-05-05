//headers included
#include "wave.h"
#include "screen.h"
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h> //eliminates warning when -c99 is used

//this program will open a wave file, and display WAV header info if DEBUG is enabled

int main(int argc, char *argv[]){
	FILE *fp;	//file pointer
	WAVHDR myhdr;	//header
	short int sa[SAMPLE_RATE];	//array for samples
	int answer, ret;
	for(;;){	//starts a never ending loop
	  	ret=system("arecord -r16000 -c1 -d1 -f S16_LE -q data.wav");	//returns the recording command
	  	if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT || WTERMSIG(ret)==SIGQUIT))break;	//if a terminating signal is hit the program stops running
		clearScreen();	//clears screen
	  	fp=fopen("data.wav", "r");	//opens to read the file
	  	fread(&myhdr, sizeof(myhdr), 1, fp);	//reads the header
	  	displayWAVHDR(myhdr);	//displays the header
          	fread(&sa, sizeof(short int), SAMPLE_RATE, fp);	//reads the sample rate
		displayWAVdata(sa);	//displays the wave data
		fclose(fp);	//closes the file
	}
	printf("wanna generate a test tone?(1: yes, 0:no)\n");	//gives an option to user if they wish to generate a test  tone
	scanf("%d", &answer);	//gets the response from user
	if(answer==1)TestTone(440, 5);	//generates a test tone if the user wishes to
}
