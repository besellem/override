#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>

int		auth(char *buffer, unsigned int num)
{
	size_t	len;
	unsigned int tmp;
	
	buffer[strcspn(buffer, "\n")] = '\0';
	len = strnlen(buffer, 32);
	if ((int)len < 6)
		return 1;

	if (ptrace(PT_TRACE_ME, 0, 0, 0) == -1)
	{
		puts("\x1b[32m.---------------------------.");
		puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m\'---------------------------\'");
		return 1;
	}


	tmp = ((int)buffer[3] ^ 0x1337U) + 0x5eeded;
	for (int i = 0; i < (int)len; ++i)
	{
		if (buffer[i] < ' ')
			return 1;
		tmp = tmp + ((int)buffer[i] ^ tmp) % 0x539;
	}
	// printf("tmp: %u  num: %u\n", tmp, num);
	return (num != tmp);
}

int		main(void)
{
	char			buffer[32];
	unsigned int	num;
	
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");

	printf("-> Enter Login: ");
	fgets(buffer, 32, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");

	printf("-> Enter Serial: ");
	scanf("%u", &num);

	if (auth(buffer, num) == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
	}
	return 1;
}
