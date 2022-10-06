#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	char *text;
	int i = 0, t1 = -1, t2 = -1, p1, p2 = -1, tf, sum = 0, ch, n, per, len;

	if(!(text = (char*)calloc(300, 1))) return 0;

	printf("Введите текст:\n"); //Создание и заполнение строки
	gets(text);

	for (len = 0;text[len];len++); //Нахождение длины текста

	do
	{
		t1 = t2;
		do t2++;		//Нахождение границы предложения
		while(text[t2] != 46);

		n = 0;
		tf = 0;
		for (i = (t1 + 1);i < t2;i++)
		{
			if ((text[i] < 48 || text[i] > 57) && text[i] != 32)
			{
				tf = 1;					//Проверка предложения
				break;					//на соответствие условию
			}
			if (text[i] > 48 && text[i] < 57) n++;
		}

		if (tf == 0 && n > 0)
		{
			for(p1 = t1;text[p1 + 1] < 48 || text[p1 + 1] > 57;p1++);
			do
			{
				ch = 0;
				p2 = p1;
				do p2++;
				while (text[p2] != 32 && text[p2] != 46);
				for (i = p2 - 1;i > p1;i--)
				{
					per = (text[i] - 48);
					for (n = 0;n < (p2 - 1 - i); n++)
						per *= 10;
					ch += per;
				}
				/*поиск границ слова и перевод из симв. в числ.*/
				sum += ch;

				for (i = len;i >= p1;i--)  //выделение слова,
					text[i + 1] = text[i]; //состоящего из цифер
				text[p1 + 1] = '[';
				p2++;
				t2++;
				len++;

				for (i = len;i >= p2;i--)
					text[i + 1] = text[i];
				text[p2] = ']';
				p2++;
			 	t2++;
				len++;

				p1 = p2;

				for (p1 = p2;p1 < t2;p1++)  //поиск начала след. слова
					if (text[p1 + 1] > 48 && text[p1 + 1] < 57) break;
			} while (p1 != t2);
		}
		 
	} while (text[t2 + 1]);

	printf("\nПреобразованный текст:\n");
	puts(text);
	
	printf("\nСумма всех чисел из предложений, состоящих только из цифр: %d\n", sum);

	free(text); //высвобождение массива

	printf("\n");
	return 0;
}