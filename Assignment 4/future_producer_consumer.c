/* producer_consumer.c - main, produce, consume */
#include <future.h>
#include <stdio.h>
#include<fstruct.h>
#include<stddef.h>
typedef struct futures futures;

void future_prod(futures *fptr){
	int i=120;
	//for(i=0;i<4;i++){
		future_set(fptr,i);
	//}
}

void future_cons(futures *fptr);

void future_producer_consumer(void){
	futures *f1=NULL,*f2=NULL,*f3=NULL;
	f1=future_alloc(0);
	f2=future_alloc(0);
	f3=future_alloc(0);
	resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
	
	resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
	//resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
//resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
//future_free(&f1);
//f1=NULL;
//printf("f1 flag %d\n",f1->value);
//resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );

//resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
		
//resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
	//resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
	resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
	resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
	resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
	resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );
	//resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
//printf("hi");	
}

void future_cons(futures *fptr){
	int ans=-1,i;
	syscall arg;
	//for(i=0;i<4;i++){
		arg=future_get(fptr,&ans);
		if(arg!=-1 && ans!=-1){
			printf("the value produced %d\n",ans);
		//printf("the arg %d\n",arg);
	//}
		}
}

