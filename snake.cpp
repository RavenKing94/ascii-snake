#include <cstdlib>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

char dir='R';
struct pix{ int x,y; };
pix food;
int eatcount=0;
class _stack{
    private :
        pix sp[140];
    public :
        int index;
        _stack(void)
        {
            index=0;
            for (int i=0;i<140;i++)
            sp[i].x=sp[i].y=0;
        }
        
        int push(int x,int y)
        {
            if (index==139)
            return -1;
            sp[index].x=x;
            sp[index].y=y;
            index++;
            return 0;
        }
        int pop(int &x,int &y)
        {
            if (index>0)
            {
            index--;
            x=sp[index].x;
            y=sp[index].y;
            return 0;
            }
            else
            return -1;
        }
        int instack(int x,int y)
        {
        	for (int i=0;i<index;i++)
        	if ((sp[i].x==x)&&(sp[i].y==y))
        	return 1;
        	return 0;
        }
    
} snake;
void gameover(void)
{
	system("CLS");
	cout<<"\n\n\n\n\n\n              GAME OVER\n";
	cout<<"              SCORE : "<<eatcount*15<<endl;
	getch();
	exit(0);
	
}
void drawsnake(void)
{   
	system("CLS");
    int x,y;
    _stack temp;
    bool head=true;
    while (snake.pop(y,x)==0)
    {
        //draw
        gotoxy(x,y);
        if (head)
        {
        	putchar('#');
        	head = false;
		} else
        	putchar('O');
        temp.push(y,x);
        
    }
    while (temp.pop(y,x)==0)
        snake.push(y,x);
}
void genfood(void)
{
	srand(time(0));
	food.x=rand()%70;
	food.y=rand()%20;
	
}
void drawfood(void)
{
	gotoxy(food.x,food.y);
	putchar('X');
}
void movesnake(void)
{
	int mx=0,my=0;
	if (dir=='R')
	mx=1;
	if (dir=='L')
	mx=-1;
	if (dir=='U')
	my=-1;
	if (dir=='D')
	my=1;
	////////
	int x,y,eat=0;
	snake.pop(y,x);
	if (food.y==y+my && food.x==x+mx)
	{
		eat=1;
		eatcount++;
	}
	if (((x+mx==70)||(y+my==20))||((x+mx<0)||(y+my<0)))
	gameover();
	if (snake.instack(y+my,x+mx))
	gameover();
	snake.push(y,x);
	snake.push(y+my,x+mx);
    _stack temp;
    while (snake.pop(y,x)==0)
    {
        temp.push(y,x);
    }
    if (!eat){
    temp.pop(x,y);}
    else genfood();
    while (temp.pop(y,x)==0)
        snake.push(y,x);
	
	
}

void getkey(void)
{
    int c;
    for (int i=0;i<10;i++)
    {
    	Sleep(1);
        if (GetKeyState(VK_DOWN)&0x80)
        {
        if (dir='D') continue;
        dir='D';
        return;}
        if (GetKeyState(VK_UP)&0x80)
        {
        if (dir='U') continue;
        dir='U';
        return;}
        if (GetKeyState(VK_LEFT)&0x80)
        {
        if (dir='L') continue;
        dir='L';
        return;}
        if (GetKeyState(VK_RIGHT)&0x80)
        {
        if (dir='R') continue;
        dir='R';
        return;}
        
    }        
}
void init(void)
{
    snake.push(10,20);
    snake.push(10,21);
    snake.push(10,22);
    drawsnake();
    genfood();
    drawfood();
}
int main(int argc, char *argv[])
{
    int a,b;
    init();
    getch();
    while (1)
    {
    	getkey();
    	movesnake();
    	drawsnake();
    	drawfood();
    }
    
    //the end
	system("PAUSE");
    return EXIT_SUCCESS;
}
