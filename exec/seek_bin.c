/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:56:39 by anadege           #+#    #+#             */
/*   Updated: 2021/09/24 14:31:51 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to verify is a filepath is absolute or not depending of it's syntax.
** Return 0 if path is absolute, 1 if syntax indicate it must be in PATH,
** 2 if syntax indicate it must be in HOME.
*/
int	is_absolute_path(char *filepath)
{
	if (!ft_strncmp("~", filepath, 1))
		return (2);
	else if (!ft_strncmp("./", filepath, 2) || !ft_strncmp("../", filepath, 3)
		|| !ft_strncmp("/", filepath, 1))
		return (0);
	return (1);
}

/*
** Function to reconstitute an absolute path starting with env_var
** and ending by non-absolute filepath.
*/
char	*reconstitute_absolute_path(char *env_var, char *filepath)
{
	char	*path;
	char	*tmp;

	if (!env_var)
		return (filepath);
	if (!filepath)
		return (NULL);
	tmp = ft_strjoin(env_var, "/");
	path = ft_strjoin(tmp, filepath);
	free(tmp);
	return (path);
}

/*
** Sub-function to get_absolute_path.
** Try to seek the absolute filepath from the PATH variables.
** Return NULL if not found.
*/
char	*get_absolute_path_from_path(char *filepath, char *env_var)
{
	int			i;
	char		*path;
	char		**paths;
	struct stat	buf;

	i = 0;
	paths = ft_split(env_var, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		path = reconstitute_absolute_path(paths[i], filepath);
		free(paths[i++]);
		if (!stat(path, &buf))
			break ;
		free(path);
		path = NULL;
	}
	free(paths);
	return (path);
}

/*
** Function to seek absolute path from PATH or HOME.
** If is_home == 1, seek in HOME. If is_home == 0, seek in PATH.
** Return NULL if one of the two variable is missing or if the file
** wasn't found in PATH.
*/
char	*get_absolute_path(char *filepath, char **env, char in_home)
{
	char	*path;
	char	*env_var;
	char	*tmp;

	if (in_home)
	{
		env_var = get_env_elem(env, "HOME");
		if (!env_var)
			return (NULL);
		path = env_var;
		if (ft_strlen(filepath) > 2)
			path = reconstitute_absolute_path(env_var, &filepath[2]);
		return (path);
	}
	env_var = get_env_elem(env, "PATH");
	if (!env_var)
		return (NULL);
	return (get_absolute_path_from_path(filepath, env_var));
}

/*
** Function which return a string corresponding to the absolute
** path of the file pointed by filepath.
** If the file is not found or a directory is not accessible, NULL is returned.
*/
char	*get_path(char *filepath, char **env)
{
	int			res;
	char		*path;
	struct stat	buf;

	path = filepath;
	if (!path)
		return (NULL);
	res = is_absolute_path(filepath);
	if (res == 2)
		path = get_absolute_path(filepath, env, 1);
	else if (res == 1)
		path = get_absolute_path(filepath, env, 0);
	if (path && !stat(path, &buf))
		return (path);
	return (NULL);
}

/*
// TEST
int main(int argc, char **argv, char **env)
{
	char	*filepath;

	if (argc != 2)
		return (0);
	filepath = ft_strdup(argv[1]);
	char *path = get_path(filepath, env);
	if (path)
	{
		free(path);
		printf("valid\n");
	}
	return (0);
}
*/
