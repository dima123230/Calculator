/*
 ============================================================================
 Name        : Calculator.c
 Author      : Dmitriy Nevedrov
 Version     :
 Copyright   : Your copyright notice
 Description : Calculator with 6 operations with real numbers: (+),(-),(*),(/),(^),(!)
 ============================================================================
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)

{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	puts("Welcome to calculator!"); // ���������� � ������������ � ��� ��� ��������� ��������.
	puts("all possible operations on this calculator are provided here:");
	puts("1. + (adds the first number to the second)");
	puts("2. - (subtracts the second number from the first)");
	puts("3. * (multiplies the first number by the second)");
	puts("4. / (divides the first number by the second");
	puts("5. ^ (raises the first number to the power of the second)");
	puts("6. ! (Finds the factorial of a number)");

	long int f, g;    // ���������� ����� ����� ��� �������� "���������� � ������� ^".
	long long int j, res = 1;  // ���������� ����� ����� ��� �������� "��������� ����� !".
	double a, b;      // ���������� ������������ ����� ��� ��������: "����, �����, ������� � ���������".
	char c, r;       // ���������� ��� ��������, ������ ��� ������ ��������, ������ ��� ���������� ������ ������������.
	do  // ���� ���� ������������ ������� ���������� ������ � ����������
	{
		printf("Enter one of the provided operations: (+),(-),(*),(/),(^),(!): ");
		scanf(" %c", &c); // ����� ����� �� ��������.
		switch (c)
		{
		case '+': // �������� �������� ���� �����.
			printf("Enter the first number:");
			scanf("%lf", &a);
			printf("Enter the second number:");
			scanf("%lf", &b);
			printf("%lf+%lf=%lf\n", a, b, a + b); // ����� ���������� ��������.
			break;
		case '-': // �������� ���������.
			printf("Enter the first number:");
			scanf("%lf", &a);
			printf("Enter the second number:");
			scanf("%lf", &b);
			printf("%lf-%lf=%lf\n", a, b, a - b); // ����� ���������� ���������.
			break;
		case '*': // �������� ���������.
			printf("Enter the first number:");
			scanf("%lf", &a);
			printf("Enter the second number:");
			scanf("%lf", &b);
			printf("%lf*%lf=%lf\n", a, b, a * b); // ����� ���������� ���������.
			break;
		case '/': // �������� �������.
			printf("Enter the first number:");
			scanf("%lf", &a);
			printf("Enter the second number:");
			scanf("%lf", &b);
			printf("%lf/%lf=%lf\n", a, b, a / b); // ����� ���������� �������.
			break;
		case '^': // �������� ���������� ������ ����� � �������.
			printf("Enter the first number:");
			scanf("%li", &f);
			printf("Enter the second number:");
			scanf("%li", &g);
			long int d = 1;
			for (int i = 0; i < g; i++)
			{
				d = d * f;
			}
			printf("%li^%li=%li\n", f, g, d); // ����� ���������� ���������� � ������� �����.
			break;
		case '!': // �������� ���������� ���������� ������ �����.
			printf("Enter the number:");
			scanf("%llu", &j);
			for (int i = 1; i <= j; i++)
			{
				res = res * i;
			}
			if (j == 0) printf("%lli!=1\n", j); // �������, ���� ��������� ����� 0.
			else if (j < 0)   // ������� ���� ������������ �������� ����� ��������� �������������� �����.
			{
				printf("the factorial exists only for positive numbers\n");
			}
			else printf("%lli!=%lli\n", j, res); // ����� ���������� ���������� �����.
			break;
		default:
			printf("unknown operation\n"); // ����� "����������� ��������", ���� ������������ ���� ������������ ��������
		}
		printf("do you want to repeat one of the operations? (y/n):");
		scanf(" %c", &r);  // ������ �� ������������ ��������� ����� �� ��������
	} while (r == 'y');
	return 0;
}