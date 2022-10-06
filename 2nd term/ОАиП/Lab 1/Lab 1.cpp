#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

#define PagePrice 10
#define BlackPrice 0.01
#define ColoredPrice 0.02

enum color { black, red, blue };

struct paragraph
{
	int count, length, font, between, before, after;
	color col;
};

const char* colorName(color col)
{
	switch (col)
	{
	case 0: return "Black";
	case 1: return "Red";
	case 2: return "Blue";
	}
}

int high (int numb, paragraph* par)
{
	int h = 0;
	for (int i = 0;i < numb;i++)
		h += par[i].before + par[i].after + (par[i].count * par[i].font) + ((par[i].count - 1) * par[i].between);
	return h;
}

int filling(int n, int numb, paragraph* par)
{
	if (n < numb)
	{
		printf("Для параграфа №%d\n", n + 1);
		do 
		{
			printf("  Введите количество строк:\n  ");
			rewind(stdin);
		}
		while (!(scanf_s("%d", &par[n].count)));
		do
		{
			printf("  Введите длину строки:\n  ");
		}while (!(scanf_s("%d", &par[n].length)));
		do
		{
			printf("  Введите размер шрифта:\n  ");
		}while(!(scanf_s("%d", &par[n].font)));
		do
		{
			printf("  Введите междустрочный интервал:\n  ");
			rewind(stdin);
		}while (!(scanf_s("%d", &par[n].between)));
		do
		{
			printf("  Введите интервал до параграфа:\n  ");
			rewind(stdin);
		} while (!(scanf_s("%d", &par[n].before)));
		do
		{
			printf("  Введите интервал после параграфа:\n  ");
			rewind(stdin);
		} while (!(scanf_s("%d", &par[n].after)));
		do 
		{
			rewind(stdin);
			printf("  Введите цвет текста (0 - чёрный, 1 - красный, 2 - синий):\n  ");
			scanf_s("%d", &par[n].col);
		} while (par[n].col < 0 || par[n].col > 2);
		n++;
		n = filling(n, numb, par);
	}
	return(n);
}

void info(int i, paragraph* par)
{
	printf("Для параграфа №%d:\n", i + 1);
	printf("  Количество строк: %d\n  ", par[i].count);
	printf("  Длина строки: %d\n  ", par[i].length);
	printf("  Размер шрифта: %d\n  ", par[i].font);
	printf("  Междустрочный интервал: %d\n  ", par[i].between);
	printf("  Интервал до параграфа: %d\n  ", par[i].before);
	printf("  Интервал после параграфа: %d\n  ", par[i].after);
	printf("  Цвет текста: %s\n  ", colorName(par[0].col));
}



int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	int numb = 0, i = 0, n = 0, h, PgHigh, PgCount;
	double price;

	do
	{
		system("CLS");
		printf("Введите количество параграфов:\n");
		rewind(stdin);
	} while (scanf_s("%d", &numb), numb < 0);

	paragraph* par;
	if (!(par = (paragraph*)calloc(numb, sizeof(paragraph)))) return 0;

	n = filling(n, numb, par);

	do
	{
		system("CLS");
		printf("Введите высоту страницы:\n");
		rewind(stdin);
	} while (scanf_s("%d", &PgHigh), PgHigh < 0);


	for (;;)
	{
		do {
			system("CLS");
			printf("===============МЕНЮ===============\n");
			printf("1.Узнать количество параграфов\n");
			printf("2.Добавить параграфы\n");
			printf("3.Узнать информацию о параграфе\n");
			printf("4.Узнать высоту текста в пикселях\n");
			printf("5.Узнать кол-во страниц\n");
			printf("6.Изменить высоту страницы\n");
			printf("7.Узнать стоимость печати\n");
			printf("8.Выход\n");
			printf("==================================\n");
			rewind(stdin);
		} while (!(scanf_s("%d", &i)) || (i < 1) || (i > 8));
		switch (i)
		{
		
		case 1: 
			printf("\nВсего в тексте параграфов: %d\n\n", numb);
			system("PAUSE");
			break;
		
		case 2: 
			printf("\nВведите количество параграфов, которые вы хотите добавить: ");
			scanf_s("%d", &i);
			numb += i;
			system("CLS");
			if (!(par = (paragraph*)realloc(par, numb * sizeof(paragraph)))) 
			{
				free(par);
				return 0;
			}

			n = filling(n, numb, par);
			break;
		
		case 3:
			do {
				rewind(stdin);
				printf("\nВведите номер параграфа, о котором вы бы хотели узнать: ");
				scanf_s("%d", &i);
			} while (i < 1 || i > numb);
			info((i - 1), par);
			system("PAUSE");
			break;
	
		case 4: 
			h = high(numb, par);
			printf("\nВысота текста (в пикселях): %d\n\n", h);
			system("PAUSE");
			break;

		case 5:
			h = high(numb, par);
			PgCount = (h / PgHigh) + 1;
			printf("Текст помещается на %d стр. \n", int(PgCount));
			system("PAUSE");
			break;

		case 6:
			do
			{
				printf("Введите высоту страницы:\n");
				rewind(stdin);
			} while (scanf_s("%d", &PgHigh), PgHigh < 0);
			system("PAUSE");
			break;

		case 7:
			h = high(numb, par);
			PgCount = (h / PgHigh) + 1;
			price = PagePrice * PgCount;
			for (i = 0;i < numb;i++)
			{
				int txt = par[i].count * par[i].length * par[i].font;
				if (par[i].col == black) price += txt * BlackPrice;
				else price += txt * ColoredPrice;
			}
			printf("Распечатка текста будет стоить: %.2f\n", price);
			system("PAUSE");
			break;

		case 8: 
			free(par);
			return 0;
		}
	}
}
