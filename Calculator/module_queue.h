#ifndef module_queue
#define module_queue

//��������� ��������� �������
typedef struct queueElem {
	long long int f; // ���������� ��� ������ ����������
	char* g; // ���������� ��� ��������� �� ������ ��� ������������ �����
	char op, type; // ���������� ��� �������� � ���� ���������
	float  a, b, r, Size; // ���������� ��� ������ � ���������� ��������
	float* value1, * value2, * res; // ���������� ��� ����� � ���������� ��������� ��������
	struct queueElem* nextElem;
} queueElem;


// ��� ������ � ��������
typedef struct queue
{
	queueElem* head;
	queueElem* end;
} queue;


void putElem(queue* to_This_Queue, queueElem* newItem);

queueElem* getElem(queue* from_This_Queue);

void delElemQueue(queueElem *del);

#endif
