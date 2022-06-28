#ifndef module_list
#define module_list

//��������� ��������� ������
typedef struct listElem {
	long long int f; // ���������� ��� ������ ����������
	char* g; // ���������� ��� ��������� �� ������ ��� ������������ �����
	char op, type; // ���������� ��� �������� � ���� ���������
	float  x, y, r, Size; // ���������� ��� ������ � ���������� ��������
	float* value1, * value2, * res; // ���������� ��� ����� � ���������� ��������� ��������
	struct listElem* nextElem;
} lElem;

// ��� ������ �� �������
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
