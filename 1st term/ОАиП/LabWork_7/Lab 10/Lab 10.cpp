#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	int n = 0, i, p;
	char *txt, *res;

	if (!(txt = (char*)malloc(300, 1))) return 0;
	if (!(res = (char*)calloc(300, 1)))
	{
		free(txt);
		return 0;
	}

	printf("Введите количество предложений: ");
	scanf_s("%d", &n);

	rewind(stdin);
	gets(txt);
	
	p = 0;
	i = 0;
	while (txt[i] && p < n )
	{
		if (txt[i] == '.') p++;
		i++;
	}

	txt[i + 1] = NULL;

//	system("CLS");

	printf("Исходный текст: \n");
	puts(txt);

	metod(txt, res);

	printf("Слова, встречающиеся больше одного раза:\n");
	puts(res);

	free(txt);
	free(res);


	printf("\n");
	return 0;
}


int metod(char *text, char *result)
{
	int i, j, count = 0, num = 0, k, tf, amount;
	char **words;

	for (i = 0;text[i];i++)
		if ((i == 0 || text[i - 1] == ' ' || text[i - 1] == '.') && text[i] != ' ' && text[i] != '.')
			count++;
	
	words = (char**)calloc(count, sizeof(char*));

	j = 0;
	for (i = 0;text[i];i++)
		if ((i == 0 || text[i - 1] == ' ' || text[i - 1] == '.') && text[i] != ' ' && text[i] != '.')
		{
			k = 1;
			while (text[i] != ' ' && text[i] != '.')
				{
					k++;
					i++;
				}
			words[j] = (char*)malloc(k);
			words[j][k] = NULL;
			j++;
		}
	
	for (i = 0;text[i];i++)
		if ((i == 0 || text[i - 1] == ' ' || text[i - 1] == '.') && text[i] != ' ' && text[i] != '.')
		{
			j = 0;
			while (text[i] != ' ' && text[i] != '.')
			{
				words[num][j] = text[i];
				i++;
				j++;
			}
			i--;
			words[num][j] = NULL;
			num++;
		}

	for (i = 0;i < count;i++)
	{
		amount = 0;
		for (j = i + 1;j < count; j++)
		{
			tf = 0;
			for (k = 0;words[i][k];k++)
				if (words[i][k] != words[j][k])
				{
					tf = 1;
					break;
				}

			if (tf == 1) continue;
			if (words[j][k] == NULL)
			{
				amount++;
				for (num = j++;j < count;j++)
					words[j - 1] = words[j];
				count--;
			}
			else continue;
		}
		if (amount == 0)
		{
			for (num = i + 1;num < count;num++)
				words[num - 1] = words[num];
			count--;
			i--;
		}
	}

	num = 0;
	for (i = 0;i < count;i++)
	{
		k = 0;
		while (words[i][k])
		{
			result[num] = words[i][k];
			k++;
			num++;
		}

		result[num] = ' ';
		num++;	
	}

	result[num] = NULL;

	free(words);
}