#include <stdio.h>
//#include <signal.h>
#include<stddef.h>

typedef unsigned int future;
struct futures{
        future value;
        int flag;
};
typedef struct futures futures;

//futures f1;

futures*  future_alloc(int future_flags);

syscall future_free(futures *data);

syscall  future_get(futures *data,int *val);

syscall future_set(futures *data, int fData);
