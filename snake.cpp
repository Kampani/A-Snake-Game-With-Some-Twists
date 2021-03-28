#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<time.h>
using namespace std;

bool gameOver;
int const length_map=20;
int const width_map=30;
int x,y,fruitX,fruitY,score;
int tailX[500];
int tailY[500];
int pointX, pointY;
int trailPointY[5];
enum eDirection{STOP, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void setup()
{
    gameOver=false;
    dir=STOP;
    x=width_map/2;
    y=length_map/2;
    srand(time(0));
    fruitX= rand() % width_map;
    fruitY= rand() % length_map;
    score=0;
}


void draw()
{
    system("cls");
        cout<<"By Manav Kampani"<<endl<<endl<<endl;
        cout<<"CONTROLS:  ";
        cout<<"W: UP ,  A:LEFT ,  D:RIGHT, S:DOWN"<<endl;
        cout<<endl;
        cout<<"  Points="<<score<<endl<<endl;

    for(int j=0; j<length_map; j++)
    {
            for(int i=0; i<width_map; i++)
            {
              if((j==0 && i<width_map) || (j==length_map-1 && i<width_map) || (j>0 || j<length_map-1) && (i==0 || i==width_map-1) )
                cout<<"#";

                else if(j==fruitY && i==fruitX)
                 {
                     cout<<"F";
                 }

                else if(j==y && i==x)
                 {
                    cout<<"O";
                 }

                else if((i==pointX && j==trailPointY[0]) || (i==pointX && j==trailPointY[1])|| (i==pointX && j==trailPointY[2]) || (i==pointX && j==trailPointY[3]) || (i==pointX && j==trailPointY[4]) )
                    cout<<"|";

                else {
                        bool print = false;
                        for (int k = 1; k <= score; k++)
                        {
                            if (tailX[k] == i && tailY[k] == j)
                                {
                                    cout << "o";
                                    print = true;
                                }
                        }

                        if (!print)
                        cout << " ";
                    }

            }

            cout<<endl;
    }
}

void input()
{
    if(kbhit())
        switch(getch())
    {
        case 'w':
        if (dir!=DOWN && score!=0)dir=UP;
        else if(score==0) dir=UP;
        break;

        case 'a':
        if (dir!=RIGHT && score!=0)dir=LEFT;
        else if(score==0)dir=LEFT;
        break;

        case 'd':
        if (dir!=LEFT && score!=0)dir=RIGHT;
        else if(score==0)dir=RIGHT;
        break;

        case 's':
        if (dir!=UP && score!=0)dir=DOWN;
        else if(score==0)dir=DOWN;
        break;

        case 'x':
        gameOver=true;
        break;

    }
}


void logic()
{
    tailX[0]=x;
    tailY[0]=y;

    for(int i=score; i>=0; i--)
    {
        tailX[i+1]=tailX[i];
        tailY[i+1]=tailY[i];
    }

    switch(dir)
    {
        case UP:
        y--;
        break;

        case LEFT:
            x--;
        break;

        case RIGHT:
            x++;
        break;

        case DOWN:
            y++;
        break;

        default:
            break;
    }

    for(int i=3; i<=score; i++)
    {
        if(x==tailX[i]&&y==tailY[i])
            gameOver=true;
    }

    if(x==width_map-1 || x==0 || y==0 || y==length_map-1 )
    {
        gameOver=true;
    }

    if(x==fruitX && y==fruitY)
    {
            fruitX= rand() % (width_map-3)+1;
            fruitY= rand() % (length_map-3)+1;

            pointX= rand() % (width_map-3)+1;
            pointY= rand() % (length_map-7)+1;

            for(int k=0; k<5; k++)
            {
                trailPointY[k]=pointY++;
            }
        score++;
    }

    if(x==pointX)
    {
        for(int k=0;k<5; k++)
        {
            if(y==trailPointY[k])
                gameOver=true;

        }
    }
}

int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
    }
    cout<<"GAME OVER"<<endl<<"Your Score:"<<score<<endl;
    cout<<"if you want to play again press Z"<<endl<<"if you want to exit press any other character"<<endl;

    char temp=getch();

    //getch();
    
    if('z'==temp)
        main();
    else
        return 0;

}



