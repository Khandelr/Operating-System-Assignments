#include <stddef.h>
#include <stdio.h>

typedef struct futures futures;
void future_producer_consumer(void);
void future_prod(futures *data);
void future_cons(futures *data);
