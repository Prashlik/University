#include <cstdio>
#include <sys/sem.h>
#include <sys/shm.h>
#include <ncurses.h>
#include <cstdlib>

using namespace std;

bool CheckKill(int sid)
{
    struct sembuf op[1] = {0, 0, IPC_NOWAIT};
    int res = semop(sid, op, 1);
    return res == -1;
}

void WaitServer(int sid)
{
    struct sembuf op[1] = {1, -1, 0};
    int res = semop(sid, op, 1);
}

void CallServer(int sid)
{
    struct sembuf op[1] = {2, 1, 0};
    semop(sid, op, 1);
}

int main(int argc, char* argv[])
{
    initscr();
    curs_set(0);
    int smid = shmget(505, 256, IPC_CREAT | 0666);
    if (smid < 0) { perror("smid"); }

    int sid = semget(505, 3, IPC_CREAT | 0666); 
    if (sid < 0) { perror("sid"); }

    char *mem = (char*) shmat(smid, nullptr, 0);
    while(true)
    {
        WaitServer(sid);
        if (CheckKill(sid)) break;
        clear();
        printw("Client recieved: ");
        printw("%s",mem);
        refresh();
        CallServer(sid);
    }

    endwin();
    return 0;
}