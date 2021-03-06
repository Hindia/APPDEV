/* this header file contains a wave header information as a struct. it also contains necessary
 constant definitions and function prototypes used in this project*/

typedef struct {
	char ChunkID[4];
	int ChunkSize;
	char Format[4];
	char Subchunk1ID[4];
	int Subchunk1Size;
	short int AudioFormat;
	short int NumChannels;
	int SampleRate;
	int ByteRate;
	short int BlockAlign;
	short int BitsPerSample;
	char Subchunk2ID[4];
	int Subchunk2Size;
}WAVHDR;

#define DEBUG 1	//for conditional compiling
#define SAMPLE_RATE 16000	//sample rate is defined
#define PI 3.1415926	//PI is defined

//function prototypes to be defined in the wave.c folder

void displayWAVHDR(WAVHDR hdr);
void printID(char *);
void fillID(const char *, char []);
void TestTone (int freq, double duration);
void displayWAVdata(short int []);
