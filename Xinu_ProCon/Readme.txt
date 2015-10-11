producer_consumer.c version 1.0 09/30/2013

GENERAL USAGE NOTES
--------------------

- We have extended the Xinu Shell by adding our command "ProCon".

- "ProCon" implements the basic Producer-Consumer code without synchronization.

- For implementing this command, we studied how to implement and add our own commands in Xinu. 

------------------------------------------------------------------------------------------
Steps:

1. We have created a source file for our command by the name "producer_consumer.c" in "apps" directory and also updated "Makerules" to bind files in the directory by adding the filename under C_FILES.
2. We created a file "xsh_producer_consumer.c" in the shell directory so that we can can insert our own command in the Xinu shell. This is the file which
   would be executed when user types the command in Xinu, "ProCon" in our case which will call the required function in the source file in the apps directory.
3. We updated "Makerules" in the shell directory to bind files in the directory and added our command in the shell.c so that Xinu recognizes our command.
4. We have created a header file "producer_consumer.h" in the "include" directory. It contains the function declaration of the file "producer_consumer.c" which is in the "apps" directory.
5. We have added the function prototype "xsh_producer_consumer" in "shell.h" in the "include" directory.
6. After this, we compiled the entire code by running make && make download.
7. The output of our command is shown in the file attached "Output.txt".
------------------------------------------------------------------------------------------

Developers:

- Ratish Dalvi[ rdalvi@indiana.edu ] +1 [812-360-1061]

- Ramakant Khandel [ khandelr@indiana.edu ] +1 [812-361-0137]

--------------------------------------------------------------------------------------------

Help from the following sources was taken to understand the concepts of Xinu:

- Operating Systems Design: The Xinu Approach, Linksys Version (Chapter 2)

- https://github.iu.edu/SOIC-Operating-Systems/xinu-arm/wiki/Getting-Started

----------------------------------------------------------------------------------------------------------------------------------
