#include <stdio.h>
#include <stdlib.h>
#include "module_stack.h"

void sPutElem(stack* s, stackElem* e)
{
	e->next = s->head;
	s->head = e;
}

stackElem* sGetElem(stack* s)
{
	stackElem* ret = s->head;
	s->head = s->head->next;
	return ret;
}


void delElemStack(stackElem* del)
{
	if (del != NULL) free(del);
}