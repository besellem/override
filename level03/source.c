#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void	prog_timeout(void)
{
	exit(1);
}

void	clear_stdin(void)
{
	int	c;

	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

int		decrypt(unsigned int num)
{
	char	buffer[] = "Q}|u`sfg~sf{}|a3";

	for (size_t i = 0; buffer[i]; ++i)
	{
		buffer[i] = buffer[i] ^ num;
	}

	if (strncmp(buffer, "Congratulations!", 17) == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");
}

void	test(int num1, int num2)
{
	unsigned int	diff = num2 - num1;

	switch (diff)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			decrypt(diff);
			break ;
		default:
			decrypt(rand());
	}
}

unsigned int	get_unum(void)
{
	unsigned int	unum = 0;

	fflush(stdout);
	scanf("%u", &unum);
	clear_stdin();
	return unum;
}

int		main(void)
{
	int	passwd;

	srand(time(NULL));

	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");

	scanf("%d", &passwd);
	test(passwd, 322424845);

	return 0;
}
