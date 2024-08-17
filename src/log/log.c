#include "log.h"

#include <stdio.h>

void log_sysenv(const char** sys_env)
{
	if (!sys_env)
		return;

	while (*sys_env)
	{
		printf("%s\n", *sys_env);
		sys_env++;
	}
}

void log_env(const t_env* env)
{
	if (!env || !env->path)
		return;

	int i = 0;
	while (env->path[i])
	{
		printf("%s\n", env->path[i]);
		i++;
	}
}
