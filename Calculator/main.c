/*
 ============================================================================
 Name        : Calculator.c
 Author      : Dmitriy Nevedrov
 Version     :
 Copyright   : Your copyright notice
 Description : Calculator with 6 operations with real numbers: (+),(-),(*),(/),(^),(!)
			   and 3 operations with vectors (+),(-),(*). Calculator with stack.
 ============================================================================
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Для русских символов в visual studio
#include "module_queue.h"
#include "module_stack.h"


//Возводит а в степень b
double degree(float a, float b)
{
	if (b == 0) return 1; // Создаем условие в котором число в нулевой степени будет = 1
	else
	{
		float deg = a;
		for (int i = 1; i < b; i++)
		{
			deg *= a;
		}
		return deg;
	}
}

// Функция принимает целое число и возвращает его факториал
long long int fact(int a)
{
	if (a == 0) return 1; // Создаем условие в котором факториал нуля = 1
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


// Функция для обработки векторного выражения
void CalcForVectors(char op, queueElem* task)
{
	// Проверка на целостность числа
	int wSize = task->Size;
	float fSize = task->Size / wSize;
	if (fSize != 1) task->g = "Число должно быть целым!";

	int vectorSize = task->Size;

	task->res = calloc(vectorSize, sizeof(float));
	switch (op)
	{
	case '+':
		for (int i = 0; i < vectorSize; i++) task->res[i] = task->value1[i] + task->value2[i];
		break;
	case '-':
		for (int i = 0; i < vectorSize; i++) task->res[i] = task->value1[i] - task->value2[i];
		break;
	case '^':
		task->r = 0;
		for (int i = 0; i < vectorSize; i++) task->r += task->value1[i] * task->value2[i];
		break;
	default:
		task->g = "Недопустимая операция!";
	}
}


// Функция для обработки арифметического выражения
void Arithm(char op, queueElem* task)
{
	int wA = task->a;
	float fA = task->a / wA;
	int wB = task->b;
	float fB = task->b / wB;

	switch (op)
	{
	case '+':
		task->r = task->a + task->b;
		break;
	case '-':
		task->r = task->a - task->b;
		break;
	case '*':
		task->r = task->a * task->b;
		break;
	case '/':
		if (task->b == 0) task->g = "Делить на ноль нельзя!";
		else task->r = task->a / task->b;
		break;
	case '!':
		if ((fA != 1) || (task->a < 0)) task->g = "Под знаком факториала должно стоять целое число|!";
		else task->f = fact(task->a);
		break;
	case '^':
		if ((fB != 1) || (task->b < 0)) task->g = "Степень должна быть целым числом!";
		else task->r = degree(task->a, task->b);
		break;
	default:
		task->g = "Недопустимая операция!";
	}
}

// Функция для обработки в обратной польской нотации
void pNotation(char* str, queueElem* o)
{
	stack* stk = calloc(1, sizeof(stack));
	o->g = str;
	int pCharIsNum = 0;

	for (int i = 0; str[i] != '\0'; i++) // Пока не будет конец строки
	{
		float aC = str[i];
		if ((aC - 48 < 10) & (aC - 48 >= 0))
		{
			if (pCharIsNum > 0) stk->head->nD = stk->head->nD * 10 + (aC - 48);
			else if (pCharIsNum < 0)
			{
				stk->head->nD = stk->head->nD + (aC - 48) / (degree(10, pCharIsNum * (-1)));
				pCharIsNum -= 1;
			}
			else // Добавление нового числа в стек
			{
				stackElem* new = calloc(1, sizeof(stackElem));
				new->nD = aC - 48;
				pCharIsNum = 1;
				sPutElem(stk, new);
			}
		}
		else //если имеем дело с символом
		{
			stackElem* new = calloc(1, sizeof(stackElem));
			stackElem* a;
			stackElem* b;
			switch (str[i])
			{
			case '.':
				if (pCharIsNum > 0) pCharIsNum = -1;
				break;
			case '+':
				a = sGetElem(stk);
				b = sGetElem(stk);
				new->nD = sGetElem(stk)->nD + sGetElem(stk)->nD;
				sPutElem(stk, new);
				delElemStack(a);
				delElemStack(b);
				break;
			case '-':
				a = sGetElem(stk);
				b = sGetElem(stk);
				new->nD = (sGetElem(stk)->nD - sGetElem(stk)->nD) * (-1);
				sPutElem(stk, new);
				delElemStack(a);
				delElemStack(b);
				break;
			case '*':
				a = sGetElem(stk);
				b = sGetElem(stk);
				new->nD = sGetElem(stk)->nD * sGetElem(stk)->nD;
				sPutElem(stk, new);
				delElemStack(a);
				delElemStack(b);
				break;
			case '/':;
				a = sGetElem(stk);
				b = sGetElem(stk);
				float second = sGetElem(stk)->nD;
				new->nD = sGetElem(stk)->nD / second;
				sPutElem(stk, new);
				break;
			case '!':
				a = sGetElem(stk);
				new->nD = fact(sGetElem(stk)->nD);
				sPutElem(stk, new);
				delElemStack(a);
				break;
			case '^':;
				float dSecond = sGetElem(stk)->nD;
				new->nD = degree(sGetElem(stk)->nD, dSecond);
				sPutElem(stk, new);
				break;
			default:
				pCharIsNum = 0;
			}
		}
	}
	o->r = stk->head->nD; //результат работы записываем в очередь на вывод
	if (stk != NULL) free(stk);
}


// Функция для печати массива по правилам задания
void pVect(float* vector, int size, FILE* output)
{
	fprintf(output, "(");
	for (int i = 0; i < (size - 1); i++) fprintf(output, "%g, ", vector[i]);
	fprintf(output, "%g)", vector[size - 1]);
	free(vector);
}


int main()
{
	setlocale(LC_ALL, "Russian"); // для русских символов ( особенность Visual Studio )

	while (1) // Постоянный ввод выражения
	{
		char choice, op, type;
		char nameinput[255];
		char nameoutput[255];
		float Num;

		printf("Выберите режим работы (p - префиксная нотация, r - обратная польская нотация): ");
		scanf(" %c", &choice);
		printf("Введите имя входного файла: ");
		scanf("%s", &nameinput);
		printf("Введите имя выходного файла: ");
		scanf("%s", &nameoutput);

		//создаём очередь, который будет хранить входные данные для подсчёта
		queue* tasks = calloc(1, sizeof(queue));
		FILE* input = fopen(nameinput, "r");

		while (feof(input) == 0) //пока не достигнем конца
		{
			queueElem* newT = calloc(1, sizeof(queueElem));
			if (choice == 'p')
			{
				fscanf(input, " %c %c %f", &op, &type, &Num);
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
					newT->a = Num;
					if (op != '!') fscanf(input, "%f", &newT->b);
				}
				else fgets(nameinput, 100, input); // убираем ненужную строку
			}
			else if (choice == 'r')
			{
				newT->g = calloc(255, sizeof(char));
				fgets(newT->g, 255, input);
			}
			putElem(tasks, newT);
		}
		fclose(input); // закрытие файла после чтения

		queue* rD = calloc(1, sizeof(queue)); //очередь на печать
		while (tasks->head != NULL) //пока не достигнем конца списка
		{
			queueElem* T = tasks->head;
			if (choice == 'p')
			{
				if (tasks->head->type == 'v') CalcForVectors(T->op, T);
				else if (tasks->head->type == 's') Arithm(T->op, T);
				else
				{
					T->g = "Неизвестный тип данных!";
				}
			}
			else if (choice == 'r')
			{
				pNotation(T->g, T);
			}
			putElem(rD, T); //после обработки переносим элемент в очередь на печать
			delElemQueue(getElem(tasks));
		}
		if (tasks != NULL) free(tasks); // Освобождение


		FILE* output = fopen(nameoutput, "w");

		while (rD->head != NULL) // пока не будет конец очереди
		{
			queueElem* cT = rD->head;
			if (choice == 'p')
			{
				if (cT->g != NULL)
				{
					fprintf(output, "%s\n", cT->g);
					delElemQueue(getElem(rD));
					continue;
				}

				if (cT->type == 's')
				{
					if (cT->op != '!') fprintf(output, "%g %c %g = %g", cT->a, cT->op, cT->b, cT->r);
					else fprintf(output, "%g! = %lli", cT->a, cT->f);
				}
				else if (cT->type == 'v')
				{
					pVect(cT->value1, cT->Size, output);
					fprintf(output, " %c ", cT->op);
					pVect(cT->value2, cT->Size, output);
					fprintf(output, " = ");
					if (cT->op != '^') pVect(cT->res, cT->Size, output);
					else fprintf(output, "%g", cT->r);
				}
				fprintf(output, "\n");
			}
			else if (choice == 'r')
			{
				for (int i = 0; ((rD->head->g[i] != '\n') & (rD->head->g[i] != '\0')); i++) fprintf(output, "%c", rD->head->g[i]);
				fprintf(output, "%g\n", rD->head->r);
			}
			delElemQueue(getElem(rD));
		}
		fclose(output);
		
		printf("Хотите продолжить? (y/n) \n"); // Предлагаем пользователю продолжить работу
		scanf(" %c", &choice);
		if (rD != NULL) free(rD);
		if (choice == 'n') break;
	}
	return 0;
}