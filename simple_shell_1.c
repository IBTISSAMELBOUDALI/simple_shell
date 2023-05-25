#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

	while (1)
	{
		printf("%s", PROMPT);
		nread = getline(&buffer, &bufsize, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
		}
		if (buffer[nread - 1] == '\n')
			buffer[nread - 1] = '\0';

		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(buffer, NULL, NULL) == -1)
			{
				printf("Error: command not found\n");
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
