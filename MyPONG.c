#include<ncurses.h>
#include<string.h>
typedef struct object{short x, y, pts;bool con1, con2;} object;

void main()
{
    object scr;
    int i = 0, cont = 0;
    bool des = false;
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    keypad(stdscr, true);
    curs_set(0);
    getmaxyx(stdscr, scr.y, scr.x);
    object P1={1, scr.y/2, 0, false, false};
    object P2={scr.x-2, scr.y/2, 0, false, false};
    object ball={scr.x/2, scr.y/2, 0, false, false}; 
    char s01[] = " oooooooooo                                  ";
    char s02[] = " 888    888  ooooooo    ooooooo    oooooooo8 ";
    char s03[] = " 888oooo88 888     888 888   888  888    88o ";
    char s04[] = " 888       888     888 888   888   888oo888o ";
    char s05[] = "o888o        88ooo88  o888o o888o 888     888";
    char s06[] = "                                   888ooo888 ";
    char s07[] = "Press any KEY to Start";
    char s08[] = "Player 1 Controls: W and S    ";
    char s09[] = "Player 2 Controls: UP and DOWN";
    char s10[] = "Developed By ROSHAN PRASHANT BARA";

    mvprintw(scr.y/2-22, scr.x/2-5, s01);   
    mvprintw(scr.y/2-22, scr.x/2-4, s02);   
    mvprintw(scr.y/2-22, scr.x/2-3, s03);   
    mvprintw(scr.y/2-22, scr.x/2-2, s04);   
    mvprintw(scr.y/2-22, scr.x/2-1, s05);   
    mvprintw(scr.y/2-22, scr.x/2, s06);
    mvprintw(scr.y/2-strlen(s07)/2, scr.x/2+1, s07);
    mvprintw(scr.y/2-strlen(s08)/2, scr.x/2+1, s08);
    mvprintw(scr.y/2-strlen(s09)/2, scr.x/2+1, s09);
    mvprintw(scr.y/2-strlen(s10)/2, scr.x-1, s10);
    getch();
    for(nodelay(stdscr, true); !des; usleep(4000))
    {
        if(++cont%16==0)
        {
            if((ball.y==scr.y-1)||(ball.y==1))
                ball.con2=!ball.con2;
            if((ball.x>=scr.x-2)||(ball.x<=2))
            {
                ball.con1=!ball.con1;
                if((ball.y==P2.y-1)||(ball.y==P1.y-1))
                {
                    ball.con2=false;
                }
                else if((ball.y==P2.y+1)||(ball.y==P1.y+1))
                {
                    ball.con2=true;
                }
                else if((ball.y != P2.y) && (ball.y != P1.y))
                {
                    (ball.x>=scr.x-2) ? P2.pts++: P1.pts++;
                    ball.x=scr.x/2;
                    ball.y=scr.y/2;
                }
            }
        }
        ball.x=ball.con1? ball.x+1: ball.x-1;
        ball.y=ball.con1? ball.x+1: ball.y-1;

        if(P2.y<=1)
        {
            P2.y=scr.y-2;
        }
        if(P2.y>=scr.y-1)
        {
            P2.y=2;
        }
        if(P1.y<=1)
        {
            P1.y=scr.y-2;
        }
        if(P1.y>=scr.y-1)
        {
            P1.y=2;
        }
        switch (getch())
        {
            case KEY_DOWN: P2.y++; break;
            case KEY_UP:   P2.y--; break;
            case 'q':      P1.y--; break;
            case 'a':      P1.y++; break;
            case 'p':      getchar(); break;
            case 0x1B:    endwin(); des++; break;
        }
        erase();
        mvprintw(2,scr.x/2-2,"%i | %i",P2.pts,P1.pts);
        mvvline(0,scr.x/2,ACS_VLINE,scr.y);
        attron(COLOR_PAIR(1));
        mvprintw(ball.y,ball.x,"o");
        for(i=-1;i<2;i++)
        {
            mvprintw(P2.y+i,P2.x,"|");
            mvprintw(P1.y+i,P1.x,"|");
        }
        attroff(COLOR_PAIR(1));
    }
}