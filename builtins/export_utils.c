/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:29:45 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/05 14:19:02 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to obtains the position of an element identified
** by the name elem_name inside **env.
** Returns index (or position insided **env) if success, -1 if
** env or elem_name is NULL, -2 if the element isn't found inside **env.
*/
int	seek_elem_pos(char **env, char *elem_name)
{
	int	i;
	int	elem_pos;

	i = 0;
	elem_pos = 0;
	if (!env || !elem_name)
		return (return_error(1, "something went wrong", 0, -1));
	while (env[i])
		i++;
	while (env[elem_pos])
	{
		if (!ft_strncmp(env[elem_pos], elem_name, ft_strlen(elem_name)))
			break ;
		elem_pos++;
	}
	if (elem_pos == i)
		return (-2);
	return (elem_pos);
}

/*
** Function used to print when a invalid identifier is encountered.
*/
int	invalid_token(t_token **token, int is_export, int *res)
{
	char	*tmp;
	char	*str;

	g_exit_status = 1;
	if (res)
		*res = 1;
	if (is_export)
		tmp = ft_strnjoin("export: « ", (*token)->token, (*token)->length);
	else
		tmp = ft_strnjoin("unset: « ", (*token)->token, (*token)->length);
	if (!tmp)
		return (return_error(1, "memory allocation error", 0, -1));
	str = ft_strjoin(tmp, " » : not a valid identifier");
	free(tmp);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	move_to_next_token(token, 1);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (-1);
}

/*
** Function to check if the argument to unset is valid or not.
** 1. Check if all the characters are '_' -> valid
** 2. Check if all the characters are either 0-9 or '_' -> invalid
** 3. Check if all the characters are either alphanumeric or '_' -> valid
** 4. If the third check fails -> invalid
*/
int	check_validity_token(t_token **token, int is_export, int *res)
{
	char	*str;
	int		i;

	i = 0;
	str = get_elem_name(*token);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	if (ft_strlen(str) == 0)
		return (invalid_token(token, is_export, res));
	while (str[i] && str[i] == '_')
		i++;
	if (i == ft_strlen(str))
		return (0);
	i = 0;
	while (str[i] && (str[i] == '_' || ft_isdigit(str[i])))
		i++;
	if (i == ft_strlen(str))
		return (invalid_token(token, is_export, res));
	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (i == ft_strlen(str))
		return (0);
	return (invalid_token(token, is_export, res));
}

/*
**	Sub-function to free_var name & value of a var.
*/
void	free_var(t_var **var)
{
	free((*var)->name);
	free((*var)->value);
	free(*var);
}