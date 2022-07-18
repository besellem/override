#include <stdio.h>

int		main(void)
{
	int		var;
	
	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");
	
	printf("Password:");
	scanf("%d", &var);

	if (var != 5276)
	{
		puts("\nInvalid Password!");
		return 1;
	}
	else
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
	}

	return 0;
}
