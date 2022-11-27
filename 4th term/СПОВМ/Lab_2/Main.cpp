#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <signal.h>
#include <ncurses.h>

using namespace std;

#define max_count 10

int child();
void printpid(int pid);

int main(int argc, char* argv[])
{
    initscr();

    int count = 1, flag = 0, sig;
    char ch;
    pid_t array[max_count];

    array[count-1] = getpid();

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    do
    {
        clear();
        refresh();

        printw("||========================================||\n\r");
        printw("||                                        ||\n\r");
        printw("|| -Press '+' to add new process          ||\n\r");
        printw("|| -Press '-' to delete the last process  ||\n\r");
        printw("|| -Press 'q' to exit                     ||\n\r");
        printw("||                                        ||\n\r");
        printw("||----------------------------------------||\n\r");
        printw("\n\r");
        refresh();
        printw(" The number of active processes: %d\n\r", count);
        printw("    Process #0:     ");
        printpid(getpid());
        printw("\n\r");
        refresh();

        for (int i = 1;i < count;i++)
        {
            printw("    Process #%d:     ", i);
            refresh();
            kill(array[i], SIGUSR2);
            sigwait(&mask, &sig);
            printw("\n\r");

        }

        ch = 0;
        do
        {
            //rewind(stdin);
            ch = getch();
            switch(ch)
            {
            case '+':
            {
                pid_t pid;
                if (count < max_count) 
                {
                    count++;
                    pid = fork();
                }   
                switch (pid) 
                {
                case -1: 
                {
                    printw("\n\r\tError creating child process\n\r");
                    refresh();
                    exit(-1);
                    break;
                }
                case 0: 
                {
                    child();
                    exit(0);
                    break;
                }
                default: 
                {
                    array[count - 1] = pid;
                    break;
                }
                }
                break;
                }
                case '-':
                {
                    if (count > 1)
                    {
                        kill(array[count - 1], SIGKILL);
                        count--;
                    }
                    break;
                }
                case 'q':
                {
                    while (count > 1)
                    {
                        kill(array[count-1], SIGKILL);
                        count--;
                    } 
                    
                    flag++;
                    break;
                }
            }
        
        } while (ch == 0);

    } while (!flag);

    endwin();
    return 0;
}
 

int child()
{
    int sig;
    sigset_t cmask;
    sigemptyset(&cmask);
    sigaddset(&cmask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &cmask, NULL);

    while(true)
    {
        sigwait(&cmask, &sig);
        printpid(getpid());
        kill(getppid(), SIGUSR1);
    }

    return 0;
}   

void printpid(int pid)
{
    char* mypid = (char*)malloc(5);
    sprintf(mypid, "%d", pid);
    for (int i = 0;i < 5;i++)
    {
        printw("%c", mypid[i]);
        refresh();
        usleep(100000);
    }

    return;
}