#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void	log_wrapper(FILE *stream, char *msg, char *fmt)
{
	char	buffer[264];

	strcpy(buffer, msg);
	snprintf(buffer + strlen(buffer), 254 - strlen(buffer), fmt);
	buffer[strcspn(buffer, "\n")] = '\0';
	fprintf(stream, "LOG: %s\n", buffer);
}

int		main(int argc, char **argv)
{
	char	backup_path[100] = "./backups/";
	FILE	*log_file;
	FILE	*input_file;
	int		fd;
	char	c;

	if (argc != 2)
	{
		printf("Usage: %s filename\n", *argv);
	}

	log_file = fopen("./backups/.log", "w");
	if (!log_file)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}

	log_wrapper(log_file, "Starting back up: ", argv[1]);
	
	input_file = fopen(argv[1], "r");
	if (!input_file)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}
	
	
	strncat(backup_path, argv[1], 99 - strlen(backup_path));

	fd = open(backup_path, O_WRONLY | O_CREAT | O_EXCL, 0660);
	if (fd < 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}

	while (1)
	{
		c = fgetc(input_file);
		if (c == EOF)
			break;
		write(fd, &c, 1);
	}

	log_wrapper(log_file, "Finished back up ", argv[1]);
	
	fclose(input_file);
	close(fd);

	return 0;
}
