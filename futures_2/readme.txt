                                                                     
                                                                     
                                                                     
                                             
Assignment# 5: Futures 2
Dated: 11/18/2013

-------------------------------------------------------------------------
Developers:

- Ratish Dalvi  [ rdalvi@indiana.edu ] [ Student ID# 0003226371 ]
	cont implementation
	test function
	design document 
- Ramakant Khandel  [ khandelr@indiana.edu ] [ Student ID# 0003080002 ] 
	async implementation
	queue implementation
	design document
-------------------------------------------------------------------------
Details

- In this implementation, the command 'fProCon' has been modified to synchronize producer and consumer using futures.

- The assignment shows how synchronization can be achieved using futures. 

-------------------------------------------------------------------------
Steps Followed:

1. We have created a source file for our command by the name future_producer_consumer.c (which contains the code for producer-consumer problem)and fstruct.c(which contains the code for memory, set, free, get, async, asyncthread, cont, contthread, generatedata and prdata values for the futures variables) in apps directory and also updated Makerules by adding our filenames under C_FILES.
2. We created a file xsh_future_producer_consumer.c in the shell directory so that we can insert our own command in the Xinu shell. This is the file which would be executed when we type our own command in Xinu, fProCon in our case which will inturn call the required source files in the apps directory.
3. We updated Makerules in the shell directory and added our command in the command table (shell/shell.c) .
4. We have created header files future_producer_consumer.h and fstruct.h in the include directory. It contains the function declaration of the files future_producer_consumer.c and fstruct.c which is in the apps directory.
5. We have added the function prototype xsh_future_producer_consumer in shell.h in the include directory.
6. We have created header file futqueue.h in the include directory. It contains the function implementation for the queue.
7. The flag FT_SHARED and FT_QUEUE are allowed in this implementation and the handling for each one of them has been explained in the design document.  
-------------------------------------------------------------------------
Following sources was taken to understand the concepts of Xinu:

- Operating Systems Design: The Xinu Approach, Linksys Version

-------------------------------------------------------------------------
