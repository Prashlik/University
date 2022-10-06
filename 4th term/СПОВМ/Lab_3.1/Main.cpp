#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <signal.h>
#include <ncurses.h>

using namespace std;

int child(void* ptr/*int pipedes[]*/);

int main(int argc, char* argv[])
{
    initscr();

    int flag = 0, sig;
    char ch;
    //int key = ftok();
    char msg[256];

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    //int pipedes[2] = {0};
    //pipe(pipedes);

    int smid = shmget(12345678, 256, IPC_CREAT | 0666);
    if (smid <= 0)
    {
        printf("Sharing memory creation error!\n\r");
        exit(-1);
    }

    void* ptr = shmat(smid, NULL, 0);
    if (ptr = (void*) -1)
    {
        printf("Sharing memory error!\n\r");
        exit(-1);   
    }

    pid_t pid;
    pid = fork();
                
    switch (pid) 
    {
    case -1: 
    {
        printf("\n\r\tError creating child process\n\r");
        refresh();
        exit(-1);
        break;
    }
    case 0: 
    {
        child(ptr/*pipedes*/);
        exit(0);
        break;
    }
    default: 
    {
        //close(pipedes[0]);
        break;
    }
    }
                
    do
    {
        clear();
        refresh();

        printf("||========================================||\n\r");
        printf("||                                        ||\n\r");
        printf("|| -Press 's' to send the message         ||\n\r");
        printf("|| -Press 'q' to exit                     ||\n\r");
        printf("||                                        ||\n\r");
        printf("||----------------------------------------||\n\r");
        printf("\n\r");
        refresh();


        do
        {
            ch = 0;
            rewind(stdin);
            ch = getch();
            switch(ch)
            {
            case 's':
            {
                //cin.get();
                //fflush(stdin);
                //getline(wcin, msg);
                //write(pipedes[1], (void*)msg.c_str(), msg.size() + 1);
                scanw("%d", &msg);
                char* smsg = (char*) ptr;
                smsg = msg;

                clear();
                refresh();
                printf("%s", msg);
                kill(pid, SIGUSR2);
                sigwait(&mask, &sig);  
                break;
            }
            case 'q':
            {
                kill(pid, SIGKILL);
                flag++;
                break;
            }
            }
        
        } while (ch == 0);

    } while (!flag);

    endwin();
    return 0;
}
 

int child(void* ptr/*int pipedes[]*/)
{
    int sig;
    //char msg[256];
    sigset_t cmask;
    sigemptyset(&cmask);
    sigaddset(&cmask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &cmask, NULL);

    //close(pipedes[1]);

    while(true)
    {
        sigwait(&cmask, &sig);
        //read(pipedes[0], msg, 256);
        char* smsg = (char*)ptr;
        printf("Cild process #%d recieved the string:\n\r", getpid());
        printf("%s\n\r", smsg);
        refresh();
        getch();
        kill(getppid(), SIGUSR1);
    }

    return 0;
}   