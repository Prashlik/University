#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");

	int data, code, cent, num = 0;
 // Для нахождения числа, на которое выпадает День Учителя, воспользуемся формулой:
 // День недели = (число(data) + код месяца(для октября равен 1) + код года(code)) % 7 - 1
	                                                                       
	do
	{
		printf("Bведите номер года (целое положительное число):\n");
		scanf_s("%d", &num);
		rewind(stdin);
	} while (!(num > 0));



	switch ( ( (num + 1) / 100) % 4 )   //Определим код столетия
	{
	case 0: cent = 6; break;
	case 1: cent = 4; break;
	case 2: cent = 2; break;
	case 3: cent = 0; break;
	}

	code = (cent + num % 100 + (num % 100) / 4) % 7;   //Kод года
	data = 7 - 1 + 1 - code;   //Вычислим дату первого воскресенья октября года num

	printf("День учителя в %d году выпал бы на %d октября.", num, data );
	printf("\n");
	return 0;
}