#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	char* s, * a;
	int n = 0, ns, na, i, j, k;

	do				//интеллектуальный ввод
	{				//длины строки
		rewind(stdin);
		printf("Введите размер строки: ");
		scanf_s("%d", &n);
	} while (!n);


	if (!(s = (char*)calloc(n + 1, sizeof(char)))) return 0;
	if (!(a = (char*)calloc(n + 1, sizeof(char))))
	{
		free(s);				//создание строк а и s
		return 0;
	}

	printf("Введите строку s:\n");	 //заполнение строк
	rewind(stdin);
	gets(s);

	printf("Введите строку a:\n");
	rewind(stdin);
	gets(a);

	na = ns = 0;
	while (s[ns]) ns++;
	if (ns > n) ns = n;
	s[n] = NULL;
	while (a[na]) na++;
	if (na > n) na = n;
	a[n] = NULL;

	for (i = 0;i < 50;i++)    //декор
		printf("=");

	printf("\nИсходная строка s:\n");
	puts(s);
	printf("\nИсходная строка a:\n");
	puts(a);


	for (i = 0;i < na;i++)		//преобразование s согласно условию
		for (j = 0;j < ns;j++)
			if (s[j] == a[i])
			{
				for (k = j;k < ns;k++)
					s[k] = s[k + 1];
				ns--;
			}

	printf("\nПреобразованная строка s:\n");
	puts(s);		//вывод строки s

	free(a);		//высвобождение указателей
	free(s);

	printf("\n");
	return 0;
}
