#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

static int	check_script(char *path)
{
	if (access(path, F_OK) == -1)
	{
		perror("script inexistant");
		return (1);
	}
	if (access(path, X_OK) == -1)
	{
		perror("script non executable");
		return (1);
	}
	return (0);
}

static void	exec_script(char *path)
{
	char	*argv[2];

	argv[0] = path;
	argv[1] = NULL;
	execve(path, argv, NULL);
	perror("execve");
	exit(1);
}

static int	wait_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	main(void)
{
	char	*path;
	pid_t	pid;

	path = "/sgoinfre/goinfre/Perso/zcadinot/script.sh";
	if (check_script(path))
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		exec_script(path);
	return (wait_child(pid));
}

