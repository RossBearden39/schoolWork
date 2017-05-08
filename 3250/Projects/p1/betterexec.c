#include <stdio.h>

main()
{
    int rc,s;
    char *args[] = { "/bin/date", NULL };

    printf("pid=%d\n",getpid());
    rc = fork();
    if (rc == 0)  /* child */
    {
	printf("child pid=%d\n",getpid());
	execve("/bin/date",args,NULL);
	printf("should NOT see this message\n");
    }
    printf("rc=%d\n",rc);
    wait(&s);
}
