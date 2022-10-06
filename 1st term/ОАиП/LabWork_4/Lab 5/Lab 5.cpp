#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

#define N 4


int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	int arr[N][N];
	int i, j, max, el=0;

	printf("Введите матрицу размером %dх%d:\n", N, N); //заполнение матрицы
	for (i = 0;i < N;i++)
		for (j = 0;j < N;j++)
			scanf_s ("%d", &arr[i][j]);

	max = arr[0][0];

	for (i = 1;i < N;i++)  //поиск макмимального элемента в главной диагонали
		if (max < arr[i][i])
			max = arr[i][i];

	printf("Наибольший элемент главной диагонали max = %d\n", max);

	for (i = 1;i < N;i++)  //поиск элементов под главной диагональю, равных max
		for (j = 0;j < i;j++)
			if(arr[i][j] == max)
			{
				printf("Элемент под главной диагональю, равный max, имеет координаты:[%d][%d]\n", i, j);
				el = 1;
			}
	if (!el) printf("В данной матрице нету элементов под главной диагональю, равных max.");

	printf("\n");
	return 0;
}