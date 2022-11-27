#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	int arr[9];
	int i, j;

	printf("Введите 9 элементов массива:\n");
	
	for (i = 0;i < 9;i++)     //заполение массива
		scanf_s("%d",&arr[i]);

	for (i = 0;i < 8;i++)    //преобразование массива, согласно условию
		for (j = i + 1;j < 9;j++)
		{
			if (arr[i] < arr[j])
			{
				arr[i] = arr[j];
				break;
			}
			if (j == 8) arr[i] = 0;
		}
	
	arr[8] = 0;

	printf("Преобразованный массив:\n");

	for (i = 0;i < 9;i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}
