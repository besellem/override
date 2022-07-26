#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int		main(void)
{
	char	buffer[32] = {0};
	int		status = 0;
	long	ret = 0;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		prctl(PR_SET_PDEATHSIG, 1);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(buffer);
	}
	else
	{
		do
		{
			wait(&status);
			if (WIFEXITED(status) || WIFSIGNALED(status))
			{
				puts("child is exiting...");
				return 0;
			}
			ret = ptrace(PT_READ_U, pid, 44, 0);
		} while (ret != 0xb);

		puts("no exec() for you");
		kill(pid, SIGKILL);
	}

	return 0;
}
