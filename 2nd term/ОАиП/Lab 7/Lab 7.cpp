#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

//вариант 11

typedef struct node node;

struct node
{
	int key;
	int value;
	struct node* left;
	struct node* right;
};

int add(char* adress, int count, node** root)
{
	node* current = *root;
	node* New = (node*)malloc(sizeof(node));


	New->left = NULL;
	New->right = NULL;

	while (count)
	{
		if (adress[count] == '0')
			current = current->left;
		else current = current->right;

		if (current == NULL && count != 1)
			return 0;

		count--;
	}

	if (adress[count] == '0')
	{
		if (current->left == NULL)
		{
			New->key = current->key * 2;
			current->left = New;
		}
		else
		{
			free(New);
			return 2;
		}
	}
	else
	{
		if (current->right == NULL)
		{
			New->key = current->key * 2 + 1;
			current->right = New;
		}
		else
		{
			free(New);
			return 2;
		}
	}

	do
	{
		rewind(stdin);
		printf("\nEnter the value of your new element: ");
	} while (!scanf_s(" %d", &New->value));

	printf("\n\nYou added a new element with the key number %d and value %d\n", New->key, New->value);

	return 1;
}

int symmetric(node* left, node* right)
{
	int flag = 0;

	if (left != right)
		if (left != NULL && right != NULL)
			flag = symmetric(left->left, right->right);
		else flag = 1; 

	return flag;
}

void Free(node* root)
{
	if (root->left != NULL)
		Free(root->left);

	if (root->right != NULL)
		Free(root->right);

	free(root);

	return;
}

int maximum(node* point, int max)
{
	if (point->value > max)
		max = point->value;

	if (point->left != NULL)
		max = maximum(point->left, max);

	if (point->right != NULL)
		max = maximum(point->right, max);

	return max;
}

int minimum(node* point, int min)
{
	if (point->value < min)
		min = point->value;

	if (point->left != NULL)
		min = minimum(point->left, min);

	if (point->right != NULL)
		min = minimum(point->right, min);

	return min;
}





int main()
{
	int key, count = 0, flag;
	char* adress;

	node* root = (node*)malloc(sizeof(node));

	root->left = NULL;
	root->right = NULL;
	root->key = 1;

	for (;;)
	{
		system("CLS");
		printf("=================MENU=================\n"
			"0. Exit\n"
			"1. Add a new node\n"
			"2. Check the symmetricity of your tree\n"
			"3. Find maximum element in some branch\n"
			"4. Find minimum element in some branch\n"
			"======================================\n");
		rewind(stdin);


		switch (_getch())
		{

		case '0':
			system("CLS");

			Free(root);

			return 0;

		case '1':
			flag = 0;
			
			do
			{
				system("CLS");

				do
				{
					printf("Enter the key of the node you want to add to:\n");
					rewind(stdin);
				} while (!scanf_s("%d", &key) || key < 1);

				count = 2;
				adress = (char*)malloc(256);

				do
				{
					printf("From wich side do you want to add:\n"
						"1. Left\n"
						"2. Right\n");

					switch (_getch())
					{
					case '1':
						adress[0] = '0';
						count = 0;
						break;

					case '2':
						adress[0] = '1';
						count = 0;
						break;

					default:
						printf("Invalid choise.\n\n");
						break;
					}
				} while (count == 2);


					
				while (key != 1)
				{
					count++;

					if (key % 2 == 0)
						adress[count] = '0';
					else adress[count] = '1';

					key = key / 2;
				}

				switch (add(adress, count, &root))
				{
				case 2:
					printf("This node is already added!\n\n");
					flag = 1;
					system("PAUSE");
					break;

				case 1:
					printf("Success!\n\n");
					flag = 1;
					system("PAUSE");
					break;

				case 0:
					printf("Uncorrect choise!\n\n");
					system("PAUSE");
					break;
				}
			} while (flag == 0);


			break;


		case '2':
			switch (symmetric(root->left, root->right))
			{
			case 0:
				printf("The tree is symmetric.\n");
				break;

			case 1:
				printf("The tree is asymmetric.\n");
				break;
			}

			system("PAUSE");

			break;


		case '3':
			flag = 0;

			printf("From witch branch do you want to find the maximum element:\n"
				"1. Left\n"
				"2. Right\n");
			do
			{
				switch (getch())
				{
				case '1':
					if (root->left != NULL)
						printf("The maximum element in the left branch is: %d\n", maximum(root->left, root->left->value));
					else printf("This branch is empty!\n");
					flag = 1;

					system("PAUSE");
					break;

				case '2':
					if (root->right != NULL)
						printf("The maximum element in the right branch is: %d\n", maximum(root->right, root->right->value));
					else printf("This branch is empty!\n");
					flag = 1;
					system("PAUSE");
					break;

				default:
					printf("Invalid choise\n");
				}

			} while (flag == 0);
			
			break;


		case '4':
			flag = 0;

			printf("From witch branch do you want to find the minimum element:\n"
				"1. Left\n"
				"2. Right\n");
			do
			{
				switch (getch())
				{
				case '1':
					if (root->left != NULL)
						printf("The minimum element in the left branch is: %d\n", minimum(root->left, root->left->value));
					else printf("This branch is empty!");
					flag = 1;
					system("PAUSE");
					break;

				case '2':
					if(root->right != NULL)
						printf("The maximum element in the right branch is: %d\n", minimum(root->right, root->right->value));
					else printf("This branch is empty!");
					flag = 1;
					system("PAUSE");
					break;

				default:
					printf("Invalid choise\n");
				}

			} while (flag == 0);

			break;


		default:
			system("CLS");
			printf("Unknown command\n\n");
			system("PAUSE");
			break;

		}

	}

}