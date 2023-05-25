#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PROMPT "#cisfun$ "

/**
 * main - Simple Shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	int endOfFile = 0;

	while (!endOfFile)
	{
		printf("%s", PROMPT);
		nread = getline(&buffer, &bufsize, stdin);
		if (nread == -1)
		{
			perror("Error reading input");
			break;
		}
		else if (nread == 0)
		{
			printf("\n");
			endOfFile = 1;
			break;
		}

		if (buffer[nread - 1] == '\n')
			buffer[nread - 1] = '\0';

		/* Check if input contains more than one word */
		if (strchr(buffer, ' '))
		{
			printf("Error: Invalid command\n");
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("Error forking process");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			char *args[] = {buffer, NULL};
			if (execve(args[0], args, NULL) == -1)
			{
				printf("Error: Command not found\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(buffer);
	exit(EXIT_SUCCESS);
}
