#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <vector>
#include <glob.h>

using namespace std;

int main()
{
    glob_t globbuf;
    //globbuf.gl_offs;
    glob("./*.cpp", GLOB_DOOFFS, NULL, &globbuf);
    glob("../*.cpp", GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
    //glob("../*.cpp", GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
    //globbuf.gl_pathv[0] = "ls";
    //globbuf.gl_pathv[1] = "ls";
    //execvp("ls", &globbuf.gl_pathv[0]);
    //execvp("ls", &globbuf.gl_pathv[1]);
    cout << globbuf.gl_pathc;
}