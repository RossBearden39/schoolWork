#include <stdio.h>

main()
{
    int i;

    i = fork();
    printf("%d got i=%d\n", getpid(), i);
}


/*****
if ((rc = fork())  == -1)
   print failed
else if (rc == 0)
   do what a child does
else
   do some parental thing
*****/
