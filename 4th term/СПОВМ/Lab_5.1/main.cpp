#include "lib.h"

#define smkey 505

int main() {
    info inf;
    search_pathes_to_files(inf);

    int smid;

    smid = semget(smkey, 3, 0666 | IPC_CREAT);

    semctl(smid, 0, SETVAL, 0);
    semctl(smid, 1, SETVAL, 1);
    semctl(smid, 2, SETVAL, 0);

    create_threads(inf);

    //desc = dlopen("./lib.so", RTLD_LAZY);

    //if (!desc) {
    //    cout << "Dynamic library not found!\n";
    //    exit(1);
    //}

    pthread_join(inf.thrds[0], NULL);
    pthread_join(inf.thrds[1], NULL);

    semctl(smid, 0, IPC_RMID);

    //dlclose(desc);

    cout << "The end of the program\n";

    return 0;
}

void create_threads(info& inf) {

    pthread_t rthrd, wthrd;

    pthread_create(&rthrd, NULL, reader, &inf);
    pthread_create(&wthrd, NULL, writer, &inf);

    inf.thrds[0] = rthrd;
    inf.thrds[1] = wthrd;
}

void search_pathes_to_files(info& inf) {
    DIR *directory = opendir("./Files/");
    if (!directory) {
        cout << "Open directory error!\n";
        exit(1);
    }
    struct dirent *filedes;
    string full_path;

    while ((filedes = readdir(directory)) != NULL) {
        full_path = "./Files/";
        if (strcmp(filedes->d_name, "Result.txt") == 0) continue;
        if (strcmp(filedes->d_name, "..") == 0) continue;
        if (strcmp(filedes->d_name, ".") == 0) continue;
        full_path += filedes->d_name;
        inf.fnames.push_back(full_path);
        full_path.clear();
    }
    
    for (int i = 0; i < inf.fnames.size(); i++)
        cout << i + 1 << ") " << inf.fnames[i] << '\n';
    
    closedir(directory);
}

void* reader(void* data) {
    //info* inf = static_cast<info*>(data);
    //info inf = *temp;
    int file_desc;
    int smid = 0;

    smid = semget(smkey, 3, 0);

    //char* (*read_from_file)(int, string&);
    //*(void**)(&read_from_file) = dlsym(lib_desc, "read_from_file");

    cout << "START READING\n";

    for (int i = 1; ((info*)data)->fnames.size() != 0; i++) {
        if (((info*)data)->fnames.size() == 0) break;
        
        while (semctl(smid, 0, GETVAL, 0));
        semctl(smid, 1, SETVAL, 1);

        cout << "Reading " << i << " file...\n";
        file_desc = open(((info*)data)->fnames[0].c_str(), O_RDONLY);
        //(*read_from_file)(file_descriptor, ((Data*)_rdata)->buffer);
        read_from_file(file_desc, ((info*)data)->buffer);

        close(file_desc);
        ((info*)data)->fnames.erase(((info*)data)->fnames.begin());

        semctl(smid, 1, SETVAL, 0);
    }
    //завершаем поток записи
    semctl(smid, 2, SETVAL, 1);
    return 0;
}

void* writer(void* data) {
    //info* inf = static_cast<info*>(data);
    //info inf = *temp;
    int file_desc;
    int smid = 0;
    
    smid = semget(smkey, 3, 0);

    //int (*write_to_file)(int, string&);
    //*(void**)(&write_to_file) = dlsym(desc, "write_to_file");

    //remove("./files/Result.txt");
    file_desc = open("./files/Result.txt", O_WRONLY | O_CREAT, S_IRWXU);

    for (int i = 1; !semctl(smid, 2, GETVAL, 0);) {
        if (semctl(smid, 1, GETVAL, 0)) {
            
            semctl(smid, 0, SETVAL, 1);
            cout << "Writting " << i << " file...\n";
            //(*write_to_file)(file_descriptor, ((Data*)_wdata)->buffer);
            write_to_file(file_desc, ((info*)data)->buffer);
            ((info*)data)->buffer.clear();
            i++;

            semctl(smid, 0, SETVAL, 0);
        }
    }
    close(file_desc);
    return 0;
}