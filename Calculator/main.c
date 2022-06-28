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
#include <locale.h>
#include "module_list.h"

// ������� ��������� ����� ����� � ���������� ��������� ��� ����������
long long int fact(int a)
{
	if (a == 0) return 1; // ������� �������, � ������� ��������� ���� ����� = 1
	else
	{
		long long int fact = 1;
		for (int i = 1; i <= a; i++)
		{
			fact *= i;
		}
		return fact;
	}
}


// ������� �������� ����� x � ������� y
double degree(float x, float y)
{
	if (y == 0) return 1; // �������, � ������� ����� � ������� ������� ����� = 1
	else
	{
		float deg = x;
		for (int i = 1; i < y; i++)
		{
			deg *= x;
		}
		return deg;
	}
}


// ������� ��� ���������� ���������
void CalcforVectors(char op, lElem* t)
{
	// �������� �� ����� ����� fSize = 1
	int wSize = t->Size;
	float fSize = t->Size / wSize;
	if (fSize != 1) t->g = "����� ������ ���� �����!";

	int vectorSize = t->Size;

	t->res = calloc(vectorSize, sizeof(float));
	switch (op)
	{
	case '+':
		for (int i = 0; i < vectorSize; i++) t->res[i] = t->value1[i] + t->value2[i];
		break;
	case '-':
		for (int i = 0; i < vectorSize; i++) t->res[i] = t->value1[i] - t->value2[i];
		break;
	case '^':
		t->r = 0;
		for (int i = 0; i < vectorSize; i++) t->r += t->value1[i] * t->value2[i];
		break;
	default:
		t->g = "������������ ��������!";
	}
}



// ������� ��� ��������������� ���������
void Arithm(char op, lElem* t)
{
	int wA = t->x;
	float fA = t->x / wA;

	int wB = t->y; // �������� �� ����� �����
	float fB = t->y / wB;

	switch (op)
	{
	case '+':
		t->r = t->x + t->y;
		break;
	case '-':
		t->r = t->x - t->y;
		break;
	case '*':
		t->r = t->x * t->y;
		break;
	case '/':
		if (t->y == 0) t->g = "������ �� ���� ������!";
		else t->r = t->x / t->y;
		break;
	case '!':
		if ((fA != 1) || (t->x < 0)) t->g = "��� ������ ���������� ������ ���� ����� �����!";
		else t->f = fact(t->x);
		break;
	case '^':
		if ((fB != 1) || (t->y < 0)) t->g = "������� ������ ���� ����� ������!";
		else t->r = degree(t->x, t->y);
		break;
	default:
		t->g = "������������ ��������!";
	}
}

// ������� ��� ����, ����� �������� ������ ����� ��� ������� � �������
void ForPrintVect(float* vect, int size, FILE* output)
{
	fprintf(output, "(");
	for (int i = 0; i < (size - 1); i++) fprintf(output, "%g, ", vect[i]);
	fprintf(output, "%g)", vect[size - 1]);
	free(vect);
}


int main()
{
	setlocale(LC_ALL, "Russian"); // ��� ������� �������� ( ����������� Visual Studio ), ����� ��������� �������������� ���������� locale.h
	while (1) // ���� ��� ����������� �������
	{
		char choice, op, type; // ���������� ��� �����������, �������� � ���� ���������
		char nameinput[255]; // ���������� ��� �������� �����
		char nameoutput[255]; // ���������� ��� �������� �����
		float Num; // ���������� ��� �����
		printf("������� ��� �������� �����: ");
		scanf("%s", &nameinput);
		printf("������� ��� ��������� �����: ");
		scanf("%s", &nameoutput);

		// ������ ��� ������� ������
		list* tasks = calloc(1, sizeof(list));
		FILE* input = fopen(nameinput, "r");

		while (fscanf(input, " %c %c %f", &op, &type, &Num) != EOF) // ���������� ������ �����
		{
			lElem* newT = calloc(1, sizeof(lElem));
			newT->op = op;
			newT->type = type;
			newT->g = NULL;
			if (type == 'v')
			{
				newT->Size = Num;
				newT->value1 = malloc(Num * sizeof(float));
				newT->value2 = malloc(Num * sizeof(float));
				for (int i = 0; i < Num; i++) fscanf(input, "%f", &newT->value1[i]);
				for (int i = 0; i < Num; i++) fscanf(input, "%f", &newT->value2[i]);
			}
			else if (type == 's')
			{
				newT->x = Num;
				if (op != '!') fscanf(input, "%f", &newT->y);
			}
			else fgets(nameinput, 100, input); // �������� ���������� ������
			Applist(tasks, newT);
		}
		fclose(input); // �������� ����� ����� ������

		To_Head_Elem(tasks);

		while (tasks->current != NULL) // ���� �� ����� ����� ������
		{
			if (tasks->current->type == 'v') CalcforVectors(tasks->current->op, tasks->current);
			else if (tasks->current->type == 's') Arithm(tasks->current->op, tasks->current);
			else
			{
				tasks->current->g = "����������� ��� ������!";
			}
			nextElem(tasks);
		}

		To_Head_Elem(tasks);

		FILE* output = fopen(nameoutput, "w");

		while (tasks->current != NULL) // ���� �� ����� ����� ������
		{
			lElem* T = tasks->current;
			if (T->g != NULL)
			{
				fprintf(output, "%s\n", T->g);
				deleteElem(tasks);
				continue;
			}

			if (T->type == 's')
			{
				if (T->op != '!') fprintf(output, "%g %c %g = %g", T->x, T->op, T->y, T->r);
				else fprintf(output, "%g! = %lli", T->x, T->f);
			}
			else if (T->type == 'v')
			{
				ForPrintVect(T->value1, T->Size, output);
				fprintf(output, " %c ", T->op);
				ForPrintVect(T->value2, T->Size, output);
				fprintf(output, " = ");
				if (T->op != '^') ForPrintVect(T->res, T->Size, output);
				else fprintf(output, "%g", T->r);
			}
			fprintf(output, "\n");
			deleteElem(tasks);
		}
		fclose(output); // �������� �����
		free(tasks); // ������������ ������
		printf("������ ����������? (y/n) \n"); // ������ �� ������������ ����������
		scanf(" %c", &choice);
		if (choice == 'n') break;
	}
	return 0;
}
