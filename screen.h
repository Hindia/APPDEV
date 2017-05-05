//includes the function prtotypes for screen manipulation
enum COLOR{BLACK=30, RED, GREEN, YELLOW, BLUE, MAGNETA,CYAN, WHITE};	//enumeration for the colors to be used in the screen.c
#define UNICODE	//used in the screen.c for debug mode
#define BAR "\u2590" //unicoe for bar



//function prototypes defined in the screen.c file
void setFGcolor(int fg);
void resetColors(void);
void gotoXY(int row, int col);
void clearScreen(void);
void displayBar(double rms, int col);

