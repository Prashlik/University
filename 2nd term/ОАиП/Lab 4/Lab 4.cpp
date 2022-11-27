#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>
#include <io.h>


void add(FILE* file)
{
	int flag, high = 1, width = 1, size, pixel = 0;

	system("CLS");
	printf("Enter the high of the picture: ");
	
	do
	{
		rewind(stdin);
		if (high <= 0)
			printf("Uncorrect choise!\n");
		scanf_s("%d", &high);
	} while (high <= 0);

	fwrite(&high, 1, sizeof(int), file);


	printf("\nEnter the width of the picture: ");
	do
	{
		rewind(stdin);
		if (width <= 0)
			printf("Uncorrect choise!\n");
		scanf_s("%d", &width);
	} while (width <= 0);

	fwrite(&width, 1, sizeof(int), file);


	printf("\nChoose the size of the pixel\n"
		"1. 3 bytes (RGB)\n"
		"2. 4 bytes (RGBW)\n");

	flag = 1;
	do
	{
		switch (getch())
		{
		case '1':
			size = 3;
			break;

		case '2':
			size = 4;
			break;

		default:
			printf("Uncorrect choise!\n");
			rewind(stdin);
			flag = 0;
			break;
		} 
	} while (!flag);

	fwrite(&size, sizeof(int), 1, file);

	printf("\nEnter the array of pixels:\n");

	for (int i = 0;i < width * high; i++)
	{
		do
		{
			scanf_s("%x", &pixel);

			if ((pixel > 0xFFFFFF && size == 3 ) || ((pixel > 0xFFFFFFFF && size == 4)))
			{
				printf("The wrong code of the pixel!\n");
				flag = 1;
			}
			else flag = 0;

		} while (flag);

		fwrite(&pixel, 1, size, file);
	}
	
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

//void delete(FILE* file, int numb)
//{
//	int high, width, key, size, pixel, i, j, step;
//	fseek(file, 0, SEEK_END);
//	i = ftell(file);
//
//	fseek(file, 0, SEEK_SET);
//	for (;;)
//	{
//		fread(&key, sizeof(int), 1, file);
//		if (key == numb)
//			break;
//
//		fread(&high, sizeof(int), 1, file);
//		fread(&width, sizeof(int), 1, file);
//		fread(&size, sizeof(int), 1, file);
//
//		fseek(file, high * width * size, SEEK_CUR);
//	}
//
//	fread(&high, sizeof(int), 1, file);
//	fread(&width, sizeof(int), 1, file);
//	fread(&size, sizeof(int), 1, file);
//	step = high * width * size + 3;
//
//
//	fseek(file, -3, SEEK_CUR);
//
//	int k;
//	k = ftell(file);
//
//	for (;;)
//	{
//
//		fseek(file, step, SEEK_CUR);
//		if (ftell(file) == i) break;
//
//		k = ftell(file);
//
//		fread(&j, 1, 1, file);
//
//		k = ftell(file);
//
//		fseek(file, -step - 1, SEEK_CUR);
//
//		k = ftell(file);
//
//		fwrite(&j, 1, 1, file);
//
//		k = ftell(file);
//	}
//
//	_chsize(_fileno(file), i - step);
//
//};


int main()
{
	int count = 0, numb = 0, i, j;
	FILE* file;

	if (!(file = fopen("pictures.dat", "a+b")))
		return 0;


	fseek(file, 0, SEEK_END);
	i = ftell(file);

	if (ftell(file) != 0)
	{
		fseek(file, 0, SEEK_SET);
		do
		{
			int a, b, c;
			fread(&count, sizeof(int), 1, file);
			fread(&a, sizeof(int), 1, file);
			fread(&b, sizeof(int), 1, file);
			fread(&c, sizeof(int), 1, file);

			fseek(file, a * b * c, SEEK_CUR);
			j = ftell(file);
		} while (j != i);
	}


	for (;;)
	{
		system("CLS");
		printf("=================MENU=================\n"
			"0. Exit\n"
			"1. Add a new picture\n"
			"2. Show a picture\n"
			"3. Show all the pictures\n"
			"======================================\n");
		rewind(stdin);


		switch (_getch())
		{

		case '0':
			system("CLS");

			fclose(file);

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


		//case '4':
		//	system("CLS");

		//	if (count == 0)
		//		printf("There are no pictures!\n");
		//	else
		//	{
		//		printf("Enter the key of picture you want to delete (1..%d): ", count);

		//		numb = 1;
		//		do
		//		{
		//			rewind(stdin);
		//			if (numb < 1 || numb > count)
		//				printf("\nUncorrect choise!\n");
		//			scanf_s("%d", &numb);
		//		} while (numb < 1 || numb > count);

		//		delete(file, numb);
		//	}
		//	break;


		default:
			system("CLS");
			printf("Unknown command\n\n");
			system("PAUSE");
			break;

		} 

	}
	

	return 0;
}

