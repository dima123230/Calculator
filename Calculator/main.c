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
	puts("4. / (divides the first number by the second)");
	puts("5. ^ (raises the first number to the power of the second)");
	puts("6. ! (Finds the factorial of a number)");
	puts("7. v (uses a code branch with vector operations: (+),(-),(*).)");

	long int f, g;    // Переменные целых чисел для операции "возведение в степень ^".
	long long int j, res = 1;  // Переменные целых чисел для операции "факториал числа !".
	double a, b;      // Переменные вещественных чисел для операций: "плюс, минус, деление и умножение".
	double* A, * B, *C;  // Переменные для операций с векторами.
	char c, r;       // Переменные для символов, первая для выбора операции, вторая для повторения работы калькулятора.
	char op;         // Операция с векторами.
	int size;        // Для размера векторов.
	FILE* input, * output; // для ввода-вывода из файлов.
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	do  // Цикл если пользователь захочет продолжить работу с программой.
	{
		fscanf(input," %c", &c); // Выбор одной из операций.
		switch (c)
		{
		case 'v': // Операции с векторами.
			fscanf(input,"%i", &size);
			A = malloc(size * sizeof(int));
			B = malloc(size * sizeof(int));
			C = malloc(size * sizeof(int));
			for (int i = 0; i < size; i++) fscanf(input,"%lf", &A[i]);
			for (int i = 0; i < size; i++) fscanf(input,"%lf", &B[i]);
			for (int i = 0; i < size; i++) C[i] = A[i] + B[i];
			fscanf(input," %c", &op);
			switch (op)
			{
			case '+': // Операция сложения с векторами.
				fprintf(output,"Addition of vectors: ");
				fprintf(output, "( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", A[i]);
				fprintf(output, ") ");
				fprintf(output, "+ ( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", B[i]);
				fprintf(output, ")");
				fprintf(output, " = ");
				fprintf(output, "( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", A[i] + B[i]);
				fprintf(output, ")");
				fprintf(output,"\n");
				break;
			case '-': // Операция вычитания с векторами.
				fprintf(output,"Subtracting vectors: ");
				fprintf(output, "( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", A[i]);
				fprintf(output, ") ");
				fprintf(output, "- ( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", B[i]);
				fprintf(output, ")");
				fprintf(output, " = ");
				fprintf(output, "( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", A[i] - B[i]);
				fprintf(output, ")");
				fprintf(output, "\n");
				break;
			case '*': // Операция скалярного произведения с векторами.
				fprintf(output,"Scalar product of vectors: ");
				fprintf(output, "( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", A[i]);
				fprintf(output, ") ");
				fprintf(output, "* ( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", B[i]);
				fprintf(output, ")");
				fprintf(output, " = ");
				fprintf(output, "( ");
				for (int i = 0; i < size; i++) fprintf(output, "%lf ", A[i] * B[i]);
				fprintf(output, ")");
				fprintf(output, "\n");
				break;
			default: // В случае неверной выбранной операции.
				fprintf(output,"unknown operation!\n");
			}
			break;
			free(A); // Освобождение использованной памяти.
			free(B);
			free(C);
		case '+': // Операция сложения двух чисел.
			fscanf(input,"%lf", &a);
			fscanf(input,"%lf", &b);
			fprintf(output,"%lf+%lf=%lf\n", a, b, a + b); // Вывод результата сложения.
			break;
		case '-': // Операция вычитания.
			fscanf(input,"%lf", &a);
			fscanf(input,"%lf", &b);
			fprintf(output,"%lf-%lf=%lf\n", a, b, a - b); // Вывод результата вычитания.
			break;
		case '*': // Операция умножения.
			fscanf(input,"%lf", &a);
			fscanf(input,"%lf", &b);
			fprintf(output,"%lf*%lf=%lf\n", a, b, a * b); // Вывод результата умножения.
			break;
		case '/': // Операция деления.
			fscanf(input,"%lf", &a);
			fscanf(input,"%lf", &b);
			fprintf(output,"%lf/%lf=%lf\n", a, b, a / b); // Вывод результата деления.
			break;
		case '^': // Операция возведения целого числа в степень.
			fscanf(input,"%li", &f);
			fscanf(input,"%li", &g);
			long int d = 1;
			for (int i = 0; i < g; i++)
			{
				d = d * f;
			}
			fprintf(output,"%li^%li=%li\n", f, g, d); // Вывод результата возведения в степень числа.
			break;
		case '!': // Операция нахождения факториала целого числа.
			fscanf(input,"%llu", &j);
			for (int i = 1; i <= j; i++)
			{
				res = res * i;
			}
			if (j == 0) fprintf(output,"%lli!=1\n", j); // Условие, если факториал равен 0.
			else if (j < 0)   // Условие если пользователь пытается найти факториал отрицательного числа.
			{
				fprintf(output,"the factorial exists only for positive numbers\n");
			}
			else fprintf(output,"%lli!=%lli\n", j, res); // Вывод результата факториала числа.
			break;
		default:
			fprintf(output,"unknown operation\n"); // Вывод "неизвестная операция", если пользователь ввел недопустимую операцию
		}
		fprintf(output,"do you want to repeat one of the operations? (y/n):\n");
		fscanf(input," %c", &r);  // Желает ли пользователь повторить любую из операций
	} while (r == 'y');
	fclose(input);
	fclose(output);
	return 0;
}