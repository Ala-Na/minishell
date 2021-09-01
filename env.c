/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:39:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/01 22:49:58 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fonction retournant la valeur d'environnement correspondant a l'element donne
** (ex : Pour HOME, retourne "/home/user42").
** Fait le meme chose que la fonction getenv mais pour notre environnement ou des
** variables ont pu etre ajoutee. Il faut lui passer infos->env commme argument
** pour char **env.
** Retourne NULL si l'element n'est pas trouve.
*/
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

/*
** Fonction permettant de montrer les variables environnementales.
** A appeler lorsque le builtin "env" est entre en ligne de commande.
** Lui passer infos->env en argument.
*/
void	show_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write (1, "\n", 1);
		i++;
	}
}

/*
** Fonction pour libérer la mémoire allouée pour le tableau **env ainsi
** que chacun de ses élements. L'argument last représente le dernier élement
** du tableau ayant été alloué. S'il est égal à -1, tous les élements sont
** libérés.
*/
void	free_env(char **env, int last)
{
	int	i;

	i = 0;
	if (last > 0)
	{
		while (i < last)
			free(env[i++]);
	}
	else if (last == -1)
	{
		while (env[i])
			free(env[i++]);
	}
	free(env);
}

/*
** Fonction ayant pour visee de sauvegarder les variables d'environnement 
** dans
** une struture contenant les informations pour le minishell.
** Autre option : Sauvegarder env dans une liste chainee contenant le nom de
** l'element
** (ex : PATH), le contenu correspondant et next vers le prochain element.
** Avantage : Plus propre et evite realloc pour ajouter/supprimer une
** variable. 
** Inconvenient : Plus complique a mettre en place et plus long/lent a
** explorer.
** Des allocations sont realisees pour pouvoir free sans soucis.
** Retourne -1 si erreur, 0 sinon.
*/
int	save_env(t_infos *infos, char **env)
{
	int		i;
	int		y;
	char	**tmp_env;

	i = 0;
	while (env[i])
		i++;
	tmp_env = malloc(sizeof(*tmp_env) * (i + 1));
	if (!tmp_env)
		return (-1);
	i = 0;
	while (env[i])
	{
		y = 0;
		tmp_env[i] = ft_strdup(env[i]);
		if (!tmp_env[i])
		{
			free_env(tmp_env, i);
			return (-1);
		}
		i++;
	}
	tmp_env[i] = NULL;
	infos->env = tmp_env;
	return (0);
}
