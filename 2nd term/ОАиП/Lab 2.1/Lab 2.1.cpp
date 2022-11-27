#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

struct FileType
{
	char ext[10];
	int size;
	unsigned int read : 1, write : 1, execute : 1;
};

struct Directory
{
	int count, countOFdir;
	struct FILE* file;
};

enum Type { File, Directory };

const char* FileT(enum Type t)
{
	switch (t)
	{
	case 0: return "File";
	case 1: return "Directory";
	}
}

struct FILE
{
	char zero[5];
	char name[15], login[20];
	enum Type TypeOfFile;
	union FileOrDir
	{
		struct FileType FilTyp;
		struct Directory Direct;
	};
};



void clearing(struct FILE* file, int count)
{
	int i;
	for (i = 0; i < count; i++)
		if (file[i].TypeOfFile == 1)
		{
			clearing(&file[i].Direct.file, file[i].Direct.count);
			free(file[i].Direct.file);
		}

}

int compare(char* a, char* b)
{
	int i;
	for (i = 0;a[i];i++)
		if (a[i] != b[i]) return 0;
	if (b[i]) return 0;

	return 1;
}

void filling(int n, struct FILE* file)
{
	system("CLS");

	for (;;)
	{
		int flag = 0;
		do {
			printf("  Введите имя файла:\n  ");
			rewind(stdin);
			gets(file[n].name);
		} while (!file[n].name[0]);
		
		for (int i = 0;i < n;i++)
			if (compare(file[i].name, file[n].name))
			{
				flag = 1;
				break;
			}

		if (!flag) break;

		printf("Данное имя уже используется!\n");
	}

	do {
		printf("  Введите логин:\n  ");
		fflush(stdin);
		gets(file[n].login);
	} while (!file[n].login[0]);

	do {
		printf("  Введите подтип файла(0 - файл, 1 - директория):\n  ");
		rewind(stdin);
		scanf_s("%d", &file[n].TypeOfFile);
	} while (file[n].TypeOfFile > 1 || file[n].TypeOfFile < 0);

	if (file[n].TypeOfFile == 0)
	{
		file[n].FilTyp.read = 0;
		file[n].FilTyp.write = 0;
		file[n].FilTyp.execute = 0;

		do {
			printf("  Введите размер файла:\n  ");
			rewind(stdin);
			scanf_s("%d", &file[n].FilTyp.size);
		} while (!file[n].FilTyp.size);

		do {
			printf("  Введите расширение файла:\n  ");
			rewind(stdin);
			gets(file[n].FilTyp.ext);
		} while (!file[n].FilTyp.ext[n]);
	}
	else
	{
		file[n].Direct.count = 0;
	}
}

void print(int n, struct FILE* file)
{
	system("CLS");

	printf("Файл № %d\n", n + 1);

	printf("   Имя файла: ");
	puts(file[n].name);

	printf("   Логин: ");
	puts(file[n].login);

	printf("   Подтип файла: ");
	puts(FileT(file[n].TypeOfFile));

	if (file[n].TypeOfFile == 0)
	{
		printf("\n   Размер файла: %d\n", file[n].FilTyp.size);

		printf("   Расширение файла: ");
		puts(file[n].FilTyp.ext);

		printf("\n\nЗапуск файла");
		if (file[n].FilTyp.execute) printf(" запрещён\n");
		else printf(" разрешён\n");

		printf("Чтение файла");
		if (file[n].FilTyp.read) printf(" запрещено\n");
		else printf(" разрешено\n");

		printf("Запись файла");
		if (file[n].FilTyp.write) printf(" запрещена\n\n");
		printf(" разрешена\n\n");

	}
	else
	{
		printf("\n   Kоличество файлов в директории: %d\n\n", file[n].Direct.count);
	}

	system("PAUSE");
	system("CLS");
}

int fprint(int flag, struct FILE *file, int numb, char* adress)
{
	int i, j, n, fl;
	char cmd[30] = { "\0" }, command[10] = { "\0" }, fname[15], type[10];

	if (flag == 0)
		if(!(file = (FILE*)calloc(30, sizeof(FILE)))) return 0;
	
	for (;;)
	{
		system("CLS");
		
		fputs(adress, stdout);
		printf(":");
		printf("\0");
		
		if (numb == 0)
		{
			if (flag) printf("\n back - вернуться назад \n");
			else printf("\n exit - выход\n");

			printf(" add - добавить файл\n\n");
		}

		if (numb != 0)
		{
			printf("\n № |Имя файла       |Тип файла  |Логин владельца |\n");
			for (n = 0; n < numb; n++)
			{
				printf("%2d.", n + 1);
				printf("|");

				fputs(file[n].name, stdout);
				for (i = 0;i <= (15 - strlen(file[n].name)); i++) printf(" ");
				printf("|");

				fputs(FileT(file[n].TypeOfFile), stdout);
				for (i = 0;i <= (10 - strlen(FileT(file[n].TypeOfFile))); i++) printf(" ");
				printf("|");

				fputs(file[n].login, stdout);
				for (i = 0;i <= (15 - strlen(file[n].login)); i++) printf(" ");
				printf("|");

				printf("\n");
			}
			if (flag) printf("\n back - вернуться назад \n");
			else printf("\n exit - выход\n");

			printf(" add - добавить файл\n");

			printf(" info Имя_Файла - информация о файле\n open Имя_Файла - открыть(запустить) файл\n read - чтение файла\n write - запись в файл\n\n");
		}


		rewind(stdin);

		do gets(cmd);
		while (!cmd[0]);

		i = 0;

		while (cmd[i] && cmd[i - 1] != ' ' && i < 6)
		{
			command[i] = cmd[i];
			i++;
		}
		command[i] = '\0';

		if (compare(command, "back") && flag) return numb;

		else if (compare(command, "add"))
		{
			numb++;
			
			if (numb > 30)
				file = (FILE*)realloc(numb, sizeof(FILE));

			filling(numb - 1, file);

		}

		else if (compare(command, "read ")) 
		{
			system("CLS");
			j = 0;

			for (i;cmd[i];i++)
			{
				fname[j] = cmd[i];
				j++;
			}
			fname[j] = '\0';
			
			fl = 0;

			for (n = 0; n <= numb; n++)
			{
				if (compare(fname, file[n].name))
				{
					if (file[n].TypeOfFile == 0)
					{
						if (!file[n].FilTyp.read) printf("Разрешено\n\n");
						else printf("Запрещено\n\n");
						fl = 1;
						system("PAUSE");
						break;
					}

				}
			}
			if (!fl)
			{
				printf("Файл отсутствует\n\n");
				system("PAUSE");
			}
		}

		else if (compare(command, "write "))
		{
			system("CLS");
			j = 0;

			for (i;cmd[i];i++)
			{
				fname[j] = cmd[i];
				j++;
			}
			fname[j] = '\0';

			fl = 0;

			for (n = 0; n <= numb; n++)
			{
				if (compare(fname, file[n].name))
				{
					if (file[n].TypeOfFile == 0)
					{
						if (!file[n].FilTyp.write) printf("Разрешено\n\n");
						else printf("Запрещено\n\n");
						fl = 1;
						system("PAUSE");
						break;
					}
				}
			}
			if (!fl)
			{
				printf("Файл отсутствует\n\n");
				system("PAUSE");
			}
		}

		else if (compare(command, "open ")) 
		{
			system("CLS");
			j = 0;

			for (i;cmd[i];i++)
			{
				fname[j] = cmd[i];
				j++;
			}
			fname[j] = '\0';

			fl = 0;

			for (n = 0; n < numb; n++)
			{
					if (compare(fname, file[n].name))
				{
					if (file[n].TypeOfFile == 1)
					{
						file[n].Direct.file = (FILE*)calloc(30, sizeof(FILE));
						file[n].Direct.count = fprint(1, &file[n].Direct.file, file[n].Direct.count, file[n].name);
						fl = 1;
					}
					else
					{
						if (!file[n].FilTyp.execute) printf("Разрешено\n\n");
						else printf("Запрещено\n\n");
						fl = 1;
						system("PAUSE");
						break;
					}
				}
			}
			if (!fl)
			{
				printf("Файл(директория) отсутствует\n\n");
				system("PAUSE");
			}
		}

		else if (compare(command, "chmod "))
		{
			j = 0;

			for (i;cmd[i] != ' ';i++)
			{
				fname[j] = cmd[i];
				j++;
			}
			fname[j] = '\0';

			i++;
			j = 0;

			for (i;cmd[i];i++)
			{
				type[j] = cmd[i];
				j++;
			}
			type[j] = '\0';

			fl = 0;

			for (n = 0; n <= numb; n++)
			{
				if (compare(fname, file[n].name))
				{
					if (file[n].TypeOfFile == 0)
					{
						if (compare(type, "execute"))
						{
							file[n].FilTyp.execute++;
							fl++;
						}
						else if (compare(type, "read"))
						{
							file[n].FilTyp.read++;
							fl++;
						}
						else if (compare(type, "write"))
						{
							file[n].FilTyp.write++;
							fl++;
						}
						else
						{
							printf("\nНеизвестная команда.\n");
							system("PAUSE");
						}
						break;
					}
				}
				if (fl)
				{
					printf("Успешно.");
					system("PAUSE");
					break;
				}
			}
			if (!fl) 
			{ 
				printf("Файл отсутствует"); 
				system("PAUSE"); 
			}
		}

		else if (compare(command, "info "))
		{
			j = 0;

			for (i;cmd[i];i++)
			{
				fname[j] = cmd[i];
				j++;
			}
			fname[j] = '\0';

			for (n = 0; n <= numb; n++)
				if (compare(fname, file[n].name))
					print(n, file);
				else printf("Файл отсутствует");
		}

		else if (compare(command, "exit") && !flag)
		{
			clearing(&file, numb);
			free(file);
			return 0;

		}

		else
		{
			printf("Неизвестная команда.\n");
			system("PAUSE");
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");
	
	struct FILE* file;

	char* adress;

	adress = (char*)calloc(100,1);

	adress = "Корень\0";
	
	fprint(0, &file, 0,adress);

	return 0;

}