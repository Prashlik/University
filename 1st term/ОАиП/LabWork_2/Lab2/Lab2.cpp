#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>


int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	int x, y, z, i;
	int a = 1;


	do
	{
		printf("\nВведите x от 0 до 10:\n");
		printf("\n x = ");
		scanf_s("%d", &x);
	} while (x < 0 || x > 10);

	printf("\nВведите y, z :\n");
	printf("\n y = ");
	scanf_s("%d", &y);

	printf("\n z = ");
	scanf_s("%d", &z);

	if (y > 0 && z > 0)
		for (i = 0;i < y;i++) a *= x;	// возведение в х в степень у
	else
		if (y < 0 && z < 0)
			for (i = 0;i < -y;i++) a *= x;	// возведение в х в степень -у
		else a = 0;

	printf("\n a = %d", a);

		printf("\n");
		return 0;
}
