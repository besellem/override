#include <stdio.h>
#include <unistd.h>

char	a_user_name[256];

int		verify_user_name(void)
{
	const char	username[] = "dat_wil";

	for (int i = 5; i > 0; --i)
	{
		if (username[i] != a_user_name[i])
			return 1;
	}
	return 0;
}

int		verify_user_pass(char *buffer)
{
	const char	pass[] = "admin";

	for (int i = 5; i > 0; --i)
	{
		if (pass[i] != buffer[i])
			return 1;
	}
	return 0;
}

int		main(void)
{
	char	buffer[16] = {0};
	int		ret;

	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 256, stdin);

	if (verify_user_name() == 0)
	{
		puts("Enter Password: ");
		fgets(buffer, 100, stdin);

		ret = verify_user_pass(buffer);
		if ((ret == 0) || (ret != 0))
		{
			puts("nope, incorrect password...\n");
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		puts("nope, incorrect username...\n");
		return 1;
	}

	return 0;
}
