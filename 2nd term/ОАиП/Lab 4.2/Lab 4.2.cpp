#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>


void add1(FILE* file)
{
	int high, width;
	char model[10];

	system("CLS");

	printf("Enter the model of the telephone: ");

	gets_s(model);

	fwrite(&model, 10, 1, file);


	printf("\nEnter the high of the screen: ");
	do
	{
		rewind(stdin);
		if (high <= 0)
			printf("Uncorrect choise!\n");
		scanf_s("%d", &high);
	} while (high <= 0);

	fwrite(&high, sizeof(int), 1, file);

	printf("\nEnter the width of the screen: ");
	do
	{
		rewind(stdin);
		if (width <= 0)
			printf("Uncorrect choise!\n");
		scanf_s("%d", &width);
	} while (width <= 0);
	
	fwrite(&width, sizeof(int), 1, file);

	return;
}

void add2(FILE* file)
{
	int dencity;
	char model[10], OS[10];

	system("CLS");

	printf("Enter the model of the telephone: ");

	gets_s(OS);

	fwrite(&OS, 10, 1, file);


	printf("Enter the OS of the telephone: ");

	gets_s(model);

	fwrite(&model, 10, 1, file);

	printf("\nEnter the dencity of the screen: ");
	do
	{
		rewind(stdin);
		if (dencity <= 0)
			printf("Uncorrect choise!\n");
		scanf_s("%d", &dencity);
	} while (dencity <= 0);

	fwrite(&dencity, sizeof(int), 1, file);

	return;
}

void print(FILE* file, int numb)
{
	int high, width, key, size, pixel, i, j;

	fseek(file, 0, SEEK_SET);
	for (;;)
	{
		fread(&key, sizeof(int), 1, file);
		if (key == numb)
			break;

		fread(&high, sizeof(int), 1, file);
		fread(&width, sizeof(int), 1, file);
		fread(&size, sizeof(int), 1, file);

		fseek(file, high * width * size, SEEK_CUR);
	}

	printf("Picture %d:\n\n", key);

	fread(&high, sizeof(int), 1, file);
	fread(&width, sizeof(int), 1, file);
	fread(&size, sizeof(int), 1, file);

	for (i = 0; i < high; i++)
	{
		printf("	");
		for (j = 0; j < width; j++)
		{
			fread(&pixel, size, 1, file);
			if (size == 3)
			{
				printf("%06X  ", pixel - 0xCC000000);
			}
			else printf("%08X  ", pixel);
		}
		printf("\n");
	}

	return;
};

void printall(FILE* file)
{
	int i, j, high, width, size, key, pixel, m, k;

	fseek(file, 0, SEEK_END);
	m = ftell(file);

	if (ftell(file) != 0)
	{
		fseek(file, 0, SEEK_SET);
		do
		{
			fread(&key, sizeof(int), 1, file);
			printf("Picture %d:\n\n", key);

			fread(&high, sizeof(int), 1, file);
			fread(&width, sizeof(int), 1, file);
			fread(&size, sizeof(int), 1, file);

			for (i = 0; i < high; i++)
			{
				printf("	");
				for (j = 0; j < width; j++)
				{
					fread(&pixel, size, 1, file);
					if (size == 3)
					{
						printf("%06X  ", pixel - 0xCC000000);
					}
					else printf("%08X  ", pixel);
				}
				printf("\n");
			}

			printf("\n\n");

			k = ftell(file);
		} while (k != m);
	}

};


int main()
{
	int count = 0, numb = 0, i, j;
	FILE* f1, * f2, * f3;

	if (!(f1 = fopen("F1.dat", "a+b")))
		return 0;
	if (!(f2 = fopen("F2.dat", "a+b")))
	{
		fclose(f1);
		return 0;
	}
	if (!(f3 = fopen("F3.dat", "a+b")))
	{
		fclose(f1);
		fclose(f2);
		return 0;
	}



	for (;;)
	{
		system("CLS");
		printf("=================MENU=================\n"
			"0. Exit\n"
			"1. Add a new model into file 1\n"
			"2. Add a new model into file 2\n"
			"3. Add the result into file 3\n"
			"======================================\n");
		rewind(stdin);


		switch (_getch())
		{

		case '0':
			system("CLS");

			fclose(f1);
			fclose(f2);
			fclose(f3);

			return 0;

		case '1':
			system("CLS");

			count++;

			fwrite(&count, 1, sizeof(int), file);

			add(file);

			break;


		case '2':
			system("CLS");

			if (count == 0)
				printf("There are no pictures!\n");
			else
			{
				printf("Enter the key of picture you want to look at (1..%d): ", count);

				numb = 1;
				do
				{
					rewind(stdin);
					if (numb < 1 || numb > count)
						printf("\nUncorrect choise!\n");
					scanf_s("%d", &numb);
				} while (numb < 1 || numb > count);

				print(file, numb);
			}

			system("PAUSE");

			break;


		case '3':
			system("CLS");

			if (count == 0)
				printf("There are no pictures!\n");
			else printall(file);

			system("PAUSE");

			break;


		default:
			system("CLS");
			printf("Unknown command\n\n");
			system("PAUSE");
			break;

		}

	}


	return 0;
}