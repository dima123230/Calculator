#ifndef module_queue
#define module_queue

//структура элементов очереди
typedef struct queueElem {
	long long int f; // Переменная для ответа факториала
	char* g; // Переменная для сообщения об ошибке или неправильном вводе
	char op, type; // Переменные для операций и типа операндов
	float  a, b, r, Size; // Переменные для данных и результата операций
	float* value1, * value2, * res; // Переменные для чисел и результата векторных операций
	struct queueElem* nextElem;
} queueElem;


// Для работы с очередью
typedef struct queue
{
	queueElem* head;
	queueElem* end;
} queue;


void putElem(queue* to_This_Queue, queueElem* newItem);

queueElem* getElem(queue* from_This_Queue);

void delElemQueue(queueElem *del);

#endif
