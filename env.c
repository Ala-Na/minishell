char	*get_env_elem(char **env, char *elem)
{
	int		i;
	char	*elem_value;
	int		elem_size;

	i = 0;
	elem_size = ft_strlen(elem);
	while (env[i])
	{
		if (!ft_strncmp(env[i], elem, elem_size))
		{
			elem_value = env[i];
			elem_value += elem_size + 1;
			return (elem_value);
		}
		i++;
	}
	return (NULL);
}

