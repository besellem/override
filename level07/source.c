#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		store_number(unsigned int *buffer)
{
	unsigned int	number;
	unsigned int	index;

	printf(" Number: ");
	scanf("%u", &number);

	printf(" Index: ");
	scanf("%u", &index);

	if ((index % 3 == 0) || (number >> 0x18 == 0xb7))
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}
	else
	{
		buffer[index] = number;
		return 0;
	}
}

int		read_number(unsigned int *buffer)
{
	int	num;

	printf(" Index: ");
	scanf("%u", &num);

	printf(" Number at data[%u] is %u\n", num, buffer[num]);
	return 0;
}

int		main(int argc, char **argv, char **envp)
{
	unsigned int	buffer[100] = {0};
	char			command[20] = {0};
	int				ret;

	for (char **tmp = argv; *tmp != NULL; ++tmp)
		memset(*tmp, 0, strlen(*tmp));

	for (char **tmp = envp; *tmp != NULL; ++tmp)
		memset(*tmp, 0, strlen(*tmp));

	puts("----------------------------------------------------\n"
		 "  Welcome to wil\'s crappy number stora ge service!   \n"
		 "----------------------------------------------------\n"
		 " Commands:                                           \n"
		 "    store - store a number into the data storage    \n"
		 "    read   - read a number from the data storage     \n"
		 "    quit  - exit the program                         \n"
		 "----------------------------------------------------\n"
		 "   wil has reserved some storage :>                  \n"
		 "----------------------------------------------------\n");

	while (1)
	{
		printf("Input command: ");
		fgets(command, 20, stdin);
		command[strlen(command) - 1] = 0;

		ret = 1;
		if (strncmp(command, "store", 5) == 0)
			ret = store_number(buffer);
		else if (strncmp(command, "read", 4) == 0)
			ret = read_number(buffer);
		else if (strncmp(command, "quit", 4) == 0)
			return 0;

		if (ret == 0)
			printf(" Completed %s command successfully\n", command);
		else
			printf(" Failed to do %s command\n", command);

		memset(command, 0, sizeof(command));
	}
}
