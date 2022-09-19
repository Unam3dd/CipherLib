#include "base64.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int ac, char **av)
{
	unsigned char	decode[0x100];
	unsigned char	decode_pipe[0x100];
	size_t			len = 0;
	int				fd[2][2];
	pid_t			pid[2];
	int				bytes = 0;
	
	if (ac < 2)
		return (fprintf(stderr, "usage : %s <data>\n", av[0]), 1);
	
	memset(decode, 0, sizeof(decode));
	memset(decode_pipe, 0, sizeof(decode_pipe));
	len = strlen(av[1]);

	if (len >= 0x100 || (len >> 2) >= 0x100)
		return (fprintf(stderr, "[!] please your message must be larger than 256 bytes\n"), 1);

	base64_decode((uint8_t *)av[1], decode, strlen(av[1]), &len);

	if (pipe(fd[0]) < 0)
		return (1);

	if (pipe(fd[1]) < 0)
		return (1);

	pid[0] = fork();

	if (!pid[0])
	{
		close(fd[0][0]);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[1][1]);
		execlp("echo", "echo", "-n", av[1], NULL);
		perror("echo");
		exit(1);
	}
	
	
	pid[1] = fork();

	if (!pid[1])
	{
		dup2(fd[0][0], STDIN_FILENO);
		dup2(fd[1][1], STDOUT_FILENO);
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[1][1]);
		execlp("base64", "base64", "-d", NULL);
		perror("base64");
		exit(1);
	}
	else
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], NULL, 0);
		bytes = read(fd[1][0], decode_pipe, sizeof(decode_pipe));
		close(fd[1][0]);
	}

	if (strncmp((char *)decode, (char *)decode_pipe, len))
		return (fprintf(stderr, "Error output is not the same !\n"), 1);

	printf("Base64 Decoder : %s\n", decode);
	printf("Base64 Decoder with pipe : %s\n", decode_pipe);
	printf("Bytes readed from pipe : %d\n", bytes);

	return (0);
}
