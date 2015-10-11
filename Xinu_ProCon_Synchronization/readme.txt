                                                                     
                                                                     
                                                                     
                                             
Assignment# 3: Xinu Project 2
Dated: 10/09/2013

-------------------------------------------------------------------------
Developers:

- Ratish Dalvi  [ rdalvi@indiana.edu ] [ Student ID# 0003226371 ]

- Ramakant Khandel  [ khandelr@indiana.edu ] [ Student ID# 0003080002 ] 

-------------------------------------------------------------------------
Details

- In this implementation, the command 'ProCon' has been modified to synchronize producer and consumer.

- The semaphores  Wait() and Signal()  calls have been used to implement the synchronization. Two semaphore variables have been used called Produced and Consumed.

- The assignment shows how synchronization can be achieved between processes with the use of semaphores. 

-------------------------------------------------------------------------
Steps Followed:

1. Modified the source file for the command by the name 'producer_consumer.c' in 'apps' directory.
2. The initial code was the implementation of Producer-consurmer problem without synchronization. For this assignment, synchronization between producer and consumer was implemented using the semaphores variable and Wait() and Signal() calls.
3. Compiled the entire code by running 'make && make download' command in unix shell.
4. The output of the command is shown in the file attached 'Output.txt'.

-------------------------------------------------------------------------
Following sources was taken to understand the concepts of Xinu:

- Operating Systems Design: The Xinu Approach, Linksys Version

-------------------------------------------------------------------------
