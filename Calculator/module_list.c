#include <stdio.h>
#include <stdlib.h>
#include "module_list.h"

// Функция для того, чтобы добавить новый элемент в списке
int Applist(list* to_This_List, lElem* newElem)
{
	if (to_This_List->head == NULL)
	{
		to_This_List->head = newElem;
		to_This_List->current = newElem;
		return 0;
	}
	to_This_List->current->nextElem = newElem;
	to_This_List->current = newElem;
	return 0;
}


// Функция для следующего элемента
lElem* nextElem(list* in_This_List)
{
	lElem* next = in_This_List->current->nextElem;
	in_This_List->current = next;
	return next;
}

int To_Head_Elem(list* in_This_List)
{
	in_This_List->current = in_This_List->head;
	return 0;
}


// Функция для удаления элемента
int deleteElem(list* in_This_List)
{
	lElem* del = in_This_List->current;
	if (del == in_This_List->head)
	{
		in_This_List->head = del->nextElem;
		nextElem(in_This_List);
	}
	else
	{
		To_Head_Elem(in_This_List);
		while (in_This_List->current->nextElem != del) nextElem(in_This_List);
		in_This_List->current->nextElem = del->nextElem;
		if (del->nextElem != NULL) in_This_List->current = del->nextElem;
	}
	free(del);
	return 0;
}