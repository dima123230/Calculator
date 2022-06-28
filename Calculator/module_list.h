#ifndef module_list
#define module_list

//структура элементов списка
typedef struct listElem {
	long long int f; // Переменная для ответа факториала
	char* g; // Переменная для сообщения об ошибке или неправильном вводе
	char op, type; // Переменные для операций и типа операндов
	float  x, y, r, Size; // Переменные для данных и результата операций
	float* value1, * value2, * res; // Переменные для чисел и результата векторных операций
	struct listElem* nextElem;
} lElem;

// Для работы со списком
typedef struct list
{
	lElem* head;
	lElem* current;
} list;

int Applist(list* to_This_List, lElem* newElem);

lElem* nextElem(list* in_This_List);

int To_Head_Elem(list* inThisList);

int deleteElem(list* in_This_List);

#endif
