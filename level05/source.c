#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	main(void)
{
	char	buffer[100];
	size_t	i = 0;

	fgets(buffer, 100, stdin);
	while (i < strlen(buffer))
	{
		if (buffer[i] > '@' && buffer[i] < '[')
		{
			buffer[i] ^= 32;
		}
		++i;
	}
	printf(buffer);
	exit(0);
}
