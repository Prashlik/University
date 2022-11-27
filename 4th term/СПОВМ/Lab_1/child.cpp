#include <iostream>
#include <curses.h>

using namespace std;

int main(int argc, const char *argv[])
{
    initscr();
    printw("Child:\n");
    refresh();

    time_t now;
    char *dt;

    for(int i=0;i<20;i++)
    {

        now = time(0);
        now+=86400;
        dt = ctime(&now);
        
        printw("%s", dt);
        refresh();
        napms(666);
    }
    return 0;
}
