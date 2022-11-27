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

struct Direction
{
	int count, countOFdir;
	struct File* file;
};

enum Type {File, Directory};

const char* FileT(enum Type t)
{
	switch (t)
	{
	case 0: return "File";
	case 1: return "Directory";
	}
}

struct File
{
	char name[15], login[20];
	enum Type TypeOfFile;
	union FileOrDir
	{
		struct FileType FilTyp;
		struct Direction Direct;
	};
};

int compare(char* a, char* b)
{
	int i;
	for (i = 0;a[i];i++)
		if (a[i] != b[i]) return 0;
	return 1;
}

void filling(int n, struct File* file)
{
	
	do {
		printf("  Введите имя файла:\n  ");
		rewind(stdin);
		gets(file[n].name);
	} while (!file[n].name[0]);

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

void print(int n, struct File* file)
{
	system("CLS");

	printf("Файл № %d\n", n);
	
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
		if (file[n].FilTyp.write) printf(" запрещена\n");
		printf(" разрешена\n");

	}
	else
	{
		printf("\n   Kоличество файлов в директории: %d\n", file[n].Direct.count);
	}

	system("PAUSE");
	system("CLS");
}

void fprint(int numb, struct File* file)
{

	int i, j, n;
	char cmd[20] = { "\0" }, command[10] = { "\0" }, fname[15];

	for (;;)
	{
		system("CLS");

		printf(" № |Имя файла       |Тип файла  |Логин владельца |\n");
		for (n = 1; n <= numb; n++)
		{
			printf("%2d.", n);
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
		printf("\n back - вернуться назад \n open Имя_Файла - открыть файл \n info Имя_Файла - информация о файле\n");

		rewind(stdin);

		do gets(cmd);
		while (!cmd[0]);

		i = 0;

		while (cmd[i] && cmd[i - 1] != ' ' && i < 5)
		{
			command[i] = cmd[i];
			i++;
		}
		command[i] = '\0';

		if (compare(command, "back")) return;

		else if (command == "read ") {}

		else if (command == "write ") {}

		else if (command == "open ") {}

		else if (compare(command, "info "))
		{
			j = 0;
			
			for (i;cmd[i];i++)
			{
				fname[j] = cmd[i];
				j++;
			}
			fname[j] = '\0';

			for (n = 1; n <= numb; n++)
				if (compare(fname, file[n].name))
					print(n, file);
		}
		else printf("Неизвестная команда\n");
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	int n, numb = 0;
	char i = '\0';

	struct File* file;
	if (!(file = (struct File*)calloc(1, sizeof(struct File)))) return 0;

	for (;;)
	{
		do {
			system("CLS");
			printf("==============| МЕНЮ |==============\n");
			printf("0.Выход\n");
			printf("1.Добавить файл\n");
			printf("2.Узнать количество файлов\n");
			printf("3.Узнать информацию о файле\n");
			printf("4.Вывести все текущие файлы\n");
			printf("====================================\n");
			rewind(stdin);
			 i = _getch();
		} while ((i < 48) || (i > 52));

		switch (i)
		{
		case '1':
			numb++;
			if (!(file = (struct File*)realloc(file, numb * sizeof(struct File)))) return 0;
			filling(numb, &file);
			break;

		case '2':
			printf("Всего файлов: %d\n", numb);
			system("PAUSE");
			break;

		case '3':
			do {
				printf("Введите номер файла (от 1 до %d): ", numb);
			}while (!(scanf_s("%d", &n)) || n < 0 || n > numb);
			print(n, &file);
			break;

		case '4':
			fprint(numb, &file);
			break;

		case '0': return 0;
		}
	}
}