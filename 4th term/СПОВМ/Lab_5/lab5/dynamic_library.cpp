#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <aio.h>
#include <cerrno>

extern "C" {
    void read_from_file(int _filedes, std::string& _buffer_to_fill) {
        int count;
        char written_character;
        do {
            written_character = 0;
            count = read(_filedes, &written_character, sizeof(char));
            _buffer_to_fill.insert(_buffer_to_fill.size(), 1, written_character);
        } while (count != 0);
        /*std::cout << "\tREAD FUNCTION\n";
        std::cout << _filedes << "\n";
        std::cout << _buffer_to_fill << "\n";*/
    }
}

extern "C" {
    void write_to_file(int _filedes, std::string& _placeholder) {
        /*std::cout << "\tWRITE FUNCTION\n";
        std::cout << _filedes << "\n";
        std::cout << _placeholder << "\n";*/
        if (write(_filedes, _placeholder.c_str(), _placeholder.size() - 1) <= 0) {
            std::cout << "Writting ERROR!";
            std::cout << errno;
            _exit(1);
        }
        write(_filedes, "\n", 1);
    }
}