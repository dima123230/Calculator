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

	puts("Welcome to calculator!"); // ���������� � ������������ � ��� ��� ��������� ��������.
	puts("all possible operations on this calculator are provided here:");
	puts("1. + (adds the first number to the second)");
	puts("2. - (subtracts the second number from the first)");
	puts("3. * (multiplies the first number by the second)");
	puts("4. / (divides the first number by the second)");
	puts("5. ^ (raises the first number to the power of the second)");
	puts("6. ! (Finds the factorial of a number)");
	puts("7. v (uses a code branch with vector operations: (+),(-),(*).)");

	long int f, g;    // ���������� ����� ����� ��� �������� "���������� � ������� ^".
	long long int j, res = 1;  // ���������� ����� ����� ��� �������� "��������� ����� !".
	double a, b;      // ���������� ������������ ����� ��� ��������: "����, �����, ������� � ���������".
	double* A, * B, *C;  // ���������� ��� �������� � ���������.
	char c, r;       // ���������� ��� ��������, ������ ��� ������ ��������, ������ ��� ���������� ������ ������������.
	char op;         // �������� � ���������.
	int size;        // ��� ������� ��������.
	FILE* input, * output; // ��� �����-������ �� ������.
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	do  // ���� ���� ������������ ������� ���������� ������ � ����������.
	{
		fscanf(input," %c", &c); // ����� ����� �� ��������.
		switch (c)
		{
		case 'v': // �������� � ���������.
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
			case '+': // �������� �������� � ���������.
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
			case '-': // �������� ��������� � ���������.
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
			case '*': // �������� ���������� ������������ � ���������.
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
			default: // � ������ �������� ��������� ��������.
				fprintf(output,"unknown operation!\n");
			}
			break;
			free(A); // ������������ �������������� ������.
			free(B);
			free(C);
		case '+': // �������� �������� ���� �����.
			fscanf(input,"%lf", &a);
			fscanf(input,"%lf", &b);
			fprintf(output,"%lf+%lf=%lf\n", a, b, a + b); // ����� ���������� ��������.
			break;
		case '-': // �������� ���������.
			fscanf(input,"%lf", &a);
			fscanf(input,"%lf", &b);
			fprintf(output,"%lf-%lf=%lf\n", a, b, a - b); // ����� ���������� ���������.
			break;
		case '*': // �������� ���������.
			fscanf(input,"%lf", &a);
			fscanf(input,"%lf", &b);
			fprintf(output,"%lf*%lf=%lf\n", a, b, a * b); // ����� ���������� ���������.
			break;
		case '/': // �������� �������.
			fscanf(input,"%lf", &a);
			fscanf(input,"%lf", &b);
			fprintf(output,"%lf/%lf=%lf\n", a, b, a / b); // ����� ���������� �������.
			break;
		case '^': // �������� ���������� ������ ����� � �������.
			fscanf(input,"%li", &f);
			fscanf(input,"%li", &g);
			long int d = 1;
			for (int i = 0; i < g; i++)
			{
				d = d * f;
			}
			fprintf(output,"%li^%li=%li\n", f, g, d); // ����� ���������� ���������� � ������� �����.
			break;
		case '!': // �������� ���������� ���������� ������ �����.
			fscanf(input,"%llu", &j);
			for (int i = 1; i <= j; i++)
			{
				res = res * i;
			}
			if (j == 0) fprintf(output,"%lli!=1\n", j); // �������, ���� ��������� ����� 0.
			else if (j < 0)   // ������� ���� ������������ �������� ����� ��������� �������������� �����.
			{
				fprintf(output,"the factorial exists only for positive numbers\n");
			}
			else fprintf(output,"%lli!=%lli\n", j, res); // ����� ���������� ���������� �����.
			break;
		default:
			fprintf(output,"unknown operation\n"); // ����� "����������� ��������", ���� ������������ ���� ������������ ��������
		}
		fprintf(output,"do you want to repeat one of the operations? (y/n):\n");
		fscanf(input," %c", &r);  // ������ �� ������������ ��������� ����� �� ��������
	} while (r == 'y');
	fclose(input);
	fclose(output);
	return 0;
}