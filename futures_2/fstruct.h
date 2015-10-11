#include <stdio.h>
//#include <signal.h>
#include<stddef.h>

typedef unsigned int future;
typedef struct Queue Queue;
struct futures{
        future value;
        int flag;
	 int FT_SHARED;
	 int FT_QUEUE;
	 Queue *queue;
};
typedef struct futures futures;

//futures f1;

futures*  future_alloc(int future_flags);

syscall future_free(futures *data);

syscall  future_get(futures *data,int *val);

syscall future_set(futures *data, int fData);

syscall async(futures *data, void *f);

void asyncthread(futures *f, void *fname);

syscall cont(futures *f, void *fname);

void contthread(futures *f, void *fname);

void generatedata(int *a);

void prdata(int d);