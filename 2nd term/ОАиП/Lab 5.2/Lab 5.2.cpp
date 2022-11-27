#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>
#include <string.h>

//вариант 6

typedef struct word word;

struct word
{
	char* word;
	struct word* prev;
};

void push(word** s, char* a)
{
	word* current = (word*)malloc(sizeof(word));

	current->word = (char*)malloc(100, 1);

	strcpy(current->word, a);

	current->prev = *s;
	*s = current;
}

void pop(word** s)
{
	word* current, * previous;

	current = previous = *s;

	while (previous != NULL)
	{
		current = previous;
		for (int i = 0;current->word[i]; i++)
		{
			printf("%c", current->word[i]);
		}

		printf(" ");

		previous = current->prev;
		free(current);
	}

	*s = previous;
}




int main()
{
	word* start = NULL;
	int i;
	char *string = (char*)malloc(1000, sizeof(char));
	char* word = (char*)malloc(100, sizeof(char));

	for (;;)
	{
		system("CLS");
		printf("Press '0' to finish the program. Press '1' to change your text.");
		rewind(stdin);


		switch (_getch())
		{

		case '0':
			system("CLS");
			return 0;

		case '1':
			system("CLS");
			printf("Enter your text:\n");
			gets(string);

			i = 0;
			do
			{
				while (string[i] == ' ')
					i++;

				int j = 0;
				
				do
				{
					word[j] = string[i];
					j++;
					i++;
				} while (string[i] && string[i] != ' ');

				word[j] = '\0';
				push(&start, word);

			} while (string[i]);

			printf("Your converted text:\n");

			pop(&start);
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