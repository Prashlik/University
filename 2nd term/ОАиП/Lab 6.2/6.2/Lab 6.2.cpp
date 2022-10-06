#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct circle {
	char symbol;
	struct circle* next;
}circle;

void Free(circle** s)
{
	circle* current = *s;
	
	if (*s != NULL)
	{
		*s = current->next;
		current->next = NULL;
		current = *s;
	}

	while (*s != NULL)
	{
		*s = current->next;
		free(current);
		current = NULL;
		current = *s;
	}
}

void add(circle** head, circle** tmp, char sym) 
{
	circle* current = *tmp;

	circle* New = (circle*)malloc(sizeof(circle));
	New->symbol = sym;
	New->next = *head;
	current->next = New;
	*tmp = New;
}

void palindrome(circle* head, int length) {
	int N = 0, rebound, flag = 0, j, k;
	char symbol = 0;
	printf("Enter the length of the palindrome: ");
	rewind(stdin);
	scanf_s("%d", &N);

	circle* current = head;
	printf("\nYour string:\n");

	for (int i = 0; i < length; i++)
	{
		printf("%c", current->symbol);
		current = current->next;
	}

	current = head;
	circle* first = head;

	for (int i = 0; i < length; i++)
	{
		current = first;
		rebound = 1;

		for (j = 0; j < N / 2; j++)
		{
			symbol = current->symbol;

			for (k = 0; k < N - rebound; k++)
				current = current->next;

			if (symbol == current->symbol)
			{
				if (j != N / 2 - 1)
				{
					rebound += 2;
					current = first;

					for (k = 0; k <= j; k++)
						current = current->next;
				}
				else
				{
					if (flag == 0)
						printf("\n\nPalindromes:\n");
					flag++;
					current = first;
					for (k = 0; k < N; k++)
					{
						printf("%c", current->symbol);
						current = current->next;
					}
					printf("\n");
					first = first->next;
				}
			}
			else
			{
				first = first->next;
				break;
			}

		}
		
	}
	if (flag == 0) {
		printf("\nThere are no palendromes!");
	}

}

int main(void) {
	int stop = 0, i, length;
	char sim = 0, str[30];

	circle* start = NULL;


	for (;;)
	{
		system("CLS");
		printf("===============MENU===============\n");
		printf("0.Exit\n");
		printf("1.Add a new string\n");
		printf("2.Find all the palindromes\n");
		printf("==================================\n");
		rewind(stdin);


		switch (_getch())
		{

		case '0':
			system("CLS");
			Free(&start);

			return 0;



		case '1':
			Free(&start);

			system("CLS");

			start = (circle*)malloc(sizeof(circle));

			printf("Enter a string:");
			rewind(stdin);
			
			i = 0;
			length = 0;

			gets(str);
			start->symbol = str[i];
			i++;
			length++;
			start->next = start;
			
			circle* tmp = start;

			while (str[i] != '\0') 
			{

				add(&start, &tmp, str[i]);
				i++;
				length++;
			}
			break;



		case '2':
			system("CLS");

			palindrome(start, length);
			printf("\n");
			system("PAUSE");

			break;



		default:
			system("CLS");
			printf("Unknown command\n\n");
			system("PAUSE");
			break;

		}
	}
}