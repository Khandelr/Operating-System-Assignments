#include<stdio.h>
#define MAXSIZE 10
struct Queue
{
   int queArray[10];
   int rear;
};
typedef struct Queue Queue;
    
void initialize(Queue *queue);

int insertfutqueue(Queue *queue,int j);

int removedata(Queue *queue);

int isEmpty(Queue *queue);

int isFull(Queue *queue);

int size(Queue *queue);