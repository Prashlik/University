#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

//вариант 6

typedef struct list list;

struct list
{
	int numb;
	struct list* prev;
};

void push(list** s)
{
	system("CLS");

	list* current = (list*)malloc(sizeof(list));

	printf("Enter a new element: ");
	scanf_s("%d", &(current->numb));

	current->prev = *s;
	*s = current;
}

void show(list** s)
{

	list* current = *s;

	if (current == NULL)
	{
		printf("The list is empty.\n");
		return;
	}

	printf("Your elements are: ");

	while (current != NULL)
	{
		printf("%d", current->numb);

		current = current->prev;

		if (current != NULL)
			printf(" --> ");
	}

	printf("\n");
}

void deleting(list** s, int count, int numb)
{
	int i;

	list* current = *s, * previous;
	
	for (i = 0; i < numb; i++)
		current = current->prev;

	for (i = 0;i < count;i++)
	{
		previous = current->prev;
		if (previous != NULL)
		{
			current->prev = previous->prev;
			free(previous);
		}
		else
		{
			*s = previous;
			free(current);
		}
	}
}

void Free(list** s)
{
	list* current = *s, * previous;
	while (*s != NULL)
	{
			*s = current->prev;
			free(current);
			current = *s;
	}
}

int main()
{
	list* start = NULL;
	int count = 0, co = 0;

	for (;;)
	{
		system("CLS");
		printf("===============MENU===============\n");
		printf("0.Exit\n");
		printf("1.Add a new element\n");
		printf("2.Show a list\n");
		printf("3.Delete a middle element(elements)\n");
		printf("==================================\n");
		rewind(stdin);

		
		switch (_getch())
		{

		case '0':
			system("CLS");
			Free(&start);
			return 0;

		case '1':
			system("CLS");
			push(&start); 
			count++;
			break;

		case '2':
			show(&start);
			system("PAUSE");
			break;

		case '3':
			if (!count)
			{
				printf("The list is empty.\n");
				system("PAUSE"); 
				break;
			}
			if (count % 2 == 0)
				co = 2;
			else co = 1;

			printf("Before: ");
			show(&start);

			deleting(&start, co, (count/2 - co));

			count -= co;
			printf("After: ");
			show(&start);
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