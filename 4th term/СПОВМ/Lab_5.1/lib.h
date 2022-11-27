#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <semaphore.h>
#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>

//#include <string>
//#include <iostream>
//#include <unistd.h>
//#include <fcntl.h>
//#include <dlfcn.h>
#include <aio.h>
using namespace std;

struct info { 
    pthread_t thrds[2];
    vector<string> fnames;
    string buffer;
};

void* lib_desc;
sem_t semaph;

void* reader(void* );
void* writer(void* );

void search_pathes_to_files(info&);
void create_threads(info&);



    void read_from_file(int filedes, string& buf) {
        int count;
        char written_character;
        do {
            written_character = 0;
            count = read(filedes, &written_character, sizeof(char));
            buf.insert(buf.size(), 1, written_character);
        } while (count != 0);
    }

    void write_to_file(int filedes, string& buf) {
        if (write(filedes, buf.c_str(), buf.size() - 1) <= 0) {
            std::cout << "Writting ERROR!";
            _exit(1);
        }
        write(filedes, "\n", 1);
    }
