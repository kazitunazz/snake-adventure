/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"

# include <stdlib.h>
# include <time.h>
int gameState=-1;
struct highScore {
	int score;
	char name[50];
}top[6], playerInfo;
boolean done;
	struct snake
	{
		int x;
		int y;
		bool show;
	}body[100];
int direction=1,x=4,y=6,t,f1=0,fruitx,fruity,generator=3,i; const int width=600,height=600;int dx1=10,dx2=10,dy1=10,dy2=10,score=0;
bool up= false,right=false,left=false,down=false;
char str[100], str2[100], name[5][20],sc[20],str3[50],scorers[5][200];
FILE *hscore;
int len,highscore[5];
int mode,lvl=0,flag=0;
int dx=5,dy=6,hs;
void drawTextBox()
{
	iClear();
	iText(500,550,"EntEr your namE plEasE :)");
	iSetColor(150, 150, 150);
	iRectangle(500, 450, 400, 50);
}


void gameover() {
	struct highScore temp;
	iShowBMP(200, 500, "gameover.bmp");

	
	iShowBMP(500, 400, "box.bmp");
	if (mode == 1)
	{
		iSetColor(255, 255, 255);
		iText(510, 410, str);
	}
	if (done)
	{
		hscore = fopen("highscore.txt", "r");
		for (int p = 0; p < 5; p++) {
			fscanf(hscore, "%s %d\n", &top[p].name, &top[p].score);
		}
		fclose(hscore);
		playerInfo.score = score;

		if (playerInfo.score > top[4].score)
			top[5] = playerInfo;

		for (int i = 0; i < 6; i++) {
			for (int j = 1; j < 6 - i; j++) {
				if (top[j].score > top[j - 1].score) {
					temp = top[j - 1];
					top[j - 1] = top[j];
					top[j] = temp;
				}
			}
		}
		hscore = fopen("highscore.txt", "w");
		for (int p = 0; p < 5; p++) {
			fprintf(hscore, "%s %d\n", top[p].name, top[p].score);
		}
		fclose(hscore);
		done = false;
	}
	iText(310, 10, "Click to activate the box, enter to finish.");
}void Score()
{
	iSetColor(100,200,30);
	char scr[1000];
	_itoa(score,scr,10);
	strcpy(str2,"your score is : ");
	strcat(str2,scr);
	iText(800,500,str2);
}
void high() {
	iClear();

	iShowBMP(400, 500, "HIGHS.bmp");
	iShowBMP(370, 380, "box.bmp");
	iShowBMP(370, 310, "box.bmp");
	iShowBMP(370, 240, "box.bmp");
	iShowBMP(370, 170, "box.bmp");
	iShowBMP(370, 100, "box.bmp");
	iShowBMP(750, 80, "back-button-hi.bmp");

	hscore = fopen("highscore.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(hscore, "%s %d\n", &top[i].name, &top[i].score);
		sprintf(scorers[i], "Name: %s Score:%d", top[i].name, top[i].score);
	}
	fclose(hscore);

	iSetColor(0, 168, 243);
	iText(380, 400, scorers[0], GLUT_BITMAP_HELVETICA_18);
	iText(380, 330, scorers[1], GLUT_BITMAP_HELVETICA_18);
	iText(380, 260, scorers[2], GLUT_BITMAP_HELVETICA_18);
	iText(380, 190, scorers[3], GLUT_BITMAP_HELVETICA_18);
	iText(380, 120, scorers[4], GLUT_BITMAP_HELVETICA_18);

}

void Snake()
{
	iSetColor(255,32,164);
	iFilledRectangle(fruitx,fruity,8,8);
	iFilledCircle(body[0].x,body[0].y,13);
	iLine(0,0,width,0);
	iLine(0,0,0,height);
	iLine(0,height,width,height);
	iLine(width,0,width,height);
	for(int i=0; i<100;i++){
		if(body[i].show)
			iFilledCircle(body[i].x,body[i].y,10);
	}


}
void about()
{
	iShowBMP(0,0,"credits.bmp");
}
void instructions(){
	iShowBMP(0,0,"instructions.bmp");
}
void startPage()
{
	iShowBMP(0,0,"startpage.bmp");
		iSetColor(229,228,226);
	iText(650, 270, "Start Game", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(650, 200, "High Score", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(670, 55, "Credits", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(650, 130, "Instructions", GLUT_BITMAP_TIMES_ROMAN_24);
}
void move()
{
	for(int i=0;i<100;i++){
		if(right){
			body[i].x+=direction;
			if(i >0 ){
				body[i].y = body[i-1].y;
				body[i].x = body[i-1].x-10;
			}
		}
	}

	for(int i=0;i<100;i++){
		if(left){
			body[i].x-=direction;
			if(i >0 ){
				body[i].y = body[i-1].y;
				body[i].x = body[i-1].x+10;
			}
		}
	}
	for(int i=0;i<100;i++){
		if(up){
			body[i].y+=direction;
			if(i >0 ){
				body[i].y = body[i-1].y-10;
				body[i].x = body[i-1].x;
			}
		}
	}
	for(int i=0;i<100;i++){
		if(down){
			body[i].y-=direction;
			if(i >0 ){
			
			
				body[i].y = body[i-1].y+10;
				body[i].x = body[i-1].x;
			}
		}
	}
		if ((body[0].x + dx1>fruitx&&body[0].x<fruitx + dx2) && (body[0].y + dy1>fruity&&fruity + dy2>body[0].y))
		{
			fruitx= rand()% (width-10);
			fruity= rand()% (height-10);
			score=score+10;
			body[generator].show= true;
			generator++;
			//flag=1;
		}
		else if ((body[0].x + dx1<fruitx&&body[0].x>fruitx + dx2) && (fruity + dy2 > body[0].y &&body[0].y + dy1 > fruity))
			{
			fruitx= rand()% (width-10);
			fruity= rand()% (height-10);
			score=score+10;
			body[generator].show= true;
			generator++;
			//flag=1;
		}
}

void iDraw()
{
	iClear();
	if(gameState==-1){
		iClear();
		startPage();
	iShowBMP(850,450,"exit.bmp");}
	if(gameState==1) 
		{
			iClear();
			iShowBMP(800,40,"back-button-hi.bmp");
			high();
		}
	else if(gameState==2)//About the game
		{
			iClear();
			about();
			iShowBMP(800,40,"back-button-hi.bmp");
			iShowBMP(850,450,"exit.bmp");
		}
	else if(gameState==3)//instructions
	{iClear();
	instructions();
	iShowBMP(800,40,"back-button-hi.bmp");
	iShowBMP(850,450,"exit.bmp");}
	if(gameState==0)//play the game 
	{
		iClear();
		iShowBMP(800,40,"back-button-hi.bmp");
		Snake();
		iText(650,300,"press p to pause the game &r to resume");
		Score();

	}
	if(body[0].x > 590 || body[0].x < 10||body[0].y > 590 || body[0].y < 10){iClear();iShowBMP(850,450,"exit.bmp");iShowBMP(1150,40,"back-button-hi.bmp");gameover();}
}

/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button ==GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		{
			if(mx>=630 && mx<=780 && my>=250 && my<=300)
		{
			gameState=0;
		}
	}
	if (button ==GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		{
			if(mx>=630 && mx<=780 && my>=180 && my<=230)
		{
			gameState=1;
		}
		}
	if (button ==GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		{
			if(mx>=630 && mx<=780 && my>=110 && my<=160)
		{
			gameState=3;
		}
	}
	if (button ==GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		{
			if(mx>=630 && mx<=780 && my>=40 && my<=90)
		{
			gameState=2;
		}
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
		if(mx >= 500 && mx <= 900 && my >= 450 && my <= 500 && mode == 0)
		{
			mode = 1;
		}
	}
	if (button ==GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		{
			if(mx>=800 && mx<=1080 && my>=40 && my<=177)
		{
			gameState=-1;
		}
	}
	if (button ==GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		{
			if(mx>=850 && mx<=978 && my>=450 && my<=578)
		{
			exit(0);
		}
	}
	
}
/*iPassiveMouseMove is called to detect and use 
the mouse point without pressing any button */

void iPassiveMouseMove(int mx,int my)
{
	//place your code here
	
 if(mx== 2){}        /*Something to do with mx*/
 else if(my== 2){}   /*Something to do with my*/
 
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/

void iKeyboard(unsigned char key)
{
	int i;
	if (mode == 1) {
		if (key == '\r')
		{
			mode = 0;
			strcpy(playerInfo.name, str);
			done = true;
			printf("%s\n", playerInfo.name);
			for (i = 0; i < len; i++)
				str[i] = 0;
			len = 0;
		}
		else
		{
			str[len] = key;
			len++;
		}
	}
	if(key =='p'){iShowBMP(800,40,"back-button-hi.bmp");iPauseTimer(t);}
	if(key =='r'){iResumeTimer(t);}
}
/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}
	if(key== GLUT_KEY_LEFT)
	{right=false;left=true;up=false;down=false;}
	if(key==GLUT_KEY_RIGHT)
	{right=true;left=false;up=false;down=false;}
	if(key==GLUT_KEY_UP)
	{right=false;left=false;up=true;down=false;}
	if(key==GLUT_KEY_DOWN)
	{right=false;left=false;up=false;down=true;}
	//place your codes for other keys here
}
void setup()
{
	//gameover=false;
	body[0].x= width/2;
	body[0].y= height/2;
	fruitx= rand()% (width-10);
	fruity= rand()% (height-10);
}
/*void setdim()
{
	int sum = 250;
	for(int i=0; i<100;i++){
	body[i].y=200;
		body[i].x=sum;
		sum -= 10;
		if(i ==0 || i==1 || i==2)
			body[i].show = true;
		else
			body[i].show = false;
	}
}*/


int main()
{
	srand(time(NULL));
	setup();
	t=iSetTimer(0.1,move);
	len = 0;
	mode = 0;
	str[0]= 0;
	//place your own initialization codes here.
	iInitialize(980, 650, "demooo");
	return 0;
}