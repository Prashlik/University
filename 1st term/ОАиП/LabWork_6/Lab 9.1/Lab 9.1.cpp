#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int atoi(char* ss, int flag1)
{
	int n, i = 0, znak;
	for (n = 0; ss[flag1] >= '0' && ss[flag1] <= '9'; flag1++)
		n = 10 * n + (ss[flag1] - '0');
	return n;
}
int main()
{
	int sum = 0;
	setlocale(LC_ALL, "rus");
	char* s;
	int j;
	char c;
	int i, q = 0;
	s = (char*)malloc(sizeof(char));
	while ((c = getchar()) != '\n')
	{
		s[q++] = c;
		s = (char*)realloc(s, sizeof(char) * (q + 1));
	}
	s[q] = '\0';
	printf("Введённая строка:");
	for (i = 0; i < q; i++)
		printf("%c", s[i]);
	i = 0;
	int flag1, flag2;
	while (s[i] != '\0')
	{
		flag1 = 0;
		flag2 = 0;
		if (s[i] >= '0' && s[i] <= '9' && ((s[i - 1] >= '0' && s[i - 1] <= '9') || s[i - 1] == ' ' || (i - 1) == -1 || s[i - 1] == ']'))
		{
			flag1 = i;
			while (s[i] >= '0' && s[i] <= '9')
			{
				i++;
			}
			if (s[i] == ' ' || s[i] == '\0')
				flag2 = i++;
			if (flag2)
			{
				sum += atoi(s, flag1);
				s = (char*)realloc(s, sizeof(char) * (++q + 1));
				for (j = 0; j < (q - flag1 + 1); j++)
				{
					s[q - j + 1] = s[q - j];
				}
				s[q] = '\0';
				s[flag1] = '[';
				s[flag2 + 1] = ']';
			}
		}
		i++;
	}
	printf("\n\nНовая строка:");
	for (i = 0; i < q + 1; i++)
		printf("%c", s[i]);
	printf("\nСумма:%d", sum);
	return 0;
}