//headers included
#include "wave.h"
#include <stdio.h>
#include <math.h>
#include "screen.h"
#include "comm.h"

void fillID(const char *s, char d[]){	//function for filling the wave ID
	int i;
	for(i=0; i<4; i++) d[i]=*s++;

}

void TestTone (int freq, double d){	//function for generating a test tone
	FILE *fp;	//file pointer defined
	int i;
	WAVHDR h;	//wave header defined
	short int sample;	//variable for sample
	fp=fopen("testtonestereo.wav", "w");	//file opened to write the wav file
	fillID("RIFF", h.ChunkID);	//fills the ID of the wav file
	//ChunkSize will be calculated later
	fillID("WAVE", h.Format);	//fills the format of the WAV file
	fillID("fmt ", h.Subchunk1ID);	//fills the ID of the wave file of the test tone
	h.Subchunk1Size=16;	//sets the subcunk size of the test tone
	h.AudioFormat=1;	//sets the audio format of the test tone
	h.NumChannels=1;	//sets the number of channles of the test tone
	h.SampleRate=SAMPLE_RATE;	//sets the sample rate of the test tone
	h.BitsPerSample=16;	//sets the bits per sample of the test tone
	h.ByteRate=SAMPLE_RATE*h.NumChannels*(h.BitsPerSample/8);	//calculates the byte rate of the test tone
	h.BlockAlign=h.NumChannels*(h.BitsPerSample/8);	//calculates the block align
	fillID("data", h.Subchunk2ID);	//fills the ID
	h.Subchunk2Size=(int)d*h.ByteRate;	//calculates the size
	h.ChunkSize=h.Subchunk2Size+36;	//calculates the chunk size
	fwrite(&h, sizeof(h), 1, fp);	//writes the header with the infos
	for(i=0; i<d*SAMPLE_RATE; i++){
		sample=32768*sin(2*PI*freq*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
	}
	fclose(fp);

}

//calculates 1 sec samples into 80 pieces of RMS value. each calculates by 1600/80 columns=200
//however, only 8 pieces of RMS data are sent to the server fast mode of sound level meter(SLM)

void displayWAVdata(short int d[]){	//function to display the wave data
	int i,j;
	double sum200, rms200, max200=0.0, min200=20000.0;
	//the following variables are used to calculate rms2000 (fast leq values)
	double Leqf[8], sum2000=0.0;
	for(i=0; i<80; ++i){	//80 is the number of columns of the terminal window
		sum200=0.0; 	//initializes the accumulator
		for(j=0; j<SAMPLE_RATE/80; ++j){
			sum200 +=(*d)*(*d);	//sum updated
			d++;			//pointer increement
		}
		sum2000 +=sum200;
		if(i%10==9){	//for every 10 pieces of rms200, we get an rms2000

			Leqf[i/10]=sqrt(sum2000/(SAMPLE_RATE/8));
			sum2000=0.0;	//reset sum2000
		}

		rms200=sqrt(sum200/(SAMPLE_RATE/80));
		//finds decibel value of sound using logirithm
	       	rms200=20*log10(rms200);
		//finds max and min value of rms200
		if(rms200<min200)min200=rms200;
		if(rms200>max200)max200=rms200;

#ifdef DEBUG	//performs conditional compiling
		printf("%d %10.2f ", i, rms200);
#else
		setFGcolor(BLUE);
		displayBar(rms200, i+1);
		resetColors();
#endif
	}	// end of for loop

//displays max200 and min200 in debug mode
#ifdef DEBUG
	printf("\nmin=%.2f max=%.2f\n",min200, max200);
#endif

//sends data to server if comm is defined
#ifdef COMM
	send_data_curl(Leqf);
#endif
}

//function to display wave header
void displayWAVHDR(WAVHDR hdr){
	double duration;
	duration=(double)hdr.Subchunk2Size/hdr.ByteRate;

#ifdef DEBUG	//displays the info below if in debug mode

	printf("ChunkID: "); printID(hdr.ChunkID);
	printf("ChunkSize: %d\n", hdr.ChunkSize);
	printf("Format: "); printID(hdr.Format);
	printf("Subchunk1ID: "); printID(hdr.Subchunk1ID);
	printf("Subchunk1Size: %d\n", hdr.Subchunk1Size);
	printf("Audio Format: %d\n", hdr.AudioFormat);
	printf("Number of Channels: %d\n", hdr.NumChannels);
	printf("Sample rate: %d\n", hdr.SampleRate);
	printf("Byte rate: %d\n", hdr.ByteRate);
	printf("Block Align: %d\n", hdr.BlockAlign);
	printf("Bits per sample: %d\n", hdr.BitsPerSample);
	printf("Subchunk2ID: "); printID(hdr.Subchunk2ID);
	printf("Subchunk2Size: %d\n", hdr.Subchunk2Size);
	printf("Duration of Audio %.3f sec\n", duration);
#else

	gotoXY(1,1); setFGcolor(RED); printf("%.2f sec", duration);
	gotoXY(1,10); setFGcolor(CYAN);printf("%d bit/s", hdr.BitsPerSample);
	gotoXY(1,20); setFGcolor(YELLOW);printf("%d sps", hdr.SampleRate);
	resetColors();
#endif

}

void printID(char id[]){	//function to print the ID of the file
	int i;
	for(i=0; i<4;i++) putchar(id[i]);
	printf("\n");
}
