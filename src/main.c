#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "error/t_error.h"
#include "env/t_env.h"
#include "log/log.h"
#include "command/t_command.h"

#include "libft/ft_io.h"

typedef struct s_pipex {
	t_command* cmd1;
	t_command* cmd2;
	char* infile;
	char* outfile;
	t_env env;
} t_pipex;

t_pipex t_pipex_init(void)
{
	return (
		(t_pipex){
		.cmd1 = NULL,
		.cmd2 = NULL,
		.infile = NULL,
		.outfile = NULL,
		.env = (t_env){.sys_env = NULL, .path = NULL}
	}
	);
}

t_error load_pipex_input(int ac, char** av, char** sys_env, t_pipex* out)
{
	t_error err;

	if (ac != 5)
		return  BAD_N_ARGS_ERROR;

	*out = t_pipex_init();

	err = load_env(sys_env, &out->env);
	if (err != NO_ERROR)
		return err;

	out->cmd1 = malloc(sizeof(*out->cmd1));
	if (!out->cmd1)
		return OOM_ERROR;

	err = load_command(av[2], &out->env, out->cmd1);
	if (err != NO_ERROR)
		return err;

	out->cmd2 = malloc(sizeof(*out->cmd2));
	if (!out->cmd2)
		return OOM_ERROR;

	return load_command(av[3], &out->env, out->cmd2);
}

static void cleanup(void);
static void cleanup_exit(t_error error);

int main(int ac, char** av, char** sys_env)
{
	(void)ac;
	t_pipex pipex;
	t_error err;

	err = load_pipex_input(ac, av, sys_env, &pipex);
	if (err != NO_ERROR)
		cleanup_exit(err);

	log_cmd(pipex.cmd1);
	log_cmd(pipex.cmd2);

	execve(pipex.cmd1->location, pipex.cmd1->args, sys_env);
	/*
	char* command_name = av[1];
	char** args = av + 2;
	char* command_location;
	err = locate_command(command_name, &env, &command_location);
	if (err != NO_ERROR)
		cleanup_exit(err);

	if (execve(command_location, args, sys_env) == -1)
		cleanup_exit(DUMMY_ERROR);
	*/
}

static void cleanup(void)
{}

static void cleanup_exit(t_error error)
{
	cleanup();
	ft_putstr_fd("Error:\n", 2);
	ft_putstr_fd(error_repr(error), 2);
	exit(EXIT_FAILURE);
}
