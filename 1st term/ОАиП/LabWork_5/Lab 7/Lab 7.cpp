#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	
	int a, i, j, **mtrx, max, im = 0, jm = 0;

	printf("Введите длину стороны квадратной мартицы (>1):\n");
	do scanf_s("%d", &a);
	while (a <= 1);

	mtrx = (int**)calloc(a,sizeof(int*));

	for (i = 0;i < a;i++)
		mtrx[i] = (int*)calloc(a,sizeof(int));   //создание матрицы

	for (i = 0;i < a;i++)
		for (j = 0;j < a;j++)
			do
			{
				rewind(stdin);
				printf("mtrx[%d][%d] = ", i, j);
			}
			while (!scanf_s("%d", &mtrx[i][j]));	//заполнение матрицы с клавиатуры

//	system("CLS");
	
	printf("Исходный массив:");
	   
	for (i = 0;i < a;i++)
		{
			printf("\n");
			for (j = 0;j < a;j++)
				printf("%d ", mtrx[i][j]);
		}

	
	if (mtrx[0][0] > 0)
		max = mtrx[0][0];
	else max = -mtrx[0][0];

	for (i = 0;i < a;i++)		//поиск наибольшего по модулю элемента
		for (j = 0;j < a;j++)
		{
			if (mtrx[i][j] > max)
			{
				max = mtrx[i][j];
				im = i;
				jm = j;
			}

			if (mtrx[i][j] < -max)
			{
				max = -mtrx[i][j];
				im = i;
				jm = j;
			}
			
		}

	printf("\n\nМаксимальный по модулю элемент:\nmtrx[%d][%d] = %d", im, jm, mtrx[im][jm]);
	
	for (i = 0;i < a;i++)					//преобразование матрицы согласно условию
		for (j = jm;j < (a - 1);j++)
			mtrx[i][j] = mtrx[i][j + 1];

	for (i = im;i < (a - 1);i++)
		for (j = 0;j < a;j++)
			mtrx[i][j] = mtrx[i + 1][j];

	
	for (i = 0;i < a;i++)
		mtrx[i] = (int*)realloc(mtrx[i], (a - 1) * sizeof(int));	//уменьшение матрицы 
	mtrx = (int**)realloc(mtrx, (a - 1) * sizeof(int*));		   //на один стлобец и одну строку

	printf("\n\nПреобразованный массив:");		//вывод матрицы в консоль

	for (i = 0;i < (a-1);i++)
	{
		printf("\n");
		for (j = 0;j < (a-1);j++)
			printf("%d ", mtrx[i][j]);
	}

	for (i = 0;i < (a - 1);i++)		//высвобождение указателя
		free(mtrx[i]);
	free(mtrx);

	printf("\n");
	return 0;
}