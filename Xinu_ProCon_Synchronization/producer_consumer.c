/* producer_consumer.c - main, produce, consume */
#include <producer_consumer.h>
#include <stdio.h>
void produce(int consumed, int produced), consume(int consumed, int produced);
int n = 0; /* external variables are shared by all processes */
/*------------------------------------------------------------------------
* main -- example of unsynchronized producer and consumer processes
*------------------------------------------------------------------------
*/
void producer_consumer(void)
{
int produced, consumed;
consumed= semcreate(0);
produced= semcreate(1);
resume( create(consume, 1024, 20, "cons", 2, consumed, produced) );
resume( create(produce, 1024, 20, "prod", 2, consumed, produced) );
}
/*------------------------------------------------------------------------
* produce -- increment n 2000 times and exit
*------------------------------------------------------------------------
*/
void produce(int consumed, int produced)
{
int i;
for( i=1 ; i<=2000 ; i++ ){
wait(consumed);
n++;
signal(produced);
}
}
/*------------------------------------------------------------------------
* consume -- print n 2000 times and exit
*------------------------------------------------------------------------
*/
void consume(int consumed, int produced)
{
int i;
for( i=1 ; i<=2000 ; i++ ){
wait(produced);
printf("The value of n is %d \n", n);
signal(consumed);
}
}
