#include "hex.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int ac, char **av)
{
	unsigned char	encode[0x100];
	unsigned char	encode_pipe[0x100];
	size_t			len = 0;
	int				fd[3][2];
	pid_t			pid[3];
	int				bytes = 0;
	
	if (ac < 2)
		return (fprintf(stderr, "usage : %s <data>\n", av[0]), 1);
	
	memset(encode, 0, sizeof(encode));
	memset(encode_pipe, 0, sizeof(encode_pipe));
	len = strlen(av[1]);

	if (len >= 0x100 || (len << 1) >= 0x100)
		return (fprintf(stderr, "[!] please your message must be larger than 256 bytes\n"), 1);

	hex_encode((uint8_t *)av[1], encode, len, sizeof(encode));

	if (pipe(fd[0]) < 0)
		return (1);

	if (pipe(fd[1]) < 0)
		return (1);

	if (pipe(fd[2]) < 0)
		return (1);

	pid[0] = fork();

	if (!pid[0])
	{
		close(fd[0][0]);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[1][1]);
		close(fd[2][0]);
		close(fd[2][1]);
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
		close(fd[2][0]);
		close(fd[2][1]);
		execlp("xxd", "xxd", "-ps", "-c 200", NULL);
		perror("xxd");
		exit(1);
	}

	pid[2] = fork();

	if (!pid[2])
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		dup2(fd[1][0], STDIN_FILENO);
		dup2(fd[2][1], STDOUT_FILENO);
		close(fd[1][0]);
		close(fd[2][1]);
		execlp("tr", "tr", "-d", "'\n'", NULL);
		perror("tr");
		exit(1);
	}
	else
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[1][1]);
		close(fd[2][1]);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], NULL, 0);
		waitpid(pid[2], NULL, 0);
		bytes = read(fd[2][0], encode_pipe, sizeof(encode_pipe));
		close(fd[2][0]);
	}

	if (strncmp((char *)to_lower(encode), (char *)encode_pipe, len << 1))
		return (fprintf(stderr, "Error output is not the same !\n"), 1);

	printf("Hex Encoder : %s\n", to_lower(encode));
	printf("Hex Encoder with pipe : %s\n", encode_pipe);
	printf("Bytes readed from pipe : %d\n", bytes);

	return (0);
}
