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
#include <locale.h> // ��� ������� �������� � visual studio


 //��������� ��������� �������
typedef struct queueElem {
	long long int f; // ���������� ��� ������ ����������
	char* g; // ���������� ��� ��������� �� ������ ��� ������������ �����
	char op, type; // ���������� ��� �������� � ���� ���������
	float  x, y, r, Size; // ���������� ��� ������ � ���������� ��������
	float* value1, * value2, * res; // ���������� ��� ����� � ���������� ��������� ��������
	struct queueElem* nextElem;
} queueElem;


// ��� ������ � ��������
typedef struct queue
{
	queueElem* head;
	queueElem* end;
} queue;


//������� ��� ��������� ������� �� ������ �������
queueElem* getElem(queue* from_This_Queue)
{
	queueElem* ret = from_This_Queue->head;
	from_This_Queue->head = from_This_Queue->head->nextElem;
	return ret;
}

//������� ��� ���������� ������ ��������
void putElem(queue* to_This_Queue, queueElem* newItem)
{
	if (to_This_Queue->head == NULL) to_This_Queue->head = newItem;
	if (to_This_Queue->end != NULL) to_This_Queue->end->nextElem = newItem;
	to_This_Queue->end = newItem;
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


// ������� ��� ���������� ���������
void CalcforVectors(char op, queueElem* t)
{
	// �������� �� ����� ����� fSize = 1
	int wSize = t->Size;
	float fSize = t->Size / wSize;
	if (fSize != 1) t->g = "����� ������ ���� �����!";
	int vSize = t->Size;
	t->res = calloc(vSize, sizeof(float));
	switch (op)
	{
	case '+':
		for (int i = 0; i < vSize; i++) t->res[i] = t->value1[i] + t->value2[i];
		break;
	case '-':
		for (int i = 0; i < vSize; i++) t->res[i] = t->value1[i] - t->value2[i];
		break;
	case '^':
		t->r = 0;
		for (int i = 0; i < vSize; i++) t->r += t->value1[i] * t->value2[i];
		break;
	default:
		t->g = "������������ ��������!";
	}
}



// ������� ��� ��������������� ���������
void Arithm(char op, queueElem* t)
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

// ������� ��� ����, ����� �������� ������ ����� ��� ������� � ������� ( ������������ � ��������� ��������� )
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

		// ������� ��� ������� ������
		queue* tasks = calloc(1, sizeof(queue));
		FILE* input = fopen(nameinput, "r");

		while (fscanf(input, " %c %c %f", &op, &type, &Num) != EOF) // ���������� ������ �����
		{
			queueElem* newT = calloc(1, sizeof(queueElem));
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
			putElem(tasks, newT);
		}
		fclose(input); // �������� ����� ����� ������

		queue* rData = calloc(1, sizeof(queue)); //������� �� ������
		while (tasks->head != NULL) // ���� �� ����� ����� ������
		{
			queueElem* cT = tasks->head; //���� �� ������� ������� ��� ����������� ���������
			if (tasks->head->type == 'v') CalcforVectors(cT->op, cT);
			else if (tasks->head->type == 's') Arithm(cT->op, cT);
			else
			{
				cT->g = "����������� ��� ������!";
			}
			putElem(rData, cT); // ���������� �������� � �������
			getElem(tasks);
		}
		free(tasks);

		FILE* output = fopen(nameoutput, "w");
		while (rData->head != NULL) // ���� �� ����� ����� ������
		{
			queueElem* T = rData->head;
			if (T->g != NULL)
			{
				fprintf(output, "%s\n", T->g);
				getElem(rData);
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
			getElem(rData);
		}
		fclose(output); // �������� �����
		printf("������ ����������? (y/n) \n"); // ������ �� ������������ ����������
		scanf(" %c", &choice);
		if (choice == 'n') break;
		free(tasks); // ������������ ������
	}
	return 0;
}
