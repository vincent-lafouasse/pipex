#include "t_command.h"

#include <stdlib.h>
#include <unistd.h>
#include "libft/ft_string.h"
#include "libft/string.h"

static char* full_path(const char* dir, const char* file);
static t_error locate_command(const char* name, const t_env* env, char** cmd_out);

t_error load_command(const char* command, const t_env* env, t_command* cmd_out)
{
	t_error err;

	if (!command || !env || !cmd_out)
		return NULL_PARAM_ERROR;
	*cmd_out = (t_command){
		.location = NULL,
		.args = NULL,
		.in_fd = STDIN_FILENO,
		.out_fd = STDOUT_FILENO
	};
	cmd_out->args = ft_split(command, ' ');
	if (!cmd_out->args)
		return OOM_ERROR;
	err = locate_command(cmd_out->args[0], env, &cmd_out->location);
	return err;
}

static t_error locate_command(const char* name, const t_env* env, char** cmd_out)
{
	char* candidate;
	char* dir;
	int i = 0;

	dir = env->path[0];
	while (dir)
	{
		candidate = full_path(dir, name);
		if (!candidate)
			return OOM_ERROR;
		if (access(candidate, X_OK) == 0)
		{
			*cmd_out = candidate;
			return NO_ERROR;
		}
		free(candidate);
		dir = env->path[++i];
	}
	return FILE_NOT_FOUND_ERROR;
}

static char* full_path(const char* dir, const char* file)
{
	char* dir_with_slash;
	char* path;

	if (!dir || !file)
		return NULL;
	dir_with_slash = ft_strjoin(dir, "/");
	if (!dir_with_slash)
		return NULL;
	path = ft_strjoin(dir_with_slash, file);
	if (!path)
		return NULL;
	free(dir_with_slash);
	return path;
}
