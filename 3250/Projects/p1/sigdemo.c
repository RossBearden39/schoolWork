#include <stdio.h>
#include <signal.h>

void handler(int signum)
{
    printf("handler called with signum=%d\n",signum);
}

main()
{
    printf("PID=%d\n",getpid());
    signal(SIGFPE,handler);
    signal(SIGSEGV,handler);
    for (;;)
        ;
}
