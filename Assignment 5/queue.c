#include<stdio.h>
#include<futqueue.h>
#define MAXSIZE 10
typedef struct Queue Queue;
    
void initialize(Queue *queue){
	int i=0;
	for( i=0;i<MAXSIZE;i++){
		queue->queArray[i]=0;
	}
	queue->rear=0;
}
    
int insertfutqueue(Queue *queue,int j){
	//int index=queue->rear;
	//printf("\n inside insertfutqueue1\n");
	if(queue->rear == MAXSIZE){         
       	return -1;
	}
	//printf("2\n");
       queue->queArray[queue->rear] = j;
	//printf("3 queue rear %d\n",queue->rear);
	//printf("3 data %d\n",queue->queArray[queue->rear]);
	queue->rear=queue->rear+1;
	//printf("4 queue rear %d\n",queue->rear);
	return 1;                  
}
int removedata(Queue *queue){
	int i;
	if(queue->queArray[0]!=0 && queue->rear>0){
      		int temp = queue->queArray[0];
		
		for(i=1;i<queue->rear;i++){
			queue->queArray[i-1]=queue->queArray[i];
		} 
		queue->rear-=1;                     
      		return temp;
	}
	else{
		return -1;
	}
}
int isEmpty(Queue *queue){
	if(queue->rear==0){
      		return 1;
	}
	else{
		return 0;
	}
}
int isFull(Queue *queue){
	if(queue->rear==(MAXSIZE)){
                return 1;
        }
        else{
                return 0;
        }
}
  
int size(Queue *queue){
      return (queue->rear);
}
   
