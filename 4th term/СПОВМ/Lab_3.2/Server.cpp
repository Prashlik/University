#include <unistd.h>
#include <cstdio>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <ncurses.h>

using namespace std;

void KillClient(int sid)
{
    struct sembuf op[1] = {0, 1, 0};
    semop(sid, op, 1);
}

void CallClient(int sid).



{
    struct sembuf op[1] = {1, 1, 0};
    semop(sid, op, 1);
}

void WaitClient(int sid)
{
    struct sembuf op[1] = {2, -1, 0};
    semop(sid, op, 1);
}

int main(int argc, char* argv[])
{
    initscr();
    int a = 505;
    int flag = 0;
    char string[255];

    int smid = shmget(505, 256, IPC_CREAT | 0666);
    if (smid < 0) { perror("smid"); }

    char *mem = (char*) shmat(smid, nullptr, 0);

    int sid = semget(505, 3, IPC_CREAT | 0666); 
    if (sid < 0) { perror("sid"); }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); }
    if (pid == 0) 
    { 
        execlp("gnome-terminal", "gnome-terminal", "--", "./client", &a, NULL); 
        return 0;
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

        noecho();
        switch(getch())
        {
        case 's':
        {
            echo();
            rewind(stdin);
            getstr(string);
            strcpy(mem, string);
            CallClient(sid);
            WaitClient(sid);
            printw("\n\rMessage has been delivered! Please press any key to continue...\n\r");
            refresh();
            getch();
            break;
        }
        case 'q':
        {
            flag++;
            CallClient(sid);
            KillClient(sid);
            waitpid(pid, nullptr, 0);
            break;
        }
        }

    } while (!flag);

    semctl(sid, 0, IPC_RMID);
    shmctl(smid, IPC_RMID, nullptr);

    endwin();
    return 0;
}