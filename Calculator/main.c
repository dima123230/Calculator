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
#include <locale.h> // Для русских символов в visual studio


 //структура элементов очереди
typedef struct queueElem {
	long long int f; // Переменная для ответа факториала
	char* g; // Переменная для сообщения об ошибке или неправильном вводе
	char op, type; // Переменные для операций и типа операндов
	float  x, y, r, Size; // Переменные для данных и результата операций
	float* value1, * value2, * res; // Переменные для чисел и результата векторных операций
	struct queueElem* nextElem;
} queueElem;


// Для работы с очередью
typedef struct queue
{
	queueElem* head;
	queueElem* end;
} queue;


//функция для получения лемента из головы очереди
queueElem* getElem(queue* from_This_Queue)
{
	queueElem* ret = from_This_Queue->head;
	from_This_Queue->head = from_This_Queue->head->nextElem;
	return ret;
}

//функция для добавления нового элемента
void putElem(queue* to_This_Queue, queueElem* newItem)
{
	if (to_This_Queue->head == NULL) to_This_Queue->head = newItem;
	if (to_This_Queue->end != NULL) to_This_Queue->end->nextElem = newItem;
	to_This_Queue->end = newItem;
}


// Функция возводит число x в степень y
double degree(float x, float y)
{
	if (y == 0) return 1; // Условие, в котором число в нулевой степени будет = 1
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


// Функция принимает целое число и возвращает результат его факториала
long long int fact(int a)
{
	if (a == 0) return 1; // Создаем условие, в котором факториал нуля будет = 1
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


// Функция для векторного выражения
void CalcforVectors(char op, queueElem* t)
{
	// Проверка на целое число fSize = 1
	int wSize = t->Size;
	float fSize = t->Size / wSize;
	if (fSize != 1) t->g = "Число должно быть целым!";
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
		t->g = "Недопустимая операция!";
	}
}



// Функция для арифметического выражения
void Arithm(char op, queueElem* t)
{
	int wA = t->x;
	float fA = t->x / wA;

	int wB = t->y; // Проверка на целое число
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
		if (t->y == 0) t->g = "Делить на ноль нельзя!";
		else t->r = t->x / t->y;
		break;
	case '!':
		if ((fA != 1) || (t->x < 0)) t->g = "Под знаком факториала должно быть целое число!";
		else t->f = fact(t->x);
		break;
	case '^':
		if ((fB != 1) || (t->y < 0)) t->g = "Степень должна быть целым числом!";
		else t->r = degree(t->x, t->y);
		break;
	default:
		t->g = "Недопустимая операция!";
	}
}

// Функция для того, чтобы печатать массив чисел как сказано в задании ( используется в векторном выражении )
void ForPrintVect(float* vect, int size, FILE* output)
{
	fprintf(output, "(");
	for (int i = 0; i < (size - 1); i++) fprintf(output, "%g, ", vect[i]);
	fprintf(output, "%g)", vect[size - 1]);
	free(vect);
}


int main()
{
	setlocale(LC_ALL, "Russian"); // Для русских символов ( особенность Visual Studio ), также добавлена соответсвующая библиотека locale.h
	while (1) // Цикл для постоянного запуска
	{
		char choice, op, type; // Переменные для продолжения, операции и типа операндов
		char nameinput[255]; // Переменная для названия файла
		char nameoutput[255]; // Переменная для названия файла
		float Num; // Переменная для числа
		printf("Введите имя входного файла: ");
		scanf("%s", &nameinput);
		printf("Введите имя выходного файла: ");
		scanf("%s", &nameoutput);

		// Очередь для входных данных
		queue* tasks = calloc(1, sizeof(queue));
		FILE* input = fopen(nameinput, "r");

		while (fscanf(input, " %c %c %f", &op, &type, &Num) != EOF) // Построчное чтение файла
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
			else fgets(nameinput, 100, input); // Удаление оставшейся строки
			putElem(tasks, newT);
		}
		fclose(input); // Закрытие файла после чтения

		queue* rData = calloc(1, sizeof(queue)); //очередь на печать
		while (tasks->head != NULL) // Пока не будет конец списка
		{
			queueElem* cT = tasks->head; //берём из очереди элемент для последующей обработки
			if (tasks->head->type == 'v') CalcforVectors(cT->op, cT);
			else if (tasks->head->type == 's') Arithm(cT->op, cT);
			else
			{
				cT->g = "Неизвестный тип данных!";
			}
			putElem(rData, cT); // переностка элемента в очередь
			getElem(tasks);
		}
		free(tasks);

		FILE* output = fopen(nameoutput, "w");
		while (rData->head != NULL) // Пока не будет конец списка
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
		fclose(output); // закрытие файла
		printf("Хотите продолжить? (y/n) \n"); // Желает ли пользователь продолжить
		scanf(" %c", &choice);
		if (choice == 'n') break;
		free(tasks); // Освобождение памяти
	}
	return 0;
}
