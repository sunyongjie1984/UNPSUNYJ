#include "../lib/unpsunyj.h"

void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated_syj\n", pid);
	return;
}
