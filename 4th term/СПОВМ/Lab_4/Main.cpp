#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <fcntl.h>
#include <iostream>
#include <pthread.h>
#include <iostream>
using namespace std;

#define MAX_THREADS_NUM 10

void *printLine(void *line_num);
pthread_t create_thread(int line_num);
void delete_thread(pthread_t pth_id);

void* funct(void*);
void printid(int);
bool _knbit();

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    int threads_num = 0;
    bool flag = 1;
    pthread_t threads[MAX_THREADS_NUM];

    initscr();
    noecho();
    curs_set(0);
   
    do {
        mvprintw(0, 0, "||========================================||\n\r");
        mvprintw(1, 0, "||                                        ||\n\r");
        mvprintw(2, 0, "|| -Press '+' to add new process          ||\n\r");
        mvprintw(3, 0, "|| -Press '-' to delete the last process  ||\n\r");
        mvprintw(4, 0, "|| -Press 'q' to exit                     ||\n\r");
        mvprintw(5, 0, "||                                        ||\n\r");
        mvprintw(6, 0, "||----------------------------------------||\n\r");
        refresh();

        fflush(stdin);
        switch (getch())
        {
        case '+':
        {
            if (threads_num < MAX_THREADS_NUM)
            {
                threads[threads_num] = create_thread(threads_num);
                threads_num++;
            }
            break;
        }
        case '-':
        {
            if(threads_num != 0)
                threads_num--;
            
            delete_thread(threads[threads_num]);
            break;
        }
        case 'q':
        {
            for (int i = 0; i < threads_num; i++)
                delete_thread(threads[i]);

            flag = 0;
            break;
        }
        }


        usleep(1000);
        clear();
    } while (flag);

    endwin();
    return 0;
}

void *printLine(void *arg)
{
    int *line_num_ptr = static_cast<int *>(arg);
    int line_num = *line_num_ptr;

    pthread_t thread = pthread_self();
    string myid = to_string(thread);
    string line;
    int i = 0;

    while (true)
    {
        pthread_mutex_lock(&mutex);

        if(i > 15)
        {
            i = 0;
            mvprintw(line_num + 9, 0, "%s", "                ");
        }
        i++;


        line = to_string(line_num) + ") ";
        line.append(myid, 3, i);
        mvprintw(line_num + 9, 0, "%s", line.c_str());
        refresh();

        line.clear();

        pthread_mutex_unlock(&mutex);
        usleep(200000);
    }
}

pthread_t create_thread(int line_num)
{
    pthread_t id;
    long num = line_num + 1;
    pthread_create(&id, NULL, printLine, &num);
    return id;
}

void delete_thread(pthread_t pth_id)
{
    pthread_cancel(pth_id);
    pthread_join(pth_id, NULL);
}