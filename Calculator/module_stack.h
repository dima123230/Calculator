#ifndef module_stack
#define module_stack

typedef struct stackElem
{
	float nD;
	struct stackElem* next;
} stackElem;

typedef struct stack
{
	stackElem* head;
} stack;

void sPutElem(stack* s, stackElem* e);

stackElem* sGetElem(stack* s);

void delElemStack(stackElem* del);

#endif