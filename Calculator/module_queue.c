#include <stdio.h>
#include <stdlib.h>
#include "module_queue.h"

//функция для добавления нового элемента
void putElem(queue* to_This_Queue, queueElem* newItem)
{
	if (to_This_Queue->head == NULL) to_This_Queue->head = newItem;
	if (to_This_Queue->end != NULL) to_This_Queue->end->nextElem = newItem;
	to_This_Queue->end = newItem;
}


//функция для получения лемента из головы очереди
queueElem* getElem(queue* from_This_Queue)
{
	if (from_This_Queue->head == NULL) return NULL;
	queueElem* ret = from_This_Queue->head;
	from_This_Queue->head = from_This_Queue->head->nextElem;
	return ret;
}


void delElemQueue(queueElem* del)
{
	if (del != NULL)
	{
		if (del->g != NULL) {
			free(del->g);
		}
		if (del->res != NULL) {
			free(del->res);
		}
		if (del->value1 != NULL) {
			free(del->value1);
		}
		if (del->value2 != NULL) {
			free(del->value2);
		}
		free(del);
	}
}

