/* future_struct.c - main, produce, consume */
#include <future.h>
#include <stdio.h>
#include <fstruct.h>
#include <stddef.h>
#include <semaphore.h>
typedef struct futures futures;

futures* future_alloc(int future_flags){
	 futures *glb;
	 glb= (futures *)malloc(sizeof(struct futures));
        //glb->value=future_flags;
	 glb->flag= semcreate(0);
	 //printf("the flag hhh %d\n",glb->flag);
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
	
		if(semtab[data->flag].count < 0){
			return SYSERR;
		}
        		wait(data->flag);
			*val=data->value;
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
	if(semtab[data->flag].count>=1){
		return SYSERR;
	}
        data->value=fData;
		
	 signal(data->flag);
		//printf("data flag in set %d\n",semtab[data->flag].count);
		return OK;
       
}




