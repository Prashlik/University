#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <semaphore.h>
#include <signal.h>
#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
using namespace std;

class Data {
public:
    pthread_t threads_arr[2];
    vector<string> filenames_vector;
    string buffer;

    Data() {
        this->threads_arr[2] = { 0 };
    }

    Data(const Data& data) {
        this->threads_arr[0] = data.threads_arr[0];
        this->threads_arr[1] = data.threads_arr[1];
        this->filenames_vector = data.filenames_vector;
    }

    ~Data() {
        this->threads_arr[0] = 0;
        this->threads_arr[1] = 0;
    }
};

void* dynamic_lib_desc;
sem_t semaph;

void* file_reader(void* );
void* file_writter(void* );

void search_pathes_to_files(Data&);
void create_threads(Data&);