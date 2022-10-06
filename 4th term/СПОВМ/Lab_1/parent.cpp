#include <iostream>
#include <curses.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    initscr();
    while (true)
    {
        int pid = fork();
        
        switch(pid)
        {
        case -1:
        {
            return 0;
        }
        case 0:
        {
            execlp("gnome-terminal", "gnome-terminal", "--", "./child", NULL);
        }
        default:
        {
            printw("Parent:\n");
            time_t now;
            char *dt;

            for (int i = 0; i < 10; i++)
            {
                now = time(0);
                dt = ctime(&now);
                
                printw("%s", dt);
                refresh();

                napms(666);
            }
            int status;
            waitpid(pid, &status, 0);
            endwin();
        }
        }
        return 0;
    }
}