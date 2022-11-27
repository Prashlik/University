#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

//вариант 10

typedef struct Node Node;

struct Node
{
	char* string;
	struct Node* next;
};

typedef struct queue
{
	Node* head;
	Node* tail;
}queue;

void push_back(queue* Queue, char str[100])
{
	Node* new = (Node*)malloc(sizeof(Node));
	new->string = (char*)malloc(100, sizeof(char));
	strcpy_s(new->string, 100,str);
	new->next = NULL;
	if (Queue->head == NULL)
	{
		Queue->head = new;
		Queue->tail = new;
		return;
	}
	else
	{
		Queue->tail->next = new;
		Queue->tail = new;
	}
}


char* pop_front(queue* Queue)
{
	Node* old_head = Queue->head;   

	Queue->head = old_head->next;   
	if (Queue->head == NULL) 
	{ 
		Queue->tail = NULL; 
	}   
	char* string = old_head->string;   
	free(old_head);   
	return string;
};

void push_stack(Node** s, char str[100])
{
	Node* current = (Node*)malloc(sizeof(Node));

	current->string = (char*)malloc(100, sizeof(char));

	strcpy_s(current->string, 100, str);

	current->next = *s;
	*s = current;
}


char* pop_stack(Node** s)
{
	Node * current = *s;
	char *string;

	string = (char*)malloc(100, sizeof(char));

	string = current->string;
	
	*s = current->next;
	free(current);

	return string;
};




int main()
{
	Node* start = NULL;
	Node* stack = NULL;
	int i, count = 0;
	char string[100];

	queue Queue;

	for (;;)
	{
		system("CLS");
		printf("=================MENU=================\n"
			"0. Exit\n"
			"1. Change your list\n"
			   "======================================\n");
		rewind(stdin);


		switch (_getch())
		{

		case '0':
			system("CLS");
			
			return 0;

		case '1':
			system("CLS");

			Queue.head = NULL;
			Queue.tail = NULL;
			count = 0;

			printf("Enter your text('0' - the end of entering):\n");
			for (;;)
			{
				rewind(stdin);
				gets(string);
				if (string[0] != '0' || string[1] != '\0')
				{
					push_back(&Queue, string);
					count++;
				}
				else break;
			}

			for (i = 0;i != count;i++)
				push_stack(&stack, pop_front(&Queue));

			for (i = 0;i != count;i++)
				push_back(&Queue, pop_stack(&stack));

			printf("\nYour converted text:\n\n");

			for (count;count != 0;count--)
			puts(pop_front(&Queue));

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