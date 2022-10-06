#include "library.h"

#define SEMAPHORE_KEY 2001
#define SHAREDMEM_KEY 2002

int main() {
    Data data;
    search_pathes_to_files(data);

    int semaphore_id = 0;

    semaphore_id = semget(SEMAPHORE_KEY, 3, 0666 | IPC_CREAT);

    semctl(semaphore_id, 0, SETVAL, 0);
    semctl(semaphore_id, 1, SETVAL, 0);
    semctl(semaphore_id, 2, SETVAL, 0);

    create_threads(data);

    pthread_join(data.threads_arr[0], NULL);
    pthread_join(data.threads_arr[1], NULL);

    pthread_cancel(data.threads_arr[0]);
    pthread_cancel(data.threads_arr[1]);

    semctl(semaphore_id, 0, IPC_RMID);

    dlclose(dynamic_lib_desc);
    cout << "End\n";

    return 0;
}

void search_pathes_to_files(Data& _data) {
    DIR *directory = opendir("./files/");
    if (!directory) {
        cout << "Opening directory ERROR\n";
        exit(1);
    }
    struct dirent *filedes;
    string full_path;

    while ((filedes = readdir(directory)) != NULL) {
        full_path = "./files/";
        if (strcmp(filedes->d_name, "Result.txt") == 0) continue;
        if (strcmp(filedes->d_name, "..") == 0) continue;
        if (strcmp(filedes->d_name, ".") == 0) continue;
        full_path += filedes->d_name;
        _data.filenames_vector.push_back(full_path);
        full_path.clear();
    }
    cout << _data.filenames_vector.size() << "\n"
        << _data.filenames_vector[0] << "\n"
        << _data.filenames_vector[1] << "\n"
        << _data.filenames_vector[2] << "\n"
        << _data.filenames_vector[3] << "\n";
    
    closedir(directory);
}

void* file_reader(void* _rdata) {
    int file_descriptor;
    int semaphore_id = 0;

    semaphore_id = semget(SEMAPHORE_KEY, 3, 0);

    char* (*read_from_file)(int, string&);
    *(void**)(&read_from_file) = dlsym(dynamic_lib_desc, "read_from_file");

    cout << "START READING\n";

    for (int i = 1; ((Data*)_rdata)->filenames_vector.size() != 0; i++) {
        if (((Data*)_rdata)->filenames_vector.size() == 0) break;
        //ожидаем пока не освободится общая память или пока нет сообщения об успешной записи текста в Result.txt
        while (semctl(semaphore_id, 0, GETVAL, 0) || semctl(semaphore_id, 1, GETVAL, 0));

        //занимаем общую память
        semctl(semaphore_id, 0, SETVAL, 1);

        cout << "Reading " << i << " file...\n";
        file_descriptor = open(((Data*)_rdata)->filenames_vector[0].c_str(), O_RDONLY);
        (*read_from_file)(file_descriptor, ((Data*)_rdata)->buffer);
        close(file_descriptor);
        ((Data*)_rdata)->filenames_vector.erase(((Data*)_rdata)->filenames_vector.begin());
        //устанавливаем 1, тем самым говоря о необходимости обработать переданный в общую память текст
        semctl(semaphore_id, 1, SETVAL, 1);
        //освобождаем обзую память
        semctl(semaphore_id, 0, SETVAL, 0);
    }
    //завершаем поток записи
    semctl(semaphore_id, 2, SETVAL, 1);
    return 0;
}

void* file_writter(void* _wdata) {
    int file_descriptor;
    int semaphore_id = 0;
    
    semaphore_id = semget(SEMAPHORE_KEY, 3, 0);

    int (*write_to_file)(int, string&);
    *(void**)(&write_to_file) = dlsym(dynamic_lib_desc, "write_to_file");

    remove("./files/Result.txt");
    file_descriptor = open("./files/Result.txt", O_WRONLY | O_CREAT, S_IRWXU);

    for (int i = 1; !semctl(semaphore_id, 2, GETVAL, 0);) {
        if (!semctl(semaphore_id, 0, GETVAL, 0) && semctl(semaphore_id, 1, GETVAL, 0)) {
            //занимаем общую память
            semctl(semaphore_id, 0, SETVAL, 1);

            cout << "Writting " << i << " file...\n";
            (*write_to_file)(file_descriptor, ((Data*)_wdata)->buffer);
            ((Data*)_wdata)->buffer.clear();
            i++;
            //говорим, что сообщение обработано
            semctl(semaphore_id, 1, SETVAL, 0);
            //освобождаем общуб память
            semctl(semaphore_id, 0, SETVAL, 0);
        }
    }
    close(file_descriptor);
    return 0;
}

void create_threads(Data& _data) {
    dynamic_lib_desc = dlopen("./librw.so", RTLD_LAZY);

    if (!dynamic_lib_desc) {
        cout << "Dynamic library not found!\n";
        exit(1);
    }

    pthread_t readthread;
    pthread_t writethread;

    pthread_attr_t attrread;
    pthread_attr_t attrwrite;

    pthread_attr_init(&attrread);
    pthread_attr_init(&attrwrite);

    pthread_create(&readthread, &attrread, file_reader, &_data);
    pthread_create(&writethread, &attrwrite, file_writter, &_data);

    _data.threads_arr[0] = readthread;
    _data.threads_arr[1] = writethread;
}