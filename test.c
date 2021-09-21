#include "minishell.h"

int main(int argc, char **args, char **env)
{
	int	env_elems;
	int	args_elems;

	env_elems = 0;
	args_elems = 0;
	while (env[env_elems])
	{
		printf("%s\n", env[env_elems]);
		env_elems++;
	}
	printf("Process received %i env elems.\n", env_elems);
	while (args[args_elems])
	{
		printf("%i arg is %s.\n", args_elems, args[args_elems]);
		args_elems++;
	}
	return (0);
}
