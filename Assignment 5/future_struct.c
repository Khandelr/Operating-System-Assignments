/* future_struct.c - main, produce, consume */
#include <future.h>
#include <stdio.h>
#include <fstruct.h>
#include <stddef.h>
#include <semaphore.h>
#include<futqueue.h>
typedef struct futures futures;
typedef struct Queue Queue; 
int number=11;


futures* future_alloc(int future_flags){
	futures *glb;
	glb= (futures *)malloc(sizeof(struct futures));
        //glb->value=future_flags;
	glb->value=0;
	glb->flag= semcreate(0);
	if (future_flags == 0){	
		glb->FT_SHARED = 1;
		glb->FT_QUEUE = 0;
	}
	else if (future_flags == 1){
		glb->FT_SHARED = 0;
		glb->FT_QUEUE = 1;
	}
	else{
		glb->FT_SHARED = 0;
		glb->FT_QUEUE = 0;
	} 
	//printf("the flag hhh %d\n",glb->flag);
	Queue *queu;
	initialize(queu);
	//queu =(Queue) calloc
	//printf("queu rear before calloc %d\n",queu.rear);
	//glb->queue=(Queue *)calloc(1,sizeof(struct Queue)) ;
	glb->queue=queu;
	//printf("struct rear after calloc %d\n",glb->queue->rear);
       return glb;


}

syscall future_free(futures *data){
	 if(data!=NULL){
	 	signal(data->flag);
        	free(data);
		//printf("free");
		//*data=NULL;
		return OK;
	 }
	 else{
	 	return SYSERR;	
	 }
}

syscall future_get(futures *data, int *val){
       if(data!=NULL){
		//printf("data flag in get %d\n",semtab[data->flag].count); 
		//printf("data->FT_SHARED %d\n",data->FT_SHARED);
		if(semtab[data->flag].count < 0 && data->FT_SHARED!=1){
			//printf("before syserr");
			return SYSERR;
		}
		

		//printf("data->FT_SHARED %d\n",data->FT_SHARED);
		
		//printf("data->value %d\n",data->value);
			if(data->FT_SHARED==0 || (data->FT_SHARED==1 && data->value == 0)){
				//printf("to wait for the value to set\n");
        			wait(data->flag);
				//printf("data flag innnnnnnnnnnnn get %d\n",semtab[data->flag].count); 
	
			}
			*val=data->value;
			if(data->FT_QUEUE==1){
				data->value=0;
			}
			return OK;

	}
	else{
		//printf("null data \n");
		//printf("bye\n");
		return SYSERR;
	}
}

syscall future_set(futures *data, int fData){
	if(data==NULL){
		data=future_alloc(0);
	}
	
	//printf("data flag in set %d\n",semtab[data->flag].count); 
	if(semtab[data->flag].count>=1 || (data->FT_SHARED==1 && data->value!=0)){
		//printf("syserr");
		return SYSERR;
	}
        data->value=fData;
	//printf("data->value future set %d\n",data->value);
	signal(data->flag);
	while(semtab[data->flag].count < 0 && data->FT_SHARED==1){
		//printf("to release thread\n");
		signal(data->flag);
	}
		//printf("data flag in set %d\n",semtab[data->flag].count);
		return OK;
       
}

syscall async(futures *f, void *fname){	
	//printf("inside async");
	resume( create(asyncthread, 1024, 20, "hello", 2, f,fname) );
	return OK;
}

void asyncthread(futures *f, void *fname)
{
	//printf("inside async thread");
	//printf("hi");
		int x;
	void (*fnam)(int *)=fname;
	fnam(&x);
	//printf("x %d",x);
	//printf("f->ft_queue %d\n",f->FT_QUEUE);
	//printf("semtab[f->flag].count %d\n",semtab[f->flag].count);
	//printf("async thread struct rear %d\n",f->queue->rear);

	if(f->FT_QUEUE== 1 && semtab[f->flag].count>0 ){
		 if(f->queue!=NULL){
			//printf("inside value %d\n",f->value);
			//printf("struct rear inside else if %d\n",f->queue->rear);			
			
			insertfutqueue(f->queue,x);
			//return OK;
		}
				
	}
	else{
		//printf("inside async else %d\n",x);
		future_set(f,x);
	}
}

syscall cont(futures *f, void *fnamecont){
	//printf("inside cont");
	resume( create(contthread, 1024, 20, "hello", 2, f,fnamecont) );
	return OK;
}

void contthread(futures *f, void *fnamecont)
{
		//printf("inside cont thread");
	int x;
	void (*fnameco)(int )=fnamecont;
	if(f->FT_QUEUE== 1 && f->queue!=NULL &&f->value==0 && (size(f->queue)>0)){
			future_set(f,removedata(f->queue));
	}
	future_get(f, &x);
	
	fnameco(x);		
	//printf("size of queue %d\n",size(f->queue));
}

void generatedata(int *y){
	//int k=7;
	*y=number;
	--number;
}
void prdata(int data){
	printf("the value is %d\n",data);
}	