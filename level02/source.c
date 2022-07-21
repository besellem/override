#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int		main(void)
{
	char	password[14] = {0};
	char	buffer[41] = {0};
	char	username[12] = {0};
	int		ret;
	FILE	*f = NULL;

	f = fopen("/home/users/level03/.pass", "r");
	if (f == NULL)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
						/* WARNING: Subroutine does not return */
		exit(1);
	}

	ret = fread(buffer, 1, 41, f);
	buffer[strcspn(buffer, "\n")] = 0;
	if (ret != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(1);
	}
	fclose(f);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");

	printf("--[ Username: ");
	fgets(username, 100, stdin);
	username[strcspn(username, "\n")] = 0;

	printf("--[ Password: ");
	fgets(password, 100, stdin);
	password[strcspn(password, "\n")] = 0;

	puts("*****************************************");

	if (strncmp(buffer, password, 41) == 0)
	{
		printf("Greetings, %s!\n", username);
		system("/bin/sh");
		return 0;
	}

	printf(username);
	puts(" does not have access!");
	exit(1);
}
