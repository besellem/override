#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct
{
	char	msg[140];
	char	username[40];
	int		len;
}	t_save;

// t_save	save;

void	secret_backdoor(void)
{
	char	buffer[128];

	fgets(buffer, sizeof(buffer), stdin);
	system(buffer);
}

void	set_msg(t_save save)
{
	char	buffer[1024] = {0};

	puts(">: Msg @Unix-Dude");
	printf(">>: ");

	fgets(buffer, sizeof(buffer), stdin);

	strncpy(save.msg, buffer, save.len);
}

void	set_username(t_save save)
{
	char	buffer[128] = {0};
	int		i;

	puts(">: Enter your username");
	printf(">>: ");
	
	fgets(buffer, sizeof(buffer), stdin);

	for (i = 0; i <= 40 && buffer[i] != '\0'; ++i)
	{
		save.username[i] = buffer[i];
	}

	printf(">: Welcome, %s", save.username);
}

void	handle_msg(void)
{
	t_save	save;

	save.len = 140;
	set_username(save);
	set_msg(save);
	puts(">: Msg sent!");
}

int		main(void)
{
	puts("--------------------------------------------\n"
		 "|   ~Welcome to l33t-m$n ~    v1337        |\n"
		 "- -------------------------------------------");

	handle_msg();
	return 0;
}
