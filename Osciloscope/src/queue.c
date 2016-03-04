#include "queue.h"

void Queue_Init(QUEUE * q)
{	
	unsigned int i;
	for (i=0; i<QUEUE_SIZE; i++)  
	{
		q->Data[i] = 0x00;
	}
	q->Head = 0;
	q->Tail = 0;
	q->Size = 0;
}

int Queue_Size(QUEUE * q)
{
	return q->Size;
}

int Queue_Empty(QUEUE * q)
{	
	return q->Size == 0;
}

int Queue_Full(QUEUE * q)
{	
	return q->Size == QUEUE_SIZE;
}

int	 Queue_Enqueue_String(QUEUE * q, unsigned char * d)
{
	while(*d!=0)
	{
		Queue_Enqueue(q,*d);
		*d++;
	}
}
int Queue_Enqueue(QUEUE * q, unsigned char d)
{	
	// What if queue is full?
	if (!Queue_Full(q))
	{	q->Data[q->Tail++] = d;
		q->Tail %= QUEUE_SIZE;
		q->Size++;
		return 1; // success
	}
	else 
	{
		return 0; // failure
	}
}

unsigned char Queue_Dequeue(QUEUE * q)
{	
	// Must check to see if queue is empty before dequeueing
	unsigned char t=0;
	if (!Queue_Empty(q))
	{	t = q->Data[q->Head];
		q->Data[q->Head++] = 0; // to simplify debugging
		q->Head %= QUEUE_SIZE;
		q->Size--;
	}
	return t;
}