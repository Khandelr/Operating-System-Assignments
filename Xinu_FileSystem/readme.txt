Project: Filesystem on XINU
12/21/2013

GENERAL USAGE NOTES
--------------------

- This is the implementation of a filesystem on XINU

- In this implementation, Read, Write, Create , Open, seek and Close functions were implemented.

----------------------------------------------------------------------------------------------------------------
Implementation Details:

1. In the  xinu-arm directory in the system, we created "fs.h" file in the include directory and "fs.c" file in the system directory.
2. "fs.h" has the declarations for the arrays and structs of of inode, filetable, directory entry, directory and filesystem. These functions were then implemented in fs.c
3. "fs.c" contains the all the handling for implementing the file system.
4. Details of all the functions in fs.c have been included in the design document.
5. To test the filesystem, the command 'fstest' was added which contains the functions rread and wwrite  which in turn call fread and fwrite respectively. These functions are created to implement a higher level of abstraction for testing.  
6. In the test funtion, the same data(eg '777777777') is written into the file and then read from the file for blockSize of 5 and 3 blocks.
----------------------------------------------------------------------------------------------------------------

Developers:

- Ramakant Khandel [ Khandelr@indiana.edu ] 812-3610137
	Contribution: Read, Write seek

- Ratish Dalvi [ rdalvi@indiana.edu ] 812-360-1061
	Contribution: create, open , close and functions for other initialisations


------------------------------------------------------------------------------------------------------------------

the following sources were referred.

- Operating Systems Design: The Xinu Approach, Linksys Version (Chapter 2)

- http://www.lehman.cuny.edu/cgi-bin/man-cgi?fseek+3

- http://www.tutorialspoint.com/unix/unix-file-system.htm


----------------------------------------------------------------------------------------------------------------------------------
