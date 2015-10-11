/*
 * @file     xsh_fstest.c
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <fs.h>

void testbitmask(void);

void test_fs(void);
/**
 * @ingroup shell
 *
 * Shell command fstest.
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_fstest(int nargs, char *args[])
{

    /* Output help, if '--help' argument was supplied */
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
    {
        printf("Usage: %s\n\n", args[0]);
        printf("Description:\n");
        printf("\tFilesystem Test\n");
        printf("Options:\n");
        printf("\t--help\tdisplay this help and exit\n");
        return OK;
    }

    /* Check for correct number of arguments */
    if (nargs > 1)
    {
        fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
    }
    if (nargs < 1)
    {
        fprintf(stderr, "%s: too few arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
    }

#ifdef FS
    mkbsdev(0, 5, 5); /* device "0" and default blocksize (=0) and count */
    mkfs(0,100); /* bsdev 0*/
    //testbitmask();
	test_fs();
#else
    printf("No filesystem support\n");
#endif

    return OK;
}

/*
void
testbitmask(void) {

    setmaskbit(31); setmaskbit(95); setmaskbit(159);setmaskbit(223);
    setmaskbit(287); setmaskbit(351); setmaskbit(415);setmaskbit(479);
    setmaskbit(90); setmaskbit(154);setmaskbit(218); setmaskbit(282);
    setmaskbit(346); setmaskbit(347); setmaskbit(348); setmaskbit(349);
    setmaskbit(350); setmaskbit(100); setmaskbit(164);setmaskbit(228);
    setmaskbit(292); setmaskbit(356); setmaskbit(355); setmaskbit(354);
    setmaskbit(353); setmaskbit(352);
    
    printfreemask();

    clearmaskbit(31); clearmaskbit(95); clearmaskbit(159);clearmaskbit(223);
    clearmaskbit(287); clearmaskbit(351); clearmaskbit(415);clearmaskbit(479);
    clearmaskbit(90); clearmaskbit(154);clearmaskbit(218); clearmaskbit(282);
    clearmaskbit(346); clearmaskbit(347); clearmaskbit(348); clearmaskbit(349);
    clearmaskbit(350); clearmaskbit(100); clearmaskbit(164);clearmaskbit(228);
    clearmaskbit(292); clearmaskbit(356); clearmaskbit(355); clearmaskbit(354);
    clearmaskbit(353); clearmaskbit(352);

    printfreemask();

}

*/
void test_fs(void){

int fd1, fd2; //File descriptors
fd1 = fcreat("Test File", 0); //Creating a new file
printf("Helo %d\n", fd1);
//fd2 = fcreat("Sample", 0); //Creating a new file

fd1 = fopen("Test File", 1);//Opening a file in write-only mode
printf("file opened in write only mode..%d\n",fd1);
wwrite(fd1);
fclose(fd1);
//fwrite(fd1, )
fd1 = fopen("Test File", 0); //Opening the same file in Read only mode
rread(fd1);
//fclose(fd1);

//fd2 = fopen("Sample", 1); //Opening a file in write only mode
//fwrite(fd2, )
//fseek(fd2, 2);
//fd2 = fopen("Sample", 0); //Opening a file in read only mode
//rread(fd2);
//fclose(fd2);

}
