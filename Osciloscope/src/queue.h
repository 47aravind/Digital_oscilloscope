// Define this data struct as QUEUE
// to create a QUEUE objects do

// How to make a struct
// QUEUE RX_Data;
// QUEUE TX_Data;

// Get data from a struct
// RX_Data.Size   	// gets the size of the QUEUE
// RX_Data.Data[0]	// get the 0 index of the character array

// Get data from a struct pointer
// QUEUE * mydata;
// mydata=&RX_Data;
// mydata->Size		// gets the size of the QUEUE
// mydata->Data[0]	// get the 0 index of the character array

#define QUEUE_SIZE 50				// define the size of the queue

typedef struct 
{
	unsigned char Data[QUEUE_SIZE];	// char array for our string
	unsigned int Head; 				// points to oldest data element
	unsigned int Tail; 				// points to next free space 
	unsigned int Size; 				// quantity of elements in queue
} QUEUE;

void Queue_Init(QUEUE * q);
int  Queue_Empty(QUEUE * q);
int	 Queue_Full(QUEUE * q);
int  Queue_Size(QUEUE * q);
int	 Queue_Enqueue(QUEUE * q, unsigned char d);
int	 Queue_Enqueue_String(QUEUE * q, unsigned char * d);
unsigned char Queue_Dequeue(QUEUE * q);