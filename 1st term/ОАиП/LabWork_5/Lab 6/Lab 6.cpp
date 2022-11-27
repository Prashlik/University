#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");
	
	int i, j, a, l, h, res;
	float* arr;

	printf("Введите размеры матрицы: ");
	printf("\nСтолбцы: ");
	scanf_s("%d", &l);
	printf("Строки: ");
	scanf_s("%d", &h);

	if (!(arr = (float*)malloc(l * h * sizeof(float)))) //создание матрицы
		return 0;

//	system("CLS");
	
	printf("\nВведите элементы массива: \n");

	for (j = 0;j < h;j++)
		for (i = 0;i < l;i++)
		{
			printf("arr[%d][%d] = ",j, i);	//заполнение массива вручную
			scanf_s("%f", arr + j * sizeof(float) + i);
		} 
	
	for (j = 0;j < h;j++)
		for (i = 0;i < (l - 1);i++)					//изменение массива согласно условию
			if (*(arr + j * sizeof(float) + i) > 0)
				for (a = i;a < l;a++)
					if (*(arr + j * sizeof(float) + a) > * (arr + j * sizeof(float) + i))
					{
						res = *(arr + j * sizeof(float) + a);
						*(arr + j * sizeof(float) + a) = *(arr + j * sizeof(float) + i);
						*(arr + j * sizeof(float) + i) = res;
					}
	
	printf("Преобразованный массив:\n");		//вывод массива в консоль
	for (j = 0;j < h;j++)
	{
		printf("\n");
		for (i = 0;i < l;i++)
			printf("%.2f ", *(arr + j * sizeof(float) + i));
	}

//	free(arr);		//высвобождение массива
	
	printf("\n");
	
	return 0;
}