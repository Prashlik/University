#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    ifstream info_file;
    ofstream result_file;
    string info, path;
    char name[20];
    int size = 20;
    gethostname(name, size);

    path = "./";
    path += name;
    path += "_info.txt";

    result_file.open(path);

    info_file.open("/proc/cpuinfo");
    if (!info_file)
        result_file << "There are no information about CPU.\n";
    else 
    {
        result_file << "The CPU information:\n";

        while (!info_file.eof())
        {
            getline(info_file, info);

            if (info.find("processor") != -1)
                result_file << '\n' << info << '\n';
            else if (info.find("vendor_id") != -1 || info.find("model") != -1 || info.find("cpu ") != -1 )
                result_file << info << '\n';
        }
    }
    info_file.close();

    info_file.open("/proc/version");
    if (!info_file)
        result_file << "\nThere are no information about core.\n";
    else 
    {
        result_file << "\nThe core information:\n\n";

        while (!info_file.eof())
        {
            getline(info_file, info);
            result_file << info << '\n';
        }
    }
    info_file.close();
    
    
    
    result_file.close();
}