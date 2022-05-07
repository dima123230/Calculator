/*
 ============================================================================
 Name        : Calculator.c
 Author      : Dmitriy Nevedrov
 Version     :
 Copyright   : Your copyright notice
 Description : Calculator with 6 operations with real numbers: (+),(-),(*),(/),(^),(!)
			   and 3 operations with vectors (+),(-),(*).
 ============================================================================
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int main(void)

{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	puts("Welcome to calculator!"); // Информация о калькуляторе и про его возможные операции.
	puts("all possible operations on this calculator are provided here:");
	puts("1. + (adds the first number to the second)");
	puts("2. - (subtracts the second number from the first)");
	puts("3. * (multiplies the first number by the second)");
	puts("4. / (divides the first number by the second");
	puts("5. ^ (raises the first number to the power of the second)");
	puts("6. ! (Finds the factorial of a number)");
	puts("7. v (uses a code branch with vector operations: (+),(-),(*).)");

	long int f, g;    // Переменные целых чисел для операции "возведение в степень ^".
	long long int j, res = 1;  // Переменные целых чисел для операции "факториал числа !".
	double a, b;      // Переменные вещественных чисел для операций: "плюс, минус, деление и умножение".
	double* A, * B;  // Переменные для операций с векторами.
	double resv;
	char c, r;       // Переменные для символов, первая для выбора операции, вторая для повторения работы калькулятора.
	char op;         // Операция с векторами.
	int size;
	do  // Цикл если пользователь захочет продолжить работу с программой
	{
		printf("Enter one of the provided operations: (+),(-),(*),(/),(^),(!) (v): ");
		scanf(" %c", &c); // Выбор одной из операций.
		switch (c)
		{
		case 'v': // Операции с векторами.
			printf("Enter the size of the vectors: ");
			scanf("%i", &size);
			A = malloc(size * sizeof(int));
			B = malloc(size * sizeof(int));
			printf("Enter the coordinates of the first vector: ");
			for (int i = 0; i < size; i++) scanf("%lf", &A[i]);
			printf("Enter the coordinates of the second vector: ");
			for (int i = 0; i < size; i++) scanf("%lf", &B[i]);
			printf("Enter one of the provided operations for vectors: (+),(-),(*): ");
			scanf(" %c", &op);
			switch (op)
			{
			case '+': // Операция сложения с векторами.
				printf("Addition of vectors: ");
				for (int i = 0; i < size; i++) printf("%lf ", A[i] + B[i]);
				printf("\n");
				break;
			case '-': // Операция вычитания с векторами.
				printf("Вычитание векторов: ");
				for (int i = 0; i < size; i++) printf("%lf ", A[i] - B[i]);
				printf("\n");
				break;
			case '*': // Операция скалярного произведения с векторами.
				printf("Скалярное произведение векторов: ");
				for (int i = 0; i < size; i++) printf("%lf ", A[i] * B[i]);
				printf("\n");
				break;
			default: // В случае неверной выбранной операции.
				printf("Неправильно выбрана операция!");
			}
			free(A); // Освобождение использованной памяти.
			free(B);
			break;
		case '+': // Операция сложения двух чисел.
			printf("Enter the first number:");
			scanf("%lf", &a);
			printf("Enter the second number:");
			scanf("%lf", &b);
			printf("%lf+%lf=%lf\n", a, b, a + b); // Вывод результата сложения.
			break;
		case '-': // Операция вычитания.
			printf("Enter the first number:");
			scanf("%lf", &a);
			printf("Enter the second number:");
			scanf("%lf", &b);
			printf("%lf-%lf=%lf\n", a, b, a - b); // Вывод результата вычитания.
			break;
		case '*': // Операция умножения.
			printf("Enter the first number:");
			scanf("%lf", &a);
			printf("Enter the second number:");
			scanf("%lf", &b);
			printf("%lf*%lf=%lf\n", a, b, a * b); // Вывод результата умножения.
			break;
		case '/': // Операция деления.
			printf("Enter the first number:");
			scanf("%lf", &a);
			printf("Enter the second number:");
			scanf("%lf", &b);
			printf("%lf/%lf=%lf\n", a, b, a / b); // Вывод результата деления.
			break;
		case '^': // Операция возведения целого числа в степень.
			printf("Enter the first number:");
			scanf("%li", &f);
			printf("Enter the second number:");
			scanf("%li", &g);
			long int d = 1;
			for (int i = 0; i < g; i++)
			{
				d = d * f;
			}
			printf("%li^%li=%li\n", f, g, d); // Вывод результата возведения в степень числа.
			break;
		case '!': // Операция нахождения факториала целого числа.
			printf("Enter the number:");
			scanf("%llu", &j);
			for (int i = 1; i <= j; i++)
			{
				res = res * i;
			}
			if (j == 0) printf("%lli!=1\n", j); // Условие, если факториал равен 0.
			else if (j < 0)   // Условие если пользователь пытается найти факториал отрицательного числа.
			{
				printf("the factorial exists only for positive numbers\n");
			}
			else printf("%lli!=%lli\n", j, res); // Вывод результата факториала числа.
			break;
		default:
			printf("unknown operation\n"); // Вывод "неизвестная операция", если пользователь ввел недопустимую операцию
		}
		printf("do you want to repeat one of the operations? (y/n):");
		scanf(" %c", &r);  // Желает ли пользователь повторить любую из операций
	} while (r == 'y');
	return 0;
}