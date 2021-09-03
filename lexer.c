/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:27:33 by anadege           #+#    #+#             */
/*   Updated: 2021/09/03 17:47:02 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Sub function of nbr_pipeline to modify some variables
*/
void	sub_nbr_pipeline(char c, int *prev_was_pipe, int *in_string,
		char *string_char)
{
	if (c != '|' && c != ' ' && c != '\t')
		*prev_was_pipe = 0;
	if (c == '"' || c == '\'')
	{
		if (*in_string == 0)
		{
			*in_string = 1;
			*string_char = c;
		}
		else if (c == *string_char)
			*in_string = 0;
	}
}

/*
** Check if there is pipeline and return the number of pipes found.
** Return -1 if there's any synthax error (pipe in the beginning of cmd, 
** pipe after another pipe, ...).
** DOES NOT CHECK IF A PIPELINE IS INCOMPLETE (ex "cat text | grep word |"
** should wait for a new command, it doesn't right now and return -1) AND IS NOT COMPATIBLE
** WITH BONUS ||
*/
int	nbr_pipeline(char *cmd)
{
	int		i;
	int		nbr_pipeline;
	int		prev_was_pipe;
	int		in_string;
	char	string_char;

	i = -1;
	prev_was_pipe = 1;
	nbr_pipeline = 0;
	in_string = 0;
	while (cmd[++i])
	{
		sub_nbr_pipeline(cmd[i], &prev_was_pipe, &in_string, &string_char);
		if (cmd[i] == '|' && in_string == 0)
		{
			if (prev_was_pipe == 1)
				return (-1);
			prev_was_pipe = 1;
			nbr_pipeline++;
		}
	}
	if (prev_was_pipe == 1)
		return (-1);
	return (nbr_pipeline);
}

int		get_pipeline_length(char *cmd)
{
	int		i;
	int		in_string;
	char	string_char;

	i = 0;
	in_string = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			if (in_string == 0)
			{
				in_string = 1;
				string_char = cmd[i];
			}
			else if (cmd[i] == string_char)
				in_string = 0;
		}
		if (in_string == 0 && cmd[i] == '|')
			break ;
		i++;
	}
	return (i);
}

char	**split_by_pipes(char	*cmd, int	nbr_pipes)
{
	char	**pipelines;
	int		i;
	int		j;
	int		sub_cmd_len;

	i = 0;
	pipelines = malloc(sizeof(*pipelines) * (nbr_pipes + 2));
	if (!pipelines)
		return (NULL);
	while (i < nbr_pipes + 1)
	{
		j = 0;
		sub_cmd_len = get_pipeline_length(cmd);
		pipelines[i] = malloc(sizeof(**pipelines) * (sub_cmd_len + 1));
		if (!pipelines[i])
			return (NULL);
		while (j < sub_cmd_len)
		{
			pipelines[i][j] = *cmd;
			cmd += 1;
			j++;
		}
		pipelines[i][j] = 0;
		cmd += 1;
		i++;
	}
	pipelines[i] = NULL;
	return (pipelines);
}

/*
** Verifier avant si cmd est NULL
*/
int		check_pipes(t_infos	*infos)
{
	char	**pipelines;
	int		nbr_pipes;

	nbr_pipes = nbr_pipeline(infos->curr_cmd);
	if (nbr_pipes <= 0)
		return (nbr_pipes); //-1 si erreur syntaxe, 0 si pas de pipe
	pipelines = split_by_pipes(infos->curr_cmd, nbr_pipes);
	int i = 0;
	while (pipelines[i])
		printf("%s\n", pipelines[i++]);
	if (pipelines == NULL)
		return (-2); // erreur lors split
	// stocker pipelines qq part dans infos
	return (nbr_pipes);
}

int main()
{
	t_infos infos;
	infos.curr_cmd = "truc \"| muche\" | truc";
	check_pipes(&infos);
}
